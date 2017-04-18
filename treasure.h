#ifndef __TREASURE_H__
#define __TREASURE_H__

#include <string>
#include "uncopyable.h"

namespace maze
{
	
class Treasure : private Uncopyable
{
public:
	Treasure(size_t _HP, size_t _coins, size_t _numOfKeys, size_t _attackLevel, size_t _defenceLevel, const std::string& _description = "");
	size_t GetHP() const;
	size_t GetCoins() const;
	size_t GetNumOfKeys() const;
	size_t GetAttack() const;
	size_t GetDefence() const;
	const std::string& GetDescription() const;
	bool Take();

private:
	size_t m_HP;
	size_t m_coins;
	size_t m_numOfKeys;
	size_t m_attackLevel; 
	size_t m_defenceLevel;
	const std::string m_description;
	bool m_isTaken;
};

}

#endif //__TREASURE_H__
