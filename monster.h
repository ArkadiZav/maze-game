#ifndef __MONSTER_H__
#define __MONSTER_H__

#include <stddef.h>

#include "player.h"

namespace maze
{

class Treasure;
	
class Monster : public Character
{
public:
	Monster(const std::string& _name,const std::string& _description, size_t _HP, size_t _attack, size_t _defence, Room* _room = 0);
	const std::string& GetDescription() const;
	virtual ~Monster();
	
protected:
	const std::string m_description;
};

}

#endif // __MONSTER_H__
