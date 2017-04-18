#ifndef __MAZE_EXCEPTIONS_H__
#define __MAZE_EXCEPTIONS_H__

#include <exception>

namespace maze
{
	
class MazeException : public std::exception
{
};	

namespace parser_exception
{
	
class WrongFileException : public MazeException
{
};

} //namespace parser_exception

namespace event_exception
{

class WrongEventType : public MazeException
{
};
	
} //namespace event_exception

namespace junction_exception
{
	
class WrongJunctionType : public MazeException
{
};

class InvalidRoomException : public MazeException
{
};
}
	
} //namespace junction_exception

#endif //__MAZE_EXCEPTIONS_H__

