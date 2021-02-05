#ifndef SEGMENT_1_ON_H
#define SEGMENT_1_ON_H

#include "MKL25Z4.h"

int Clear_locker_selection = 0;

int Display_locker_number(int Locker_display_number){			//displays the locker number that is to be unlocked
	Clear_locker_selection = 1;
	switch(Locker_display_number){
	
	case 0: 
		PTE->PDOR = ~((1UL << 30) | (1UL << 29) | (1UL << 23) | (1UL << 22) | (1UL << 21) | (1UL << 20) | (0UL << 5));		//0
		break;	
	case 1:	
		PTE->PDOR = ~((0UL << 30) | (1UL << 29) | (1UL << 23) | (0UL << 22) | (0UL << 21) | (0UL << 20) | (0UL << 5));		//1
		break;	
	case 2:	
		PTE->PDOR = ~((1UL << 30) | (1UL << 29) | (0UL << 23) | (1UL << 22) | (1UL << 21) | (0UL << 20) | (1UL << 5));		//2
		break;	
	case 3:	
		PTE->PDOR = ~((1UL << 30) | (1UL << 29) | (1UL << 23) | (1UL << 22) | (0UL << 21) | (0UL << 20) | (1UL << 5));		//3
		break;
	default:
		break;
}
	return Clear_locker_selection;
}

void Segment_1_on(int Segment_display_number){							//Cycle through 0-9 depending on the number wanted by the increment and decrement switches for the first 7 segment

switch(Segment_display_number){
	
	case 0: 
		PTC->PDOR = ~((1UL << 7) | (1UL << 0) | (1UL << 3) | (1UL << 4) | (1UL << 5) | (1UL << 6) | (0UL << 10));		//0
		break;	
	case 1:	
		PTC->PDOR = ~((0UL << 7) | (1UL << 0) | (1UL << 3) | (0UL << 4) | (0UL << 5) | (0UL << 6) | (0UL << 10));		//1
		break;	
	case 2:	
		PTC->PDOR = ~((1UL << 7) | (1UL << 0) | (0UL << 3) | (1UL << 4) | (1UL << 5) | (0UL << 6) | (1UL << 10));		//2
		break;	
	case 3:	
		PTC->PDOR = ~((1UL << 7) | (1UL << 0) | (1UL << 3) | (1UL << 4) | (0UL << 5) | (0UL << 6) | (1UL << 10));		//3
		break;
	case 4:
		PTC->PDOR = ~((0UL << 7) | (1UL << 0) | (1UL << 3) | (0UL << 4) | (0UL << 5) | (1UL << 6) | (1UL << 10));		//4
		break;	
	case 5:	
		PTC->PDOR = ~((1UL << 7) | (0UL << 0) | (1UL << 3) | (1UL << 4) | (0UL << 5) | (1UL << 6) | (1UL << 10));		//5
		break;
	case 6:	
		PTC->PDOR = ~((0UL << 7) | (0UL << 0) | (1UL << 3) | (1UL << 4) | (1UL << 5) | (1UL << 6) | (1UL << 10));		//6
		break;
	case 7:	
		PTC->PDOR = ~((1UL << 7) | (1UL << 0) | (1UL << 3) | (0UL << 4) | (0UL << 5) | (0UL << 6) | (0UL << 10));		//7
		break;
	case 8:	
		PTC->PDOR = ~((1UL << 7) | (1UL << 0) | (1UL << 3) | (1UL << 4) | (1UL << 5) | (1UL << 6) | (1UL << 10));		//8
		break;
	case 9:	
		PTC->PDOR = ~((1UL << 7) | (1UL << 0) | (1UL << 3) | (0UL << 4) | (0UL << 5) | (1UL << 6) | (1UL << 10));		//9
		break;
	default:	
		break;	
}
}
void Segment_2_on(int Segment_display_2_number){							//Cycle through 0-9 depending on the number wanted by the increment and decrement switches for the second 7 segment
switch(Segment_display_2_number){
	
	case 0: 
		PTE->PDOR = ~((1UL << 30) | (1UL << 29) | (1UL << 23) | (1UL << 22) | (1UL << 21) | (1UL << 20) | (0UL << 5));		//0
		break;	
	case 1:	
		PTE->PDOR = ~((0UL << 30) | (1UL << 29) | (1UL << 23) | (0UL << 22) | (0UL << 21) | (0UL << 20) | (0UL << 5));		//1
		break;	
	case 2:	
		PTE->PDOR = ~((1UL << 30) | (1UL << 29) | (0UL << 23) | (1UL << 22) | (1UL << 21) | (0UL << 20) | (1UL << 5));		//2
		break;	
	case 3:	
		PTE->PDOR = ~((1UL << 30) | (1UL << 29) | (1UL << 23) | (1UL << 22) | (0UL << 21) | (0UL << 20) | (1UL << 5));		//3
		break;
	case 4:
		PTE->PDOR = ~((0UL << 30) | (1UL << 29) | (1UL << 23) | (0UL << 22) | (0UL << 21) | (1UL << 20) | (1UL << 5));		//4
		break;	
	case 5:	
		PTE->PDOR = ~((1UL << 30) | (0UL << 29) | (1UL << 23) | (1UL << 22) | (0UL << 21) | (1UL << 20) | (1UL << 5));		//5
		break;
	case 6:	
		PTE->PDOR = ~((0UL << 30) | (0UL << 29) | (1UL << 23) | (1UL << 22) | (1UL << 21) | (1UL << 20) | (1UL << 5));		//6
		break;
	case 7:	
		PTE->PDOR = ~((1UL << 30) | (1UL << 29) | (1UL << 23) | (0UL << 22) | (0UL << 21) | (0UL << 20) | (0UL << 5));		//7
		break;
	case 8:	
		PTE->PDOR = ~((1UL << 30) | (1UL << 29) | (1UL << 23) | (1UL << 22) | (1UL << 21) | (1UL << 20) | (1UL << 5));		//8
		break;
	case 9:	
		PTE->PDOR = ~((1UL << 30) | (1UL << 29) | (1UL << 23) | (0UL << 22) | (0UL << 21) | (1UL << 20) | (1UL << 5));		//9
		break;
	default:	
		break;		
}
}

#endif