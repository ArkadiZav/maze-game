#ifndef __GAME_H__
#define __GAME_H__

#include <string>
#include <map>

#include "uncopyable.h"

namespace maze
{

class Communication;
class Player;
class PlayerPool;
class CommandsContainer;
	
class Game : private Uncopyable
{
public:
	static const size_t VICTORY_COIN_CONDITION = 1000;
	static const size_t LOSING_HP_CONDITION = 0;
	
public:
	Game(CommandsContainer* _commands, Communication* _com, PlayerPool* _pool);
	void Play();
	
private:
	void EndTurnRoutine(Player* _player);

	const CommandsContainer* m_commands;
	Communication* m_com;
	PlayerPool* m_pool;
	bool m_toPlay;
};
	
	
}


#endif /*ifndef __GAME_H__*/
