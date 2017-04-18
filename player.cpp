#include <algorithm>
#include <time.h> // used for srand
#include <cassert>

#include "communications.h"
#include "directions.h"
#include "communications.h"
#include "treasure.h"
#include "rooms.h"
#include "player.h"

namespace maze
{
//--------------------------CHARACTER--------------------------------	

Character::Character(const std::string& _name, Room* _room) : m_attributes(_name), m_currentRoom(_room)
{
}


//--------------------------------------------------------------------
size_t Character::CalculateAttackDamage(Character* _attackedCharacter, size_t _modifier)
{
	assert(_attackedCharacter);
	srand(time(0));
	int combatDiff = std::max(1, (static_cast<int> (m_attributes.m_attackLevel - _attackedCharacter->m_attributes.m_defenceLevel)));
	return combatDiff + (rand() % ((combatDiff + CONSTANT_ATTACK_MODFIER) * _modifier)); //+ 5 * (_modifier - 2)- combatDiff + 1));
}

//--------------------------------------------------------------------
void Character::ChangeHP(int _amount)
{
	assert(_amount);
	int newAttr = m_attributes.m_HP + _amount;
	m_attributes.m_HP = (newAttr > 0) ? newAttr : 0;
}

//--------------------------------------------------------------------

size_t Character::AttackCharacter(Character* _attackedCharacter, size_t _modifier, Communication* _com)
{
	assert(_attackedCharacter && _com);
	size_t damage = CalculateAttackDamage(_attackedCharacter, _modifier);
	_attackedCharacter->ChangeHP(-1 * damage);
	return damage;
}

//--------------------------------------------------------------------

const std::string& Character::GetName()
{
	return m_attributes.m_name;
}


//--------------------------------------------------------------------
size_t Character::GetHP() const
{
	return m_attributes.m_HP;
}

//--------------------------------------------------------------------

CharacterAttributes& Character::GetAttributes()
{
	return m_attributes;
}

//--------------------------------------------------------------------

void Character::SetRoom(Room* _room)
{
	assert(_room);
	m_currentRoom = _room;
}

//--------------------------------------------------------------------

Room* Character::GetRoom()
{
	return m_currentRoom;
}

//----------------------------PLAYER-------------------------------

Player::Player(const std::string& _name, Room* _room,  size_t _id) : Character(_name, _room), m_direction(const_cast <North*>(&North::s_instance)), m_directionToPreviousRoom(const_cast <North*>(&North::s_instance)), m_id(_id)
{
	assert(_room);
	m_currentRoom->AddPlayerToRoom(this);
}

//--------------------------------------------------------------------

void Player::TurnRight()
{
	m_direction = const_cast<Direction*>(&m_direction->TurnRight());
}

//--------------------------------------------------------------------

void Player::TurnLeft()
{
	m_direction = const_cast<Direction*>(&m_direction->TurnLeft());
}

//--------------------------------------------------------------------
void Player::TurnBack()
{
	std::swap(m_directionToPreviousRoom,m_direction);
}

//--------------------------------------------------------------------
void Player::SetPreviousRoomDirection()
{
	m_directionToPreviousRoom = const_cast<Direction*>(&m_direction->TurnBack());
}
	
//--------------------------------------------------------------------

void Player::GoToRoom(Room* _room)
{
	assert(_room);
	SetPreviousRoomDirection(); 
	m_currentRoom = _room;
}	

//--------------------------------------------------------------------

bool Player::UseKey()
{
	if (!m_possesions.m_numOfKeys)
	{
		return false;
	}
	--m_possesions.m_numOfKeys;
	return true;
}	

//-------------------------------------------------------------------

Possesions& Player::GetPossesions()
{
	return m_possesions;
}

//--------------------------------------------------------------------

std::string Player::GetDirectionName() const
{
	return m_direction->GetName();
}

//--------------------------------------------------------------------

void Player::TakeTreasure(Treasure* _treasure, Communication* _com)
{
	assert(_treasure && _com);
	if(_treasure->Take())
	{
		m_attributes.m_HP += _treasure->GetHP();
		m_possesions.m_coins += _treasure->GetCoins();
		m_possesions.m_numOfKeys += _treasure->GetNumOfKeys();
		
		m_attributes.m_attackLevel  = std::max(m_attributes.m_attackLevel,_treasure->GetAttack());
		m_attributes.m_defenceLevel  = std::max(m_attributes.m_defenceLevel,_treasure->GetDefence());
		_com->SendMessage("Yay! You have Taken the treasure :-)\n\a");
		return;
	}
	_com->SendMessage("The treasure chest is empty. Can Dana offer you a hug instead?\n");
}

//--------------------------------------------------------------------

void Player::AddCoins(size_t _amount, Communication* _com)
{
	m_possesions.m_coins += _amount;
	_com->SendMessage("You gained " + std::to_string(_amount) + " coins!\n");
}

//--------------------------------------------------------------------

Direction*  Player::GetDirection() 
{
	return m_direction;
}

//--------------------------------------------------------------------
size_t Player::GetID() const
{
	return m_id;
}

//--------------------------------------------------------------------
size_t  Player::GetCoins() const
{
	return m_possesions.m_coins;
}

}
