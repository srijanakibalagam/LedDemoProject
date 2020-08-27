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
* @file   main.cc
* @date   2020.08.31
* @author georg.guenthoer@zf.com
*
*
* @brief program entry
*
* Add some more description right here.
*/

#ifndef __APP_VERSION__
#define APP_VERSION "un.know.n"
#else
#define APP_VERSION __APP_VERSION__
#endif

#include <iostream>
#include <string>

#include "run_led.h"  // NOLINT

/**
 * @description    entry point (main)
 */
int main(int argc, const char* argv[]) {
  std::cout << "\tHello this is the demo led project!! " << std::endl;

  return run_led();
}
