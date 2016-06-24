/*
 * TIM.c
 *
 *  Created on: 2016/06/05
 *      Author: evaota
 */
#include "../Inc/MW_TIM.h"

static TIM_HandleTypeDef htim1 = {
  .Instance = TIM1,
  .Init.Prescaler = 0,
  .Init.CounterMode = TIM_COUNTERMODE_UP,
  .Init.Period = 0,
  .Init.ClockDivision = TIM_CLOCKDIVISION_DIV1,
  .Init.RepetitionCounter = 0
};
static TIM_HandleTypeDef htim2 = {
  .Instance = TIM2,
  .Init.Prescaler = 0,
  .Init.CounterMode = TIM_COUNTERMODE_UP,
  .Init.Period = 0,
  .Init.ClockDivision = TIM_CLOCKDIVISION_DIV1,
  .Init.RepetitionCounter = 0
};

static TIM_HandleTypeDef *timid[2] = {
  &htim1,
  &htim2
};

static TIM_ClockConfigTypeDef sClockSourceConfig1 = {
  .ClockSource = TIM_CLOCKSOURCE_INTERNAL
};
static TIM_ClockConfigTypeDef sClockSourceConfig2 = {
  .ClockSource = TIM_CLOCKSOURCE_INTERNAL
};

static TIM_ClockConfigTypeDef *clockconfigid[2] = {
  &sClockSourceConfig1,
  &sClockSourceConfig2,
};
static TIM_MasterConfigTypeDef sMasterConfig1 = {
  .MasterOutputTrigger = TIM_TRGO_RESET,
  .MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE,
};

static TIM_MasterConfigTypeDef sMasterConfig2 = {
  .MasterOutputTrigger = TIM_TRGO_RESET,
  .MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE,
};
static TIM_MasterConfigTypeDef *masterconfigid[2] = {
  &sMasterConfig1,
  &sMasterConfig2
};


void MW_SetTIMPrescaler(timid_t id,uint32_t Prescaler)
{
  assert_param(IS_TIM_ID(id));
  timid[(uint32_t)id]->Init.Prescaler = Prescaler;
}
void MW_SetTIMCounterMode(timid_t id,uint32_t CounterMode)
{
  assert_param(IS_TIM_ID(id));
  timid[(uint32_t)id]->Init.CounterMode = CounterMode;
}
void MW_SetTIMPeriod(timid_t id,uint32_t Period)
{
  assert_param(IS_TIM_ID(id));
  timid[(uint32_t)id]->Init.Period = Period;
}
void MW_SetTIMClockDivision(timid_t id,uint32_t ClockDivision)
{
  assert_param(IS_TIM_ID(id));
  timid[(uint32_t)id]->Init.ClockDivision = ClockDivision;
}

void MW_SetTIMClockSource(timid_t id,uint32_t ClockSource)
{
  assert_param(IS_TIM_ID(id));
  clockconfigid[(uint32_t)id]->ClockSource = ClockSource;
}

void MW_SetTIMMasterOutputTrigger(timid_t id,uint32_t MasterOutputTrigger)
{
  assert_param(IS_TIM_ID(id));
  masterconfigid[(uint32_t)id]->MasterOutputTrigger = MasterOutputTrigger;
}
void MW_SetTIMMasterSlaveMode(timid_t id,uint32_t MasterSlaveMode)
{
  assert_param(IS_TIM_ID(id));
  masterconfigid[(uint32_t)id]->MasterSlaveMode = MasterSlaveMode;
}

/* TIMx init function */
void MW_TIMInit(timid_t id)
{
  assert_param(IS_TIM_ID(id));
  if (HAL_TIM_Base_Init(timid[(uint32_t)id]) != HAL_OK)
    {
      Error_Handler();
    }
  if (HAL_TIM_ConfigClockSource(timid[(uint32_t)id], clockconfigid[(uint32_t)id]) != HAL_OK)
    {
      Error_Handler();
    }
  if (HAL_TIMEx_MasterConfigSynchronization(timid[(uint32_t)id], masterconfigid[(uint32_t)id]) != HAL_OK)
    {
      Error_Handler();
    }
}
void MW_TIMStart(timid_t id)
{
  assert_param(IS_TIM_ID(id));
  if (HAL_TIM_Base_Start(timid[(uint32_t)id]) != HAL_OK)
    {
      //      Error_Handler();
    }
}

void MW_TIMStop(timid_t id)
{
  assert_param(IS_TIM_ID(id));
  if (HAL_TIM_Base_Stop(timid[(uint32_t)id]) != HAL_OK)
    {
      //Error_Handler();
    }
}

uint32_t MW_GetTIMCounter(timid_t id)
{
  assert_param(IS_TIM_ID(id));
  return __HAL_TIM_GET_COUNTER(timid[(uint32_t)id]);
}

void TIM1_UP_IRQHandler(void)
{
  MW_ResetTIMxFlag(TIM1ID);
  MW_TIM1Hadler();
}

void TIM2_IRQHandler(void)
{
  MW_ResetTIMxFlag(TIM2ID);
  MW_TIM2Hadler();
}

void MW_ResetTIMxFlag(timid_t id)
{
  assert_param(IS_TIM_ID(id));
  HAL_TIM_IRQHandler(timid[(uint32_t)id]);
}

void MW_EnableTIMHandle(timid_t id)
{
  __HAL_TIM_ENABLE_IT(timid[(uint32_t)id], TIM_IT_UPDATE);	
  HAL_NVIC_SetPriority(TIM1_UP_IRQn, 0, 0);			
}

void MW_DisableTIMHandle(timid_t id)
{
  __HAL_TIM_DISABLE_IT(timid[(uint32_t)id], TIM_IT_UPDATE);
}

