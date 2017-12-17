#include "app.h"
#include "configuration.h"
#include <stdlib.h>

Configuration::Configuration()
{

}

Configuration::~Configuration(){

}

void Configuration::Set(string key, string value){
    m_CFG[key] = value;
}

string Configuration::GetString(string key, string defaultValue){
    if ( m_CFG.find(key) == m_CFG.end()){
        return defaultValue;
    }else{
        return m_CFG[key];
    }
}
int Configuration::GetInt(string key, int defaultValue){
    if ( m_CFG.find(key) == m_CFG.end()){
        return defaultValue;
    }else{
        return atoi(m_CFG[key].c_str());
    }
}
bool Configuration::exists(string key){
    return m_CFG.find(key) != m_CFG.end();
}
void Configuration::ReadConfiguration(string file){
    ifstream in;
    in.open(file.c_str());

    if ( in.fail() ){
        CONSOLE_Print("[Config] warning - unable to read file ["+file+"]");
    }else{
        CONSOLE_Print("[Config] loading configuration file ["+file+"]");
        string Line;

        while ( !in.eof() ){
            getline(in,Line);

            // ignore blank lines and comments

            if( Line.empty( ) || Line[0] == '#' )
                continue;

            // remove newlines and partial newlines to help fix issues with Windows formatted config files on Linux systems


          // Line.erase( remove( Line.begin( ), Line.end( ), '\r' ), Line.end( ) );
            //Line.erase( remove( Line.begin( ), Line.end( ), '\n' ), Line.end( ) );

            string :: size_type Split = Line.find( "=" );

            if( Split == string :: npos )
                continue;

            string :: size_type KeyStart = Line.find_first_not_of( " " );
            string :: size_type KeyEnd = Line.find( " ", KeyStart );
            string :: size_type ValueStart = Line.find_first_not_of( " ", Split + 1 );
            string :: size_type ValueEnd = Line.size( );

            if( ValueStart != string :: npos )
                m_CFG[Line.substr( KeyStart, KeyEnd - KeyStart )] = Line.substr( ValueStart, ValueEnd - ValueStart );
        }

        in.close( );
    }


}
