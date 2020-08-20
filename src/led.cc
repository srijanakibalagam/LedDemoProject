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


#include <string.h>
#include <iostream>

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


#include "led.h"

CLed::CLed(){}

void CLed::SetFileName( std::string filename )
{
	str_filename = filename;
}

int  CLed::Write( unsigned int value )
{
static const char values_str[] = "01";
int fd;

	fd = open(str_filename.c_str(), O_WRONLY);
	if (fd < 0)
	{
		std::cout << "ERROR open fh for led! Fehler =  " << errno << "  " << str_filename.c_str() <<  std::endl;
		return -1;
	}

	if (write(fd, &values_str[value == 0 ? 0 : 1], 1) < 0)
	{
		std::cout << "ERROR write to fh! Fehler =  " << errno << "  " << str_filename.c_str() <<  std::endl;
		return -2;
	}

	close(fd);

	return 0;
}
