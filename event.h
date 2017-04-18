#ifndef __EVENT_H__
#define __EVENT_H__

#include "uncopyable.h"

namespace maze
{
class Character;
class Player;
class Communication;
class Monster;
class Treasure;
	
class Event : private Uncopyable
{
public:
	static Event s_instance;

public:
	virtual Event* TakeTreasure(Player* _character, Communication* _com);
	virtual Event* FightMonster(Player* _character,size_t _modifier, Communication* _com);
	virtual std::string GetDrawing() const;
	virtual std::string GetName() const;
	virtual std::string GetDescription() const;
};

class HasTreasure : public Event
{
public:
	HasTreasure(Treasure* _tresure);
	virtual Event* TakeTreasure(Player*_character, Communication* _com);
	virtual std::string GetDrawing() const;
	virtual std::string GetDescription() const;
	
private:
	Treasure* m_treasureContent;
};

class HasMonster : public Event
{
public:
	const static size_t MONSTER_ATTACK_MODIFIER = 1;
public:
	HasMonster(Monster* _monster);
	HasMonster(Monster* _monster, Treasure* _tresure);
	virtual  Event* TakeTreasure(Player* _character, Communication* _com);
	virtual  Event* FightMonster(Player* _character, size_t _modifier, Communication* _com);
	virtual std::string GetDrawing() const;
	virtual std::string GetDescription() const;

private:
	void FightRoutine(Character* _attacker, Character* _defender, size_t _modifier, Communication* _com);
	
	Monster* m_monster;
	Treasure* m_treasure;	
};


}



#endif /*ifndef __EVENT_H__*/
