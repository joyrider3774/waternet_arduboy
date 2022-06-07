#ifndef PRINTFUNCS_H
#define PRINTFUNCS_H

#include "commonvars.h"

void printDebugCpuLoad();
void printDebug(uint8_t ax, uint8_t ay, const __FlashStringHelper* amsg);
void printNumber(uint8_t ax, uint8_t ay, uint16_t aNumber, uint8_t maxDigits);
void printMessage(uint8_t ax, uint8_t ay, const __FlashStringHelper* amsg);
void printCongratsScreen(uint8_t ax, uint8_t ay, const __FlashStringHelper* amsg);

#endif