#include <cassert>

#include "communications.h"
#include "monster.h"
#include "rooms.h"
#include "treasure.h"
#include "event.h"

namespace maze
{
	
//--------------------------BASE-CLASS--------------------------------

Event* Event::TakeTreasure(Player*_character, Communication* _com)
{
	assert(_character && _com);
	_com->SendMessage("There is no Treasure To take!\n");
	return this;
}

//---------------------------------------------------------
Event* Event::FightMonster(Player* _player, size_t _modifier, Communication* _com)
{
	assert(_player && _com);	
	_com->SendMessage("There is no one to attack!\n");
	return this;
}

//---------------------------------------------------------
std::string Event::GetName() const
{
	return "Class";
}

//---------------------------------------------------------
std::string Event::GetDrawing() const
{
	return "         ";
}

//---------------------------------------------------------
std::string Event::GetDescription() const
{
	return "";
}


//--------------------------HasTreasure--------------------------------
HasTreasure::HasTreasure(Treasure* _treasure) : m_treasureContent(_treasure)
{
	assert(_treasure);
}

//---------------------------------------------------------
Event* HasTreasure::TakeTreasure(Player*_character, Communication* _com)
{
	assert(_character && _com);
	_character->TakeTreasure(m_treasureContent, _com);
	_com->SendMessage(colors::MAGNETA + m_treasureContent->GetDescription());
	return new Event;
}

//---------------------------------------------------------
std::string HasTreasure::GetDescription() const
{
	return colors::GREEN + "Thers is a treasure in the room\n" + colors::DEFAULT_COLOUR;
}

//---------------------------------------------------------
std::string HasTreasure::GetDrawing() const
{
	return "[̲̅$̲̅(̲̅ιοο̲̅)̲̅$̲̅]";
}


//--------------------------HasMonster--------------------------------
HasMonster::HasMonster(Monster* _monster) : m_monster(_monster), m_treasure(0)
{
	assert(m_monster);
}

//---------------------------------------------------------
HasMonster::HasMonster(Monster* _monster, Treasure* _treasure) : m_monster(_monster), m_treasure(_treasure)
{
	assert(m_monster);
}

//---------------------------------------------------------
std::string HasMonster::GetDescription() const
{
	return colors::RED + "Thers is a monster in the room: " + m_monster->GetName() + "\n" + colors::MAGNETA + m_monster->GetDescription() + "\n" + colors::LIGHT_BLUE;
}

//---------------------------------------------------------
Event* HasMonster::TakeTreasure(Player* _character, Communication* _com)
{
	assert(_character && _com);
	if(m_monster->GetHP())
	{
		_com->SendMessage("You have to kill The Monster First!\n");
		return this;
	}
	_character->TakeTreasure(m_treasure, _com);
	return this;
}

//---------------------------------------------------------
void HasMonster::FightRoutine(Character* _attacker, Character* _defender, size_t _modifier, Communication* _com)
{
	assert(_attacker && _defender && _com);
	size_t damage = _attacker->AttackCharacter(_defender, _modifier, _com);
	_com->SendMessage(_attacker->GetName() + " Has done: " +  std::to_string(damage) + " points of damage to " + _defender->GetName() +  "\n");
}

//---------------------------------------------------------
Event* HasMonster::FightMonster(Player* _character, size_t _modifier, Communication* _com)
{
	assert(_character && _com);
	if (m_monster->GetHP())
	{
		FightRoutine(_character, m_monster, _modifier, _com);
		FightRoutine(m_monster, _character, MONSTER_ATTACK_MODIFIER, _com);
		if (!m_monster->GetHP())
		{
			_com->SendMessage(colors::RED + "Woo-Hoo! You've killed the monster!\n");
			if (m_treasure)
			{
				_com->SendMessage(colors::GREEN + "The monster left a treasure!\n");
				//_com->SendMessage(_character->GetRoom()->GetRoomDescription(_character->GetDirectionName()));
				HasTreasure* newMe = new HasTreasure(m_treasure);
				return newMe;
			}
			_com->SendMessage(colors::MAGNETA + "unfortunately the monster had not left a treasure...\n");
			return new Event;
		}
	}
	else
	{
		_com->SendMessage(colors::RED + "The monster is already Dead!!!\n");
	}
	return this;
}

//---------------------------------------------------------
std::string HasMonster::GetDrawing() const
{
	return " \,,/(◣_◢)\,,/ ";
}

}
