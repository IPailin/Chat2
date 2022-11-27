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
		������� ������������ ��� ����� ������ �������������, ��� ����� ������ �������� ����� ���������� �����������
		@return ���������� ������, ������ �������� ������� ������ �������������
	*/
	std::string write_password();	


	/*!
		������� ��������� ��������� ������ ��� ������������ ������� � ������ ������ ���������
		@param[out] client - ������������ ������� ��������� � �������
	*/
	void chenge_password(Client& client);


	/*!
		������� ������������� ����������� ������ ���� ������������
		@param[out] client - ������������ ������� ��������� � �������
	*/
	void settings(Client& client);
	

	/*!
		������� ������������ ��� �������� ��������� � �������� ��������� ����� ������������� ������� ���� � ����
		@param[out] client - ������������ ������� ��������� � �������
	*/
	void create_message(Client& client);
	

	/*!
		������� ���������� ��� ��������� �������������
		@param[out] client - ������������ ������� ��������� � �������
	*/
	void show_message(Client& client);


	/*!
		������� ���������� ��������� ���������� ��� ������������ ����� ����������� �����������
		@param[out] client - ������������ ������� ��������� � �������
		@return ������ �������� ������������ � ����������� �� ������������, ������� ��� ��� ������� ������������
	*/
	bool main_menu(Client& client);

public:

	Server() = default;	
	~Server() = default;

	/*!
		������� ��������� ��� � ������������� ����������� ����������������� ��� ����� � ������� ������������		
	*/
	void start_chat();
};
