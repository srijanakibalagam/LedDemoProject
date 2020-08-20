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


#include <iostream>
#include <unistd.h>
#include <string>

#include "led.h"


int run_led()
{
CLed ledRed;
int i = 3;
int ret = 0;

    std::cout << "\tHello this is the demo led project!! " << std::endl;

    ledRed.SetFileName( "/sys/devices/platform/leds/leds/ind:red/brightness" );

    while( i > 0 )
    {
    	i--;
    	std::cout << "\t\tActive!! " << std::endl;
    	ret = ledRed.Write( 255 );
    	if( ret ) return ret;

    	usleep(1000000);

    	std::cout << "\t\tNOT Active!! " << std::endl;
    	ret = ledRed.Write( 0 );
    	if( ret ) return ret;

    	usleep(1000000);
    }

    return 0;
}
