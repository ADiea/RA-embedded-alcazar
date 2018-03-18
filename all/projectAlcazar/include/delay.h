/* STM32f0discovery embedded essentials project
 Author: Andrei Diea (github.com/ADiea)
 */

//This file contains delay functions

#ifndef DELAY_H
#define DELAY_H

//define cpu frequency default it is 8MHz
#define CPU_FREQ 8000000

/*
 * How much does the counter need to count per ms
 * We will use timer 15 for measuring time, with prescaler set to 1,
 * so the counter will count with the CPU_FREQ frequency
*/
#define TIMER_COUNT_PER_MS (CPU_FREQ / 1000)

//delay for ms miliseconds. keeps the cpu busy
void busyDelayMs(unsigned int ms);


#endif //DELAY_H
