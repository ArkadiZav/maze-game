#include "treasure.h"

namespace maze
{
	
Treasure::Treasure(size_t _HP, size_t _coins, size_t _numOfKeys, size_t _attackLevel, size_t _defenceLevel, const std::string& _description) 
			: m_HP(_HP), m_coins(_coins), m_numOfKeys(_numOfKeys), m_attackLevel(_attackLevel), m_defenceLevel(_defenceLevel),m_description(_description), m_isTaken(false)
{
}
		
//--------------------------------------------------------------------
size_t Treasure::GetHP() const 
{
	return m_HP;
}

//--------------------------------------------------------------------
size_t Treasure::GetCoins() const 
{
	return m_coins;
}

//--------------------------------------------------------------------
size_t Treasure::GetNumOfKeys() const 
{
	return m_numOfKeys;
}

//--------------------------------------------------------------------
size_t Treasure::GetAttack() const 
{
	return m_attackLevel;
}

//--------------------------------------------------------------------
size_t Treasure::GetDefence() const 
{
	return m_defenceLevel;
}

//--------------------------------------------------------------------
const std::string& Treasure::GetDescription() const
{
	return m_description;
}

//--------------------------------------------------------------------
bool Treasure::Take() 
{
	if (!m_isTaken)
	{
		m_isTaken = true;
		return true;
	}
	return false;
}

}
