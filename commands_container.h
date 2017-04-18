#ifndef __COMMANDS__CONTAINER_H__
#define __COMMANDS__CONTAINER_H__

#include <map>
#include "commands.h"
#include "uncopyable.h"

namespace maze
{
	
class Communication;

class CommandsContainer : private Uncopyable
{
public:
	virtual ~CommandsContainer() {};
	virtual void AddCommand(Command* _command, const std::string& _commandName) = 0;
	virtual Command* GetCommand(const std::string& _commandName) const = 0;	
};

class DefaultCommandsContainer: public CommandsContainer
{
public:
	DefaultCommandsContainer(Communication* _com);
	virtual ~DefaultCommandsContainer();
	virtual void AddCommand(Command* _command, const std::string& _commandName);
	virtual Command* GetCommand(const std::string& _commandName) const;
	
private:
	std::map<std::string, Command*> m_commandMap;
	Communication* m_com;
};

}

#endif // __COMMANDS__CONTAINER_H__
