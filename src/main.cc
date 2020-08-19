/** __________
 * |__  /  ___|
 *   / /| |_
 *  / /_|  _|
 * /____|_|   Friedrichshafen AG
 *
 * @file      main.cc
 * @date      August 8, 2020
 * @author    georg.guenthoer@zf.com
 * @copyright [2020] ZF Friedrichshafen AG
 */


#ifndef __APP_VERSION__
#define APP_VERSION "un.know.n"
#else
#define APP_VERSION __APP_VERSION__
#endif

#include <iostream>
#include <string>
#include <sstream>


int main(int argc, const char* argv[]) {
    // Standard string to output

    std::cout << "\tHello this is the demo led project!! " << std::endl;

    return 0;
}
