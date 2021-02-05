#include "MKL25Z4.h"
#include "delay.h"
#include "segment_1_on.h"
#include "Increment_decrement_switches.h"
#define Mask(x) (1UL << (x))

const uint32_t Interrupt_Pin [3] = {1,2,12};
int Combinations[3] = {0x21, 0x92, 0x63};				//passcode combination for the 3 lockers
int Segment_display_number = 0;												
int Segment_display_2_number = 0;
int Final_Number;
int Selection_switch = 0;
int Increment_switch = 0;
int Decrement_switch = 0;
int Selection_check_switch = 0;
int selecter = 0;
int Locker_display_number = 0;

void IO_Config(void){

	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;				//Enable clock for PORTA
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;				//Enable clock for PORTB
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;				//enable clock for PORTC
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;				//Enable clock for PORTE
	
	PORTB->PCR[0] |= PORT_PCR_MUX(1);					//Pin 0 PORT B as GPIO
	PORTB->PCR[1] |= PORT_PCR_MUX(1);					//Pin 1 PORT B as GPIO
	PORTB->PCR[2] |= PORT_PCR_MUX(1);					//Pin 2 PORT B as GPIO
	
	/*************************************
	Turning on the ports for the first 7 segment display
	*************************************/
	PORTC->PCR[0]	|= PORT_PCR_MUX(1);					//Pin 0 PORTC as GPIO
	PORTC->PCR[3]	|= PORT_PCR_MUX(1);					//Pin 3 PORTC as GPIO
	PORTC->PCR[4]	|= PORT_PCR_MUX(1);					//Pin 4 PORTC as GPIO
	PORTC->PCR[5]	|= PORT_PCR_MUX(1);					//Pin 5 PORTC as GPIO
	PORTC->PCR[6]	|= PORT_PCR_MUX(1);					//Pin 6 PORTC as GPIO
	PORTC->PCR[7]	|= PORT_PCR_MUX(1);					//Pin 7 PORTC as GPIO
	PORTC->PCR[10]|= PORT_PCR_MUX(1);					//Pin 10 PORTC as GPIO
	
	/*************************************
	Turning on the ports for the second 7 segment display
	*************************************/
	
	PORTE->PCR[30] |= PORT_PCR_MUX(1);				//Pin 30 PORT E as GPIO
	PORTE->PCR[29] |= PORT_PCR_MUX(1);				//Pin 29 PORT E as GPIO
	PORTE->PCR[23] |= PORT_PCR_MUX(1);				//Pin 23 PORT E as GPIO
	PORTE->PCR[22] |= PORT_PCR_MUX(1);				//Pin 22 PORT E as GPIO
	PORTE->PCR[21] |= PORT_PCR_MUX(1);				//Pin 21 PORT E as GPIO
	PORTE->PCR[20] |= PORT_PCR_MUX(1);				//Pin 20 PORT E as GPIO
	PORTE->PCR[5] |= PORT_PCR_MUX(1);					//Pin 5 PORT E as GPIO
	
	PTB->PDDR |= (1UL << 0) | (1UL << 1) | (1UL << 2);		//Enable pin 0,1,2 as output for my LEDs to show which locker is being unlocked
	PTC->PDDR |= (1UL << 0) | (1UL << 3) | (1UL << 4) | (1UL << 5) | (1UL << 6) | (1UL << 7) | (1UL << 10);	//Enable pin 0,3,4,5,6,7,10 as output this allows me to turn on my first 7 segment display
	PTE->PDDR |= (1UL << 30) | (1UL << 29) | (1UL << 23) | (1UL << 22) | (1UL << 21) | (1UL << 20) | (1UL << 5); //Enable pin 30,29,23,22,21,20,5 as output this allows me to turn on my second 7 segment display
		
}

void Interrupt_Setup(void){
	int i;
	for(i=0;i<3;i++){
		PORTA->PCR[Interrupt_Pin[i]] |= PORT_PCR_MUX(1) | PORT_PCR_IRQC(9) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK; // 	Set pin 1 2 & 12 of port A to be an interrupt on  falling edge
		PTA->PDDR &= ~Mask(Interrupt_Pin[i]);		//Makes the interrupt pin an input
	}																		
	NVIC_EnableIRQ(PORTA_IRQn);								//enable_delay interrupt on PORT A
	NVIC_SetPriority(PORTA_IRQn,2);						//sets to non maskable interrupt
}


void PORTA_IRQHandler(void){
	
	int j;
	for(j=0;j<0x1ffff;j++){
		__ASM("nop");							//assebmly delay loop to stop deboucing 
	}
	if(PORTA->ISFR & (Mask(Interrupt_Pin[0]))){				//If the switch on PORT A pin 1 is pressed, then do the following.
		Increment_switch = 1;
	}
	if(PORTA->ISFR & (Mask(Interrupt_Pin[1]))){				//If the switch on PORT A pin 2 is pressed, then do the following.
		Decrement_switch = 1;
	}
	if(PORTA->ISFR & (Mask(Interrupt_Pin[2]))){				//If tge switch on PORT A pin 12 is pressen, then do the following.
		Selection_check_switch = 1;
	}
	
	PORTA->ISFR = 0xffffffff;		//resets the ISFR
	
}
void Display_final_number(void){			//Checks to see if the combination was correct or not
	int i;
	Final_Number = Segment_display_number << 4;							//shifts the first number by 4 to make it the most significant bit
	Final_Number = Final_Number | Segment_display_2_number;	//Or with the second number to get a 2 digit combination 
	
	if(Segment_display_2_number == Locker_display_number && Final_Number == Combinations[0]){		//Checks to see if the 2 numbers entered is the same as the comination saved for locker 1
		PTB->PDOR = (1UL << 0);								//Turns on the LED for locker 1 to show that the locker is unlocked
		delay(5000);
		PTB->PDOR = ~(1UL << 0);							//Turns off the LED for locker 1 to show that the locker is locked
	}
	else if(Segment_display_2_number == Locker_display_number && Final_Number == Combinations[1]){	//Checks to see if the 2 numbers entered is the same as the comination saved for locker 2
		PTB->PDOR = (1UL << 1);							//Turns on the LED for locker 2 to show that the locker is unlocked
		delay(5000);
		PTB->PDOR = (0UL << 1);						//Turns on the LED for locker 2 to show that the locker is unlocked
	}
	else if(Segment_display_2_number == Locker_display_number && Final_Number == Combinations[2]){	//Checks to see if the 2 numbers entered is the same as the comination saved for locker 3
		PTB->PDOR = (1UL << 2);							//Turns on the LED for locker 3 to show that the locker is unlocked
		delay(5000);
		PTB->PDOR = ~(1UL << 2);						//Turns on the LED for locker 3 to show that the locker is unlocked
	}
	else{
	PTC->PDOR = ~((1UL << 7) | (1UL << 0) | (1UL << 3) | (1UL << 4) | (1UL << 5) | (1UL << 6) | (0UL << 10));		//0
	PTE->PDOR = ~((1UL << 30) | (0UL << 29) | (0UL << 23) | (1UL << 22) | (1UL << 21) | (1UL << 20) | (1UL << 5));		//0
		delay(5000);
	}

	Segment_display_number = 0;
	Segment_display_2_number = 0;
	Final_Number = 0;
	Selection_switch = 0;
	Increment_switch = 0;
	Decrement_switch = 0;
	Selection_check_switch = 0;
	selecter = 0;
	Locker_display_number = 0;			//system reset 
	
	PTC->PDOR = ~((1UL << 7) | (1UL << 0) | (1UL << 3) | (1UL << 4) | (1UL << 5) | (1UL << 6) | (0UL << 10));		//0
	PTE->PDOR = ~((1UL << 30) | (1UL << 29) | (1UL << 23) | (1UL << 22) | (1UL << 21) | (1UL << 20) | (0UL << 5));		//0
	PTB->PDOR = (0UL << 1);	
	
}
void Debouce(void){
	delay(500);
	if(Selection_check_switch == 1){
		selecter = selecter + Selection_check_switch;
	}

}


int main(void){
	
	IO_Config();
	Interrupt_Setup();
	SysTick_Config(10000);		
	SystemCoreClockUpdate();
	PTC->PDOR = ~((1UL << 7) | (1UL << 0) | (1UL << 3) | (1UL << 4) | (1UL << 5) | (1UL << 6) | (0UL << 10));		//0
	PTE->PSOR = ~((1UL << 30) | (1UL << 29) | (1UL << 23) | (1UL << 22) | (1UL << 21) | (1UL << 20) | (0UL << 5));		//0
	
	Selection_check_switch = 0;
	Increment_switch = 0;
	Decrement_switch = 0;
	selecter = 0;
	
	while(1){
		
		while(Selection_check_switch == 0){		//state 0 selecting the locker to be unlocked
			
			if(Increment_switch == 1){					//If the increment button has been pressed then add 1 to the display
				Debouce();
				Locker_display_number = Increment_display_locker(Locker_display_number);				//Adds 1 to the display variable
				Clear_locker_selection = Display_locker_number(Locker_display_number);					//Displays the new number on the 7 segment display
				Increment_switch = 0;							//Resets the increment button variable so the button can be pressed again
			}	
			if(Decrement_switch == 1){					//If the decrement button has been pressed then minus 1 to the display
				Debouce();
				Locker_display_number = Decrement_display_locker(Locker_display_number);				//Minus 1 to the display variable
				Clear_locker_selection = Display_locker_number(Locker_display_number);					//Displays the new number on the 7 segment display
				Decrement_switch = 0;							//Resets the decrement button variable so the button can be pressed again
			}
		
		}
		if(Selection_check_switch == 1){			//If the accept button has been pressed then go into the next state
			Debouce();
			Selection_check_switch = 0;					//Resets the accept button variable so it can be pressed again
		}
		while(selecter == 1){									//state 1 selecting the first number of the combination
		if(Clear_locker_selection == 1){
		PTE->PDOR = ~((1UL << 30) | (1UL << 29) | (1UL << 23) | (1UL << 22) | (1UL << 21) | (1UL << 20) | (0UL << 5));		//0
		}
			if(Increment_switch == 1){					//If the increment button has been pressed then add 1 to the display
				Debouce();
				Segment_display_number = Increment_display(Segment_display_number);							//Adds 1 to the display variable
				Segment_1_on(Segment_display_number);																	//Displays the new number on the 7 segment display
				Increment_switch = 0;																									//Resets the increment button variable so the button can be pressed again
			}
			if(Decrement_switch == 1){																						//If the decrement button has been pressed then minus 1 to the display
				Debouce();
				Segment_display_number = Decrement_display(Segment_display_number);							//Minus 1 to the display variable
				Segment_1_on(Segment_display_number);										//Displays the new number on the 7 segment display
				Decrement_switch = 0;							//Resets the decrement button variable so the button can be pressed again
			}
			if(Selection_check_switch == 1){		//If the accept button has been pressed then go into the next state
			Debouce();
			Selection_check_switch = 0;					//Resets the accept button variable so it can be pressed again
		}
		}
	
		while(selecter == 2){									//state 2 selecting the second number of the combination
			if(Increment_switch == 1){					//If the increment button has been pressed then add 1 to the display
				Debouce();
				Segment_display_2_number = Increment_display_2(Segment_display_2_number);						//Adds 1 to the display variable
				Segment_2_on(Segment_display_2_number);										//Displays the new number on the 7 segment display
				Increment_switch = 0;							//Resets the increment button variable so the button can be pressed again
			}
			if(Decrement_switch == 1){					//If the decrement button has been pressed then minus 1 to the display
				Debouce();
				Segment_display_2_number = Decrement_display_2(Segment_display_2_number);					//Minus 1 to the display variable
				Segment_2_on(Segment_display_2_number);									//Displays the new number on the 7 segment display
					Decrement_switch = 0;						//Resets the decrement button variable so the button can be pressed again
			}
			
			if(Selection_check_switch == 1){		//If the accept button has been pressed then go into the next state
			Debouce();
			Selection_check_switch = 0;					//Resets the accept button variable so it can be pressed again
		}
		}
		while(selecter == 3){									//state 3 checks to seee if the combination was correct and if it is then the locker will be unlocked
			Display_final_number();							//Displays if the combination entered was correct or not
			}
	}
}