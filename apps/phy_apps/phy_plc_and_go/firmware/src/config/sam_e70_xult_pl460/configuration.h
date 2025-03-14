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
#define SYS_TIME_MAX_TIMERS                         (5)
#define SYS_TIME_HW_COUNTER_WIDTH                   (16)
#define SYS_TIME_HW_COUNTER_PERIOD                  (65535U)
#define SYS_TIME_HW_COUNTER_HALF_PERIOD             (SYS_TIME_HW_COUNTER_PERIOD>>1)
#define SYS_TIME_CPU_CLOCK_FREQUENCY                (300000000)
#define SYS_TIME_COMPARE_UPDATE_EXECUTION_CYCLES    (900)

#define SYS_CONSOLE_DEVICE_MAX_INSTANCES   			(1U)
#define SYS_CONSOLE_UART_MAX_INSTANCES 	   			(0U)
#define SYS_CONSOLE_USB_CDC_MAX_INSTANCES 	   		(1U)
#define SYS_CONSOLE_PRINT_BUFFER_SIZE        		(512U)

#define SYS_CONSOLE_USB_CDC_READ_WRITE_BUFFER_SIZE 	(64)

#define SYS_CONSOLE_INDEX_0                       0

/* RX buffer size has one additional element for the empty spot needed in circular buffer */
#define SYS_CONSOLE_USB_CDC_RD_BUFFER_SIZE_IDX0    129

/* TX buffer size has one additional element for the empty spot needed in circular buffer */
#define SYS_CONSOLE_USB_CDC_WR_BUFFER_SIZE_IDX0    513




// *****************************************************************************
// *****************************************************************************
// Section: Driver Configuration
// *****************************************************************************
// *****************************************************************************

/* PLC PHY Driver Configuration Options */
#define DRV_PLC_SECURE                        false
#define DRV_PLC_EXT_INT_PIO_PORT              PIO_PORT_D
#define DRV_PLC_EXT_INT_SRC                   PIOD_IRQn
#define DRV_PLC_EXT_INT_PIO                   SYS_PORT_PIN_PD28
#define DRV_PLC_EXT_INT_PIN                   SYS_PORT_PIN_PD28
#define DRV_PLC_RESET_PIN                     SYS_PORT_PIN_PA0
#define DRV_PLC_LDO_EN_PIN                    SYS_PORT_PIN_PC30
#define DRV_PLC_TX_ENABLE_PIN                 SYS_PORT_PIN_PA4
#define DRV_PLC_STBY_PIN                      SYS_PORT_PIN_PA3
#define DRV_PLC_THMON_PIN                     SYS_PORT_PIN_PC17
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
#define DRV_PLC_PHY_HOST_DESC                 "ATSAME70Q21B"
#define DRV_PLC_PHY_HOST_MODEL                3U
#define DRV_PLC_PHY_HOST_BAND                 DRV_PLC_PHY_PROFILE




// *****************************************************************************
// *****************************************************************************
// Section: Middleware & Other Library Configuration
// *****************************************************************************
// *****************************************************************************
/* Number of Endpoints used */
#define DRV_USBHSV1_ENDPOINTS_NUMBER                        4U

/* The USB Device Layer will not initialize the USB Driver */
#define USB_DEVICE_DRIVER_INITIALIZE_EXPLICIT

/* Maximum device layer instances */
#define USB_DEVICE_INSTANCES_NUMBER                         1U

/* EP0 size in bytes */
#define USB_DEVICE_EP0_BUFFER_SIZE                          64U


/* Maximum instances of CDC function driver */
#define USB_DEVICE_CDC_INSTANCES_NUMBER                     1U


/* CDC Transfer Queue Size for both read and
   write. Applicable to all instances of the
   function driver */
#define USB_DEVICE_CDC_QUEUE_DEPTH_COMBINED                 3U

/*** USB Driver Configuration ***/

/* Maximum USB driver instances */
#define DRV_USBHSV1_INSTANCES_NUMBER                        1U

/* Interrupt mode enabled */
#define DRV_USBHSV1_INTERRUPT_MODE                          true

/* Enables Device Support */
#define DRV_USBHSV1_DEVICE_SUPPORT                          true
    
/* Disable Host Support */
#define DRV_USBHSV1_HOST_SUPPORT                            false

/* Alignment for buffers that are submitted to USB Driver*/ 
#define USB_ALIGN  CACHE_ALIGN



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
