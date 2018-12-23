//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

#define BLINK_PORT_NUMBER               (3)
#define BLINK_PIN_NUMBER                (12)
#define BLINK_ACTIVE_LOW                (0)


#define BLINK_GPIOx(_N)                 ((GPIO_TypeDef *)(GPIOA_BASE + (GPIOB_BASE-GPIOA_BASE)*(_N)))
#define BLINK_PIN_MASK(_N)              (1 << (_N))
#define BLINK_RCC_MASKx(_N)             (RCC_AHB1ENR_GPIOAEN << (_N))

// ----------------------------------------------------------------------------

void
blink_led_on(void)
{
    HAL_GPIO_WritePin(BLINK_GPIOx(BLINK_PORT_NUMBER),
        BLINK_PIN_MASK(BLINK_PIN_NUMBER), GPIO_PIN_SET);
}

void
blink_led_off(void)
{
    HAL_GPIO_WritePin(BLINK_GPIOx(BLINK_PORT_NUMBER),
        BLINK_PIN_MASK(BLINK_PIN_NUMBER), GPIO_PIN_RESET);
}


void
blink_led_init()
{
  // Enable GPIO Peripheral clock
  RCC->AHB1ENR |= BLINK_RCC_MASKx(BLINK_PORT_NUMBER);

  GPIO_InitTypeDef GPIO_InitStructure;

  // Configure pin in output push/pull mode
  GPIO_InitStructure.Pin = BLINK_PIN_MASK(BLINK_PIN_NUMBER);
  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
  GPIO_InitStructure.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(BLINK_GPIOx(BLINK_PORT_NUMBER), &GPIO_InitStructure);

  // Start with led turned off
  blink_led_off();
}

// ----------------------------------------------------------------------------
