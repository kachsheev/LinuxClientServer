#ifndef COMMON_MESSAGE_HPP
#define COMMON_MESSAGE_HPP

#include <string>

class Message
{
public:
	enum Constants
	{
		MAX_BUFFER_SIZE = 256
	};

	Message()
	{
		data.reserve(MAX_BUFFER_SIZE);
	}

	Message(std::string &&message): data(message)
	{
		data.resize(MAX_BUFFER_SIZE);
	}

	const char *getData() const
	{
		return data.data();
	}

	size_t getDataSize() const
	{
		return data.size();
	}

	void clear()
	{
		data.clear();
	}

	std::string &getString()
	{
		return data;
	}

private:
	std::string data;
};

#endif // COMMON_MESSAGE_HPP
