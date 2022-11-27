#pragma once

#include <iostream>
#include <string>

class Message final
{
public:

	Message() = default;
	~Message() = default;

	//геттеры
	const std::string& get_from() const {
		return from_;
	}

	const std::string& get_to() const {
		return to_;
	}

	const std::string& get_text() const {
		return text_;
	}

	const std::string& get_time() const {
		return time_message_;
	}

	//сеттеры
	void set_from(const std::string& from) {
		from_ = from;
	}

	void set_to(const std::string& to) {
		to_ = to;
	}

	void set_text(const std::string& text) {
		text_ = text;
	}

	void set_time(const std::string& time) {
		time_message_ = time;
	}

private:
	std::string from_;
	std::string to_;
	std::string text_;
	std::string time_message_;
};