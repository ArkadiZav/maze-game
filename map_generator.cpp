#include <sstream>
#include <map>

#include "junctions.h"
#include "treasure.h"
#include "monster.h"
#include "event.h"
#include "rooms.h"
#include "event.h"
#include "maze_exceptions.h"
#include "directions.h"
#include "map_generator.h"

namespace maze
{
	
Event Event::s_instance;
		
MapGenerator::MapGenerator(const std::string& _fileName) : m_fileName(_fileName)
{
	m_configurationMap.open(m_fileName.c_str());
	if (!m_configurationMap.is_open())
	{
		throw(parser_exception::WrongFileException());
	}
}

MapGenerator::~MapGenerator()
{
	m_configurationMap.close();
	m_junctions.clear();
	m_treasures.clear();
	m_monsters.clear();
	m_events.clear();
	m_rooms.clear();
}
	
Room* MapGenerator::Generate()
{	
	CreateColorMap();
	CreateJunctions();
	CreateTreasures();
	CreateMonsters();
	CreateRooms();

	
	return m_rooms[0];	
}

void MapGenerator::CreateColorMap()
{
	colorsMap["G"] = &colors::GREEN;
	colorsMap["R"] = &colors::RED;
	colorsMap["Y"] = &colors::YELLOW;
	colorsMap["M"] = &colors::MAGNETA;
	colorsMap["D"] = &colors::DEFAULT_COLOUR;
	colorsMap["B"] = &colors::LIGHT_BLUE;
	colorsMap["N"] = &colors::NORMAL;
}

void MapGenerator::CreateJunctions()
{
	std::string line;
	m_junctions.push_back(0);
	getline(m_configurationMap,line);

	size_t numOfTokens = m_tokenizer.SeperateToTokens(line);
	for(; numOfTokens; numOfTokens -= NUM_OF_JUNCTION_SUB_TOKENS)
	{
		string token = m_tokenizer.GetToken();
		switch(token[0])
		{
			case 'P':
			{
				m_tokenizer.GetToken();
				Passage* passage = new Passage;
				m_junctions.push_back(passage);	
				break;
			}
			case 'O':
			{
				m_junctions.push_back(new Door(&OpenedDoor::s_instance,*colorsMap[m_tokenizer.GetToken()]));
				break;
			}
			case 'L':
			{

				m_junctions.push_back(new Door(&LockedDoor::s_instance,*colorsMap[m_tokenizer.GetToken()]));
				break;
			}
			case 'U':
			{
				m_junctions.push_back(new Door(&UnlockedDoor::s_instance,*colorsMap[m_tokenizer.GetToken()]));
				break;	 
			}
			default:
			{
				throw(junction_exception::WrongJunctionType());
				break;
			}
		}
	}
}

size_t MapGenerator::StringToSizet(const std::string& _str) const
{
	istringstream ist(_str);
	size_t result;
	return ist >> result ? result : 0;
}

void MapGenerator::CreateTreasures()
{
	m_treasures.push_back(0);
	std::string line;
	getline(m_configurationMap,line);
	size_t numOfTokens = m_tokenizer.SeperateToTokens(line);
	for (; numOfTokens; numOfTokens -= PARAMS_FOR_TREASURE)
	{
		size_t hp = StringToSizet(m_tokenizer.GetToken());
		size_t coins = StringToSizet(m_tokenizer.GetToken());
		size_t keys = StringToSizet(m_tokenizer.GetToken());
		size_t attack = StringToSizet(m_tokenizer.GetToken());
		size_t defence = StringToSizet(m_tokenizer.GetToken());
		std::string description = m_tokenizer.GetToken();
		Treasure* treasure = new Treasure(hp, coins, keys, attack, defence,description);
		m_treasures.push_back(treasure);
	}
}

void MapGenerator::CreateMonsters()
{
	std::string line;
	getline(m_configurationMap,line);
	size_t numOfTokens = m_tokenizer.SeperateToTokens(line);
	for (; numOfTokens; numOfTokens -= PARAMS_FOR_MONSTER)
	{
		std::string name = m_tokenizer.GetToken();
		std::string description = m_tokenizer.GetToken();
		size_t hp = StringToSizet(m_tokenizer.GetToken());
		size_t attack = StringToSizet(m_tokenizer.GetToken());
		size_t defence = StringToSizet(m_tokenizer.GetToken());
		Monster* monster = new Monster(name, description, hp, attack, defence);
		m_monsters.push_back(monster);
	}
}

Event* MapGenerator::CreateEvent(const std::string& _token)
{
	switch(_token[0])
	{
		case 'R':
		{
			return &Event::s_instance;
		}
		case 'T':
		{
			size_t serialNum =  StringToSizet(std::to_string(_token[1]-'0'));
			return new HasTreasure(m_treasures[serialNum]);
		}
		case 'M':
		{
			size_t monsterSerialNum =  StringToSizet(std::to_string(_token[1] -'0'));
			size_t treasureSerialNum =  StringToSizet(std::to_string(_token[3] -'0'));
			return new HasMonster(m_monsters[monsterSerialNum],m_treasures[treasureSerialNum]);
		}
		default:
		{
			throw(event_exception::WrongEventType());
			break;
		}
	}	
	return 0;
}

void MapGenerator::SetJunction(const Direction* _direction, Room* _room, Junction* _junction)
{
	if(_junction)
	{
		_room->AddJunction(_direction, _junction);
		_junction->SetRoom(_room);
	}
}



void MapGenerator::InsertJunctionsToRoom(Room* _room, const std::string& _token)
{
	SetJunction(&North::s_instance, _room, m_junctions[StringToSizet(_token.substr(1,2))]);
	SetJunction(&East::s_instance, _room, m_junctions[StringToSizet(_token.substr(4,5))]);
	SetJunction(&South::s_instance, _room, m_junctions[StringToSizet(_token.substr(7,8))]);
	SetJunction(&West::s_instance, _room, m_junctions[StringToSizet(_token.substr(10,11))]);
}

void MapGenerator::CreateRooms()
{
	std::string line;
	getline(m_configurationMap,line);
	size_t numOfTokens = m_tokenizer.SeperateToTokens(line);
	for(; numOfTokens; numOfTokens -= NUM_OF_ROOM_SUB_TOKENS)
	{
		size_t serialNum =  StringToSizet( m_tokenizer.GetToken());
		std::string description= m_tokenizer.GetToken();
		Event* event = CreateEvent(m_tokenizer.GetToken());
		Room* room  = new Room(serialNum, description, event);
		InsertJunctionsToRoom(room, m_tokenizer.GetToken());
		room->SetEvent(event);
		m_rooms.push_back(room);
	}	
}
}
