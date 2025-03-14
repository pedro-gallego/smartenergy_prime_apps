/*******************************************************************************
  System Configuration Header

  File Name:
    configuration.h

  Summary:
    Build-time configuration header for the system defined by this project.

  Description:
    An MPLAB Project may have multiple configurations.  This file defines the
    build-time options for a single configuration.

  Remarks:
    This configuration header must not define any prototypes or data
    definitions (or include any files that do).  It only provides macro
    definitions for build-time configuration options

*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/
// DOM-IGNORE-END

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/*  This section Includes other configuration headers necessary to completely
    define this configuration.
*/

#include "user.h"
#include "device.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: System Configuration
// *****************************************************************************
// *****************************************************************************



// *****************************************************************************
// *****************************************************************************
// Section: System Service Configuration
// *****************************************************************************
// *****************************************************************************
/* TIME System Service Configuration Options */
#define SYS_TIME_INDEX_0                            (0)
#define SYS_TIME_MAX_TIMERS                         (25)
#define SYS_TIME_HW_COUNTER_WIDTH                   (32)
#define SYS_TIME_HW_COUNTER_PERIOD                  (4294967295U)
#define SYS_TIME_HW_COUNTER_HALF_PERIOD             (SYS_TIME_HW_COUNTER_PERIOD>>1)
#define SYS_TIME_CPU_CLOCK_FREQUENCY                (200000000)
#define SYS_TIME_COMPARE_UPDATE_EXECUTION_CYCLES    (232)

#define SYS_CONSOLE_INDEX_0                       0





#define SYS_DEBUG_ENABLE
#define SYS_DEBUG_GLOBAL_ERROR_LEVEL       SYS_ERROR_DEBUG
#define SYS_DEBUG_BUFFER_DMA_READY
#define SYS_DEBUG_USE_CONSOLE


#define SYS_CONSOLE_DEVICE_MAX_INSTANCES   			(1U)
#define SYS_CONSOLE_UART_MAX_INSTANCES 	   			(1U)
#define SYS_CONSOLE_USB_CDC_MAX_INSTANCES 	   		(0U)
#define SYS_CONSOLE_PRINT_BUFFER_SIZE        		(200U)




// *****************************************************************************
// *****************************************************************************
// Section: Driver Configuration
// *****************************************************************************
// *****************************************************************************
/* Memory Driver Global Configuration Options */
#define DRV_MEMORY_INSTANCES_NUMBER          (1U)

/* USI Service Common Configuration Options */
#define SRV_USI_INSTANCES_NUMBER              1U
#define SRV_USI_USART_CONNECTIONS             1U
#define SRV_USI_CDC_CONNECTIONS               0U
#define SRV_USI_MSG_POOL_SIZE                 5U

/* PLC PHY Driver Configuration Options */
#define DRV_PLC_SECURE                        false
#define DRV_PLC_EXT_INT_PIO_PORT              PIO_PORT_A
#define DRV_PLC_EXT_INT_SRC                   PIOA_IRQn
#define DRV_PLC_EXT_INT_PIO                   SYS_PORT_PIN_PA2
#define DRV_PLC_EXT_INT_PIN                   SYS_PORT_PIN_PA2
#define DRV_PLC_RESET_PIN                     SYS_PORT_PIN_PD15
#define DRV_PLC_LDO_EN_PIN                    SYS_PORT_PIN_PD19
#define DRV_PLC_TX_ENABLE_PIN                 SYS_PORT_PIN_PA1
#define DRV_PLC_THMON_PIN                     SYS_PORT_PIN_PB15
#define DRV_PLC_CSR_INDEX                     0
#define DRV_PLC_SPI_CLK                       8000000

/* PLC Driver Identification */
#define DRV_PLC_PHY_INSTANCES_NUMBER          1U
#define DRV_PLC_PHY_INDEX                     0U
#define DRV_PLC_PHY_CLIENTS_NUMBER_IDX        1U
#define DRV_PLC_PHY_PROFILE                   4U
#define DRV_PLC_PHY_NUM_CARRIERS              97U
#define DRV_PLC_PHY_HOST_PRODUCT              0x3600U
#define DRV_PLC_PHY_HOST_VERSION              0x36000300UL
#define DRV_PLC_PHY_HOST_PHY                  0x36000003UL
#define DRV_PLC_PHY_HOST_DESC                 "PIC32CX2051MTG128"
#define DRV_PLC_PHY_HOST_MODEL                3U
#define DRV_PLC_PHY_HOST_BAND                 DRV_PLC_PHY_PROFILE



/* Memory Driver Instance 0 Configuration */
#define DRV_MEMORY_INDEX_0                   0
#define DRV_MEMORY_CLIENTS_NUMBER_IDX0       1
#define DRV_MEMORY_BUF_Q_SIZE_IDX0    1
#define DRV_MEMORY_DEVICE_START_ADDRESS      0x10A0000U
#define DRV_MEMORY_DEVICE_MEDIA_SIZE         384UL
#define DRV_MEMORY_DEVICE_MEDIA_SIZE_BYTES   (DRV_MEMORY_DEVICE_MEDIA_SIZE * 1024U)
#define DRV_MEMORY_DEVICE_PROGRAM_SIZE       512U
#define DRV_MEMORY_DEVICE_ERASE_SIZE         8192U

/* PRIME PAL Configuration Options */
#define PRIME_PAL_INDEX                     0U
#define PRIME_PAL_SNIFFER_USI_INSTANCE      SRV_USI_INDEX_0


/* USI Service Instance 0 Configuration Options */
#define SRV_USI_INDEX_0                       0
#define SRV_USI0_RD_BUF_SIZE                  1024
#define SRV_USI0_WR_BUF_SIZE                  1024



// *****************************************************************************
// *****************************************************************************
// Section: Middleware & Other Library Configuration
// *****************************************************************************
// *****************************************************************************
/* PRIME Identification */
#define PRIME_INDEX_0                               0U
#define PRIME_INSTANCES_NUMBER                      1U

/* Management Plane USI port */
#define PRIME_MNG_PLANE_USI_INDEX                   0U





// *****************************************************************************
// *****************************************************************************
// Section: Application Configuration
// *****************************************************************************
// *****************************************************************************


//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // CONFIGURATION_H
/*******************************************************************************
 End of File
*/
