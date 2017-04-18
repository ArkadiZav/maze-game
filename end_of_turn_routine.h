#ifndef __END_OF_TURN_ROUTINE_H__
#define __END_OF_TURN_ROUTINE_H__

#include "uncopyable.h"

namespace maze
{

class Communication;
class Player;
class PlayerPool;

class EndOfTurnRoutine
{
public:
	static const EndOfTurnRoutine s_instance;
	
public:
	virtual bool Do(Player*& _player, Communication* _com, PlayerPool* _pool);
};

class CheckWinningRoutine : public EndOfTurnRoutine
{
public:
	static const CheckWinningRoutine s_instance;
	static const size_t VICTORY_COIN_CONDITION = 1000;
	static const size_t LOSING_HP_CONDITION = 0;
	
public:
	virtual bool Do(Player*& _player, Communication* _com, PlayerPool* _pool);
	
private:
	bool CheckWinningConditions(Player* _player) const;
};

class CheckLosingRoutine : public EndOfTurnRoutine
{
public:
	static const CheckLosingRoutine s_instance;
	static const size_t LOSING_HP_CONDITION = 0;
	
public:
	virtual bool Do(Player*& _player, Communication* _com, PlayerPool* _pool);
	
protected:
	bool CheckLosingConditions(Player* _player) const;
};

class CheckLosingRoutineForAll : public EndOfTurnRoutine
{
public:
	static const CheckLosingRoutineForAll s_instance;
	
public:
	virtual bool Do(Player*& _player, Communication* _com, PlayerPool* _pool);
};


}

#endif /*ifndef __END_OF_TURN_ROUTINE_H__*/
