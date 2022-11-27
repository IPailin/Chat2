#include "Client.hpp"
#include "Message.hpp"
#include "Server.h"

int main()
{
	Server serv;
	serv.start_chat();

	return 0;
}

