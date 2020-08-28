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
* @file   led.h
* @date   2020.08.31
* @author georg.guenthoer@zf.com
*
*
* @brief writing a value to a symbolic linked hardware device
*
* Add some more description right here.
*/

#ifndef SRC_LED_H_
#define SRC_LED_H_

/**
 * @brief writing a value to a symbolic linked hardware device
 */
class CLed {
 public:
  CLed();

/**
 * @brief   set the path to the led
 * @param[in] value the value to be written
 */
  void SetFileName(std::string filename);
/**
 * @brief writing a value to the led
 * @return 		error value
 * @param[in] value the value to be written
 */
  int Write(unsigned int value);

 private:
  std::string str_filename;
};

#endif  // SRC_LED_H_
