#ifndef __DIRECTIONS_H__
#define __DIRECTIONS_H__

#include <string>
#include "uncopyable.h"

namespace maze
{
	
class Direction : private Uncopyable
{
public:
	virtual const std::string GetName() const = 0;
	virtual const Direction &TurnLeft() const = 0;
	virtual const Direction &TurnRight() const = 0;
	virtual const Direction &TurnBack() const = 0;
	//virtual const Junction & GetJunction (const Room& _room) const = 0;
};

class North : public Direction
{
public:
	static const North s_instance;
	
public:
	virtual const std::string GetName() const;
	virtual const Direction &TurnLeft() const;
	virtual const Direction &TurnRight() const;
	virtual const Direction &TurnBack() const;
};

class East : public Direction
{
public:
	static const East s_instance;
	
public:
	virtual const std::string GetName() const;
	virtual const Direction &TurnLeft() const;
	virtual const Direction &TurnRight() const;
	virtual const Direction &TurnBack() const;
};

class South : public Direction
{
public:
	static const South s_instance;
	
public:
	virtual const std::string GetName() const;
	virtual const Direction &TurnLeft() const;
	virtual const Direction &TurnRight() const;
	virtual const Direction &TurnBack() const;
};

class West : public Direction
{
public:
	static const West s_instance;
	
public:
	virtual const std::string GetName() const;
	virtual const Direction &TurnLeft() const;
	virtual const Direction &TurnRight() const;
	virtual const Direction &TurnBack() const;
};

}
#endif //__DIRECTIONS_H__
