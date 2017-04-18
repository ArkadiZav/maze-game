#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "attributes.h"

namespace maze
{
class Communication;
class Direction;
class Room;
class Player;
class Command;
class Treasure;

class Character : private Uncopyable
{
public:	
	static const size_t CONSTANT_ATTACK_MODFIER = 5;
public:
	Character(const std::string& _name, Room* _room = 0);
	CharacterAttributes& GetAttributes();
	size_t GetHP() const;//TODO Delete & move to char attributes
	const std::string& GetName();//TODO Delete & move to char attributes
	Room* GetRoom(); 
		
	void SetRoom(Room* _room);
	
	virtual size_t AttackCharacter(Character* _attackedCharacter, size_t _modifier, Communication* _com); //return how many damage the player has done

protected:	
	void ChangeHP(int _amount);
	size_t CalculateAttackDamage(Character* _attackedCharacter, size_t _modifier);
	
	CharacterAttributes m_attributes;
	Room* m_currentRoom; 
};


class Player : public Character
{
public:
	Player(const std::string& _name, Room* _room, size_t _id);
	Possesions& GetPossesions(); 
	size_t GetID() const; 
	size_t GetCoins() const; 
	void AddCoins(size_t _amount, Communication* _com);
	virtual Direction* GetDirection(); 
	std::string GetDirectionName() const; 
	
	virtual void TurnRight(); 
	virtual void TurnLeft(); 
	virtual void TurnBack(); 
	virtual void GoToRoom(Room* _room); 
	virtual bool UseKey(); 
	
	virtual void TakeTreasure(Treasure* _treasure, Communication* _com); 
	
private:
	void SetPreviousRoomDirection(); 
	
	Possesions m_possesions; 
	Direction* m_direction; 
	Direction* m_directionToPreviousRoom; 
	size_t m_id; 
};

}
#endif /*ifndef __PLAYER_H__*/
