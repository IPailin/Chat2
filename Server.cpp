#include "Server.h"

void Server::create_message(int index)
{
    std::string user_enter;

    std::cout << "Write e-mail to" << std::endl;
    getline(std::cin, user_enter);

    auto real_client = database.map_logint_client.find(user_enter);

    if(real_client != database.map_logint_client.end())
    {
        Message message;

        //присваиваем поля от кого (from) и кому(to)
        message.set_from(database.base_client[index].get_login());
        message.set_to(database.base_client[real_client->second].get_login());

        //вводим сообщение
        std::cout << "Write text message" << std::endl;
        getline(std::cin, user_enter);
        message.set_text(user_enter);

        //получаем дату и время
        auto now = std::chrono::system_clock::now();
        std::time_t end_time = std::chrono::system_clock::to_time_t(now);
        message.set_time(std::ctime(&end_time));

        //добавляем сообщение клиентам
        database.basa_message[index].push_back(message);
        database.basa_message[real_client->second].push_back(message);
    }
    else
    {
        std::cout << "the specified user does not exist" << std::endl;
        std::cout << "Press enter for continue ...";
        std::cin.get();
    }
}


void Server::show_message(int index)
{
    std::string space; //используется для сортировки сообщений и ввода пользователя

    if(database.basa_message[index].empty())
    {
        std::cout << "You have no messages" << std::endl;
    }
    else
    {
        for(size_t i = 0; i < database.basa_message[index].size(); ++i)
        {
            if(database.base_client[index].get_login() == database.basa_message[index].at(i).get_from())
            {
                space = "\t\t";
            }
            else
            {
                space.clear();
            }

            std::cout << space << database.basa_message[index].at(i).get_from() << " - " << database.basa_message[index].at(i).get_to();
            std::cout << "\t" << database.basa_message[index].at(i).get_time() << std::endl;

            std::cout << space << database.basa_message[index].at(i).get_text() << std::endl;
            std::cout << std::endl;
        }
    }
}


bool Server::main_menu(int index){

    std::string user_enter;
    bool m_menu{ true };

    system("cls");

    std::cout << "Your profile" << std::endl;
    std::cout << "NAME : " << database.base_client.at(index).get_name() << "\t";
    std::cout << "E-MAIL : " << database.base_client.at(index).get_login() << "\t";
    std::cout << "MESSAGE (" << database.basa_message[index].size() << ")" << std::endl;

    std::cout << std::endl;

    while(m_menu)
    {
        std::cout << "1 - show message\t 2 - create message\t 0 - exit chat\t 3 - log out" << std::endl;
        getline(std::cin, user_enter);

        switch (user_enter[0])
        {
            case '1':
            {
                show_message(index);
                break;
            }
            case '2':
            {
                create_message(index);
                break;
            }
            case '3':
            {
                m_menu = false;
                break;
            }
            case '0':
            {
                return false;
            }
        }
    }
    return true;
}


void Server::start_chat()
{

    bool reg_menu{ true };

    std::string login;
    std::string password;
    std::string name;

    std::string error;
    std::string enter_user;

    while(reg_menu)
    {

        system("cls");
        std::cout << error;
        std::cout << "To choose:" << std::endl;
        std::cout << "1 - Use registration" << std::endl;
        std::cout << "2 - Log in" << std::endl;
        std::cout << "0 - exit" << std::endl;
        error.clear();

        getline(std::cin, enter_user);

        switch (enter_user[0])
        {
            case '1':
            {
                system("cls");
                std::cout << "Write name" << std::endl;
                getline(std::cin, name);
                std::cout << "Write login (e-mail)" << std::endl;
                getline(std::cin, login);

                std::cout << "Write password" << std::endl;
                enter_user = write_password();

                std::cout << "Write the password again" << std::endl;
                password = write_password();

                if (enter_user == password)
                {
                    Client client(name, login, password);
                    std::vector<Message> vec_mes;

                    database.base_client.push_back(client);
                    database.basa_message.push_back(vec_mes);
                    database.map_logint_client[login] = database.count;
                    database.count++;
                }
                else
                {
                    error = "Passwords do not match\n";
                }

                break;
            }

            case '2':
            {
                std::cout << "Write login" << std::endl;
                getline(std::cin, login);

                bool check {false};
                auto real_client = database.map_logint_client.find(login);

                if(real_client != database.map_logint_client.end())
                {
                    system("cls");

                    for (size_t i = 3; i > 0; --i)
                    {
                        std::cout << login << std::endl;
                        std::cout << "Write password" << std::endl;
                        password = write_password();

                        if (database.base_client.at(real_client->second).get_password() == password)
                        {
                            check = true;
                            break;
                        }
                        else
                        {
                            check = false;
                            std::cout << "invalid password" << std::endl;
                            std::cout << "you have " << i - 1 << " attempts left" << std::endl;
                        }
                    }

                    if(check)
                    {
                        reg_menu = main_menu(real_client->second);
                    }
                }
                else
                {
                    error = "the specified user does not exist\n";
                }

                break;
            }

            case '0':
            {
                reg_menu = false;
                break;
            }
            default:
                error =  "command not recognized\n";
        }
    }
}


std::string Server::write_password()
{
    std::vector<char> password;
    char c{ '\0' };

    //считываем вводимые и вносим их в вектор
    while ((c = _getch()) != '\r')
    {
        password.push_back(c);
        _putch('*'); //меняем символы на звездочки
    }
    std::cout << std::endl;

    //преобразуем вектор в строку
    std::string str(password.begin(), password.end());

    return str;
}

