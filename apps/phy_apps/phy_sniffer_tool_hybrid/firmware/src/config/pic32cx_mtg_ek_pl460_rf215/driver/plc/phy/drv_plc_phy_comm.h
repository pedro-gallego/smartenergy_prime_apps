/*******************************************************************************
  PLC Driver PRIME Definitions Header File

  Company:
    Microchip Technology Inc.

  File Name:
    drv_plc_phy_comm.h

  Summary:
    PLC Driver PRIME Definitions Header File.

  Description:
    This file provides implementation-specific definitions for the PLC
    driver's system PRIME interface.
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

#ifndef DRV_PLC_PHY_COMM_H
#define DRV_PLC_PHY_COMM_H

// *****************************************************************************
// *****************************************************************************
// Section: File includes
// *****************************************************************************
// *****************************************************************************

#include <device.h>


// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: External Data
// *****************************************************************************
// *****************************************************************************

/* PLC Binary file addressing */
extern uint8_t plc_phy_bin_start;
extern uint8_t plc_phy_bin_end;

// *****************************************************************************
// *****************************************************************************
// Section: Macro Definitions
// *****************************************************************************
// *****************************************************************************

/* TX Mode: Absolute transmission */
#define TX_MODE_ABSOLUTE                       (0U)
/* TX Mode: Delayed transmission */
#define TX_MODE_RELATIVE                       (1U << 0)
/* TX Mode: Cancel transmission */
#define TX_MODE_CANCEL                         (1U << 1)
/* TX Mode: SYNCP Continuous transmission */
#define TX_MODE_PREAMBLE_CONTINUOUS            (1U << 2)
/* TX Mode: Symbols Continuous transmission */
#define TX_MODE_SYMBOLS_CONTINUOUS             (1U << 3)

/* Impedance Configuration: High mode */
#define HI_STATE                               0x00U
/* Impedance Configuration: Low mode */
#define LOW_STATE                              0x01U
/* Impedance Configuration: Very Low mode */
#define VLO_STATE                              0x02U

/* Signal Capture Mode Bit Mask */
/* MISRA C-2012 deviation block start */
/* MISRA C-2012 Rule 5.4 deviated 22 times. Deviation record ID - H3_MISRAC_2012_R_5_4_DR_1 */
#define DRV_PLC_SIGNAL_CAPTURE_CHANNEL_SHIFT 0U
#define DRV_PLC_SIGNAL_CAPTURE_CHANNEL (0xFU << DRV_PLC_SIGNAL_CAPTURE_CHANNEL_SHIFT)
#define DRV_PLC_SIGNAL_CAPTURE_SIGNAL_SHIFT 4U
#define DRV_PLC_SIGNAL_CAPTURE_SIGNAL_MODE (0x1U << DRV_PLC_SIGNAL_CAPTURE_SIGNAL_SHIFT)
#define DRV_PLC_SIGNAL_CAPTURE_SIGNAL_MODE_LOW (0x0U << DRV_PLC_SIGNAL_CAPTURE_SIGNAL_SHIFT)  /* Signal mode for low signal level : Only valid in SIGNAL_CAPTURE_BAND_MODE_FCC mode */
#define DRV_PLC_SIGNAL_CAPTURE_SIGNAL_MODE_HIGH (0x1U << DRV_PLC_SIGNAL_CAPTURE_SIGNAL_SHIFT) /* Signal mode for high signal level : Only valid in SIGNAL_CAPTURE_BAND_MODE_FCC mode */
#define DRV_PLC_SIGNAL_CAPTURE_BAND_MODE_SHIFT 5
#define DRV_PLC_SIGNAL_CAPTURE_BAND_MODE (0x1U << DRV_PLC_SIGNAL_CAPTURE_BAND_MODE_SHIFT)
#define DRV_PLC_SIGNAL_CAPTURE_BAND_MODE_CHN (0x0U << DRV_PLC_SIGNAL_CAPTURE_BAND_MODE_SHIFT) /* Frequency in Channel Mode */
#define DRV_PLC_SIGNAL_CAPTURE_BAND_MODE_FCC (0x1U << DRV_PLC_SIGNAL_CAPTURE_BAND_MODE_SHIFT) /* Frequency in all FCC band Mode */
#define DRV_PLC_SIGNAL_CAPTURE_TIME_MODE_SHIFT 6U
#define DRV_PLC_SIGNAL_CAPTURE_TIME_MODE (0x1U << DRV_PLC_SIGNAL_CAPTURE_TIME_MODE_SHIFT)
#define DRV_PLC_SIGNAL_CAPTURE_TIME_MODE_ABS (0x0U << DRV_PLC_SIGNAL_CAPTURE_TIME_MODE_SHIFT) /* Time in Absolute Mode */
#define DRV_PLC_SIGNAL_CAPTURE_TIME_MODE_REL (0x1U << DRV_PLC_SIGNAL_CAPTURE_TIME_MODE_SHIFT) /* Time in Relative Mode */
#define DRV_PLC_SIGNAL_CAPTURE_CHN_1 0x01U
#define DRV_PLC_SIGNAL_CAPTURE_CHN_2 0x02U
#define DRV_PLC_SIGNAL_CAPTURE_CHN_3 0x03U
#define DRV_PLC_SIGNAL_CAPTURE_CHN_4 0x04U
#define DRV_PLC_SIGNAL_CAPTURE_CHN_5 0x05U
#define DRV_PLC_SIGNAL_CAPTURE_CHN_6 0x06U
#define DRV_PLC_SIGNAL_CAPTURE_CHN_7 0x07U
#define DRV_PLC_SIGNAL_CAPTURE_CHN_8 0x08U
    /* MISRA C-2012 deviation block end */

#define SIGNAL_CAPTURE_FRAG_SIZE                  255U

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* PRIME PHY Information Base (PIBs)

  Summary:
    The list of all available PIB attributes.

  Description:
    The PRIME PHY layer supports all the mandatory attributes of the PHY
    Information Base (PIB) defined in the PRIME specification. In addition,
    Microchip has added several proprietary PIB attributes to support extra
    functionalities.

    The list of all available PIB attributes can be found in this data type.

   Remarks:
    None
*/
typedef enum {
  PLC_ID_HOST_DESCRIPTION_ID = 0x0100,
  PLC_ID_HOST_MODEL_ID  = 0x010A,
  PLC_ID_HOST_PHY_ID = 0x010C,
  PLC_ID_HOST_PRODUCT_ID = 0x0110,
  PLC_ID_HOST_VERSION_ID = 0x0112,
  PLC_ID_HOST_BAND_ID = 0x0116,
  PLC_ID_TIME_REF_ID = 0x0200,
  PLC_ID_PRODID = 0x4000,
  PLC_ID_MODEL,
  PLC_ID_VERSION_STR,
  PLC_ID_VERSION_NUM,
  PLC_ID_CFG_AUTODETECT_IMPEDANCE,
  PLC_ID_CFG_IMPEDANCE,
  PLC_ID_ZC_TIME,
  PLC_ID_RX_PAY_SYMBOLS,
  PLC_ID_TX_PAY_SYMBOLS,
  PLC_ID_RSV0,
  PLC_ID_MAX_RMS_TABLE_HI,
  PLC_ID_MAX_RMS_TABLE_VLO,
  PLC_ID_THRESHOLDS_TABLE_HI,
  PLC_ID_THRESHOLDS_TABLE_LO,
  PLC_ID_THRESHOLDS_TABLE_VLO,
  PLC_ID_PREDIST_COEF_TABLE_HI,
  PLC_ID_PREDIST_COEF_TABLE_LO,
  PLC_ID_PREDIST_COEF_TABLE_VLO,
  PLC_ID_GAIN_TABLE_HI,
  PLC_ID_GAIN_TABLE_LO,
  PLC_ID_GAIN_TABLE_VLO,
  PLC_ID_DACC_TABLE_CFG,
  PLC_ID_CHANNEL_CFG,
  PLC_ID_NUM_TX_LEVELS,
  PLC_ID_CORRECTED_RMS_CALC,
  PLC_ID_CURRENT_GAIN,
  PLC_ID_ZC_CONF_INV,
  PLC_ID_ZC_CONF_FREQ,
  PLC_ID_ZC_CONF_DELAY,
  PLC_ID_SIGNAL_CAPTURE_START,
  PLC_ID_SIGNAL_CAPTURE_STATUS,
  PLC_ID_SIGNAL_CAPTURE_FRAGMENT,
  PLC_ID_SIGNAL_CAPTURE_DATA,
  PLC_ID_ENABLE_AUTO_NOISE_CAPTURE,
  PLC_ID_TIME_BETWEEN_NOISE_CAPTURES,
  PLC_ID_DELAY_NOISE_CAPTURE_AFTER_RX,
  PLC_ID_RRC_NOTCH_ACTIVE,
  PLC_ID_RRC_NOTCH_INDEX,
  PLC_ID_NOISE_PEAK_POWER,
  PLC_ID_RRC_NOTCH_AUTODETECT,
  PLC_ID_RRC_NOTCH_THR_ON,
  PLC_ID_RRC_NOTCH_THR_OFF,
  PLC_ID_TX_TOTAL,
  PLC_ID_TX_TOTAL_BYTES,
  PLC_ID_TX_TOTAL_ERRORS,
  PLC_ID_TX_BAD_BUSY_TX,
  PLC_ID_TX_BAD_BUSY_CHANNEL,
  PLC_ID_TX_BAD_LEN,
  PLC_ID_TX_BAD_FORMAT,
  PLC_ID_TX_TIMEOUT,
  PLC_ID_RX_TOTAL,
  PLC_ID_RX_TOTAL_BYTES,
  PLC_ID_RX_EXCEPTIONS,
  PLC_ID_RX_BAD_LEN,
  PLC_ID_RX_BAD_CRC_FCH,
  PLC_ID_RX_FALSE_POSITIVE,
  PLC_ID_RX_BAD_FORMAT,
  PLC_ID_NOISE_PER_CARRIER,
  PLC_ID_PPM_CALIB_ON,
  PLC_ID_ZC_PERIOD,
  PLC_ID_SYNC_THRESHOLDS,
  PLC_ID_NUM_CHANNELS,
  PLC_ID_MAX_NUM_CHANNELS,
  PLC_ID_PREDIST_COEF_TABLE_HI_2,
  PLC_ID_PREDIST_COEF_TABLE_LO_2,
  PLC_ID_PREDIST_COEF_TABLE_VLO_2,
  PLC_ID_NOISE_PER_CARRIER_2,
  PLC_ID_RESET_STATS,
  PLC_ID_IC_DRIVER_CFG,
  PLC_ID_RX_CHN_EST_REAL,
  PLC_ID_RX_CHN_EST_IMAG,
  PLC_ID_RX_CHN_EST_REAL_2,
  PLC_ID_RX_CHN_EST_IMAG_2,
  PLC_ID_TX_DISABLE,
  PLC_ID_TX_HIGH_TEMP_120,
  PLC_ID_TX_CANCELLED,
  PLC_ID_RX_CD_INFO,
  PLC_ID_SFO_ESTIMATION_LAST_RX,
  PLC_ID_END_ID,
} DRV_PLC_PHY_ID;

// *****************************************************************************
/* PRIME Modulation schemes

  Summary:
    The list of all modulation schemes supported by PRIME spec.

  Remarks:
    None.
*/

typedef enum {
  SCHEME_DBPSK = 0,
  SCHEME_DQPSK = 1,
  SCHEME_D8PSK = 2,
  SCHEME_DBPSK_C = 4,
  SCHEME_DQPSK_C = 5,
  SCHEME_D8PSK_C = 6,
  SCHEME_R_DBPSK = 12,
  SCHEME_R_DQPSK = 13,
} DRV_PLC_PHY_SCH;

// *****************************************************************************
/* PRIME Types of PHY frame

  Summary:
    The list of all types of frame supported by PRIME spec.

  Remarks:
    None.
*/

typedef enum {
  FRAME_TYPE_A = 0,
  FRAME_TYPE_B = 2,
  FRAME_TYPE_BC = 3,
} DRV_PLC_PHY_FRAME_TYPE;

// *****************************************************************************
/* PRIME Header Types

  Summary:
    The list of all header types supported by PRIME spec.

  Remarks:
    None.
*/

typedef enum {
  HDR_GENERIC = 0,
  HDR_PROMOTION = 1,
  HDR_BEACON = 2,
} DRV_PLC_PHY_HEADER;

// *****************************************************************************
/* PRIME Channel definitions

  Summary:
    List of PRIME PHY channels. The PHY PLC_ID_CHANNEL_CFG uses these values.

  Remarks:
    8 single channels and 7 double channels.
*/

typedef enum
{
    /* Single Channels */
    CHN1 = 1,
    CHN2 = 2,
    CHN3 = 3,
    CHN4 = 4,
    CHN5 = 5,
    CHN6 = 6,
    CHN7 = 7,
    CHN8 = 8,
    /* Double Channels */
    CHN1_CHN2 = 9,
    CHN2_CHN3 = 10,
    CHN3_CHN4 = 11,
    CHN4_CHN5 = 12,
    CHN5_CHN6 = 13,
    CHN6_CHN7 = 14,
    CHN7_CHN8 = 15
} DRV_PLC_PHY_CHANNEL;

// *****************************************************************************
/* PRIME Internal Buffer identification

  Summary:
    Up to 2 different internal buffers can be used to store information to
    transmit. These buffers are implemented in the PLC transceiver PHY.

  Remarks:
    None.
*/

typedef enum {
  TX_BUFFER_0 = 0,
  TX_BUFFER_1 = 1,
} DRV_PLC_PHY_BUFFER_ID;

/* MISRA C-2012 deviation block start */
/* MISRA C-2012 Rule 5.2 deviated 5 times.  Deviation record ID - H3_MISRAC_2012_R_5_2_DR_1 */

// *****************************************************************************
/* PRIME Result values of a previous transmission

  Summary:
    This list provides all available transimission results in MCHP
    implementation.

  Remarks:
    None.
*/
typedef enum {
  /* Transmission result: already in process */
  DRV_PLC_PHY_TX_RESULT_PROCESS = 0,
  /* Transmission result: end successfully */
  DRV_PLC_PHY_TX_RESULT_SUCCESS = 1,
  /* Transmission result: invalid length error */
  DRV_PLC_PHY_TX_RESULT_INV_LENGTH = 2,
  /* Transmission result: busy channel error */
  DRV_PLC_PHY_TX_RESULT_BUSY_CH = 3,
  /* Transmission result: busy in transmission error */
  DRV_PLC_PHY_TX_RESULT_BUSY_TX = 4,
  /* Transmission result: busy in reception error */
  DRV_PLC_PHY_TX_RESULT_BUSY_RX = 5,
  /* Transmission result: invalid modulation scheme error */
  DRV_PLC_PHY_TX_RESULT_INV_SCHEME = 6,
  /* Transmission result: timeout error */
  DRV_PLC_PHY_TX_RESULT_TIMEOUT = 7,
  /* Transmission result: invalid buffer identifier error */
  DRV_PLC_PHY_TX_RESULT_INV_BUFFER = 8,
  /* Transmission result: invalid PRIME Mode error */
  DRV_PLC_PHY_TX_RESULT_INV_MODE = 9,
  /* Transmission result: invalid transmission mode */
  DRV_PLC_PHY_TX_RESULT_INV_TX_MODE = 10,
  /* Transmission result: Transmission cancelled */
  DRV_PLC_PHY_TX_RESULT_CANCELLED = 11,
  /* Transmission result: high temperature error */
  DRV_PLC_PHY_TX_RESULT_HIGH_TEMP_120 = 12,
  /* Transmission result: No transmission ongoing */
  DRV_PLC_PHY_TX_RESULT_NO_TX = 255,
} DRV_PLC_PHY_TX_RESULT;

/* MISRA C-2012 deviation block end */

/* Signal Capture States */
typedef enum {
	SIGNAL_CAPTURE_IDLE,
	SIGNAL_CAPTURE_RUNNING,
	SIGNAL_CAPTURE_READY,
} DRV_PLC_PHY_SIGNAL_CAPTURE_STATE;

/* Structure defining information about Noise Capture */
typedef struct {
	uint8_t numFrags;
	uint8_t status;
} DRV_PLC_PHY_SIGNAL_CAPTURE;

    /* MISRA C-2012 deviation block start */
    /* MISRA C-2012 Rule 6.1 deviated 3 times. Deviation record ID - H3_MISRAC_2012_R_6_1_DR_1 */
/* Structure defining information about CSMA algorithm */
typedef struct {
	uint8_t disableRx : 1;
	uint8_t senseCount : 3;
	uint8_t senseDelayMs : 4;
} DRV_PLC_PHY_CSMA;
    /* MISRA C-2012 deviation block end */


// *****************************************************************************
/* PRIME Transmission setup data

  Summary:
    This struct includes all the parameters needed to request a PRIME PHY
    transmission.

  Remarks:
    None.
*/
typedef struct __attribute__((packed, aligned(1))) {
  /* Pointer to data buffer to transmit */
  uint8_t *pTransmitData;
  /* Instant when transmission has to start referred to 1us PHY counter */
  uint32_t timeIni;
  /* Length of the data to transmit in bytes */
  uint16_t dataLength;
  /* Transmission Mode (absolute, relative, cancel, continuous). Constants above */
  uint8_t mode;
  /* Attenuation level with which the message will be transmitted */
  uint8_t attenuation;
  /* CSMA algorithm parameters */
  DRV_PLC_PHY_CSMA csma;
  /* Buffer Id used for transmission */
  DRV_PLC_PHY_BUFFER_ID bufferId;
  /* Scheme of Modulation */
  DRV_PLC_PHY_SCH scheme;
  /* PRIME Frame type */
  DRV_PLC_PHY_FRAME_TYPE frameType;
} DRV_PLC_PHY_TRANSMISSION_OBJ;

// *****************************************************************************
/* PRIME Result of a transmission

  Summary:
    This struct includes all the parameters provided in transmission confirm.

  Remarks:
    None.
*/
typedef struct {
  /* Instant when frame transmission started referred to 1us PHY counter */
  uint32_t timeIni;
  /* RMS value emitted */
  uint32_t rmsCalc;
  /* PRIME Frame type */
  DRV_PLC_PHY_FRAME_TYPE frameType;
  /* Tx Result (see "TX Result values" above) */
  DRV_PLC_PHY_TX_RESULT result;
  /* Buffer Id used for transmission */
  DRV_PLC_PHY_BUFFER_ID bufferId;
} DRV_PLC_PHY_TRANSMISSION_CFM_OBJ;

// *****************************************************************************
/* PRIME Reception parameters

  Summary:
    This struct includes all the parameters provided for a received message.

  Remarks:
    None.
*/
typedef struct __attribute__((packed, aligned(1))) {
  /* Pointer to received data buffer */
  uint8_t *pReceivedData;
  /* Instant when frame was received (start of message) referred to 1us PHY counter */
  uint32_t timeIni;
  /* Accumulated Error Vector Magnitude for header */
  uint32_t evmHeaderAcum;
  /* Accumulated Error Vector Magnitude for payload */
  uint32_t evmPayloadAcum;
  /* Error Vector Magnitude for header */
  uint16_t evmHeader;
  /* Error Vector Magnitude for payload */
  uint16_t evmPayload;
  /* Length of the received data in bytes */
  uint16_t dataLength;
  /* Scheme of Modulation */
  DRV_PLC_PHY_SCH scheme;
  /* PRIME Frame type */
  DRV_PLC_PHY_FRAME_TYPE frameType;
  /* Header type */
  DRV_PLC_PHY_HEADER headerType;
  /* Average RSSI (Received Signal Strength Indication) in dBuV */
  uint8_t rssiAvg;
  /* Average CNIR (Carrier to Interference + Noise ratio) */
  uint8_t cinrAvg;
  /* Minimum CNIR (Carrier to Interference + Noise ratio) */
  uint8_t cinrMin;
  /* Average Soft BER (Bit Error Rate) */
  uint8_t berSoftAvg;
  /* Maximum Soft BER (Bit Error Rate) */
  uint8_t berSoftMax;
  /* Percentage of carriers affected by narrow band noise */
  uint8_t narBandPercent;
  /* Percentage of symbols affected by impulsive noise */
  uint8_t impNoisePercent;
} DRV_PLC_PHY_RECEPTION_OBJ;

/* Rx state values for CD info */
typedef enum {
  CD_RX_IDLE = 0,
  CD_RX_PREAMBLE_1_2 = 1,
  CD_RX_PREAMBLE_2_3 = 2,
  CD_RX_PREAMBLE = 3,
  CD_RX_HEADER = 4,
  CD_RX_PAYLOAD = 5,
} DRV_PLC_PHY_CD_RX_STATE;

// *****************************************************************************
/* Structure defining PRIME CD information

  Summary:
    This struct includes the Carrier Detect related information. It gives
    information about the current state of PLC reception.

  Remarks:
    This struct is related to PLC_ID_RX_CD_INFO.
*/
typedef struct {
  /* Reception time (message end or header end if message length is not known yet) referred to 1us PHY counter */
  uint32_t rxTimeEnd;
  /* Current time referred to 1us PHY counter */
  uint32_t currentTime;
  /* Correlation peak value */
  uint16_t corrPeakValue;
  /* Average RSSI (Received Signal Strength Indication) in dBuV */
  uint8_t rssiAvg;
  /* Reception state. Similar to header from PRIME spec, but extra values for preamble */
  DRV_PLC_PHY_CD_RX_STATE cdRxState;
  /* Type A, Type B or Type BC  */
  DRV_PLC_PHY_FRAME_TYPE frameType;
} DRV_PLC_PHY_CD_INFO;

// *****************************************************************************
/* PRIME PHY Information Base (PIB)

  Summary:
    This struct includes all information to access any defined PIB.

  Remarks:
    None.
*/
typedef struct {
  /* Pointer to PIB data */
  uint8_t *pData;
  /* PLC Information base identification */
  DRV_PLC_PHY_ID id;
  /* Length in bytes of the data information */
  uint16_t length;
} DRV_PLC_PHY_PIB_OBJ;

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // #ifndef DRV_PLC_PHY_COMM_H

/*******************************************************************************
 End of File
*/
