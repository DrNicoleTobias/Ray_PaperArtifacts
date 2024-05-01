#ifndef SERIALMONITOR_h
#define SERIALMONITOR_h

#include <msp430.h>
#include <string.h>
#include <stdio.h>

void configureUART();                       // Configure UART, clock at MHz
void printStr(const char *tx_data);         // Print string to the screen
void printNum(unsigned long num);           // Print number to the screen
void printsignedNum(long num);

#endif
