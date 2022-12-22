/**
 * @file user_adc.c
 * @brief 
 * @author HLY (1425075683@qq.com)
 * @version 1.0
 * @date 2022-12-20
 * @copyright Copyright (c) 2022
 * @attention 
 * @par �޸���־:
 * Date       Version Author  Description
 * 2022-12-20 1.0     HLY     first version
 */
/* Includes ------------------------------------------------------------------*/

/* Private includes ----------------------------------------------------------*/
#include <rtthread.h>
#include <rtdevice.h>
#include <main.h>
#include <dma.h>
/*ulog include*/
#define LOG_TAG              "int measure" 
#define LOG_LVL              DBG_INFO
#include <ulog.h>
/* Private typedef -----------------------------------------------------------*/
/** 
  * @brief ADC1ͨ��ֵ����
  */  
typedef enum
{
  VREFINT_CHANNEL = 0x00,
  TEMP_CHANNEL,
}ADC1_CHANNEL;
/* Private define ------------------------------------------------------------*/
#define ADC3_CHANNEL_NUM 2  //ADC3����2ͨ��
#define ADC3_BUFFER_SIZE 8  //ÿ��ͨ����32��, ������ƽ��
#define ADC3_BUFFER_LEN  ADC3_BUFFER_SIZE * ADC3_CHANNEL_NUM

#define REAL_TIME_REFRESH 0 //�Ƿ�ʵʱˢ�»�����
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
extern ADC_HandleTypeDef hadc3;
rt_uint16_t* adc3_data = RT_NULL;
/* Private function prototypes -----------------------------------------------*/
extern void MX_ADC3_Init(void);
/**
  * @brief  ADC��ʼ��
  * @param  None
  * @retval int 
  * @note   None
*/
static int adc_init(void)
{
    /* DMA controller clock enable */
    __HAL_RCC_DMA1_CLK_ENABLE();
    /* DMA1_Stream3_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(DMA1_Stream3_IRQn, 15, 0);
    HAL_NVIC_EnableIRQ(DMA1_Stream3_IRQn);
    MX_ADC3_Init();
 
    /* У׼ ADC������ƫ��У׼ */ 
    if (HAL_ADCEx_Calibration_Start(&hadc3, ADC_CALIB_OFFSET_LINEARITY, ADC_SINGLE_ENDED) != HAL_OK) 
    { 
      Error_Handler();
    }

    adc3_data = (rt_uint16_t *)rt_malloc_align(ADC3_BUFFER_LEN,16);
    
    if (HAL_ADC_Start_DMA(&hadc3, (uint32_t *)adc3_data, ADC3_BUFFER_LEN) != HAL_OK)
    {
        Error_Handler();
    }

    rt_hw_us_delay(500000);
    
    return RT_EOK;
}
INIT_DEVICE_EXPORT(adc_init);
/**
  * @brief  ��ȡ MCU�ڲ��ο���ѹ���¶�
  * @param  None
  * @retval int 
  * @note   None
*/
int get_vref_temp(void)
{
    rt_uint16_t vref_mv,temp_mv; 
    rt_uint32_t vref_value,temp_value;
    rt_uint32_t sum = 0;
#if (REAL_TIME_REFRESH == 0)
    //ʹ��ʱ��ˢ�»���
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, adc3_data, ADC3_BUFFER_LEN);
#endif /* (REAL_TIME_REFRESH == 0) */
    for(int i = VREFINT_CHANNEL; i < ADC3_BUFFER_LEN; i += ADC3_CHANNEL_NUM)
    {
      sum += adc3_data[i];
    }
    vref_value = sum / ADC3_BUFFER_SIZE;
    
    sum = 0;
    for(int i = TEMP_CHANNEL; i < ADC3_BUFFER_LEN; i += ADC3_CHANNEL_NUM)
    {
      sum += adc3_data[i];
    }
    temp_value = sum / ADC3_BUFFER_SIZE;
    
    LOG_I("Vref = %u, Temp = %u", vref_value, temp_value);
    
    // Calculating Vref voltage
    vref_mv = __HAL_ADC_CALC_VREFANALOG_VOLTAGE(vref_value, ADC_RESOLUTION_16B);
    LOG_I("Vref voltages = %u mV", vref_mv);
    
    // Calculate Temperature
    LOG_I("Temperature = %d Degree C",
    __HAL_ADC_CALC_TEMPERATURE(vref_mv, temp_value, ADC_RESOLUTION_16B));
    return RT_EOK;
}
/* ������ msh �����б��� */
MSH_CMD_EXPORT(get_vref_temp, get MCU vref and temp);
#if (REAL_TIME_REFRESH == 0)
/**
  * @brief  ADC_DMA �����ص�����
  * @param  hadc
  * @retval None
  * @note   ADCת�������ж��а����ݴ浽�����ǰ�벿��
            ping-pong�洢
*/
void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* hadc)
{
    /* Invalidate Data Cache to get the updated content of the SRAM on the first half of the ADC converted data buffer */
    if(hadc->Instance == ADC3) 
    {
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, adc3_data, ADC3_BUFFER_LEN);
    }
}
/**
  * @brief  ADC_DMA ת����ɻص�����
  * @param  hadc
  * @retval None
  * @note   ADCת������ж��а����ݴ浽����ĺ�벿��
*/
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    /* Invalidate Data Cache to get the updated content of the SRAM on the second half of the ADC converted data buffer */
    if(hadc->Instance == ADC3) 
    {
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, adc3_data + ADC3_BUFFER_LEN / 2, ADC3_BUFFER_LEN);
    }
}
#endif /* (REAL_TIME_REFRESH == 0) */