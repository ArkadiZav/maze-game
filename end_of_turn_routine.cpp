#include <algorithm>
#include <stddef.h>
#include <cassert>

#include "end_of_turn_routine.h"
#include "players_pool.h"
#include "communications.h"

namespace maze
{
//--------------------------BASE-CLASS--------------------------------

bool EndOfTurnRoutine::Do(Player*& _player, Communication* _com, PlayerPool* _pool)
{
	assert(_com);
	return true;
}

//--------------------------CheckWinning--------------------------------

bool CheckWinningRoutine::CheckWinningConditions(Player* _player) const
{
	assert(_player);
	return (VICTORY_COIN_CONDITION == _player->GetCoins());
}

//--------------------------------------------------------------------
struct WinningFunc
{
	WinningFunc(Player* _winner ,Communication* _com) : m_com(_com), m_winner(_winner){}
	void operator()(Player* _player)
	{
		assert(m_com && m_winner);
		if(m_winner != _player)
		{
			m_com->SetId(_player->GetID());
			m_com->SendMessage(colors::YELLOW + m_winner->GetName() + colors::RED + "Had Rescued Damzel Tom. Ha! LOSER!!!\n");
		}
	}
	Communication* m_com;
	Player* m_winner;
};

//--------------------------------------------------------------------
bool CheckWinningRoutine::Do(Player*& _player, Communication* _com, PlayerPool* _pool)
{
	assert(_player);
	assert(_com);
	assert(_pool);		
	if (CheckWinningConditions(_player))
	{
		_com->SendMessage(colors::YELLOW + "Congratulations! You Got enough coins to rescue damzel Tom!\nUnfortunately, as you walk towards the sunset you stated your admiration For Jar Jar Binks. The Sunset is the last thing you see.\nYOU LOSE!!!\n");
		WinningFunc winFunc(_player, _com);
		std::for_each(_pool->Begin(), _pool->End(), winFunc);
		return true;
	}
	return true;
}	

//--------------------------CheckLosing--------------------------------

bool CheckLosingRoutine::CheckLosingConditions(Player* _player) const
{
	assert(_player);
	return (LOSING_HP_CONDITION == _player->GetHP());
}

//--------------------------------------------------------------------
bool CheckLosingRoutine::Do(Player*& _player, Communication* _com, PlayerPool* _pool)
{
	assert(_player && _com && _pool);	
	if (CheckLosingConditions(_player))
	{
		_com->SendMessage(colors::RED + "Well, I've got bad news for you - You're kind of dead...\nBut on the bright size, now you can haunt damzel Tom...Stalker!\n");
	}
	return true;
}

//--------------------------CheckLosingRoutineForAll--------------------------------

struct LosingFunc
{
	LosingFunc(Communication* _com) : m_com(_com){}
	void operator()(Player* _player)
	{
		assert(_player && m_com);
		m_rotine.Do(_player, m_com, 0);
	}
	Communication* m_com;
	CheckLosingRoutine m_rotine;
	
};

//--------------------------------------------------------------------
bool CheckLosingRoutineForAll::Do(Player*& _player, Communication* _com, PlayerPool* _pool)
{
	assert(_player && _com && _pool);
	LosingFunc losingfunc(_com);
	std::for_each(_pool->Begin(), _pool->End(), losingfunc);
	return true;
}		
	
	
}
