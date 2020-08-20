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

CLed::CLed()
{
	//fp = nullptr;
}

void CLed::SetFileName( std::string filename )
{
	str_filename = filename;
}


void CLed::Write( unsigned int value )
{
	static const char values_str[] = "01";
int fd;



	fd = open(str_filename.c_str(), O_WRONLY);
	if (fd < 0)
	{
		//return -1;
		std::cout << "ERROR open fh for led! Fehler =  " << errno << "  " << str_filename.c_str() <<  std::endl;
		return;
	}

	if (write(fd, &values_str[value == 0 ? 0 : 1], 1) < 0)
	{
		std::cout << "ERROR write to fh! Fehler =  " << errno << "  " << str_filename.c_str() <<  std::endl;
		return;
	}

	close(fd);


//FILE *fp;
//int written;
//
//	fp = fopen(str_filename.c_str(), "wb");
//	if( fp != nullptr )
//	{
//		written = fwrite( &value, 4, 1, fp );
//		if( written == 0 )
//		{
//			int error = ferror( fp );
//
//			std::cout << written << " bytes has been written!! error=" << error <<  std::endl;
//		}
//		else
//		{
//			std::cout << written << " bytes has been written" <<  std::endl;
//		}
//
//
//		fclose( fp );
//	}
//	else
//	{
//		std::cout << "ERROR open fh for led! Fehler =  " << errno << "  " << str_filename.c_str() <<  std::endl;
//	}
//	//EAGAIN
}


