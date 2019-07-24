/*******************************************************************************
* File Name: cycfg_pins.h
*
* Description:
* Pin configuration
* This file was automatically generated and should not be modified.
* 
********************************************************************************
* Copyright 2017-2019 Cypress Semiconductor Corporation
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
********************************************************************************/

#if !defined(CYCFG_PINS_H)
#define CYCFG_PINS_H

#include "cycfg_notices.h"
#include "cy_gpio.h"

#if defined(__cplusplus)
extern "C" {
#endif

#define LED_BLUE_PORT GPIO_PRT12
#define LED_BLUE_PIN 4U
#define LED_BLUE_NUM 4U
#define LED_BLUE_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define LED_BLUE_INIT_DRIVESTATE 0
#ifndef ioss_0_port_12_pin_4_HSIOM
	#define ioss_0_port_12_pin_4_HSIOM HSIOM_SEL_GPIO
#endif
#define LED_BLUE_HSIOM ioss_0_port_12_pin_4_HSIOM
#define LED_BLUE_IRQ ioss_interrupts_gpio_12_IRQn
#define LED_RED_PORT GPIO_PRT12
#define LED_RED_PIN 5U
#define LED_RED_NUM 5U
#define LED_RED_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define LED_RED_INIT_DRIVESTATE 0
#ifndef ioss_0_port_12_pin_5_HSIOM
	#define ioss_0_port_12_pin_5_HSIOM HSIOM_SEL_GPIO
#endif
#define LED_RED_HSIOM ioss_0_port_12_pin_5_HSIOM
#define LED_RED_IRQ ioss_interrupts_gpio_12_IRQn

extern const cy_stc_gpio_pin_config_t LED_BLUE_config;
extern const cy_stc_gpio_pin_config_t LED_RED_config;

void init_cycfg_pins(void);

#if defined(__cplusplus)
}
#endif


#endif /* CYCFG_PINS_H */
