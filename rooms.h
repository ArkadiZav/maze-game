#ifndef __ROOMS_H__
#define __ROOMS_H__

#include <map>
#include <set>

#include "uncopyable.h"

namespace maze
{

class CharacterAttributes;
class Junction;
class Player;
class Treasure;
class Direction;
class Possesions;
class Communication;
class Event;

class Room : private Uncopyable //- Interface
{
public:
	Room(size_t _serial, const std::string& _description, Event* _event);
	void AddJunction (const Direction* _direction, Junction* _junction);
	
	~Room();
	void TakeTreasure(CharacterAttributes& _attr, Possesions& _possesions, Communication* _com);
	
	Event* GetEvent();
	void SetEvent(Event* _event);
	void ReplaceEvent(Event* _event);
	Junction* GetJunction(Direction* _direction);
	std::string GetRoomDescription(const std::string& _direction);
	
	void AddPlayerToRoom(Player* _character);
	void RemovePlayerFromRoom(Player* _character);
	void SendMessageToPlayersInRoom(const std::string& _name,const std::string& _msg, Communication* _com);
	Player* GetRandomPlayerInRoom();
	size_t GetNumOfPlayersInRoom() const;
	
protected:
	std::string DrawMap(const std::string& _direction);
	void InitializeMap();
	
	const size_t m_serialNum;
	std::string m_description; 
	std::map<const Direction*, Junction*> m_directions;
	std::set<Player*> m_players;
	std::set<Player*>::const_iterator itr;
	Event* m_event;
	std::map<std::string, std::string> DRAWINGS;
};

}
#endif //*ifndef __ROOMS_H__
