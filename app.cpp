#include <iostream>
#include <time.h>
#include <signal.h>
#include <stdlib.h>

#include "app.h"
#include "socket.h"
#include "util.h"
#include "configuration.h"

using namespace std;



string gCFGFile;
string gLogFile;
uint32_t gLogMethod = 0;
ofstream *gLog = NULL;

App *app = NULL;

uint32_t GetTime( )
{
    return GetTicks( ) / 1000;
}

uint32_t GetTicks(){
    uint32_t ticks;
    struct timespec time;
    clock_gettime( CLOCK_MONOTONIC, &time );
    ticks = time.tv_sec * 1000;
    ticks += time.tv_nsec / 1000000;
    return ticks;

}


void CONSOLE_Print( string message )
{
    cout << message << endl;

    // logging

    if( !gLogFile.empty( ) )
    {
        if( gLogMethod == 1 )
        {
            ofstream Log;
            Log.open( gLogFile.c_str( ), ios :: app );

            if( !Log.fail( ) )
            {
                time_t Now = time( NULL );
                string Time = asctime( localtime( &Now ) );

                // erase the newline

                Time.erase( Time.size( ) - 1 );
                Log << "[" << Time << "] " << message << endl;
                Log.close( );
            }
        }
        else if( gLogMethod == 2 )
        {
            if( gLog && !gLog->fail( ) )
            {
                time_t Now = time( NULL );
                string Time = asctime( localtime( &Now ) );

                // erase the newline

                Time.erase( Time.size( ) - 1 );
                *gLog << "[" << Time << "] " << message << endl;
                gLog->flush( );
            }
        }
    }
}

void DEBUG_Print( string message )
{
    cout << message << endl;
}

void DEBUG_Print( BYTEARRAY b )
{
    cout << "{ ";

    for( unsigned int i = 0; i < b.size( ); i++ )
        cout << hex << (int)b[i] << " ";

    cout << "}" << endl;
}

int main()
{

    srand(time(NULL));
    gCFGFile = "app.properties";
    Configuration CFG;

    CFG.ReadConfiguration(gCFGFile);
    gLogMethod = CFG.GetInt("log_method", 1);
    gLogFile = CFG.GetString("log_file", "log.txt");


    if( !gLogFile.empty( ) )
    {
        if( gLogMethod == 1 )
        {
            // log method 1: open, append, and close the log for every message
            // this works well on Linux but poorly on Windows, particularly as the log file grows in size
            // the log file can be edited/moved/deleted while GHost++ is running
        }
        else if( gLogMethod == 2 )
        {
            // log method 2: open the log on startup, flush the log for every message, close the log on shutdown
            // the log file CANNOT be edited/moved/deleted while GHost++ is running

            gLog = new ofstream( );
            gLog->open( gLogFile.c_str( ), ios :: app );
        }
    }

    CONSOLE_Print( "[APP] starting up" );

    if( !gLogFile.empty( ) )
    {
        if( gLogMethod == 1 )
            CONSOLE_Print( "[APP] using log method 1, logging is enabled and [" + gLogFile + "] will not be locked" );
        else if( gLogMethod == 2 )
        {
            if( gLog->fail( ) )
                CONSOLE_Print( "[APP] using log method 2 but unable to open [" + gLogFile + "] for appending, logging is disabled" );
            else
                CONSOLE_Print( "[APP] using log method 2, logging is enabled and [" + gLogFile + "] is now locked" );
        }
    }
    else
        CONSOLE_Print( "[APP] no log file specified, logging is disabled" );



    CONSOLE_Print( "[APP] starting sockets" );
    
    
    
    App *app = new App(&CFG);
    
    

    while ( )


    return 0;
}

App::App(Configuration CFG){
  char HostName[255];
  

  if( gethostname( HostName, 255 ) == SOCKET_ERROR )
          CONSOLE_Print( "[APP] error finding local IP addresses - failed to get local hostname" );
  else
  {
          CONSOLE_Print( "[APP] local hostname is [" + string( HostName ) + "]" );
          struct hostent *HostEnt = gethostbyname( HostName );

          if( !HostEnt )
                  CONSOLE_Print( "[APP] error finding local IP addresses - gethostbyname failed" );
          else
          {
                  for( int i = 0; HostEnt->h_addr_list[i] != NULL; i++ )
                  {
                          struct in_addr Address;
                          memcpy( &Address, HostEnt->h_addr_list[i], sizeof(struct in_addr) );
                          CONSOLE_Print( "[APP] local IP address #" + UTIL_ToString( i + 1 ) + " is [" + string( inet_ntoa( Address ) ) + "]" );
                          m_LocalAddresses.push_back( UTIL_CreateByteArray( (uint32_t)Address.s_addr, false ) );
                  }
          }
  }
  
}


bool App::Update(long usecBlock){
  
}






