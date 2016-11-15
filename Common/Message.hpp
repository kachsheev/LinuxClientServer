#ifndef COMMON_MESSAGE_HPP
#define COMMON_MESSAGE_HPP

#include <string>

class Message
{
public:
	Message(std::string &&message);

	std::string &getData()
	{
		return data;
	}

	const std::string &getData() const
	{
		return data;
	}

private:
	std::string data;
};

#endif // COMMON_MESSAGE_HPP
