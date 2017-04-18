#ifndef __PLAYER__CREATOR__RELEASER_H__
#define __PLAYER__CREATOR__RELEASER_H__

#include <cassert>

#include "rooms.h"
#include "graphics.h"

namespace maze
{

struct PlayerCreator
{
	PlayerCreator(Communication* _com, PlayerPool*	_pool) : m_com(_com), m_pool(_pool){};
	void operator()(size_t _connectionId)
	{
		assert(m_com);
		assert(m_pool);		
		m_com->GetMessage();
		Graphics graphics;
		graphics.ShowHeader(m_com);
		m_com->SendMessage("Hello, and welcome to The Quest For Damsel Tom ©.\nPlease enter your name.\n");
		while (!m_pool->AddPlayer(_connectionId, m_com->GetMessage()))
		{
			m_com->SendMessage("Name Is already taken. Please try again. May I suggest Mario?\n");
		}
		Look lookFunctor(m_com);
		lookFunctor(m_pool->GetPlayer(_connectionId));
	}
	Communication* m_com;
	PlayerPool*	m_pool;
};

struct PlayerReleaser
{
	PlayerReleaser(Communication* _com, PlayerPool*	_pool) : m_com(_com), m_pool(_pool){}; 
	void operator()(size_t _connectionId)
	{
		assert(m_com);
		assert(m_pool);		
		Player* player = m_pool->GetPlayer(_connectionId);
		player->GetRoom()->RemovePlayerFromRoom(player);
		m_pool->RemovePlayer(_connectionId);
	}
	Communication* m_com;
	PlayerPool*	m_pool;
};

}
#endif // __PLAYER__CREATOR__RELEASER_H__
