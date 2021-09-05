#ifndef __MY_SERVER__
#define __MY_SERVER__

#include "../server/server.hpp"
#include "../drive/APdrive.hpp"


class MyServer : public Server {
private:
	
public:
  MyServer(int port = 5000);
  
};

#endif