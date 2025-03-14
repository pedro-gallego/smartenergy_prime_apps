/*******************************************************************************
  PLC PHY Coupling Service Library Interface Header File

  Company
    Microchip Technology Inc.

  File Name
    srv_pcoup.h

  Summary
    PLC PHY Coupling service library interface.

  Description
    The Microchip G3-PLC and PRIME implementations include default PHY layer
    configuration values optimized for the Evaluation Kits. With the help of
    the PHY Calibration Tool it is possible to obtain the optimal configuration
    values for the customer's hardware implementation. Refer to the online
    documentation for more details about the available configuration values and
    their purpose.

  Remarks:
    This service provides the required information to be included on PLC
    projects for PL360/PL460 in order to apply the custom calibration.
*******************************************************************************/

// DOM-IGNORE-BEGIN
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
// DOM-IGNORE-END

#ifndef SRV_PCOUP_H    // Guards against multiple inclusion
#define SRV_PCOUP_H


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "system/system.h"
#include "driver/plc/phy/drv_plc_phy.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif
// DOM-IGNORE-END

/* PLC PRIME PHY default channel */
#define SRV_PCOUP_DEFAULT_CHANNEL                CHN1

/* PLC PRIME PHY Channel for impedance detection */
#define SRV_PCOUP_CHANNEL_IMP_DET                CHN1

/* PLC PRIME PHY Channel List */
#define SRV_PCOUP_CHANNEL_LIST                   255

/* Equalization number of coefficients (number of carriers) */
#define SRV_PCOUP_EQU_NUM_COEF_CHN               97U

/* Equalization coefficients tables */
#define SRV_PCOUP_PRED_CHN1_HIGH_TBL             {0x756E, 0x7396, 0x730A, 0x72EB, 0x72B2, 0x7433, 0x755E, 0x75D7, 0x769E, 0x76A4, 0x77C3, 0x7851, 0x7864, 0x78A0, \
					                             0x78BA, 0x7918, 0x79B6, 0x79E9, 0x7ACC, 0x7B06, 0x7B30, 0x7B27, 0x7C1E, 0x7B96, 0x7A76, 0x7B12, 0x7AFD, 0x7C40, \
					                             0x7C5E, 0x7B48, 0x7B8A, 0x7C64, 0x7C42, 0x7BCD, 0x7AFD, 0x7A5F, 0x7A03, 0x7A9D, 0x7A1A, 0x7A4A, 0x79FC, 0x7984, \
					                             0x7A0D, 0x79CC, 0x792E, 0x780D, 0x7676, 0x75E4, 0x747A, 0x7251, 0x707E, 0x6E96, 0x6E30, 0x6D44, 0x6DBD, 0x6C9A, \
					                             0x6C3C, 0x6CF8, 0x6CA4, 0x6CDF, 0x6C59, 0x6B2C, 0x6CB9, 0x6C1F, 0x6B6D, 0x6BF5, 0x6AF0, 0x6A55, 0x6955, 0x674F, \
					                             0x6841, 0x685D, 0x670F, 0x6904, 0x6967, 0x6B01, 0x6C31, 0x6C2A, 0x6D82, 0x6F58, 0x6E62, 0x6F18, 0x6EE7, 0x7069, \
					                             0x717B, 0x7120, 0x7170, 0x72FB, 0x7491, 0x75B3, 0x75A2, 0x7664, 0x784A, 0x7A52, 0x7B51, 0x7D5A, 0x7FFF}

#define SRV_PCOUP_PRED_CHN1_VLOW_TBL             {0x7FFF, 0x7F2B, 0x7E38, 0x7CD3, 0x7B38, 0x7972, 0x77D6, 0x7654, 0x74AE, 0x7288, 0x70C0, 0x6E9A, 0x6D24, 0x6B80, \
					                             0x6A2F, 0x6852, 0x674E, 0x65DA, 0x652E, 0x637E, 0x6292, 0x6142, 0x60CC, 0x5FF8, 0x5F6D, 0x5EC2, 0x5E6F, 0x5E55, \
					                             0x5E43, 0x5E02, 0x5E5B, 0x5EB3, 0x5F4A, 0x5FD7, 0x604C, 0x60FC, 0x61F3, 0x6297, 0x63A9, 0x643D, 0x654A, 0x6634, \
					                             0x675C, 0x6824, 0x6910, 0x69A4, 0x6A73, 0x6B6F, 0x6C15, 0x6CCD, 0x6D64, 0x6E4B, 0x6ED3, 0x6F44, 0x6F85, 0x70A1, \
					                             0x70AF, 0x71B2, 0x7149, 0x71F3, 0x7203, 0x7279, 0x71FB, 0x72B4, 0x7281, 0x72A4, 0x7262, 0x72BD, 0x7295, 0x72CC, \
					                             0x729E, 0x7288, 0x7244, 0x7279, 0x726C, 0x7230, 0x71B9, 0x70D8, 0x7045, 0x7052, 0x6F8D, 0x6F3D, 0x6EB0, 0x6E6A, \
					                             0x6E76, 0x6E1C, 0x6D7A, 0x6D84, 0x6D50, 0x6D45, 0x6CF2, 0x6CA9, 0x6C92, 0x6CBA, 0x6C69, 0x6C27, 0x6C02}

#define SRV_PCOUP_PRED_NOT_USED                  {0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, \
					                             0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, \
					                             0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, \
					                             0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, \
					                             0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, \
					                             0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, \
					                             0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF}

/* DACC configuration tables */
#define SRV_PCOUP_DACC_CENA_TBL                  {0x0UL, 0x21200000UL, 0x73f0000UL, 0x3f3f0000UL, 0xcccUL, 0x0UL, \
                                                 0xa92c00ffUL, 0x1a1a1a1aUL, 0x20200000UL, 0x4400UL, 0xfd20005UL, 0x3aaUL, \
                                                 0xf0000000UL, 0x1020f0UL, 0x3aaUL, 0xf0000000UL, 0x1020ffUL}

#define SRV_PCOUP_DACC_FCC_TBL                   {0x0UL, 0x0UL, 0x100UL, 0x100UL, 0x0UL, 0x0UL, \
                                                 0xffff00ffUL, 0x1b1b1b1bUL, 0x0UL, 0x0UL, 0x6UL, 0x355UL, \
                                                 0x0UL, 0x1020f0UL, 0x355UL, 0x0UL, 0x1020ffUL}


/* PLC PHY Coupling parameters for each PRIME channel */
#define SRV_PCOUP_CHN1_RMS_HIGH_TBL              {1725, 1522, 1349, 1202, 1071, 957, 855, 764}
#define SRV_PCOUP_CHN1_RMS_VLOW_TBL              {4874, 4427, 3986, 3555, 3157, 2795, 2470, 2184}
#define SRV_PCOUP_CHN1_THRS_HIGH_TBL             {0, 0, 0, 0, 0, 0, 0, 0, 1467, 1292, 1145, 1019, 910, 811, 725, 648}
#define SRV_PCOUP_CHN1_THRS_VLOW_TBL             {0, 0, 0, 0, 0, 0, 0, 0, 8479, 7515, 6665, 5874, 5192, 4576, 4030, 3557}
#define SRV_PCOUP_CHN1_GAIN_HIGH_TBL             {81, 40, 128}
#define SRV_PCOUP_CHN1_GAIN_VLOW_TBL             {256, 128, 281}
#define SRV_PCOUP_CHN1_LINE_DRV_CONF             8
#define SRV_PCOUP_CHN1_MAX_NUM_TX_LEVELS         8

#define SRV_PCOUP_CHN2_RMS_HIGH_TBL              {737, 654, 581, 517, 460, 409, 364, 323}
#define SRV_PCOUP_CHN2_RMS_VLOW_TBL              {3492, 3124, 2766, 2430, 2122, 1853, 1622, 1425}
#define SRV_PCOUP_CHN2_THRS_HIGH_TBL             {0, 0, 0, 0, 0, 0, 0, 0, 668, 595, 529, 469, 415, 370, 329, 292}
#define SRV_PCOUP_CHN2_THRS_VLOW_TBL             {0, 0, 0, 0, 0, 0, 0, 0, 100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000}
#define SRV_PCOUP_CHN2_GAIN_HIGH_TBL             {120, 30, 256}
#define SRV_PCOUP_CHN2_GAIN_VLOW_TBL             {256, 128, 287}
#define SRV_PCOUP_CHN2_LINE_DRV_CONF             5
#define SRV_PCOUP_CHN2_MAX_NUM_TX_LEVELS         8

#define SRV_PCOUP_CHN3_RMS_HIGH_TBL              {746, 661, 584, 516, 457, 404, 358, 318}
#define SRV_PCOUP_CHN3_RMS_VLOW_TBL              {3573, 3288, 2997, 2703, 2413, 2145, 1905, 1690}
#define SRV_PCOUP_CHN3_THRS_HIGH_TBL             {0, 0, 0, 0, 0, 0, 0, 0, 561, 496, 439, 388, 344, 304, 270, 239}
#define SRV_PCOUP_CHN3_THRS_VLOW_TBL             {0, 0, 0, 0, 0, 0, 0, 0, 100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000}
#define SRV_PCOUP_CHN3_GAIN_HIGH_TBL             {30, 30, 256}
#define SRV_PCOUP_CHN3_GAIN_VLOW_TBL             {287, 128, 287}
#define SRV_PCOUP_CHN3_LINE_DRV_CONF             5
#define SRV_PCOUP_CHN3_MAX_NUM_TX_LEVELS         8

#define SRV_PCOUP_CHN4_RMS_HIGH_TBL              {1610, 1443, 1294, 1160, 1040, 932, 835, 748}
#define SRV_PCOUP_CHN4_RMS_VLOW_TBL              {3465, 3160, 2854, 2552, 2271, 2018, 1793, 1593}
#define SRV_PCOUP_CHN4_THRS_HIGH_TBL             {0, 0, 0, 0, 0, 0, 0, 0, 1285, 1152, 1034, 927, 831, 744, 666, 597}
#define SRV_PCOUP_CHN4_THRS_VLOW_TBL             {0, 0, 0, 0, 0, 0, 0, 0, 100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000}
#define SRV_PCOUP_CHN4_GAIN_HIGH_TBL             {60, 30, 256}
#define SRV_PCOUP_CHN4_GAIN_VLOW_TBL             {256, 128, 287}
#define SRV_PCOUP_CHN4_LINE_DRV_CONF             5
#define SRV_PCOUP_CHN4_MAX_NUM_TX_LEVELS         8

#define SRV_PCOUP_CHN5_RMS_HIGH_TBL              {1794, 1602, 1430, 1277, 1141, 1019, 910, 813}
#define SRV_PCOUP_CHN5_RMS_VLOW_TBL              {3749, 3421, 3087, 2758, 2455, 2182, 1937, 1719}
#define SRV_PCOUP_CHN5_THRS_HIGH_TBL             {0, 0, 0, 0, 0, 0, 0, 0, 1557, 1392, 1241, 1108, 990, 885, 790, 706}
#define SRV_PCOUP_CHN5_THRS_VLOW_TBL             {0, 0, 0, 0, 0, 0, 0, 0, 100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000}
#define SRV_PCOUP_CHN5_GAIN_HIGH_TBL             {85, 30, 256}
#define SRV_PCOUP_CHN5_GAIN_VLOW_TBL             {256, 128, 287}
#define SRV_PCOUP_CHN5_LINE_DRV_CONF             5
#define SRV_PCOUP_CHN5_MAX_NUM_TX_LEVELS         8

#define SRV_PCOUP_CHN6_RMS_HIGH_TBL              {1243, 1108, 987, 880, 784, 699, 623, 556}
#define SRV_PCOUP_CHN6_RMS_VLOW_TBL              {3694, 3368, 3037, 2713, 2416, 2149, 1911, 1698}
#define SRV_PCOUP_CHN6_THRS_HIGH_TBL             {0, 0, 0, 0, 0, 0, 0, 0, 1081, 963, 858, 765, 682, 607, 541, 483}
#define SRV_PCOUP_CHN6_THRS_VLOW_TBL             {0, 0, 0, 0, 0, 0, 0, 0, 100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000}
#define SRV_PCOUP_CHN6_GAIN_HIGH_TBL             {60, 30, 256}
#define SRV_PCOUP_CHN6_GAIN_VLOW_TBL             {256, 128, 287}
#define SRV_PCOUP_CHN6_LINE_DRV_CONF             5
#define SRV_PCOUP_CHN6_MAX_NUM_TX_LEVELS         8

#define SRV_PCOUP_CHN7_RMS_HIGH_TBL              {1441, 1280, 1137, 1010, 897, 798, 710, 631}
#define SRV_PCOUP_CHN7_RMS_VLOW_TBL              {3277, 2986, 2692, 2406, 2145, 1911, 1703, 1517}
#define SRV_PCOUP_CHN7_THRS_HIGH_TBL             {0, 0, 0, 0, 0, 0, 0, 0, 1226, 1088, 967, 859, 764, 679, 603, 537}
#define SRV_PCOUP_CHN7_THRS_VLOW_TBL             {0, 0, 0, 0, 0, 0, 0, 0, 100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000}
#define SRV_PCOUP_CHN7_GAIN_HIGH_TBL             {60, 30, 256}
#define SRV_PCOUP_CHN7_GAIN_VLOW_TBL             {256, 128, 287}
#define SRV_PCOUP_CHN7_LINE_DRV_CONF             5
#define SRV_PCOUP_CHN7_MAX_NUM_TX_LEVELS         8

#define SRV_PCOUP_CHN8_RMS_HIGH_TBL              {894, 794, 705, 626, 556, 495, 440, 392}
#define SRV_PCOUP_CHN8_RMS_VLOW_TBL              {3016, 2770, 2524, 2276, 2035, 1815, 1620, 1446}
#define SRV_PCOUP_CHN8_THRS_HIGH_TBL             {0, 0, 0, 0, 0, 0, 0, 0, 688, 611, 543, 481, 429, 381, 338, 302}
#define SRV_PCOUP_CHN8_THRS_VLOW_TBL             {0, 0, 0, 0, 0, 0, 0, 0, 100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000}
#define SRV_PCOUP_CHN8_GAIN_HIGH_TBL             {30, 30, 256}
#define SRV_PCOUP_CHN8_GAIN_VLOW_TBL             {287, 128, 287}
#define SRV_PCOUP_CHN8_LINE_DRV_CONF             5
#define SRV_PCOUP_CHN8_MAX_NUM_TX_LEVELS         8


// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************
// *****************************************************************************

/* PLC PHY Coupling data

  Summary:
    PLC PHY Coupling data.

  Description:
    This structure contains all the data required to set the PLC PHY Coupling
    parameters, for a specific PRIME channel.

  Remarks:
    Equalization coefficients and DACC table are not stored in the structure,
    just pointers to arrays were they are actually stored. This allows to use
    the same type for different PRIME channels.
*/

typedef struct
{
    /* Target RMS values in HIGH mode for dynamic Tx gain */
    uint32_t rmsHigh[8];

    /* Target RMS values in VLOW mode for dynamic Tx gain */
    uint32_t rmsVLow[8];

    /* Threshold RMS values in HIGH mode for dynamic Tx mode */
    uint32_t thrsHigh[16];

    /* Threshold RMS values in VLOW mode for dynamic Tx mode */
    uint32_t thrsVLow[16];

    /* Pointer to values for configuration of PLC DACC peripheral, according to
       hardware coupling design and PLC device (PL360/PL460) */
    const uint32_t * daccTable;

    /* Pointer to Tx equalization coefficients table in HIGH mode.
       There is one coefficient for each carrier in the used band */
    const uint16_t * equHigh;

    /* Pointer to Tx equalization coefficients table in VLOW mode.
       There is one coefficient for each carrier in the used band */
    const uint16_t * equVlow;

    /* Tx gain values for HIGH mode [HIGH_INI, HIGH_MIN, HIGH_MAX] */
    uint16_t gainHigh[3];

    /* Tx gain values for VLOW mode [VLOW_INI, VLOW_MIN, VLOW_MAX] */
    uint16_t gainVLow[3];

    /* Number of Tx attenuation levels (1 dB step) supporting dynamic Tx mode */
    uint8_t numTxLevels;

    /* Configuration of the PLC Tx Line Driver, according to hardware coupling
       design and PLC device (PL360/PL460) */
    uint8_t lineDrvConf;

} SRV_PLC_PCOUP_CHANNEL_DATA;

// *****************************************************************************
// *****************************************************************************
// Section: Service Interface Functions
// *****************************************************************************
// *****************************************************************************

/***************************************************************************
  Function:
    DRV_PLC_PHY_CHANNEL SRV_PCOUP_GetDefaultChannel(void)

  Summary:
    Get the default PRIME channel.

  Description:
    This function allows to get the PRIME channel used by default.

  Precondition:
    None.

  Parameters:
    None.

  Returns:
    Default PRIME channel.

  Example:
    <code>
    DRV_PLC_PHY_CHANNEL plcDefaultChannel;
    DRV_PLC_PHY_PIB_OBJ pibObj;

    plcDefaultChannel = SRV_PCOUP_GetDefaultChannel();

    pibObj.id = PLC_ID_CHANNEL_CFG;
    pibObj.length = 1;
    pibObj.pData = &plcDefaultChannel;
    DRV_PLC_PHY_PIBSet(handle, &pibObj);

    SRV_PCOUP_SetChannelConfig(handle, plcDefaultChannel);
    </code>

  Remarks:
    None.
  ***************************************************************************/

DRV_PLC_PHY_CHANNEL SRV_PCOUP_GetDefaultChannel( void );

/***************************************************************************
  Function:
    SRV_PLC_PCOUP_CHANNEL_DATA * SRV_PCOUP_GetChannelConfig (DRV_PLC_PHY_CHANNEL channel)

  Summary:
    Get the PLC PHY Coupling parameters for the specified PRIME channel.

  Description:
    This function allows to get the PLC PHY Coupling parameters for the
    specified PRIME channel. These parameters can be sent to the PLC device
    through PLC Driver PIB interface (DRV_PLC_PHY_PIBSet).

  Precondition:
    None.

  Parameters:
    channel   - PRIME channel for which the parameters are requested

  Returns:
    - Pointer to PLC PHY Coupling parameters
      - if channel parameter is valid
    - *NULL*
      - if channel parameter is not valid

  Example:
    <code>
    SRV_PLC_PCOUP_CHANNEL_DATA *pCoupChannelData;

    pCoupChannelData = SRV_PCOUP_GetChannelConfig
(SRV_PCOUP_DEFAULT_CHANNEL);
    </code>

  Remarks:
    If SRV_PCOUP_SetChannelConfig is used to set the PLC PHY Coupling
    parameters, this function is not needed.
  ***************************************************************************/

SRV_PLC_PCOUP_CHANNEL_DATA * SRV_PCOUP_GetChannelConfig (DRV_PLC_PHY_CHANNEL channel);

/***************************************************************************
  Function:
    bool SRV_PCOUP_SetChannelConfig(DRV_HANDLE handle, DRV_PLC_PHY_CHANNEL channel);

  Summary:
    Set the PLC PHY Coupling parameters for the specified PRIME channel.

  Description:
    This function allows to set the PLC PHY Coupling parameters for the
    specified PRIME channel, using the PLC Driver PIB interface
    (DRV_PLC_PHY_PIBSet).

  Precondition:
    DRV_PLC_PHY_Open must have been called to obtain a valid opened device
    handle.

  Parameters:
    handle   - A valid instance handle, returned from DRV_PLC_PHY_Open
    channel  - PRIME channel for which the parameters will be set

  Returns:
    - true
      - Successful configuration
    - false
      - if channel parameter is not valid
      - if there is an error when using the PLC Driver PIB interface

  Example:
    <code>
    bool result;

    result = SRV_PCOUP_SetChannelConfig(handle, CHN5);
    </code>

  Remarks:
    None.
  ***************************************************************************/

bool SRV_PCOUP_SetChannelConfig(DRV_HANDLE handle, DRV_PLC_PHY_CHANNEL channel);

/***************************************************************************
  Function:
    uint16_t SRV_PCOUP_GetChannelList(void)

  Summary:
    Get the PRIME channel list.

  Description:
    This function allows to get the PRIME channel list.

  Precondition:
    None.

  Parameters:
    None.

  Returns:
    PRIME channel list. The channel list is a bitmask corresponding to the 
    following values.
    Single channel:
      Channel 1 : bit 0
      Channel 2 : bit 1
      Channel 3 : bit 2
      Channel 4 : bit 3
      Channel 5 : bit 4
      Channel 6 : bit 5
      Channel 7 : bit 6
      Channel 8 : bit 7
    In double channel:
      Channel 1-2 : bit 8
      Channel 2-3 : bit 9
      Channel 3-4 : bit 10
      Channel 4-5 : bit 11
      Channel 5-6 : bit 12
      Channel 6-7 : bit 13
      Channel 7-8 : bit 14

  Example:
    <code>
    uint16_t plcChannelList;

    plcChannelList = SRV_PCOUP_GetChannelList();

    </code>

  Remarks:
    None.
  ***************************************************************************/

uint16_t SRV_PCOUP_GetChannelList(void);

DRV_PLC_PHY_CHANNEL SRV_PCOUP_GetChannelImpedanceDetection(void);

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif
// DOM-IGNORE-END

#endif //SRV_PCOUP_H
