#ifndef COMMON_MESSAGE_HPP
#define COMMON_MESSAGE_HPP

#include <string>

class Message
{
public:
	enum Constants
	{
		MAX_BUFFER_SIZE = 1024
	};

	Message()
	{
		data.reserve(MAX_BUFFER_SIZE);
	}

	Message(std::string &&message): data(message)
	{
		data.resize(MAX_BUFFER_SIZE);
	}

	std::string &getData()
	{
		return data;
	}

	const std::string &getData() const
	{
		return data;
	}

	size_t getDataSize() const
	{
		return data.size();
	}

private:
	std::string data;
};

#endif // COMMON_MESSAGE_HPP
