#ifndef INCLUDES_H
#define INCLUDES_H

#include <stdint.h>

#include <map>
#include <vector>
#include <set>
#include <string>
#include <iostream>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

typedef vector<unsigned char> BYTEARRAY;


uint32_t GetTime( );
uint32_t GetTicks( );



void CONSOLE_Print( string message );
void DEBUG_Print( string message );
void DEBUG_Print( BYTEARRAY b );

#endif // INCLUDES_H
