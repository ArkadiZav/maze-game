#include<cassert>

#include "commands_container.h"

namespace maze
{
	
DefaultCommandsContainer::DefaultCommandsContainer(Communication* _com) : m_com(_com)	
{
	assert(_com);
	m_commandMap["L"] = m_commandMap["look"] = new Look(m_com);
	
	m_commandMap["w"] = m_commandMap["walk"] = new Walk(m_com);
	
	m_commandMap["l"] = m_commandMap["left"] = new Left(m_com);
	
	m_commandMap["r"] = m_commandMap["right"] = new Right(m_com);

	m_commandMap["o"] = m_commandMap["open"] = new Open(m_com);
	
	m_commandMap["c"] = m_commandMap["close"] = new Close(m_com);
	
	m_commandMap["k"] = m_commandMap["lock"] = new Lock(m_com);
	
	m_commandMap["u"] = m_commandMap["unlock"] = new Unlock(m_com);

	m_commandMap["b"] = m_commandMap["back"] = new Back(m_com);

	m_commandMap["s"] = m_commandMap["status"] = new Status(m_com);
	m_commandMap["a"] = m_commandMap["attack"] = new Attack(m_com);
	m_commandMap["t"] = m_commandMap["take"] = new Take(m_com);
	m_commandMap["h"] = m_commandMap["help"] = new Help(m_com);
	m_commandMap["ta"] = m_commandMap["talk"] = new Talk(m_com);
	m_commandMap["ra"] = m_commandMap["rage"] = new Rage(m_com);
	m_commandMap["invalid"] = new Invalid(m_com);
	m_commandMap["quit"] = new Quit(m_com);
	m_commandMap["win"] = new Win(m_com);
}

void DefaultCommandsContainer::AddCommand(Command* _command, const std::string& _commandName)
{
	assert(_command);
	m_commandMap[_commandName] = _command;
}

Command* DefaultCommandsContainer::GetCommand(const std::string& _commandName) const
{
	const std::map<std::string, Command*>::const_iterator it = m_commandMap.find(_commandName);
	return (m_commandMap.end() != it) ? it->second :m_commandMap.find("invalid")->second;
}

DefaultCommandsContainer::~DefaultCommandsContainer()
{
	m_commandMap.clear();
}
	
	
}
