/**
 * @file       BlynkDebug.cpp
 * @author     Volodymyr Shymanskyy
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
 * @date       Jan 2015
 * @brief      Debug utilities for Arduino
 */
#include "BlynkDebug.h"

#if defined(__AVR__)

    #include <Arduino.h>

	size_t BlynkFreeRam()
	{
		extern int __heap_start, *__brkval;
		int v;
		return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
	}

	void BlynkReset()
	{
		void(*resetFunc)(void) = 0;
		resetFunc();
		for(;;) {} // To make compiler happy
	}

#elif defined(ESP8266)

    #include <Arduino.h>

	size_t BlynkFreeRam()
	{
		return ESP.getFreeHeap();
	}

	void BlynkReset()
	{
		ESP.restart();
		for(;;) {} // To make compiler happy
	}

#elif defined(__DUE__) //TODO

    #include <Arduino.h>

	size_t BlynkFreeRam()
	{
		struct mallinfo mi=mallinfo();

		char *heapend=sbrk(0);
		register char * stack_ptr asm("sp");
/*
		pConsole->printf("    arena=%d\n",mi.arena);
		pConsole->printf("  ordblks=%d\n",mi.ordblks);
		pConsole->printf(" uordblks=%d\n",mi.uordblks);
		pConsole->printf(" fordblks=%d\n",mi.fordblks);
		pConsole->printf(" keepcost=%d\n",mi.keepcost);

		pConsole->printf("RAM Start %lx\n", (unsigned long)ramstart);
		pConsole->printf("Data/Bss end %lx\n", (unsigned long)&_end);
		pConsole->printf("Heap End %lx\n", (unsigned long)heapend);
		pConsole->printf("Stack Ptr %lx\n",(unsigned long)stack_ptr);
		pConsole->printf("RAM End %lx\n", (unsigned long)ramend);

		pConsole->printf("Heap RAM Used: %d\n",mi.uordblks);
		pConsole->printf("Program RAM Used %d\n",&_end - ramstart);
		pConsole->printf("Stack RAM Used %d\n",ramend - stack_ptr);
*/
		size_t result = stack_ptr - heapend + mi.fordblks;
		return result;
	}
	void BlynkReset()
	{
		NVIC_SystemReset();
		for(;;) {} // To make compiler happy
	}

#elif defined (PARTICLE) || defined(SPARK)

    #include "application.h"

    size_t BlynkFreeRam()
    {
        return 0;
    }

    void BlynkReset()
    {
        System.reset();
        for(;;) {} // To make compiler happy
    }

#else

	#error "Need to implement board-specific utilities"

	size_t BlynkFreeRam()
	{
		return 0;
	}

	void BlynkReset()
	{
		for(;;) {} // To make compiler happy
	}

#endif

void BlynkFatal()
{
    delay(10000L);
    BlynkReset();
}
