#ifndef __ATTRIBUTES_H__
#define __ATTRIBUTES_H__

#include <string>
#include "uncopyable.h"

namespace maze
{

class CharacterAttributes : private Uncopyable
{
public:
	friend class Player;
	friend class Character;
	friend class Monster;
	friend class TreasureRoom;
	
	const static size_t INITIAL_HP = 100;
	const static size_t INITIAL_ATTACK = 1;
	const static size_t INITIAL_DEFENCE = 1;
	
public:	
	CharacterAttributes(const std::string& _name);
	int GetHP() const;
	size_t GetAttack() const;
	size_t GetDefence() const;
	
private:
	const std::string m_name;
	int m_HP;
	size_t m_attackLevel; 
	size_t m_defenceLevel;
};

class Possesions : private Uncopyable
{
public:
	friend class Character;
	friend class Player;
	friend class TreasureRoom;

	const static size_t INITIAL_COINS = 0;
	const static size_t INITIAL_KEYS = 1;

public:
	Possesions();
	size_t GetCoins() const;
	size_t GetNumOfKeys() const;
	 
private:
	size_t m_coins;
	size_t m_numOfKeys;
};

}

#endif //__ATTRIBUTES_H__
