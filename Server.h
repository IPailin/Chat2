#pragma once
#pragma warning(disable : 4996)

#include <iostream>
#include <vector>
#include <chrono>
#include <limits>
#include<string>
#include<conio.h>

#include"Client.hpp"
#include"Message.hpp"

class Server final {

private:	
	std::vector<Client> data_base_client_;
	

	/*!
		Функция используется для ввода пароль пользователем, при вводе пароля символыы ввода заменяются звездочками
		@return возвращает строку, строка является паролем введый пользователем
	*/
	std::string write_password();	


	/*!
		Функция выполняет изменение пароля для пользователя который в данный момент залогинен
		@param[out] client - пользователь который находится в системе
	*/
	void chenge_password(Client& client);


	/*!
		Функция предоставляет возможность менять поля пользователя
		@param[out] client - пользователь который находится в системе
	*/
	void settings(Client& client);
	

	/*!
		Функция используется для создания сообщений и отправки сообщений любым пользователям которые есть в базе
		@param[out] client - пользователь который находится в системе
	*/
	void create_message(Client& client);
	

	/*!
		Функция отображает все сообщения пользователей
		@param[out] client - пользователь который находится в системе
	*/
	void show_message(Client& client);


	/*!
		Функция предлагает различный функционал для пользователя после прохождения авторизации
		@param[out] client - пользователь который находится в системе
		@return булево значение возвращается в зависимости от пользователя, закрыть чат или сменить пользователя
	*/
	bool main_menu(Client& client);

public:

	Server() = default;	
	~Server() = default;

	/*!
		Функция запускает чат и предоставляет возможность зарегистрироватся или зайти в профиль пользователя		
	*/
	void start_chat();
};
