/**
 * @file       BlynkDebug.cpp
 * @author     Volodymyr Shymanskyy
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
 * @date       Jan 2015
 * @brief      Debug utilities for Arduino
 */
#include "BlynkDebug.h"
#include "application.h"

size_t BlynkFreeRam()
{
    return 0;
}

void BlynkReset()
{
    System.reset();
    for(;;); // To make compiler happy
}

void BlynkFatal()
{
    delay(10000L);
    BlynkReset();
}
