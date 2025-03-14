/******************************************************************************
  DRV_PLC_PHY PRIME Profile Layer

  Company:
    Microchip Technology Inc.

  File Name:
    drv_plc_phy_comm.c

  Summary:
    PLC Driver PRIME Profile Layer

  Description:
    This file contains the source code for the implementation of the PRIME
    Profile Layer.
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*
Copyright (C) 2023, Microchip Technology Inc., and its subsidiaries. All rights reserved.

The software and documentation is provided by microchip and its contributors
"as is" and any express, implied or statutory warranties, including, but not
limited to, the implied warranties of merchantability, fitness for a particular
purpose and non-infringement of third party intellectual property rights are
disclaimed to the fullest extent permitted by law. In no event shall microchip
or its contributors be liable for any direct, indirect, incidental, special,
exemplary, or consequential damages (including, but not limited to, procurement
of substitute goods or services; loss of use, data, or profits; or business
interruption) however caused and on any theory of liability, whether in contract,
strict liability, or tort (including negligence or otherwise) arising in any way
out of the use of the software and documentation, even if advised of the
possibility of such damage.

Except as expressly permitted hereunder and subject to the applicable license terms
for any third-party software incorporated in the software and any applicable open
source software license terms, no license or other rights, whether express or
implied, are granted under any patent or other intellectual property rights of
Microchip or any third party.
*/
//DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Include Files
// *****************************************************************************
// *****************************************************************************
#include <string.h>
#include "configuration.h"
#include "system/system.h"
#include "driver/plc/phy/drv_plc_phy.h"
#include "driver/plc/common/drv_plc_hal.h"
#include "driver/plc/common/drv_plc_boot.h"
#include "driver/plc/phy/drv_plc_phy_local_comm.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global data
// *****************************************************************************
// *****************************************************************************

/* This is the driver instance object array. */
static DRV_PLC_PHY_OBJ *gPlcPhyObj;

/* Buffer definition to communicate with PLC */
static CACHE_ALIGN uint8_t sDataInfo[CACHE_ALIGNED_SIZE_GET(PLC_STATUS_LENGTH)];
static CACHE_ALIGN uint8_t sDataTx[CACHE_ALIGNED_SIZE_GET((PLC_TX_PAR_SIZE + PLC_DATA_PKT_SIZE))];
static CACHE_ALIGN uint8_t sDataRxPar[CACHE_ALIGNED_SIZE_GET(PLC_RX_PAR_SIZE)];
static CACHE_ALIGN uint8_t sDataRxDat[CACHE_ALIGNED_SIZE_GET(PLC_DATA_PKT_SIZE)];
static CACHE_ALIGN uint8_t sDataTxCfm[2][CACHE_ALIGNED_SIZE_GET(PLC_CMF_PKT_SIZE)];
static CACHE_ALIGN uint8_t sDataReg[CACHE_ALIGNED_SIZE_GET(PLC_REG_PKT_SIZE)];

// *****************************************************************************
// *****************************************************************************
// Section: File scope functions
// *****************************************************************************
// *****************************************************************************

static uint32_t lDRV_PLC_PHY_COMM_GetPibBaseAddress(DRV_PLC_PHY_ID id)
{
    uint32_t addr;

    addr = 0;

    if (((uint16_t)id & DRV_PLC_PHY_REG_ADC_MASK) != 0U)
    {
        addr = (uint32_t)DRV_PLC_PHY_REG_ADC_BASE;
    }
    else if (((uint16_t)id & DRV_PLC_PHY_REG_DAC_MASK) != 0U)
    {
        addr = (uint32_t)DRV_PLC_PHY_REG_DAC_BASE;
    }
    else if (((uint16_t)id & DRV_PLC_PHY_FUSES_MASK) != 0U)
    {
        addr = (uint32_t)DRV_PLC_PHY_FUSES_BASE;
    }
    else if ((((uint16_t)id & DRV_PLC_PHY_REG_MASK) != 0U) && (id < PLC_ID_END_ID))
    {
        addr = (uint32_t)DRV_PLC_PHY_REG_BASE;
    }
    else
    {
        addr = 0;
    }

    return addr;
}

static uint16_t lDRV_PLC_PHY_COMM_GetDelayUs(DRV_PLC_PHY_ID id)
{
    uint16_t delay = 50;

    if ((((uint16_t)id & DRV_PLC_PHY_REG_MASK) != 0U) && (id < PLC_ID_END_ID))
    {
        switch (id)
        {
            case PLC_ID_CHANNEL_CFG:
            delay = 5500;
            break;

            case PLC_ID_PREDIST_COEF_TABLE_HI:
            case PLC_ID_PREDIST_COEF_TABLE_LO:
            case PLC_ID_PREDIST_COEF_TABLE_HI_2:
            case PLC_ID_PREDIST_COEF_TABLE_LO_2:
            delay = 1000;
            break;

            case PLC_ID_PREDIST_COEF_TABLE_VLO:
            case PLC_ID_PREDIST_COEF_TABLE_VLO_2:
            delay = 2000;
            break;

            default:
            delay = 50;
            break;
        }
    }

    return delay;
}

static size_t lDRV_PLC_PHY_COMM_TxStringify(DRV_PLC_PHY_TRANSMISSION_OBJ *pSrc)
{
    uint8_t *pDst;
    ptrdiff_t size;
    uint8_t csma;

    pDst = sDataTx;

    *pDst++ = (uint8_t)pSrc->timeIni;
    *pDst++ = (uint8_t)(pSrc->timeIni >> 8);
    *pDst++ = (uint8_t)(pSrc->timeIni >> 16);
    *pDst++ = (uint8_t)(pSrc->timeIni >> 24);
    *pDst++ = (uint8_t)pSrc->dataLength;
    *pDst++ = (uint8_t)(pSrc->dataLength >> 8);
    *pDst++ = pSrc->attenuation;
    *pDst++ = (uint8_t)pSrc->scheme;
    csma = pSrc->csma.disableRx | pSrc->csma.senseCount << 1 | pSrc->csma.senseDelayMs << 4;
    *pDst++ = csma;
    *pDst++ = (uint8_t)pSrc->frameType;
    *pDst++ = pSrc->mode;
    *pDst++ = (uint8_t)pSrc->bufferId;

    if (pSrc->dataLength > PLC_DATA_PKT_SIZE)
    {
        pSrc->dataLength = PLC_DATA_PKT_SIZE;
    }

    (void) memcpy(pDst, pSrc->pTransmitData, pSrc->dataLength);
    pDst += pSrc->dataLength;

    size = pDst - sDataTx;

    return (size_t)size;

}

static void lDRV_PLC_PHY_COMM_TxCfmEvent(DRV_PLC_PHY_TRANSMISSION_CFM_OBJ *pCfmObj, uint8_t id)
{
    uint8_t *pSrc;

    pSrc = sDataTxCfm[id];

    pCfmObj->rmsCalc = (uint32_t)*pSrc++;
    pCfmObj->rmsCalc += (uint32_t)*pSrc++ << 8;
    pCfmObj->rmsCalc += (uint32_t)*pSrc++ << 16;
    pCfmObj->rmsCalc += (uint32_t)*pSrc++ << 24;

    pCfmObj->timeIni = (uint32_t)*pSrc++;
    pCfmObj->timeIni += (uint32_t)*pSrc++ << 8;
    pCfmObj->timeIni += (uint32_t)*pSrc++ << 16;
    pCfmObj->timeIni += (uint32_t)*pSrc++ << 24;

    pCfmObj->frameType = (DRV_PLC_PHY_FRAME_TYPE)*pSrc++;
    pCfmObj->result = (DRV_PLC_PHY_TX_RESULT)*pSrc++;
    pCfmObj->bufferId = (DRV_PLC_PHY_BUFFER_ID)*pSrc;
}

static void lDRV_PLC_PHY_COMM_RxEvent(DRV_PLC_PHY_RECEPTION_OBJ *pRxObj)
{
    uint8_t *pSrc;

    pSrc = sDataRxPar;

    /* Parse parameters of reception event */
    pRxObj->evmHeaderAcum = (uint32_t)*pSrc++;
    pRxObj->evmHeaderAcum += (uint32_t)*pSrc++ << 8;
    pRxObj->evmHeaderAcum += (uint32_t)*pSrc++ << 16;
    pRxObj->evmHeaderAcum += (uint32_t)*pSrc++ << 24;
    pRxObj->evmPayloadAcum = (uint32_t)*pSrc++;
    pRxObj->evmPayloadAcum += (uint32_t)*pSrc++ << 8;
    pRxObj->evmPayloadAcum += (uint32_t)*pSrc++ << 16;
    pRxObj->evmPayloadAcum += (uint32_t)*pSrc++ << 24;
    pRxObj->timeIni = (uint32_t)*pSrc++;
    pRxObj->timeIni += (uint32_t)*pSrc++ << 8;
    pRxObj->timeIni += (uint32_t)*pSrc++ << 16;
    pRxObj->timeIni += (uint32_t)*pSrc++ << 24;
    pRxObj->evmHeader = (uint16_t)*pSrc++;
    pRxObj->evmHeader += (uint16_t)*pSrc++ << 8;
    pRxObj->evmPayload = (uint16_t)*pSrc++;
    pRxObj->evmPayload += (uint16_t)*pSrc++ << 8;
    pRxObj->dataLength = (uint16_t)*pSrc++;
    pRxObj->dataLength += (uint16_t)*pSrc++ << 8;
    pRxObj->scheme = (DRV_PLC_PHY_SCH)*pSrc++;
    pRxObj->frameType = (DRV_PLC_PHY_FRAME_TYPE)*pSrc++;
    pRxObj->headerType = (DRV_PLC_PHY_HEADER)*pSrc++;
    pRxObj->rssiAvg = *pSrc++;
    pRxObj->cinrAvg = *pSrc++;
    pRxObj->cinrMin = *pSrc++;
    pRxObj->berSoftAvg = *pSrc++;
    pRxObj->berSoftMax = *pSrc++;
    pRxObj->narBandPercent = *pSrc++;
    pRxObj->impNoisePercent = *pSrc++;

    if (pRxObj->dataLength > PLC_DATA_PKT_SIZE)
    {
        pRxObj->dataLength = PLC_DATA_PKT_SIZE;
    }

    /* Set data content pointer */
    pRxObj->pReceivedData = sDataRxDat;
}

static bool lDRV_PLC_PHY_COMM_CheckComm(DRV_PLC_HAL_INFO *info)
{
    if (info->key == DRV_PLC_HAL_KEY_CORTEX)
    {
        /* Communication correct */
        return true;
    }
    else if (info->key == DRV_PLC_HAL_KEY_BOOT)
    {
        /* Communication Error : Check reset value */
        if ((info->flags & DRV_PLC_HAL_FLAG_RST_WDOG) != 0U)
        {
            /* Debugger is connected */
            DRV_PLC_BOOT_Restart(DRV_PLC_BOOT_RESTART_SOFT);
            if (gPlcPhyObj->exceptionCallback != NULL)
            {
                gPlcPhyObj->exceptionCallback(DRV_PLC_PHY_EXCEPTION_DEBUG, gPlcPhyObj->contextExc);
            }
        }
        else
        {
            /* PLC needs boot process to upload firmware */
            DRV_PLC_BOOT_Restart(DRV_PLC_BOOT_RESTART_HARD);
            if (gPlcPhyObj->exceptionCallback != NULL)
            {
                gPlcPhyObj->exceptionCallback(DRV_PLC_PHY_EXCEPTION_RESET, gPlcPhyObj->contextExc);
            }

            /* Update Driver Status */
            gPlcPhyObj->status = SYS_STATUS_BUSY;
        }

        /* Check if there is any tx_cfm pending to be reported */
        if ((gPlcPhyObj->state[0] == DRV_PLC_PHY_STATE_WAITING_TX_CFM) ||
                (gPlcPhyObj->state[1] == DRV_PLC_PHY_STATE_WAITING_TX_CFM))
        {
            gPlcPhyObj->evResetTxCfm = true;
        }

        return true;
    }
    else
    {
        /* PLC needs boot process to upload firmware */
        DRV_PLC_BOOT_Restart(DRV_PLC_BOOT_RESTART_HARD);
        if (gPlcPhyObj->exceptionCallback != NULL)
        {
            gPlcPhyObj->exceptionCallback(DRV_PLC_PHY_EXCEPTION_UNEXPECTED_KEY, gPlcPhyObj->contextExc);
        }

        /* Update Driver Status */
        gPlcPhyObj->status = SYS_STATUS_ERROR;

        return false;
    }
}

static void lDRV_PLC_PHY_COMM_SpiWriteCmd(DRV_PLC_PHY_MEM_ID id, uint8_t *pData, uint16_t length)
{
    DRV_PLC_HAL_CMD halCmd;
    DRV_PLC_HAL_INFO halInfo;
    uint8_t failures = 0;

    /* Disable external interrupt from PLC */
    gPlcPhyObj->plcHal->enableExtInt(false);

    halCmd.cmd = DRV_PLC_HAL_CMD_WR;
    halCmd.memId = (uint16_t)id;
    halCmd.length = length;
    halCmd.pData = pData;

    gPlcPhyObj->plcHal->sendWrRdCmd(&halCmd, &halInfo);

    /* Check communication integrity */
    while(!lDRV_PLC_PHY_COMM_CheckComm(&halInfo))
    {
        failures++;
        if (failures == 2U) {
            if (gPlcPhyObj->exceptionCallback != NULL)
            {
                gPlcPhyObj->exceptionCallback(DRV_PLC_PHY_EXCEPTION_CRITICAL_ERROR, gPlcPhyObj->contextExc);
            }
            break;
        }
        gPlcPhyObj->plcHal->reset();
        gPlcPhyObj->plcHal->sendWrRdCmd(&halCmd, &halInfo);
    }

    /* Enable external interrupt from PLC */
    gPlcPhyObj->plcHal->enableExtInt(true);
}

static void lDRV_PLC_PHY_COMM_SpiReadCmd(DRV_PLC_PHY_MEM_ID id, uint8_t *pData, uint16_t length)
{
    DRV_PLC_HAL_CMD halCmd;
    DRV_PLC_HAL_INFO halInfo;
    uint8_t failures = 0;

    /* Disable external interrupt from PLC */
    gPlcPhyObj->plcHal->enableExtInt(false);

    halCmd.cmd = DRV_PLC_HAL_CMD_RD;
    halCmd.memId = (uint16_t)id;
    halCmd.length = length;
    halCmd.pData = pData;

    gPlcPhyObj->plcHal->sendWrRdCmd(&halCmd, &halInfo);

    /* Check communication integrity */
    while(!lDRV_PLC_PHY_COMM_CheckComm(&halInfo))
    {
        failures++;
        if (failures == 2U) {
            if (gPlcPhyObj->exceptionCallback != NULL)
            {
                gPlcPhyObj->exceptionCallback(DRV_PLC_PHY_EXCEPTION_CRITICAL_ERROR, gPlcPhyObj->contextExc);
            }
            break;
        }
        gPlcPhyObj->plcHal->reset();
        gPlcPhyObj->plcHal->sendWrRdCmd(&halCmd, &halInfo);
    }

    /* Enable external interrupt from PLC */
    gPlcPhyObj->plcHal->enableExtInt(true);
}

static void lDRV_PLC_PHY_COMM_GetEventsInfo(DRV_PLC_PHY_EVENTS_OBJ *eventsObj)
{
    uint8_t *pData;
    DRV_PLC_HAL_CMD halCmd;
    DRV_PLC_HAL_INFO halInfo;
    uint8_t failures = 0;

    pData = sDataInfo;

    halCmd.cmd = DRV_PLC_HAL_CMD_RD;
    halCmd.memId = (uint16_t)STATUS_ID;
    halCmd.length = PLC_STATUS_LENGTH;
    halCmd.pData = pData;

    gPlcPhyObj->plcHal->sendWrRdCmd(&halCmd, &halInfo);

    /* Check communication integrity */
    while(!lDRV_PLC_PHY_COMM_CheckComm(&halInfo))
    {
        failures++;
        if (failures == 2U) {
            if (gPlcPhyObj->exceptionCallback != NULL)
            {
                gPlcPhyObj->exceptionCallback(DRV_PLC_PHY_EXCEPTION_CRITICAL_ERROR, gPlcPhyObj->contextExc);
            }
            break;
        }
        gPlcPhyObj->plcHal->sendWrRdCmd(&halCmd, &halInfo);
    }

    /* Extract Events information */
    eventsObj->evCfm[0] = ((halInfo.flags & DRV_PLC_PHY_EV_FLAG_TX0_CFM_MASK) != 0U);
    eventsObj->evCfm[1] = ((halInfo.flags & DRV_PLC_PHY_EV_FLAG_TX1_CFM_MASK) != 0U);
    eventsObj->evRxDat = ((halInfo.flags & DRV_PLC_PHY_EV_FLAG_RX_DAT_MASK) != 0U);
    eventsObj->evRxPar = ((halInfo.flags & DRV_PLC_PHY_EV_FLAG_RX_PAR_MASK) != 0U);
    eventsObj->evReg = ((halInfo.flags & DRV_PLC_PHY_EV_FLAG_REG_MASK) != 0U);

    /* Extract Timer info */
    eventsObj->timerRef = ((uint32_t)*pData++);
    eventsObj->timerRef += ((uint32_t)*pData++) << 8;
    eventsObj->timerRef += ((uint32_t)*pData++) << 16;
    eventsObj->timerRef += ((uint32_t)*pData++) << 24;

    /* Extract Lengths info */
    eventsObj->rcvDataLength = ((uint16_t)*pData++);
    eventsObj->rcvDataLength += ((uint16_t)*pData++) << 8;
    eventsObj->regRspLength = ((uint16_t)*pData++);
    eventsObj->regRspLength += ((uint16_t)*pData++) << 8;
}

// *****************************************************************************
// *****************************************************************************
// Section: DRV_PLC_PHY Common Interface Implementation
// *****************************************************************************
// *****************************************************************************
void DRV_PLC_PHY_Init(DRV_PLC_PHY_OBJ *plcPhyObj)
{
    gPlcPhyObj = plcPhyObj;

    /* Clear information about PLC events */
    gPlcPhyObj->evTxCfm[0] = false;
    gPlcPhyObj->evTxCfm[1] = false;
    gPlcPhyObj->evRxPar = false;
    gPlcPhyObj->evRxDat = false;
    gPlcPhyObj->evRegRspLength = 0;
    gPlcPhyObj->evResetTxCfm = false;

    /* Enable external interrupt from PLC */
    gPlcPhyObj->plcHal->enableExtInt(true);
}

void DRV_PLC_PHY_Task(void)
{
    if (gPlcPhyObj->sleep)
    {
        return;
    }

    /* Check event flags */
    for (uint8_t idx = 0; idx < 2U; idx++)
    {
        if ((gPlcPhyObj->evTxCfm[idx]) || (gPlcPhyObj->evResetTxCfm))
        {
            DRV_PLC_PHY_TRANSMISSION_CFM_OBJ cfmObj;

            /* Reset event flag */
            gPlcPhyObj->evTxCfm[idx] = false;

            if (gPlcPhyObj->evResetTxCfm)
            {
                gPlcPhyObj->evResetTxCfm = false;
                gPlcPhyObj->state[idx] = DRV_PLC_PHY_STATE_IDLE;

                cfmObj.bufferId = (DRV_PLC_PHY_BUFFER_ID)idx;
                cfmObj.rmsCalc = 0;
                cfmObj.timeIni = 0;
                cfmObj.result = DRV_PLC_PHY_TX_RESULT_NO_TX;
            } else {
                lDRV_PLC_PHY_COMM_TxCfmEvent(&cfmObj, idx);
            }

            if (gPlcPhyObj->txCfmCallback != NULL)
            {
                /* Report to upper layer */
                gPlcPhyObj->txCfmCallback(&cfmObj, gPlcPhyObj->contextCfm);
            }
        }
    }

    if (gPlcPhyObj->evRxPar && gPlcPhyObj->evRxDat)
    {
        DRV_PLC_PHY_RECEPTION_OBJ rxObj;

        /* Reset event flags */
        gPlcPhyObj->evRxPar = false;
        gPlcPhyObj->evRxDat = false;

        lDRV_PLC_PHY_COMM_RxEvent(&rxObj);
        if (gPlcPhyObj->dataIndCallback != NULL)
        {
            /* Report to upper layer */
            gPlcPhyObj->dataIndCallback(&rxObj, gPlcPhyObj->contextInd);
        }
    }
}

void DRV_PLC_PHY_TxRequest(const DRV_HANDLE handle, DRV_PLC_PHY_TRANSMISSION_OBJ *transmitObj)
{
    DRV_PLC_PHY_TRANSMISSION_CFM_OBJ cfmObj;
    uint8_t bufIdx = (uint8_t) transmitObj->bufferId;

    if (bufIdx > (uint8_t)(TX_BUFFER_1))
    {
        /* Invalid buffer. */
        if (gPlcPhyObj->txCfmCallback != NULL)
        {
            cfmObj.rmsCalc = 0;
            cfmObj.timeIni = 0;
            cfmObj.result = DRV_PLC_PHY_TX_RESULT_INV_BUFFER;
            /* Report to upper layer */
            gPlcPhyObj->txCfmCallback(&cfmObj, gPlcPhyObj->contextCfm);
        }

        return;
    }

    if (gPlcPhyObj->sleep)
    {
        /* Do not transmit in SLeep Mode. */
        if (gPlcPhyObj->txCfmCallback != NULL)
        {
            cfmObj.rmsCalc = 0;
            cfmObj.timeIni = 0;
            cfmObj.result = DRV_PLC_PHY_TX_RESULT_NO_TX;
            /* Report to upper layer */
            gPlcPhyObj->txCfmCallback(&cfmObj, gPlcPhyObj->contextCfm);
        }

        return;
    }

    if (gPlcPhyObj->plcHal->getThermalMonitor())
    {
        /* Check thermal warning (>110ºC). Do not transmit and report High Temperature warning. */
        if (gPlcPhyObj->txCfmCallback != NULL)
        {
            cfmObj.rmsCalc = 0;
            cfmObj.timeIni = 0;
            cfmObj.result = DRV_PLC_PHY_TX_RESULT_HIGH_TEMP_110;
            /* Report to upper layer */
            gPlcPhyObj->txCfmCallback(&cfmObj, gPlcPhyObj->contextCfm);
        }

        return;
    }

    if((handle != DRV_HANDLE_INVALID) && (handle == 0U) &&
            ((gPlcPhyObj->state[bufIdx] == DRV_PLC_PHY_STATE_IDLE) || ((transmitObj->mode & TX_MODE_CANCEL) != 0U)))
    {
        size_t size;

        size = lDRV_PLC_PHY_COMM_TxStringify(transmitObj);

        if (size > 0U)
        {
            if ((transmitObj->mode & TX_MODE_CANCEL) == 0U)
            {
                /* Update PLC state: transmitting */
                gPlcPhyObj->state[bufIdx] = DRV_PLC_PHY_STATE_TX;
            }

            /* Send TX message */
            if (bufIdx == (uint8_t)(TX_BUFFER_0))
            {
                lDRV_PLC_PHY_COMM_SpiWriteCmd(TX0_PAR_ID, sDataTx, (uint16_t)size);
            }
            else
            {
                lDRV_PLC_PHY_COMM_SpiWriteCmd(TX1_PAR_ID, sDataTx, (uint16_t)size);
            }

            /* Update PLC state: waiting confirmation */
            gPlcPhyObj->state[bufIdx] = DRV_PLC_PHY_STATE_WAITING_TX_CFM;

            /* Time guard */
            gPlcPhyObj->plcHal->delay(20);
        }
        else
        {
            /* Notify DRV_PLC_PHY_TX_RESULT_INV_LENGTH */
            if (gPlcPhyObj->txCfmCallback != NULL)
            {
                cfmObj.rmsCalc = 0;
                cfmObj.timeIni = 0;
                cfmObj.result = DRV_PLC_PHY_TX_RESULT_INV_LENGTH;
                /* Report to upper layer */
                gPlcPhyObj->txCfmCallback(&cfmObj, gPlcPhyObj->contextCfm);
            }
        }
    }
    else
    {
        if (gPlcPhyObj->txCfmCallback != NULL)
        {
            /* Notify DRV_PLC_PHY_TX_RESULT_NO_TX */
            cfmObj.rmsCalc = 0;
            cfmObj.timeIni = 0;
            cfmObj.result = DRV_PLC_PHY_TX_RESULT_NO_TX;
            /* Report to upper layer */
            gPlcPhyObj->txCfmCallback(&cfmObj, gPlcPhyObj->contextCfm);
        }
    }
}

bool DRV_PLC_PHY_PIBGet(const DRV_HANDLE handle, DRV_PLC_PHY_PIB_OBJ *pibObj)
{
    if((handle != DRV_HANDLE_INVALID) && (handle == 0U))
    {
        if (gPlcPhyObj->sleep)
        {
            return false;
        }

        if (pibObj->id == PLC_ID_TIME_REF_ID)
        {
            /* Send PIB information request */
            lDRV_PLC_PHY_COMM_SpiReadCmd(STATUS_ID, pibObj->pData, pibObj->length);
            return true;
        }
        else if (((uint16_t)pibObj->id & DRV_PLC_PHY_REG_ID_MASK) != 0U)
        {
            uint8_t *pDst;
            uint32_t address;
            uint16_t offset;
            uint16_t secureCnt;
            uint16_t cmdLength;

            offset = (uint16_t)pibObj->id & DRV_PLC_PHY_REG_OFFSET_MASK;

            /* Get address offset */
            address = lDRV_PLC_PHY_COMM_GetPibBaseAddress(pibObj->id);
            if (address == 0U)
            {
                return false;
            }
            address += offset;

            /* Set CMD and length */
            cmdLength = (uint16_t)DRV_PLC_PHY_CMD_READ | (pibObj->length & DRV_PLC_PHY_REG_LEN_MASK);

            /* Build command */
            pDst = sDataReg;

            *pDst++ = (uint8_t)(address >> 24);
            *pDst++ = (uint8_t)(address >> 16);
            *pDst++ = (uint8_t)(address >> 8);
            *pDst++ = (uint8_t)(address);
            *pDst++ = (uint8_t)(cmdLength >> 8);
            *pDst++ = (uint8_t)(cmdLength);

            /* Send PIB information request */
            lDRV_PLC_PHY_COMM_SpiWriteCmd(REG_INFO_ID, sDataReg, 8U);

            /* Wait to the response : Check length of the register response */
            secureCnt = 0xFFFF;
            while (gPlcPhyObj->evRegRspLength == 0U)
            {
                if ((secureCnt--) == 0U)
                {
                    /* Didn't came the expected response */
                    return false;
                }
            }

            /* copy Register info in data pointer */
            (void) memcpy(pibObj->pData, sDataReg, pibObj->length);
            /* Reset length of the register response */
            gPlcPhyObj->evRegRspLength = 0;

            return true;
        }
        else
        {
            uint32_t value;
            bool result = true;

            /* Get HOST information */
            switch(pibObj->id)
            {
                case PLC_ID_HOST_DESCRIPTION_ID:
                {
                    const char *hostDesc = DRV_PLC_PHY_HOST_DESC;
                    (void) memcpy((void *)pibObj->pData, (const void *)hostDesc, strlen(DRV_PLC_PHY_HOST_DESC));
                    break;
                }

                case PLC_ID_HOST_MODEL_ID:
                    value = DRV_PLC_PHY_HOST_MODEL;
                    pibObj->pData[0] = (uint8_t)value;
                    pibObj->pData[1] = (uint8_t)(value >> 8);
                    break;

                case PLC_ID_HOST_PHY_ID:
                    value = DRV_PLC_PHY_HOST_PHY;
                    pibObj->pData[0] = (uint8_t)value;
                    pibObj->pData[1] = (uint8_t)(value >> 8);
                    pibObj->pData[2] = (uint8_t)(value >> 16);
                    pibObj->pData[3] = (uint8_t)(value >> 24);
                    break;

                case PLC_ID_HOST_PRODUCT_ID:
                    value = DRV_PLC_PHY_HOST_PRODUCT;
                    pibObj->pData[0] = (uint8_t)value;
                    pibObj->pData[1] = (uint8_t)(value >> 8);
                    break;

                case PLC_ID_HOST_VERSION_ID:
                    value = DRV_PLC_PHY_HOST_VERSION;
                    pibObj->pData[0] = (uint8_t)value;
                    pibObj->pData[1] = (uint8_t)(value >> 8);
                    pibObj->pData[2] = (uint8_t)(value >> 16);
                    pibObj->pData[3] = (uint8_t)(value >> 24);
                    break;

                case PLC_ID_HOST_BAND_ID:
                    value = DRV_PLC_PHY_HOST_BAND;
                    pibObj->pData[0] = (uint8_t)value;
                    break;

                default:
                    result = false;
                    break;
            }

            return result;
        }
    }
    else
    {
        return false;
    }
}

bool DRV_PLC_PHY_PIBSet(const DRV_HANDLE handle, DRV_PLC_PHY_PIB_OBJ *pibObj)
{
    if((handle != DRV_HANDLE_INVALID) && (handle == 0U))
    {
        if (gPlcPhyObj->sleep)
        {
            return false;
        }

        if (((uint16_t)pibObj->id & DRV_PLC_PHY_REG_ID_MASK) != 0U)
        {
            uint8_t *pDst;
            uint8_t *pSrc;
            uint32_t address;
            uint16_t offset;
            uint16_t delay;
            uint16_t cmdLength;

            offset = (uint16_t)pibObj->id & DRV_PLC_PHY_REG_OFFSET_MASK;

            /* Get base address */
            address = lDRV_PLC_PHY_COMM_GetPibBaseAddress(pibObj->id);
            if (address == 0U)
            {
                return false;
            }
            address += offset;

            /* Set CMD and length */
            cmdLength = (uint16_t)DRV_PLC_PHY_CMD_WRITE | (pibObj->length & DRV_PLC_PHY_REG_LEN_MASK);

            /* Build command */
            pDst = sDataReg;

            *pDst++ = (uint8_t)(address >> 24);
            *pDst++ = (uint8_t)(address >> 16);
            *pDst++ = (uint8_t)(address >> 8);
            *pDst++ = (uint8_t)(address);
            *pDst++ = (uint8_t)(cmdLength >> 8);
            *pDst++ = (uint8_t)(cmdLength);

            pSrc = pibObj->pData;
            if (pibObj->length == 4U)
            {
                *pDst++ = *pSrc++;
                *pDst++ = *pSrc++;
                *pDst++ = *pSrc++;
                *pDst++ = *pSrc++;
            }
            else if (pibObj->length == 2U)
            {
                *pDst++ = *pSrc++;
                *pDst++ = *pSrc++;
            }
            else
            {
                (void) memcpy(pDst, pSrc, pibObj->length);
            }

            /* Send PIB information request */
            lDRV_PLC_PHY_COMM_SpiWriteCmd(REG_INFO_ID, sDataReg, 6U + pibObj->length);

            /* Guard delay to ensure writing operation completion. */
            delay = lDRV_PLC_PHY_COMM_GetDelayUs(pibObj->id);
            gPlcPhyObj->plcHal->delay(delay);

            return true;
        }
    }

    return false;
}

void DRV_PLC_PHY_ExternalInterruptHandler(PIO_PIN pin, uintptr_t context)
{
    /* Avoid warning */
    (void)context;

    if ((gPlcPhyObj != NULL) && (pin == (PIO_PIN)gPlcPhyObj->plcHal->plcPlib->extIntPin))
    {
        DRV_PLC_PHY_EVENTS_OBJ evObj;

        /* Time guard */
        gPlcPhyObj->plcHal->delay(20);

        /* Get PLC events information */
        lDRV_PLC_PHY_COMM_GetEventsInfo(&evObj);

        /* Check confirmation of the transmission event */
        if (evObj.evCfm[0])
        {
            lDRV_PLC_PHY_COMM_SpiReadCmd(TX0_CFM_ID, sDataTxCfm[0], (uint16_t)PLC_CMF_PKT_SIZE);
            /* update event flag */
            gPlcPhyObj->evTxCfm[0] = true;
            /* Update PLC state: idle */
            gPlcPhyObj->state[0] = DRV_PLC_PHY_STATE_IDLE;
        }

        if (evObj.evCfm[1])
        {
            lDRV_PLC_PHY_COMM_SpiReadCmd(TX1_CFM_ID, sDataTxCfm[1], PLC_CMF_PKT_SIZE);
            /* update event flag */
            gPlcPhyObj->evTxCfm[1] = true;
            /* Update PLC state: idle */
            gPlcPhyObj->state[1] = DRV_PLC_PHY_STATE_IDLE;
        }

        /* Check received new data event (First event in RX) */
        if (evObj.evRxDat)
        {
            lDRV_PLC_PHY_COMM_SpiReadCmd(RX_DAT_ID, sDataRxDat, evObj.rcvDataLength);
            /* update event flag */
            gPlcPhyObj->evRxDat = true;
        }

        /* Check received new parameters event (Second event in RX) */
        if (evObj.evRxPar)
        {
            lDRV_PLC_PHY_COMM_SpiReadCmd(RX_PAR_ID, sDataRxPar, (uint16_t)PLC_RX_PAR_SIZE - 4U);
            /* update event flag */
            gPlcPhyObj->evRxPar = true;
        }

        /* Check register info event */
        if (evObj.evReg)
        {
            lDRV_PLC_PHY_COMM_SpiReadCmd(REG_INFO_ID, sDataReg, evObj.regRspLength);
            /* update event flag */
            gPlcPhyObj->evRegRspLength = evObj.regRspLength;
        }

        /* Time guard */
        gPlcPhyObj->plcHal->delay(20);
    }

    /* PORT Interrupt Status Clear */
    ((pio_registers_t*)DRV_PLC_EXT_INT_PIO_PORT)->PIO_ISR;
}
