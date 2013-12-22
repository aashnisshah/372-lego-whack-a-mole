
#include "stdio.h"
#include <stdlib.h>

volatile int * audio_ptr;
int score, hitflag, counter, fifospace, soundCounter;
long speed, audiobuf;
char strCount[3];

void sensor(){
	
	// resetRegs();
	asm(".equ ADDR_JP2, 0x10000070");
	asm("movia r8, ADDR_JP2");

	asm("movia r10, 0x07f557ff");
	asm("stwio r10, 4(r8)");

	asm("loop:");
		//printf("inside sensor\n");
		// asm("movia r11, 0xfffeffff");
		asm("movia r11, 0xFFFEFFBF");
		asm("stwio r11, 0(r8)");
		asm("ldwio r5, 0(r8)");
		asm("srli r5, r5, 17");
		asm("andi r5, r5,0x1");
		// asm volatile("ldw r5, %0" : : "m" (regSenseVal));
		// printf("Reg val 5: %d\n", regSenseVal);
		asm("bne r0, r5,loop");
	asm("good:");
		//printf("inside good\n");
		asm("ldwio r10, 0(r8)");
		asm("srli r10, r10, 27");
		// our code
		// asm volatile("ldw r10, %0" : : "m" (regSenseVal));
		// printf("Reg val 10: %d\n", regSenseVal);
		asm("andi r10, r10, 0x0f");

		asm("movia r6, 0x2");
		asm("ble r10, r6, senseHit");

}

void sensor2(){
	// change registers to not screw up the two different 
	// sensor interactions
	// resetRegs();
	asm(".equ ADDR_JP2, 0x10000070");
	// asm("movia r7, ADDR_JP2");
	asm("movia r8, ADDR_JP2");

	asm("movia r10, 0x07f557ff");
	// asm("stwio r9, 4(r7)");
	asm("stwio r10, 4(r8)");

	asm("loop2:");
		//printf("inside sensor\n");
		// asm("movia r12, 0xfffbffff");
		asm("movia r12, 0xFFFBFEFF");
		// asm("stwio r12, 0(r7)");
		// asm("ldwio r13, 0(r7)");
		asm("stwio r12, 0(r8)");
		asm("ldwio r13, 0(r8)");
		asm("srli r13, r13, 19");
		asm("andi r13, r13,0x1");
		// asm volatile("ldw r5, %0" : : "m" (regSenseVal));
		// printf("Reg val 5: %d\n", regSenseVal);
		asm("bne r0, r13,loop2");
	asm("good2:");
		//printf("inside good\n");
		// asm("ldwio r9, 0(r7)");
		asm("ldwio r10, 0(r8)");
		asm("srli r10, r10, 27");
		// our code
		// asm volatile("ldw r10, %0" : : "m" (regSenseVal));
		// printf("Reg val 10: %d\n", regSenseVal);
		asm("andi r10, r10, 0x0f");
		// r6 is not changed as we're using the same values for
		// both the sensors
		asm("movia r6, 0x2");
		asm("ble r10, r6, senseHit");

}

// void sensor3(){
// // change registers to not screw up the two different 
// 	// sensor interactions
// 	// resetRegs();
// 	asm(".equ ADDR_JP2, 0x10000070");
// 	// asm("movia r7, ADDR_JP2");
// 	asm("movia r8, ADDR_JP2");

// 	asm("movia r10, 0x07f557ff");
// 	// asm("stwio r9, 4(r7)");
// 	asm("stwio r10, 4(r8)");

// 	asm("loop3:");
// 		//printf("inside sensor\n");
// 		// asm("movia r12, 0xfffbffff");
// 		asm("movia r2, 0xFFFFBFEF");
// 		// asm("stwio r12, 0(r7)");
// 		// asm("ldwio r13, 0(r7)");
// 		asm("stwio r2, 0(r8)");
// 		asm("ldwio r3, 0(r8)");
// 		asm("srli r3, r3, 15");
// 		asm("andi r3, r3,0x1");
// 		// asm volatile("ldw r5, %0" : : "m" (regSenseVal));
// 		// printf("Reg val 5: %d\n", regSenseVal);
// 		asm("bne r0, r3,loop3");
// 	asm("good3:");
// 		//printf("inside good\n");
// 		// asm("ldwio r9, 0(r7)");
// 		asm("ldwio r10, 0(r8)");
// 		asm("srli r10, r10, 27");
// 		// our code
// 		// asm volatile("ldw r10, %0" : : "m" (regSenseVal));
// 		// printf("Reg val 10: %d\n", regSenseVal);
// 		asm("andi r10, r10, 0x0f");
// 		// r6 is not changed as we're using the same values for
// 		// both the sensors
// 		asm("movia r6, 0x3");
// 		asm("ble r10, r6, senseHit");
// }

void sensor4(){
// change registers to not screw up the two different 
	// sensor interactions
	// resetRegs();
	asm(".equ ADDR_JP2, 0x10000070");
	// asm("movia r7, ADDR_JP2");
	asm("movia r8, ADDR_JP2");

	asm("movia r10, 0x07f557ff");
	// asm("stwio r9, 4(r7)");
	asm("stwio r10, 4(r8)");

	asm("loop4:");
		//printf("inside sensor\n");
		// asm("movia r12, 0xfffbffff");
		asm("movia r7, 0xFFFFEFFB");
		// asm("stwio r12, 0(r7)");
		// asm("ldwio r13, 0(r7)");
		asm("stwio r7, 0(r8)");
		asm("ldwio r9, 0(r8)");
		asm("srli r9, r9, 13");
		asm("andi r9, r9,0x1");
		// asm volatile("ldw r5, %0" : : "m" (regSenseVal));
		// printf("Reg val 5: %d\n", regSenseVal);
		asm("bne r0, r9,loop4");
	asm("good4:");
		//printf("inside good\n");
		// asm("ldwio r9, 0(r7)");
		asm("ldwio r10, 0(r8)");
		asm("srli r10, r10, 27");
		// our code
		// asm volatile("ldw r10, %0" : : "m" (regSenseVal));
		// printf("Reg val 10: %d\n", regSenseVal);
		asm("andi r10, r10, 0x0f");
		// r6 is not changed as we're using the same values for
		// both the sensors
		asm("movia r6, 0x2");
		asm("ble r10, r6, senseHit");
}

void sensor5(){
// change registers to not screw up the two different 
	// sensor interactions
	// resetRegs();
	asm(".equ ADDR_JP2, 0x10000070");
	// asm("movia r7, ADDR_JP2");
	asm("movia r8, ADDR_JP2");

	asm("movia r10, 0x07f557ff");
	// asm("stwio r9, 4(r7)");
	asm("stwio r10, 4(r8)");

	asm("loop5:");
		
		// asm("movia r14, 0xFFFFFBFE");
		asm("movia r14, 0xFFFFFBEF");
		
		asm("stwio r14, 0(r8)");
		asm("ldwio r15, 0(r8)");
		asm("srli r15, r15, 11");
		asm("andi r15, r15,0x1");
		// asm volatile("ldw r5, %0" : : "m" (regSenseVal));
		// printf("Reg val 5: %d\n", regSenseVal);
		asm("bne r0, r15,loop5");
	asm("good5:");
		//printf("inside good\n");
		// asm("ldwio r9, 0(r7)");
		asm("ldwio r10, 0(r8)");
		asm("srli r10, r10, 27");
		// our code
		// asm volatile("ldw r10, %0" : : "m" (regSenseVal));
		// printf("Reg val 10: %d\n", regSenseVal);
		asm("andi r10, r10, 0x0f");
		// r6 is not changed as we're using the same values for
		// both the sensors
		asm("movia r6, 0x2");
		asm("ble r10, r6, senseHit");
}

void turnOffLights() {
	asm(".equ ADDR_JP2, 0x10000070");
	asm("movia r2, ADDR_JP2");
	asm("movia r3, 0xFFFFFFFF");
	asm("stwio r3, 0(r2)");
}

// void hitSound() {
//     // I'm not completely sure as to why the sound is not working
// 	// I think we should try running sound without changing the 
// 	// frequency ever (i.e., soundCounter)
	
//     fifospace = *(audio_ptr+1); // read the audio port fifospace register

//     if(counter < 1){
// 		audiobuf = 500032100;
// 		soundCounter++;
// 	} else {
// 		audiobuf = -500032100;
// 		soundCounter++;
// 		if(soundCounter == 2){
// 			soundCounter = 0;
// 		}
// 	}

// 	fifospace = *(audio_ptr + 1);

//     if (((fifospace & 0x00ff0000)>>16) > 96){
//    		// write to both channels
// 	    *(audio_ptr + 2) = audiobuf;
// 	    *(audio_ptr + 3) = audiobuf;
// 	    // *(audio_ptr + 3) = 0;	   		
//     }
// }

void displayTextLCD(char * text_ptr)
{
  	volatile char * LCD_display_ptr = (char *) 0x10003050;	// 16x2 character display

	while ( *(text_ptr) )
	{
		*(LCD_display_ptr + 1) = *(text_ptr);	// write to the LCD data register
		++text_ptr;
	}
}

void clearLCD1 () {
	volatile char * LCD_display_ptr = (char *) 0x10003050;
	*(LCD_display_ptr) = 0x1;
}

void senseHit() {
	// hitSound();
	if(hitflag > 0){
		score++;
		// hitSound();
		snprintf(strCount, 3, "%d", score);
		clearLCD1();
		displayTextLCD(strCount);
		
	}
	hitflag = 0; // hit happened
	turnOffLights();
	
}
// NO.
void chooseMole(){
	hitflag = rand() % 4;
	hitflag += 1;	// since we can't have hitflag set to 0
	// printf("Hitflag: %d\n", hitflag);
}


int main(){
	// audio_ptr = (int *) 0x10003040;
	// buffer_index = 0;
	score = 0;
	snprintf(strCount, 3, "%d", 0);
	displayTextLCD(strCount);
	// char strCount[3]; 
	hitflag = 1;
	counter = 0;
	speed = 1000000;
	soundCounter = 0;
	// changing the speed to reflect the 50 MHz processor
	// speed = 12500000;
	while(1){
		counter ++;
		if(counter == speed){
			chooseMole();
			counter = 0;
			// score++;
			if(score == 100) {
				score = 0;
			}
			if(score % 4 == 0){
				speed = speed - 100000;
				if(speed == 0) {
					speed = 1000000;
				}
			}
			// snprintf(strCount, 3, "%d", score);
			// clearLCD1();
			// displayTextLCD(strCount);
		}
		// sensor();
		switch(hitflag){
			case 0: break;
			case 1: sensor();
					break;
			case 2: sensor2();
					break;
			case 3: sensor4();
					break;
			case 4: sensor5();
					break;
			// case 5: sensor5();
			// 		break;
			default: break;
		}
	}
	return 0;
}
