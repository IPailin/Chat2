#pragma once

#include <iostream>
#include <vector>
#include <string>

#include"Message.hpp"

class Client final
{

public:
	std::vector<Message> arr_message;

	Client(const std::string& name, const std::string& login, const std::string& password) : name_{ name }, login_{ login }, password_{ password }
	{
	}
	Client() = default;

	~Client() = default;

	//геттеры
	const std::string& get_login() const {
		return login_;
	}

	const std::string& get_name() const {
		return name_;
	}

	const std::string& get_password() const {
		return password_;
	}

	//сеттеры
	void set_name(const std::string& name) {
		name_ = name;
	}

	void set_login(const std::string& login) {
		login_ = login;
	}

	void set_password(const std::string& password) {
		password_ = password;
	}

private:
	std::string login_;
	std::string password_;
	std::string name_;

};