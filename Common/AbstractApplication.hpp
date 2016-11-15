#ifndef COMMON_ABSTRACTAPPLICATION_HPP
#define COMMON_ABSTRACTAPPLICATION_HPP

#include <string>

class AbstractApplication
{
public:
	AbstractApplication()
	{
	}
	virtual ~AbstractApplication()
	{
	}

	virtual bool start() = 0;
};

#endif // COMMON_ABSTRACTAPPLICATION_HPP
