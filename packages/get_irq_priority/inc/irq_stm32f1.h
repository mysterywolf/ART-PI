/**
 * @file irq_stm32f1.h
 * @brief
 * @author HLY (1425075683@qq.com)
 * @version 1.0
 * @date 2022-12-27
 * @copyright Copyright (c) 2022
 * @attention
 * @par 修改日志:
 * Date       Version Author  Description
 * 2022-12-27 1.0     HLY     first version
 */
/* Exported constants --------------------------------------------------------*/
  [0]   = "WWDG_IRQn",              /*!< Window WatchDog Interrupt ( wwdg1_it, wwdg2_it)                   */
  [1]   = "PVD_IRQn",               /*!< PVD through EXTI Line detection Interrupt                         */
  [2]   = "TAMP_STAMP_IRQn",        /*!< Tamper and TimeStamp interrupts through the EXTI line             */
  [3]   = "RTC_WKUP_IRQn",          /*!< RTC Wakeup interrupt through the EXTI line                        */
  [4]   = "FLASH_IRQn",             /*!< FLASH global Interrupt                                            */
  [5]   = "RCC_IRQn",               /*!< RCC global Interrupt                                              */
  [6]   = "EXTI0_IRQn",             /*!< EXTI Line0 Interrupt                                              */
  [7]   = "EXTI1_IRQn",             /*!< EXTI Line1 Interrupt                                              */
  [8]   = "EXTI2_IRQn",             /*!< EXTI Line2 Interrupt                                              */
  [9]   = "EXTI3_IRQn",             /*!< EXTI Line3 Interrupt                                              */
  [10]  = "EXTI4_IRQn",             /*!< EXTI Line4 Interrupt                                              */
  [11]  = "DMA1_Stream0_IRQn",      /*!< DMA1 Stream 0 global Interrupt                                    */
  [12]  = "DMA1_Stream1_IRQn",      /*!< DMA1 Stream 1 global Interrupt                                    */
  [13]  = "DMA1_Stream2_IRQn",      /*!< DMA1 Stream 2 global Interrupt                                    */
  [14]  = "DMA1_Stream3_IRQn",      /*!< DMA1 Stream 3 global Interrupt                                    */
  [15]  = "DMA1_Stream4_IRQn",      /*!< DMA1 Stream 4 global Interrupt                                    */
  [16]  = "DMA1_Stream5_IRQn",      /*!< DMA1 Stream 5 global Interrupt                                    */
  [17]  = "DMA1_Stream6_IRQn",      /*!< DMA1 Stream 6 global Interrupt                                    */
  [18]  = "ADC_IRQn",               /*!< ADC1 and  ADC2 global Interrupts                                  */
#if defined (STM32F102x6) || defined (STM32F102xB)
  [19]  = "USB_HP_IRQn",            /*!< USB Device High Priority                                          */
  [20]  = "USB_LP_IRQn",            /*!< USB Device Low Priority                                           */
#else
  [19]  = "CAN1_TX_IRQn",           /*!< CAN1 TX Interrupt                                                 */
  [20]  = "CAN1_RX0_IRQn",          /*!< CAN1 RX0 Interrupt                                                */
#endif /* defined (STM32F102x6) || defined (STM32F102xB) */
  [21]  = "CAN1_RX1_IRQn",          /*!< CAN1 RX1 Interrupt                                                */
  [22]  = "CAN1_SCE_IRQn",          /*!< CAN1 SCE Interrupt                                                */
  [23]  = "EXTI9_5_IRQn",           /*!< External Line[9:5] Interrupts                                     */
#if defined (STM32F101xB) || defined (STM32F101xE) || defined (STM32F101xG) || defined (STM32F102x6) || defined (STM32F102xB) || defined (STM32F103x6)
  [24] = "TIM9_IRQn",               /*!< TIM9 global Interrupt                                             */
  [25] = "TIM10_IRQn",              /*!< TIM10 global Interrupt                                            */
  [26] = "TIM11_IRQn",              /*!< TIM11 global interrupt                                            */
#else
  [24]  = "TIM1_BRK_TIM9_IRQn",     /*!< TIM1 Break interrupt and TIM9 global interrupt                    */
  [25]  = "TIM1_UP_TIM10_IRQn",     /*!< TIM1 Update Interrupt and TIM10 global interrupt                  */
  [26]  = "TIM1_TRG_COM_TIM11_IRQn",/*!< TIM1 Trigger and Commutation Interrupt and TIM11 global interrupt */
#endif /* defined (STM32F101xB) || defined (STM32F101xE) || defined (STM32F101xG) || defined (STM32F102x6) || defined (STM32F102xB) || defined (STM32F103x6) */
  [27]  = "TIM1_CC_IRQn",           /*!< TIM1 Capture Compare Interrupt                                    */
  [28]  = "TIM2_IRQn",              /*!< TIM2 global Interrupt                                             */
  [29]  = "TIM3_IRQn",              /*!< TIM3 global Interrupt                                             */
  [30]  = "TIM4_IRQn",              /*!< TIM4 global Interrupt                                             */
  [31]  = "I2C1_EV_IRQn",           /*!< I2C1 Event Interrupt                                              */
  [32]  = "I2C1_ER_IRQn",           /*!< I2C1 Error Interrupt                                              */
  [33]  = "I2C2_EV_IRQn",           /*!< I2C2 Event Interrupt                                              */
  [34]  = "I2C2_ER_IRQn",           /*!< I2C2 Error Interrupt                                              */
  [35]  = "SPI1_IRQn",              /*!< SPI1 global Interrupt                                             */
  [36]  = "SPI2_IRQn",              /*!< SPI2 global Interrupt                                             */
  [37]  = "USART1_IRQn",            /*!< USART1 global Interrupt                                           */
  [38]  = "USART2_IRQn",            /*!< USART2 global Interrupt                                           */
  [39]  = "USART3_IRQn",            /*!< USART3 global Interrupt                                           */
  [40]  = "EXTI15_10_IRQn",         /*!< External Line[15:10] Interrupts                                   */
  [41]  = "RTC_Alarm_IRQn",         /*!< RTC Alarm (A and B) through EXTI Line Interrupt                   */
#if defined (STM32F100xB) || defined (STM32F100xE) || defined (STM32F101x6)
  [42]  = "CEC_IRQn",               /*!< HDMI-CEC Interrupt                                   */
#else
  [42]  = "OTG_FS_WKUP_IRQn",       /*!< USB OTG FS Wakeup through EXTI line interrupt                     */
#endif /* defined (STM32F100xB) || defined (STM32F100xE) || defined (STM32F101x6) */
  [43]  = "TIM8_BRK_TIM12_IRQn",    /*!< TIM8 Break Interrupt and TIM12 global interrupt                   */
  [44]  = "TIM8_UP_TIM13_IRQn",     /*!< TIM8 Update Interrupt and TIM13 global interrupt                  */
#if defined (STM32F103xB) || defined (STM32F103xE) || defined (STM32F103xG) || defined (STM32F105xC) || defined (STM32F107xC)
  [45]  = "TIM14_IRQn",             /*!< TIM14 global Interrupt                               */
#else
  [45]  = "TIM8_TRG_COM_TIM14_IRQn",/*!< TIM8 Trigger and Commutation Interrupt and TIM14 global interrupt */
#endif /* defined (STM32F103xB) || defined (STM32F103xE) || defined (STM32F103xG) || defined (STM32F105xC) || defined (STM32F107xC) */
  [46]  = "TIM8_CC_IRQn",           /*!< TIM8 Capture Compare Interrupt                                    */
  [47]  = "DMA1_Stream7_IRQn",      /*!< DMA1 Stream7 Interrupt                                            */
  [48]  = "FMC_IRQn",               /*!< FMC global Interrupt                                              */
  [49]  = "SDIO_IRQn",              /*!< SDIO global Interrupt                                             */
  [50]  = "TIM5_IRQn",              /*!< TIM5 global Interrupt                                             */
  [51]  = "SPI3_IRQn",              /*!< SPI3 global Interrupt                                             */
  [52]  = "UART4_IRQn",             /*!< UART4 global Interrupt                                            */
  [53]  = "UART5_IRQn",             /*!< UART5 global Interrupt                                            */
  [54]  = "TIM6_DAC_IRQn",          /*!< TIM6 global and DAC1&2 underrun error  interrupts                 */
  [55]  = "TIM7_IRQn",              /*!< TIM7 global interrupt                                             */
  [56]  = "DMA2_Stream0_IRQn",      /*!< DMA2 Stream 0 global Interrupt                                    */
  [57]  = "DMA2_Stream1_IRQn",      /*!< DMA2 Stream 1 global Interrupt                                    */
  [58]  = "DMA2_Stream2_IRQn",      /*!< DMA2 Stream 2 global Interrupt                                    */
  [59]  = "DMA2_Stream3_IRQn",      /*!< DMA2 Stream 3 global Interrupt                                    */
  [60]  = "DMA2_Stream4_IRQn",      /*!< DMA2 Stream 4 global Interrupt                                    */
  [61]  = "ETH_IRQn",               /*!< Ethernet global Interrupt                                         */
  [62]  = "ETH_WKUP_IRQn",          /*!< Ethernet Wakeup through EXTI line Interrupt                       */
  [63]  = "CAN2_TX_IRQn ",          /*!< CAN2 TX Interrupt                                                 */
  [64]  = "CAN2_RX0_IRQn",          /*!< CAN2 RX0 Interrupt                                                */
  [65]  = "CAN2_RX1_IRQn",          /*!< CAN2 RX1 Interrupt                                                */
  [66]  = "CAN2_SCE_IRQn",          /*!< CAN2 SCE Interrupt                                                */
  [67]  = "OTG_FS_IRQn",            /*!< USB OTG FS global Interrupt                                       */
