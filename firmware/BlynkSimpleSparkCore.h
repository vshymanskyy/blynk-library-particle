/**
 * @file       BlynkSimpleSparkCore.h
 * @author     Volodymyr Shymanskyy
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
 * @date       Mar 2015
 * @brief
 *
 */

#ifndef BlynkSimpleSparkCore_h
#define BlynkSimpleSparkCore_h

#include "BlynkSparkCore.h"

static BlynkTransportSparkCore _blynkTransport();
BlynkSparkCore Blynk(_blynkTransport);

#include "BlynkWidgets.h"

#endif
