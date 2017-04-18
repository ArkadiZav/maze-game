#include "attributes.h"

namespace maze
{
	
//------------------------CharacterAttributes--------------------------

CharacterAttributes::CharacterAttributes(const std::string& _name) 
	: m_name(_name), m_HP(INITIAL_HP), m_attackLevel(INITIAL_ATTACK), m_defenceLevel(INITIAL_DEFENCE) 
{
}

//--------------------------------------------------------------------

int CharacterAttributes::GetHP() const
{
	return m_HP;
}
size_t CharacterAttributes::GetAttack() const
{
	return m_attackLevel;
}
size_t CharacterAttributes::GetDefence() const
{
	return m_defenceLevel;
}

//--------------------------POSSESIONS--------------------------------

Possesions::Possesions() : m_coins(INITIAL_COINS), m_numOfKeys(INITIAL_KEYS) 
{
}

//--------------------------------------------------------------------

size_t Possesions::GetCoins() const
{
	return m_coins;
}
size_t Possesions::GetNumOfKeys() const
{
	return m_numOfKeys;
}
}
