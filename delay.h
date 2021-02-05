#ifndef DELAY_H
#define DELAY_H

#include "MKL25Z4.h"

//Systick Delay
volatile uint32_t msTicks;
//SysTick interrupt handler
void SysTick_Handler() {msTicks++; }

__INLINE static void delay(uint32_t delayTicks){
	uint32_t currentTicks = msTicks;
	while((msTicks - currentTicks) < delayTicks) __wfi();
}

	//Configure Systick delay
void init_delay(int time){
	//Enable sysTick interrupts every 1ms
	SysTick_Config(SystemCoreClock/time);
}

//Disable SysTick interrupts
void disable_delay(){
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

//Enable SysTick Interrupts

void enable_delay(){
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}

#endif