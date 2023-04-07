#pragma once

#include <string>
#include <vector>
#include <map>

#include "Client.hpp"
#include "Message.hpp"


class Database{

public:

    std::vector <Client> base_client;
    std::vector < std::vector<Message> > basa_message;
    std::map <std::string, int> map_logint_client;

    int count {0};
};
