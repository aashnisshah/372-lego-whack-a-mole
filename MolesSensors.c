// This is primary (and the only, for now) file for the 
// whack-a-mole built using lego

// The following modules/libraries have been added mostly for
// testing purposes. However, they have been used for main
// functionality too
#include "stdio.h"
#include <stdlib.h>

// score is a global count of player score.
// hitflag is used to register a successful
// hit of a mole.
// counter is used to determine when the speed
// of mole changing is to change, along with when
// the next mole is chosen.
int score, hitflag, counter;
// speed determines how often the moles would change
long speed;
// strCount is used to print the player score on LCD screen
char strCount[3];

// All the sensor functions are identical in functionality
// They just use different register to achieve it
void sensor1(){
	// Get the right address for JP2 connections
	asm(".equ ADDR_JP2, 0x10000070");
	asm("movia r8, ADDR_JP2");
	// And move the concerned bit into the proper
	// register
	asm("movia r10, 0x07f557ff");
	asm("stwio r10, 4(r8)");
	// keep looping until a value is registered
	// or a switch is made by the timer
	asm("loop:");
		asm("movia r11, 0xFFFEFFBF");
		asm("stwio r11, 0(r8)");
		asm("ldwio r5, 0(r8)");
		asm("srli r5, r5, 17");
		asm("andi r5, r5,0x1");
		asm("bne r0, r5,loop");
	asm("good:");
		asm("ldwio r10, 0(r8)");
		asm("srli r10, r10, 27");
		asm("andi r10, r10, 0x0f");

		asm("movia r6, 0x2");
		asm("ble r10, r6, senseHit");

}

// All the other sensor code follows suit of previous, and hence
// is not commented completely
void sensor2(){
	// change registers to not screw up the different 
	// sensor interactions
	asm(".equ ADDR_JP2, 0x10000070");
	asm("movia r8, ADDR_JP2");

	asm("movia r10, 0x07f557ff");
	asm("stwio r10, 4(r8)");

	asm("loop2:");
		asm("movia r12, 0xFFFBFEFF");
		asm("stwio r12, 0(r8)");
		asm("ldwio r13, 0(r8)");
		asm("srli r13, r13, 19");
		asm("andi r13, r13,0x1");
		asm("bne r0, r13,loop2");
	asm("good2:");
		asm("ldwio r10, 0(r8)");
		asm("srli r10, r10, 27");
		asm("andi r10, r10, 0x0f");
		// r6 is not changed as we're using the same values for
		// both the sensors
		asm("movia r6, 0x2");
		asm("ble r10, r6, senseHit");

}

void sensor3(){
	// change registers to not screw up the different 
	// sensor interactions

	asm(".equ ADDR_JP2, 0x10000070");
	asm("movia r8, ADDR_JP2");

	asm("movia r10, 0x07f557ff");
	asm("stwio r10, 4(r8)");

	asm("loop4:");
		asm("movia r7, 0xFFFFEFFB");
		asm("stwio r7, 0(r8)");
		asm("ldwio r9, 0(r8)");
		asm("srli r9, r9, 13");
		asm("andi r9, r9,0x1");
		asm("bne r0, r9,loop4");
	asm("good4:");
		asm("ldwio r10, 0(r8)");
		asm("srli r10, r10, 27");
		asm("andi r10, r10, 0x0f");
		// r6 is not changed as we're using the same values for
		// both the sensors
		asm("movia r6, 0x2");
		asm("ble r10, r6, senseHit");
}

void sensor4(){
	// change registers to not screw up the different 
	// sensor interactions
	asm(".equ ADDR_JP2, 0x10000070");
	asm("movia r8, ADDR_JP2");

	asm("movia r10, 0x07f557ff");
	asm("stwio r10, 4(r8)");

	asm("loop5:");
		asm("movia r14, 0xFFFFFBEF");
		
		asm("stwio r14, 0(r8)");
		asm("ldwio r15, 0(r8)");
		asm("srli r15, r15, 11");
		asm("andi r15, r15,0x1");
		asm("bne r0, r15,loop5");
	asm("good5:");
		asm("ldwio r10, 0(r8)");
		asm("srli r10, r10, 27");
		asm("andi r10, r10, 0x0f");
		// r6 is not changed as we're using the same values for
		// both the sensors
		asm("movia r6, 0x2");
		asm("ble r10, r6, senseHit");
}

// This function is called only when a mole is
// successfully hit. It turns off the light to indicate a
// successfuly hit.
void turnOffLights() {
	asm(".equ ADDR_JP2, 0x10000070");
	asm("movia r2, ADDR_JP2");
	asm("movia r3, 0xFFFFFFFF");
	asm("stwio r3, 0(r2)");
}

// This function is used to display the player's score
// on the LCD screen
void displayTextLCD(char * text_ptr)
{	// Get the apt address for the output screen
  	volatile char * LCD_display_ptr = (char *) 0x10003050;	// 16x2 character display
  	// Loop until all characters are printed
	while ( *(text_ptr) )
	{
		*(LCD_display_ptr + 1) = *(text_ptr);	// write to the LCD data register
		++text_ptr;
	}
}

// This function is used to clear the LCD screen whenever required
void clearLCD() {
	volatile char * LCD_display_ptr = (char *) 0x10003050;
	*(LCD_display_ptr) = 0x1;
}

// This function is used to sense a successful hit.
// It increases the player score appropriately and 
// outputs it to the LCD screen after that
void senseHit() {
	// Check to see if the mole is open for hitting or not
	if(hitflag > 0){
		score++;
		// Print the score to the container variable
		snprintf(strCount, 3, "%d", score);
		// Clear screen before printing the new score
		clearLCD();
		// Print the score on the LCD screen
		displayTextLCD(strCount);
		
	}
	// Hit happened/already happened
	hitflag = 0;
	// Turn off the mole light to indicate successful hit
	turnOffLights();
	
}

// This functions is used to select which mole is active next
void chooseMole(){
	// Use random selection to determine next active mole
	hitflag = rand() % 4;
	hitflag += 1;	// since we can't have hitflag set to 0
}

// Runner of our whack-a-mole
int main(){
	// Start the game with an initial score of 0
	score = 0;
	// Display the initial score
	snprintf(strCount, 3, "%d", 0);
	displayTextLCD(strCount);
	// Initializing all the necessary variables
	hitflag = 1;
	counter = 0;
	speed = 1000000;
	// A polling loop to keep the game running
	while(1){
		// Counter determines when the next mole is chosen
		counter ++;
		if(counter == speed){
			chooseMole();
			counter = 0;
			// You won the game, and it restarts
			if(score == 100) {
				score = 0;
			}
			// After every 4 successful hits, speed up the game
			if(score % 4 == 0){
				speed = speed - 100000;
				if(speed == 0) {
					speed = 1000000;
				}
			}
		}
		// After the mole has been chosen, activate the
		// appropriate sensor
		switch(hitflag){
			case 0: break;
			case 1: sensor1();
					break;
			case 2: sensor2();
					break;
			case 3: sensor3();
					break;
			case 4: sensor4();
					break;
			default: break;
		}
	}
	return 0;
}
