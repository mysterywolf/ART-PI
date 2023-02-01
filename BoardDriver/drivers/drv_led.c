/**
  ******************************************************************************
  * @file    led.c
  * @brief   led
  ******************************************************************************
  * @attention https://blog.csdn.net/weixin_35698805/article/details/112614144
  * @author HLY
  ��LED.C�������и��죬ʵ��ģʽö�٣����ӱ�ʶ�ȡ���ӻ�ȡ��ǰLEDģʽ����       2022.04.18
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "drv_led.h"
/* Private includes ----------------------------------------------------------*/
#include "gpio.h"
/* Private define ------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
iLed_t *head_led = NULL;
uint32_t _led_ticks = 0;
/* Private function prototypes -----------------------------------------------*/
/**
 * @brief  led_init��LED��ʼ��
 * @param  iLed_t *handle��   LED�ṹ��ָ��
 * @param  void (*on)(void)�� LED��������ָ��
 * @param  void (*off)(void)��LED�㰵����ָ��
 * @retval None.
 * @note   ��Ҫ��ע��led
 */
void led_init(iLed_t *handle, void (*on)(void), void (*off)(void))
{
    rt_memset(handle, 0, sizeof(struct iLed_t)); // ��ʼ���ṹ���ڲ�����

    handle->on = on;
    handle->off = off;
    handle->modeIndex = 0;
    handle->modeLen = 0;
    handle->tickCnt = 0;
    handle->state = 0;

    handle->off();
}
/**
  * @brief  led_reg_call_back��LEDִ����ɻص�����
  * @param  iLed_t *handle��   LED�ṹ��ָ��
  * @param  void (*overCallBack)(void)���ص�����ָ��
  * @retval None.
  * @note   ִ����ɻص������Բ�ʹ�ã�
            ��һ��led��ִ�����֮�����ô˺���
*/
void led_reg_call_back(iLed_t *handle, void (*overCallBack)(iLed_t *hled))
{
    handle->overCallBack = overCallBack;
}
/**
 * @brief  led_start������led��
 * @param  iLed_t *handle��   LED�ṹ��ָ��
 * @retval
 * @note   None.
 */
int8_t led_start(iLed_t *handle)
{
    struct iLed_t *target = head_led;

    while (target)
    {
        if (target == handle)
            return -1;
        target = target->next;
    }
    handle->next = head_led;
    head_led = handle;
    return 0;
}
/**
 * @brief  led_creat������led
 * @param  None.
 * @retval None.
 * @note   ע�Ტ����
 */
int8_t led_creat(iLed_t *handle, void (*on)(void), void (*off)(void))
{
    led_init(handle, on, off);
    return led_start(handle);
}
/**
 * @brief  ����ledģʽ
 * @param  int16_t times��������ִ�д�������ֵ����ִ��
 * @retval None.
 * @note   None.
 */
void led_set_mode(iLed_t *handle, uint16_t *mode, uint16_t modeLen, int16_t times)
{
    struct iLed_t *target = head_led;

    while (target)
    {
        if (target == handle)
        {
            target->mode = mode;
            target->times = times;
            target->modeLen = modeLen / sizeof(mode[0]);
            break;
        }
        else
        {
            target = target->next;
        }
    }
}

// led��ֹͣ
void led_stop(iLed_t *handle)
{
    struct iLed_t **curr;
    for (curr = &head_led; *curr;)
    {
        struct iLed_t *entry = *curr;
        if (entry == handle)
        {
            *curr = entry->next;
        }
        else
            curr = &entry->next;
    }
}

// led����
void led_switch(iLed_t *handle, char state)
{
    switch (state)
    {
    case 1:
        handle->on();
        handle->state = state;
        break;
    case 0:
        handle->off();
        handle->state = state;
        break;
    default:
        break;
    }
}

// ������ת
void led_toggle(iLed_t *handle)
{
    handle->state = !handle->state;
    led_switch(handle, handle->state);
}

// led��Ҫ�Ŀ����߼�
void led_handle(iLed_t *handle)
{
    if ((handle->times != 0) && (handle->modeLen > 0))
    {
        handle->tickCnt++;
        if ((handle->tickCnt * LED_TICK_TIME) <= (handle->mode[handle->modeIndex])) // ִ�д���С�ڵ���������˸����
        {
            led_switch(handle, !(handle->modeIndex % 2));
        }
        else // ���¸�ֵ��������һ����
        {
            handle->tickCnt = 0;
            handle->modeIndex++;
            if ((handle->modeIndex) >= (handle->modeLen)) // ���ڴ�������
            {
                handle->modeIndex = 0;
                if (handle->times > 0) // ִ�д���
                {
                    handle->times--;
                    if (handle->times == 0) // ִ�д�������
                    {
                        if (handle->overCallBack != NULL)
                        {
                            handle->overCallBack(handle);
                        }
                    }
                }
            }
        }
    }
}
/*************************ʹ�÷���1***********************************/
// ���Է���ϵͳѭ����
void led_loop(void)
{
    struct iLed_t *target;
    if (_led_ticks >= LED_TICK_TIME)
    {
        for (target = head_led; target; target = target->next) // ͨ�������ѯ
        {
            led_handle(target);
        }
        _led_ticks = 0;
    }
}
// ϵͳ�δ�ʱ����1msִ��һ��
void led_tick()
{
    _led_ticks++;
}
/*************************ʹ�÷���2***********************************/
// ��ʱ���øú��� ��������Ϊ LED_TICK_TIME
void led_tick_loop(void)
{
    struct iLed_t *target;

    for (target = head_led; target; target = target->next) // ͨ�������ѯ
    {
        led_handle(target);
    }
}
