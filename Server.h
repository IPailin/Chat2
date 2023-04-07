#pragma once

#include <string>
#include <iostream>

#include<conio.h>
#include<chrono>

#include "Database.h"
#include "Client.hpp"
#include "Message.hpp"


class Server{

private:
    Database database;

public:

    Server() = default;
    ~Server() = default;

    void start_chat();
    std::string write_password();
    bool main_menu(int index);
    void show_message(int index);
    void create_message(int index);
};


