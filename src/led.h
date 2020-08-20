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

#ifndef SRC_LED_H_
#define SRC_LED_H_

//#include <string.h>

class CLed
{
	public:
		CLed();
		void SetFileName( std::string filename );
		void Write( unsigned int value );


	private:
		std::string str_filename;
		//FILE *fp;
};



#endif /* SRC_LED_H_ */
