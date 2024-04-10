#pragma once
#include <iostream>
#include <exception>

class LoadResourceException : public std::exception
{
public:
	explicit LoadResourceException(const char* message) : _message(message) {}
	[[nodiscard]] const char* what() const override { return _message.c_str(); }
private:
	std::string _message;
};

class GameFailureException : public std::exception
{
public:
	explicit GameFailureException(const char* message) : _message(message) {}
	[[nodiscard]] const char* what() const override { return _message.c_str(); }
private:
	std::string _message;
};
