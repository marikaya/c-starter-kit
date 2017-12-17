#ifndef APP_H
#define APP_H

#include "includes.h"

class Configuration;
class CUDPSocket;
class CTCPServer;
class CTCPSocket;


class App{
private:
  bool m_Started;
public:
  CUDPSocket *m_UDPSocket;				// a UDP socket for sending broadcasts and other junk (used with !sendlan)
  CTCPServer *m_ReconnectSocket;			// listening socket for GProxy++ reliable reconnects
  vector<CTCPSocket *> m_ReconnectSockets;// vector of sockets attempting to reconnect (connected but not identified yet)
  vector<BYTEARRAY> m_LocalAddresses;		// vector of local IP addresses
        
  App(Configuration cfg);
  ~App();
  
  bool Update( long usecBlock );
};

#endif // APP_H
