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
* @file   led.cc
* @date   2020.08.31
* @author georg.guenthoer@zf.com
*
*
* @brief writing a value to a symbolic linked hardware device
*
* Add some more description right here.
*/

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <string>

#include "led.h"  // NOLINT

CLed::CLed() {}

/**
 * @description   set the path to the led
 * @parameter[in] value the value to be written
 */
void CLed::SetFileName(std::string filename) { str_filename = filename; }

/**
 * @description   writing a value to the led
 * @return 		error value
 * @parameter[in] value the value to be written
 */
int CLed::Write(unsigned int value) {
  static const char values_str[] = "01";
  int fd;

  fd = open(str_filename.c_str(), O_WRONLY);
  if (fd < 0) {
    std::cout << "ERROR open fh for led! Fehler =  " << errno << "  "
              << str_filename.c_str() << std::endl;
    return -1;
  }

  if (write(fd, &values_str[value == 0 ? 0 : 1], 1) < 0) {
    std::cout << "ERROR write to fh! Fehler =  " << errno << "  "
              << str_filename.c_str() << std::endl;
    return -2;
  }

  close(fd);

  return 0;
}
