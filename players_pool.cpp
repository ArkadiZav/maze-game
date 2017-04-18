#include <cassert>
#include "players_pool.h"

namespace maze
{	
PlayerPool::PlayerPool(Room* _startingRoom) : m_startingRoom(_startingRoom)
{
	assert(_startingRoom);	
}

//--------------------------------------------------------------------

PlayerPool::~PlayerPool()
{
	m_playersBySocket.clear();
	m_playersByName.clear();
}

//--------------------------------------------------------------------

bool PlayerPool::AddPlayer(size_t _id, const std::string& _name)
{
	std::map<std::string, Player*>::iterator nameIt = m_playersByName.find(_name);	
	if(m_playersByName.end() != nameIt)	
	{
		return false;
	}
	m_playersBySocket.insert(std::pair<size_t, std::string>(_id, _name));
	Player* player = new Player(_name,m_startingRoom, _id);
	m_playersByName.insert(std::pair<std::string, Player*>(_name, player));
	return true;
}

void PlayerPool::RemovePlayer(size_t _id)
{
	delete m_playersByName[(m_playersBySocket[_id])];
	m_playersByName.erase(m_playersBySocket[_id]);
	m_playersBySocket.erase(_id);
}

//--------------------------------------------------------------------

Player*  PlayerPool::GetPlayer(size_t _id)
{
	std::map<size_t,std::string> ::iterator socketIt = m_playersBySocket.find(_id);	
	if (m_playersBySocket.end() == socketIt)	
	{
		return 0; //TODO throw Exceotion
	}
	return m_playersByName[socketIt->second];
}

//--------------------------------------------------------------------

PlayerPool::Iterator PlayerPool::Begin()
{
	return Iterator(m_playersByName.begin(), m_playersByName);
}

//--------------------------------------------------------------------

PlayerPool::Iterator PlayerPool::End()
{
	return Iterator(m_playersByName.end(), m_playersByName);
}

//--------------------------------------------------------------------

PlayerPool::Iterator::Iterator(std::map<std::string, Player*> ::iterator _it, const std::map<std::string, Player*>& _pool) : m_it(_it), m_pool(_pool)
{
}

//--------------------------------------------------------------------

PlayerPool::Iterator PlayerPool::Iterator::operator++()
{
	return Iterator(++m_it, m_pool);
}

//--------------------------------------------------------------------

Player* PlayerPool::Iterator::operator*() const
{
	return m_it->second;
}

bool operator==(const PlayerPool::Iterator& _it1, const PlayerPool::Iterator& _it2)
{
	return (_it1.m_it == _it2.m_it);
}

bool operator!=(const PlayerPool::Iterator& _it1, const PlayerPool::Iterator& _it2)
{
	return !(operator == (_it1, _it2));
}
	
}
