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
#include <unistd.h>
#include <string>
//#include <sstream>

#include "led.h"

int main(int argc, const char* argv[]) {
    // Standard string to output
CLed ledRed;
int i = 3;

    std::cout << "\tHello this is the demo led project!! " << std::endl;

    ledRed.SetFileName( "/sys/devices/platform/leds/leds/ind:red/brightness" );

    while( i > 0 )
    {
    	i--;
    	std::cout << "\t\tActive!! " << std::endl;
    	ledRed.Write( 255 );
    	usleep(1000000);
    	std::cout << "\t\tNOT Active!! " << std::endl;
    	ledRed.Write( 0 );
    	usleep(1000000);
    }

    //led.SetFileName( "" );


    return 0;
}
