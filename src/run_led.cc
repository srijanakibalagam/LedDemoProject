/**
* Copyright (C) ZF Friedrichshafen AG 2020.
* @verbatim
  __________
 |__  /  ___|
   / /| |_
  / /_|  _|
 /____|_|   Friedrichshafen AG

 @endverbatim
* CONFIDENTIAL AND PROPRIETARY:
*
* This copyrighted document is the property of ZF Friedrichshafen AG
* and its affiliates, including ZF Group TRW Automotive Inc.
* and its subsidiary companies ("ZF").
*
* This document and the information contained herein is disclosed
* in confidence and may not be copied, disclosed to others,
* or used for any purpose unless authorized by ZF.
*
* This document must be returned to ZF upon request and may not
* be stored in any database or retrieval system.
*
* @file   run_led.cc
* @date   2020.08.31
* @author georg.guenthoer@zf.com
*
*
* @brief run the led
*
* Add some more description right here.
*/

#include <unistd.h>
#include <iostream>

#include "led.h"  // NOLINT

int run_led() {
  CLed ledRed;
  int i = 3;
  int ret = 0;

  ledRed.SetFileName("/sys/devices/platform/leds/leds/ind:red/brightness");

  while (i > 0) {
    i--;
    std::cout << "\t\tActive!! " << std::endl;
    ret = ledRed.Write(255);
    if (ret) return ret;

    usleep(1000000);

    std::cout << "\t\tNOT Active!! " << std::endl;
    ret = ledRed.Write(0);
    if (ret) return ret;

    usleep(1000000);
  }

  return 0;
}
