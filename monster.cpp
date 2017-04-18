#include "monster.h"

namespace maze
{
	
Monster::Monster(const std::string& _name,const std::string& _description, size_t _HP, size_t _attack, size_t _defence, Room* _room)	
				: Character(_name, _room), m_description(_description)
{
	m_attributes.m_HP = _HP;
	m_attributes.m_attackLevel = _attack;
	m_attributes.m_defenceLevel = _defence;
}
	
//--------------------------------------------------------------------
	
Monster::~Monster()	
{
	//delete m_treasureToLeave;
}

//--------------------------------------------------------------------
const std::string& Monster::GetDescription() const
{
	return m_description;
}

}
