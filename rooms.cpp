#include <algorithm>
#include <iostream>
#include <cassert>

#include "communications.h"
#include "junctions.h"
#include "directions.h"
#include "player.h"
#include "event.h"
#include "rooms.h"

namespace maze
{
Wall Wall::s_instance;

//--------------------------BASE-CLASS--------------------------------

Room::Room(size_t _serial, const std::string& _description, Event* _event) 
		: m_serialNum(_serial), m_description(_description), m_event(_event)
{
	assert(_event);
	m_directions[&North::s_instance] = &Wall::s_instance;
	m_directions[&East::s_instance] = &Wall::s_instance;
	m_directions[&South::s_instance] = &Wall::s_instance;
	m_directions[&West::s_instance] = &Wall::s_instance;
	InitializeMap();
}

//--------------------------------------------------------------------
void Room::AddJunction(const Direction* _direction, Junction* _junction)
{
	assert(_direction && _junction);
	m_directions[_direction] = _junction;
}
	
//--------------------------------------------------------------------
	
Junction* Room::GetJunction(Direction* _direction) 
{
	assert(_direction);
	return m_directions[_direction];
}

//--------------------------------------------------------------------

std::string Room::GetRoomDescription(const std::string& _direction) 
{
	std::string description = "You have entered room no. " + std::to_string(m_serialNum) + " : " + m_description + ". \n" + m_event->GetDescription() + ". \n" 
					   + DrawMap(_direction)
					   + "You are facing " + _direction + ".\n" 
					   + "There are " + std::to_string(m_players.size()) + " players in the room\n";
	return description;
}

//--------------------------------------------------------------------

void Room::AddPlayerToRoom(Player* _character)
{
	assert(_character);
	m_players.insert(_character);
}
//--------------------------------------------------------------------
void Room::RemovePlayerFromRoom(Player* _character)
{
	assert(_character);
	m_players.erase(_character);
}

//-------------------------------------------------------------------
Player* Room::GetRandomPlayerInRoom()
{
	srand(time(0));
	int whoToAttack = rand() % m_players.size();
	itr = m_players.begin();
	advance(itr, whoToAttack);
	return *itr;	
}

//-------------------------------------------------------------------
struct TalkFunc
{
	TalkFunc(const std::string& _name, const std::string& _msg, Communication* _com) : m_com(_com), m_name(_name), m_msg(_msg){}
	void operator()(Player* _character)
	{
		assert(m_com);	
		m_com->SetId(_character->GetID());
		m_com->SendMessage(m_name + " says: " + m_msg + "\n" );
	}
	Communication* m_com;
	const std::string& m_name;
	const std::string& m_msg;
};

//--------------------------------------------------------------------
void Room::SendMessageToPlayersInRoom(const std::string& _name,const std::string& _msg, Communication* _com)
{
	assert(_com);
	TalkFunc talkFunctor(_name, _msg, _com);
	size_t idToSave = _com->GetId();
	std::for_each(m_players.begin(), m_players.end(), talkFunctor);
	_com->SetId(idToSave);
}

//--------------------------------------------------------------------
size_t Room::GetNumOfPlayersInRoom() const
{
	return m_players.size();
}

//--------------------------------------------------------------------
void Room::InitializeMap()
{
	DRAWINGS["North"] = "^";
	DRAWINGS["West"] = "<";
	DRAWINGS["East"] = ">";
	DRAWINGS["South"] = "v";
	DRAWINGS["NWall"] = "---";
	DRAWINGS["WWall"] = "|  ";
	DRAWINGS["SWall"] = "---";
	DRAWINGS["EWall"] = "  |";
	DRAWINGS["NPassage"] = "   ";
	DRAWINGS["WPassage"] = "   ";
	DRAWINGS["SPassage"] = "   ";
	DRAWINGS["EPassage"] = "   ";
	DRAWINGS["NClosed Door"] = "|.|";
	DRAWINGS["WClosed Door"] = "|.|";
	DRAWINGS["SClosed Door"] = "|.|";
	DRAWINGS["EClosed Door"] = "|.|";
	DRAWINGS["NLocked Door"] = "|x|";
	DRAWINGS["WLocked Door"] = "|x|";
	DRAWINGS["SLocked Door"] = "|x|";
	DRAWINGS["ELocked Door"] = "|x|";
	DRAWINGS["NOpen Door"] = "| |";
	DRAWINGS["WOpen Door"] = "| |";
	DRAWINGS["SOpen Door"] = "| |";
	DRAWINGS["EOpen Door"] = "| |";
}


//--------------------------------------------------------------------

std::string Room::DrawMap(const std::string& _direction)
{
	Junction* northJunction =  m_directions.find(&North::s_instance)->second;
	Junction* eastJunction =  m_directions.find(&East::s_instance)->second;
	Junction* southJunction =  m_directions.find(&South::s_instance)->second;
	Junction* westJunction =  m_directions.find(&West::s_instance)->second;
	std::string north = "N" + northJunction->GetName();
	std::string east = "E" + eastJunction->GetName();
	std::string south = "S" + southJunction->GetName();
	std::string west = "W" + westJunction->GetName();
	std::string content = m_event->GetDrawing();
	
	std::string roomMap = "----------------" + northJunction->GetColour() + DRAWINGS[north] + colors::DEFAULT_COLOUR +"----------------\n"
						+ "|                                 |\n"
						+ "|                                 |\n"
						+ "|                                 |\n"
						+ "|                                 |\n"
						+ "|                                 |\n"
						+ westJunction->GetColour() + DRAWINGS[west] + colors::DEFAULT_COLOUR +"              " + DRAWINGS[_direction] + "              " + eastJunction->GetColour() +  DRAWINGS[east] + colors::DEFAULT_COLOUR + "\n"
						+ "|                                 |\n"
						+ "|                                 |\n"
						+ "|                                 |\n"
						+ "|            " + colors::YELLOW + content + colors::DEFAULT_COLOUR + "            |\n"
						+ "|                                 |\n"
						+ "----------------" +southJunction->GetColour()+ DRAWINGS[south] +colors::DEFAULT_COLOUR + "----------------\n";
	return roomMap;
}


//--------------------------------------------------------------------

void Room::TakeTreasure(CharacterAttributes& _attr,Possesions& _possesions, Communication* _com)
{
	assert(_com);
	_com->SendMessage("There is no treasure in this room\n");
}

//--------------------------------------------------------------------
Event* Room::GetEvent()
{
	return m_event;
}

//--------------------------------------------------------------------
void Room::SetEvent(Event* _event)
{
	assert(_event);
	m_event  = _event;
}

//--------------------------------------------------------------------
void Room::ReplaceEvent(Event* _event)
{
	assert(_event);
	Event* oldEvent = m_event;
	m_event  = _event;
	delete oldEvent;
}

//--------------------------------------------------------------------

Room::~Room()
{
	delete m_event;
}

}
