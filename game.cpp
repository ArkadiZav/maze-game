#include <stddef.h>
#include <algorithm>
#include <unistd.h>
#include <cassert>

#include "commands.h"
#include "players_pool.h"
#include "communications.h"
#include "commands_container.h"
#include "game.h"

namespace maze
{

//----------------------------GAME------------------------------------

Game::Game(CommandsContainer* _commands, Communication* _com, PlayerPool* _pool) : 
			m_commands(_commands), m_com(_com), m_pool(_pool), m_toPlay(true)
{
	assert(_commands && _com && _pool);
}	

//--------------------------------------------------------------------

void Game::Play()
{
	while (m_toPlay)
	{
		std::string command = m_com->GetMessage();
		Player* player = m_pool->GetPlayer(m_com->GetId());
		
		Command* cmd = m_commands->GetCommand(command);
		EndOfTurnRoutine& routine = const_cast<EndOfTurnRoutine&>((*cmd)(player));
		m_toPlay = routine.Do(player, m_com, m_pool);
	}
}
	
}
