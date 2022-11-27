#include"Server.h"


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


void Server::chenge_password(Client& client)
{
	std::string password;     //используем для проверки старого и нового пароля
	std::string new_password;

	std::cout << "Enter old password" << std::endl;	
	password = write_password();

	if (password == client.get_password()) 
	{
		password.clear();

		std::cout << "Enter new password" << std::endl;		
		password = write_password();

		std::cout << "Enter the new password again" << std::endl;		
		new_password = write_password();

		if (password == new_password)
		{
			client.set_password(password); //меняем пароль
			std::cout << "Password changed successfully" << std::endl;
		}
		else 
		{
			std::cout << "Passwords do not match" << std::endl;
		}
	}
	else 
	{
		std::cout << "Invalid password" << std::endl;
	}
}


void Server::settings(Client& client)
{
	std::string temp_str;
	bool windows_settings{ true };

	system("cls");
	while (windows_settings)
	{
		std::cout << "Press:" << std::endl;
		std::cout << "1 - chenge password  2 - chenge name  0 - exit " << std::endl;
		getline(std::cin, temp_str);

		switch (temp_str[0])
		{
			case '1':
			{
				chenge_password(client);
				break;
			}
			case '2':
			{
				std::cout << "Write new name" << std::endl;
				getline(std::cin, temp_str);
				client.set_name(temp_str);
				break;
			}
			case '0':
			{
				windows_settings = false;
				break;
			}
			default:
				std::cout << "command not recognized";
		}
	}
}


void Server::create_message(Client & client)
{
	std::string temp_str;
	bool check{ false }; //используем для проверки клиента в базе
	unsigned int index{ 0 };

	std::cout << "Write e-mail to" << std::endl;
	getline(std::cin, temp_str);

	for (size_t i = 0; i < data_base_client_.size(); ++i)
	{
		if (temp_str == data_base_client_.at(i).get_login())
		{
			check = true;
			index = i;
			break;
		}
	}

	if (check)
	{
		Message message;

		//присваиваем поля от кого (from) и кому(to) 
		message.set_from(client.get_login());
		message.set_to(data_base_client_.at(index).get_login());

		//вводим сообщение
		std::cout << "Write text message" << std::endl;
		getline(std::cin, temp_str);
		message.set_text(temp_str);

		//получаем дату и время
		auto now = std::chrono::system_clock::now();
		std::time_t end_time = std::chrono::system_clock::to_time_t(now);
		message.set_time(std::ctime(&end_time));

		//добавляем сообщение клиентам 
		client.arr_message.push_back(message);
		data_base_client_.at(index).arr_message.push_back(message);
	}
	else 
	{
		std::cout << "the specified user does not exist" << std::endl;
		std::cout << "Press enter for continue ...";
		std::cin.get();
	}
}


void Server::show_message(Client& client)
{
	system("cls");

	std::string temp_str; //используется для сортировки сообщений и ввода пользователя
	bool check{ true }; //проверка для бесконечного цикла

	//вывод имеющихся сообщений у пользователя
	if (client.arr_message.empty()) {

		std::cout << "You have no messages" << std::endl;
	}
	else
	{
		for (size_t i = 0; i < client.arr_message.size(); ++i)
		{
			if (client.get_login() == client.arr_message.at(i).get_from())
			{
				temp_str = "\t\t";
			}
			else
			{
				temp_str.clear();
			}

			std::cout << temp_str << client.arr_message.at(i).get_from() << " - > " << client.arr_message.at(i).get_to();
			std::cout << "\t" << client.arr_message.at(i).get_time() << std::endl;

			std::cout << temp_str << client.arr_message.at(i).get_text() << std::endl;
			std::cout << std::endl;
		}
	}

	while (check)
	{
		std::cout << std::endl;
		std::cout << "Press: " << std::endl;
		std::cout << "0 - come back or 1 - create message" << std::endl;
		getline(std::cin, temp_str);

		if (temp_str[0] == '0') 
		{
			check = false;
		}
		else if (temp_str[0] == '1')
		{
			create_message(client);
		}
		else
		{
			std::cout << "command not recognized";
		}
	}
}


bool Server::main_menu(Client& client)
{
	bool m_menu{ true };
	std::string temp_str;

	while (m_menu)
	{
		system("cls");
		std::cout << "Your profile" << std::endl;
		std::cout << "NAME : " << client.get_name() << "\t";
		std::cout << "E-MAIL : " << client.get_login() << "\t";
		std::cout << "MESSAGE (" << client.arr_message.size() << ")" << std::endl;

		std::cout << std::endl;

		std::cout << "1 - show message\t 2 - create message\t 3 - settings\t 0 - exit chat\t 4 - log out" << std::endl;
		getline(std::cin, temp_str);

		switch (temp_str[0]) 
		{
			case '1':
			{
				show_message(client);
				break;
			}
			case '2':
			{
				create_message(client);
				break;
			}
			case '3':
			{
				settings(client);
				break;
			}
			case '4':
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
	std::string login;
	std::string password;
	std::string name;
	std::string temp_str;
	std::string error;

	bool reg_menu{ true };

	while (reg_menu)
	{
		system("cls");
		std::cout << error;
		std::cout << "To choose:" << std::endl;
		std::cout << "1 - Use registration" << std::endl;
		std::cout << "2 - Log in" << std::endl;
		std::cout << "0 - exit" << std::endl;
		error.clear();

		getline(std::cin, temp_str);

		switch (temp_str[0])
		{
			case '1':
			{
				system("cls");

				std::cout << "Write name" << std::endl;
				getline(std::cin, name);

				std::cout << "Write login (e-mail)" << std::endl;
				getline(std::cin, login);

				std::cout << "Write password" << std::endl;			
				temp_str = write_password();

				std::cout << "Write the password again" << std::endl;			
				password = write_password();

				if (temp_str == password)
				{
					Client client(name, login, password);
					data_base_client_.push_back(client);
				}
				else
				{
					error = "Passwords do not match\n";
				}
				break;
			}
			case '2':
			{
				bool check{ false };
				size_t index{ 0 };

				temp_str.clear(); //отчищаем строку

				std::cout << "Write login" << std::endl;
				getline(std::cin, login);

				for (size_t i = 0; i < data_base_client_.size(); ++i)
				{
					if (data_base_client_.at(i).get_login() == login)
					{
						check = true;
						index = i;
						break;
					}
				}

				if (check)
				{
					system("cls");
					for (size_t i = 3; i > 0; --i)
					{
						std::cout << login << std::endl;
						std::cout << "Write password" << std::endl;					
						password = write_password();

						if (data_base_client_.at(index).get_password() == password)
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

					if (check)
					{
						reg_menu = main_menu(data_base_client_.at(index));
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


