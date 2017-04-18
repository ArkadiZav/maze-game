#ifndef __COMMANDS_H__
#define __COMMANDS_H__

#include <string>
#include "uncopyable.h"
#include "end_of_turn_routine.h"

namespace maze
{
class Room;
class Junction;
class Communication;
class Player;

class Command : private Uncopyable
{
public:
	Command(Communication* _com);
	virtual const EndOfTurnRoutine& operator() (Player*_player) = 0;
	
protected:
	Junction* GetJunction(Player*_player);
	void SendRoomDescription(Player*_player);
	void SetIdAndSendMessage(Player*_player, const std::string& _msg);
	
	Communication* m_com;
};

//ADD iddqd command

class Look: public Command
{
public:
	Look(Communication* _comm);
	const EndOfTurnRoutine&  operator()(Player*_player);
};

class Walk: public Command
{
public:
	Walk(Communication* _comm);
	const EndOfTurnRoutine& operator()(Player*_player);
};

class Right: public Command
{
public:
	Right(Communication* _comm);
	const EndOfTurnRoutine&  operator()(Player*_player);
};

class Left: public Command
{
public:
	Left(Communication* _comm);
	const EndOfTurnRoutine&  operator()(Player*_player);
};

class Take: public Command
{
public:
	Take(Communication* _comm);
	const EndOfTurnRoutine&  operator()(Player*_player);
};

class Open: public Command
{
public:
	Open(Communication* _comm);
	const EndOfTurnRoutine&  operator()(Player*_player);
};

class Close: public Command
{
public:
	Close(Communication* _comm);
	const EndOfTurnRoutine&  operator()(Player*_player);
};

class Lock: public Command
{
public:
	Lock(Communication* _comm);
	const EndOfTurnRoutine&  operator()(Player*_player);
};

class Unlock: public Command
{
public:
	Unlock(Communication* _comm);
	const EndOfTurnRoutine&  operator()(Player*_player);
};

class Back: public Command
{
public:
	Back(Communication* _comm);
	const EndOfTurnRoutine&  operator()(Player*_player);
};

class Attack: public Command
{
public:
	static const size_t ATTACK_MODIFIER = 2; 
public:
	Attack(Communication* _comm);
	const EndOfTurnRoutine&  operator()(Player*_player);
};

class Rage: public Command
{
public:
	static const size_t ATTACK_MODIFIER = 2; 
	static const size_t RAGE_MODIFIER = 3; 
	static const size_t HIT_OTHER_PLAYER_MODIFIER = 3;
public:
	Rage(Communication* _comm);
	const EndOfTurnRoutine&  operator()(Player*_player);
private:
	Player* GetRandomPlayer(Player* _player);
	void SendDamageMessages(Player* _attacker, Player* __defender);
	void CheckLosingRotuine(Player* _player);
};

class Status: public Command
{
public:
	Status(Communication* _comm);
	const EndOfTurnRoutine&  operator()(Player*_player);
};

class Talk: public Command
{
public:
	Talk(Communication* _comm);
	const EndOfTurnRoutine&  operator()(Player*_player);
};

class Invalid: public Command
{
public:
	Invalid(Communication* _comm);
	const EndOfTurnRoutine&  operator()(Player*_player);
};

class Quit: public Command
{
public:
	Quit(Communication* _comm);
	const EndOfTurnRoutine&  operator()(Player*_player);
};

class Help: public Command
{
public:
	Help(Communication* _comm);
	const EndOfTurnRoutine&  operator()(Player*_player);
};

class Win: public Command
{
public:
	Win(Communication* _comm);
	const EndOfTurnRoutine&  operator()(Player*_player);
};

} //namespace maze

#endif /*ifndef __COMMANDS_H__*/
