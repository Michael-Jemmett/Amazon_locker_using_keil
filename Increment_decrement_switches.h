#ifndef INCREMENT_DECREMENT_SWITCHES_H
#define	INCREMENT_DECREMENT_SWITCHES_H



int Increment_display_locker(Locker_display_number){					
	Locker_display_number = Locker_display_number + 1;	
	if(Locker_display_number > 3){				//If a number bigger than 3 is selected then the number is cycled back to 1
		Locker_display_number = 1;
	}
	return Locker_display_number;
}

int Decrement_display_locker(Locker_display_number){					
	Locker_display_number = Locker_display_number - 1;
	if(Locker_display_number < 1){			//If a number less than 0 is selected then the number is cycled back to 3
		Locker_display_number = 3;
	}
	return Locker_display_number;
}

int Increment_display(Segment_display_number){					//Adds 1 for the first display
	Segment_display_number = Segment_display_number + 1;
	if(Segment_display_number > 9){			//if the number wanted goes above 9 it gets set to 0 as can only display a single digit on the display
		Segment_display_number = 0;
	}
	return Segment_display_number;
}

int Decrement_display(Segment_display_number){					//Minus 1 for the second display
	Segment_display_number = Segment_display_number - 1;
	if(Segment_display_number < 0){		//if the number wanted goes below 0 it gets set to 9 as I do not want to show negative numbers and want the display to loop
		Segment_display_number = 9;
	}
	return Segment_display_number;
}

int Increment_display_2(Segment_display_2_number){				//Adds 1 for the first display
	Segment_display_2_number = Segment_display_2_number + 1;
	if(Segment_display_2_number > 9){		//if the number wanted goes above 9 it gets set to 0 as can only display a single digit on the display
		Segment_display_2_number = 0;
	}	
	return Segment_display_2_number;
}

int Decrement_display_2(Segment_display_2_number){				//Minus 1 for the second display
	Segment_display_2_number = Segment_display_2_number - 1;
	if(Segment_display_2_number < 0){		//if the number wanted goes below 0 it gets set to 9 as I do not want to show negative numbers and want the display to loop
		Segment_display_2_number = 9;
	}
	return Segment_display_2_number;
}

#endif