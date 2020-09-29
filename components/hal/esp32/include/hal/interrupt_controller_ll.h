// Copyright 2020 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once 

#include <stdint.h>
#include "soc/soc_caps.h"
#include "soc/soc.h"
#include "xtensa/xtensa_api.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief enable interrupts specified by the mask
 * 
 * @param mask bitmask of interrupts that needs to be enabled 
 */
static inline void intr_cntrl_ll_enable_interrupts(uint32_t mask) 
{
    xt_ints_on(mask);
}

/**
 * @brief disable interrupts specified by the mask
 * 
 * @param mask bitmask of interrupts that needs to be disabled 
 */
static inline void intr_cntrl_ll_disable_interrupts(uint32_t mask)
{
    xt_ints_off(mask);
}

/**
 * @brief checks if given interrupt number has a valid handler
 * 
 * @param intr interrupt number ranged from 0 to 31
 * @param cpu cpu number ranged betweeen 0 to SOC_CPU_CORES_NUM - 1
 * @return true for valid handler, false otherwise 
 */
static inline bool intr_cntrl_ll_has_handler(uint8_t intr, uint8_t cpu)
{
    return xt_int_has_handler(intr, cpu);
}

/**
 * @brief sets interrupt handler and optional argument of a given interrupt number 
 * 
 * @param intr interrupt number ranged from 0 to 31
 * @param handler handler invoked when an interrupt occurs
 * @param arg optional argument to pass to the handler
 */
static inline void intr_cntrl_ll_set_int_handler(uint8_t intr, interrupt_handler_t handler, void * arg)
{
    xt_set_interrupt_handler(intr, (xt_handler)handler, arg);
}

/**
 * @brief Gets argument passed to handler of a given interrupt number 
 * 
 * @param intr interrupt number ranged from 0 to 31
 * 
 * @return argument used by handler of passed interrupt number
 */
static inline void * intr_cntrl_ll_get_int_handler_arg(uint8_t intr)
{
    return xt_get_interrupt_handler_arg(intr);
}

/**
 * @brief Disables interrupts that are not located in iram
 * 
 * @param newmask mask of interrupts needs to be disabled
 * @return oldmask where to store old interrupts state
 */
static inline uint32_t intr_cntrl_ll_disable_int_mask(uint32_t newmask) 
{
    return xt_int_disable_mask(newmask);
}

/**
 * @brief Enables interrupts that are not located in iram
 * 
 * @param newmask mask of interrupts needs to be disabled
 */
static inline void intr_cntrl_ll_enable_int_mask(uint32_t newmask)
{
    xt_int_enable_mask(newmask);
}

#ifdef __cplusplus
}
#endif