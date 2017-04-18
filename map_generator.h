#ifndef __MAP__GENERATOR_H__
#define __MAP__GENERATOR_H__

#include <fstream>
#include <string>

#include "uncopyable.h"
#include "tokenizer.h"

namespace maze 
{

class Junction;
class Room;
class Event;
class Monster;

class MapGenerator : private Uncopyable
{
public:
	static const size_t PARAMS_FOR_TREASURE = 6;
	static const size_t PARAMS_FOR_MONSTER = 5;
	static const size_t NUM_OF_ROOM_SUB_TOKENS = 4;
	static const size_t NUM_OF_JUNCTION_SUB_TOKENS = 2;
	
public: 
	MapGenerator(const std::string& _fileName);
	~MapGenerator(); 
	Room* Generate(); // returns root - first room. create rooms and junctions 
	
private:	
	size_t StringToSizet(const std::string& _str) const;
	void CreateJunctions();
	void CreateTreasures();
	void CreateMonsters();
	void CreateRooms();
	Event* CreateEvent(const std::string& _token);
	void InsertJunctionsToRoom(Room* _room, const std::string& _token);
	void SetJunction(const Direction* _direction, Room* _room, Junction* _junction);
	void CreateColorMap();
	
	std::vector<Junction*> m_junctions;
	std::vector<Treasure*> m_treasures;
	std::vector<Monster*> m_monsters;
	std::vector<Event*> m_events;
	std::vector<Room*> m_rooms;
	 
	tokenizer_t m_tokenizer;
	std::string m_fileName;
	std::ifstream m_configurationMap;
	map<std::string,const std::string*> colorsMap;
};

}

#endif // __MAP__GENERATOR_H__
