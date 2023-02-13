/**
  ******************************************************************************
  * @file    drv_led.H
  * @brief   drv_led
  ******************************************************************************
  * @attention https://blog.csdn.net/weixin_35698805/article/details/112614144
  * @author
  ��LED.C�������и��죬ʵ��ģʽö�٣����ӱ�ʶ�ȡ����ӻ�ȡ��ǰLEDģʽ����       2022.04.18
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DRV_LED_H
#define __DRV_LED_H
/*
ʹ�÷�����
static iLed_t Led1;
led_creat(&Led1,led_1_on, led_1_off);
*/
/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* Exported types ------------------------------------------------------------*/
typedef struct iLed_t
{
  uint8_t state;                             // �źŵƵ�ǰ��״̬
  uint16_t *mode;                            // ����ָ����ǰ������˸�����еĵڼ�����Ա
  uint16_t modeLen;                          // ÿ��ģʽ�ĳ���
  uint16_t tickCnt;                          // tick����
  uint16_t modeIndex;                        // һ�������ڵ���˸����
  int32_t times;                             // ִ�д���
  void (*on)(void);                          // led��
  void (*off)(void);                         // led��
  void (*overCallBack)(struct iLed_t *hled); // led��˸�����ص�����
  struct iLed_t *next;                       // ��һ��led��
} iLed_t;
/* Exported constants --------------------------------------------------------*/
#define LED_TICK_TIME 1                     // �����������õ�ʱ����(��λ:ms)
/* Exported macro ------------------------------------------------------------*/

/* Exported variables ---------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
extern void led_tick_loop(void);
extern void led_loop(void);
extern void led_tick(void);

extern int8_t led_creat(iLed_t *handle, void (*on)(void), void (*off)(void));
extern void led_set_mode(iLed_t *handle, uint16_t *mode, uint16_t modeLen, int16_t times);
#endif /* __DRV_LED_H */