#pragma once

#include <string>

class Client {

private:
    std::string name_;
    std::string login_;
    std::string password_;

public:

    Client(const std::string &name, const std::string &login, const std::string &password ) : name_(name), login_(login), password_(password)
    {
    }

    Client() = default;
    ~Client() = default;

    const std::string& get_name() const{
        return name_;
    }

    const std::string& get_login() const{
        return login_;
    }

    const std::string& get_password() const{
        return password_;
    }


    void set_name(const std::string& name){
        name_ = name;
    }

    void set_password(const std::string& password){
        password_ = password;
    }
};
