#include "player.h"
#include "communications.h"
#include "junctions.h"
#include <cassert>
#include <iostream>

namespace maze
{
	
//--------------------------BASE-CLASS--------------------------------
Junction::Junction(const std::string& _color) : m_color(_color)
{
	m_rooms.push_back(0);
	m_rooms.push_back(0);
}

Junction::Junction() : m_color(colors::DEFAULT_COLOUR)
{
	m_rooms.push_back(0);
	m_rooms.push_back(0);
}

const std::string& Junction::GetColour() const
{
	return m_color;
}

Room* Junction::GetFirstRoom()  
{
	return m_rooms[FIRST];
} 

Room* Junction::GetSecondRoom()  
{
	return m_rooms[SECOND];
}

Room* Junction::GetOtherRoom(Room* _room)
{
	assert(_room);
	return (m_rooms[FIRST] == _room)? m_rooms[SECOND] : m_rooms[FIRST];
}

void Junction::SetFirstRoom(Room* _room)
{
	assert(_room);
	m_rooms[FIRST] = _room;
}

void Junction::SetSecondRoom(Room* _room)
{
	assert(_room);
	m_rooms[SECOND] = _room;
}

void Junction::SetRoom(Room* _room)
{
	assert(_room);
	if (m_rooms[FIRST])
	{
		SetSecondRoom(_room);
		return;
	}
	SetFirstRoom(_room);
}

struct WalkThroughFunctor
{
	void WalkThrough(Player*_player, Junction* _junction)
	{
		assert(_player);
		assert(_junction);		
		Room* nextRoom = _junction->GetOtherRoom(_player->GetRoom());
		if (nextRoom)
		{
			_player->GoToRoom(nextRoom);
		}
	}
};	

void Junction::WalkThrough(Player* _player, Communication* _com)
{
	assert(_player && _com);	
	WalkThroughFunctor walkFunc;
	return walkFunc.WalkThrough(_player, this);
}

void Junction::SendDoorErrorMsg(Communication* _com) const
{
	assert(_com);
	_com->SendMessage(colors::YELLOW + "That's not a door!\n");	
}

void Junction::UnlockDoor(Player* _player, Communication* _com)
{
	assert(_player && _com);
	return SendDoorErrorMsg(_com);
}

void Junction::LockDoor(Player* _player, Communication* _com)
{
	assert(_player && _com);
	return SendDoorErrorMsg(_com);
}

void Junction::OpenDoor(Player* _player, Communication* _com)
{
	assert(_player && _com);
	return SendDoorErrorMsg(_com);
}

void Junction::CloseDoor(Player* _player, Communication* _com)
{
	assert(_player && _com);
	return SendDoorErrorMsg(_com);
}

//--------------------------Passage--------------------------------

std::string Passage::GetName() const
{
	return "Passage";
}

//--------------------------Wall-------------------------------
	
std::string Wall::GetName() const
{
	return "Wall";
}

void Wall::WalkThrough(Player*_player, Communication* _com)
{
	_com->SendMessage(colors::YELLOW + "You Shall Not Pass (It's a wall)\n");
}	

//--------------------------DOOR-------------------------------
OpenedDoor OpenedDoor::s_instance;
UnlockedDoor UnlockedDoor::s_instance;
LockedDoor LockedDoor::s_instance;
	
Door::Door(DoorStatus* _doorStatus, const std::string& _color) : Junction(_color), m_doorStatus(_doorStatus)
{
	assert(_doorStatus);
}	
	
std::string Door::GetName() const
{
	return m_doorStatus->GetName();
}

const std::string& Door::GetColour() const
{
	return m_color;
}

void Door::WalkThrough(Player* _player, Communication* _com)
{
	assert(_player);
	m_doorStatus->WalkThrough(_player, _com,this);
}	

void Door::UnlockDoor(Player* _player, Communication* _com)
{
	assert(_player && _com);
	m_doorStatus = m_doorStatus->UnlockDoor(_player, _com);
}

void Door::LockDoor(Player* _player, Communication* _com)
{
	assert(_player && _com);
	m_doorStatus = m_doorStatus->LockDoor(_player, _com);
}

void Door::OpenDoor(Player* _player, Communication* _com)
{
	assert(_player && _com);
	m_doorStatus = m_doorStatus->OpenDoor(_player, _com);
}

void Door::CloseDoor(Player* _player, Communication* _com)
{
	assert(_player && _com);
	m_doorStatus = m_doorStatus->CloseDoor(_player, _com);
}

//--------------------------LockedDoor-------------------------------
void LockedDoor::WalkThrough(Player* _player, Communication* _com, Junction* _junction)
{
	assert(_player && _com && _junction);
	_com->SendMessage(colors::YELLOW + "The door is locked. You need to unlock & open it first\n");
}

std::string LockedDoor::GetName() const
{
	return "Locked Door";
}

DoorStatus* LockedDoor::UnlockDoor(Player* _player, Communication* _com) const
{
	assert(_player && _com);
	if(_player->UseKey())
	{
		_com->SendMessage(colors::GREEN + "You have unlocked the door!\n");
		return &UnlockedDoor::s_instance;
	}
	_com->SendMessage(colors::YELLOW + "You do not have a key!\n");
	return &LockedDoor::s_instance;
}

DoorStatus* LockedDoor::LockDoor(Player* _player, Communication* _com) const
{
	assert(_player && _com);
	_com->SendMessage(colors::YELLOW + "The door is already locked!\n");
	return &LockedDoor::s_instance;
}

DoorStatus* LockedDoor::OpenDoor(Player* _player, Communication* _com) const
{
	assert(_player && _com);
	_com->SendMessage(colors::YELLOW + "The door is locked! Use a key to unlock it first\n");
	return &LockedDoor::s_instance;
}

DoorStatus* LockedDoor::CloseDoor(Player* _player, Communication* _com) const
{
	assert(_player && _com);
	_com->SendMessage(colors::YELLOW + "The door is locked! Use a key to unlock it first\n");
	return &LockedDoor::s_instance;
}

//--------------------------UnlockedDoor-------------------------------

std::string UnlockedDoor::GetName() const
{
	return "Closed Door";
}

void UnlockedDoor::WalkThrough(Player* _player, Communication* _com, Junction* _junction)
{
	assert(_player && _com && _junction);
	_com->SendMessage(colors::YELLOW + "The door is closed. You need to open it first\n");
}

DoorStatus* UnlockedDoor::UnlockDoor(Player* _player, Communication* _com) const
{
	assert(_player && _com);
	_com->SendMessage(colors::YELLOW + "The door is already unlocked\n");	
	return &UnlockedDoor::s_instance;
}

DoorStatus* UnlockedDoor::LockDoor(Player* _player, Communication* _com) const
{
	assert(_player && _com);
	if(_player->UseKey())
	{
		_com->SendMessage(colors::GREEN + "The door is now locked\n");	
		return &LockedDoor::s_instance;
	}
	_com->SendMessage(colors::YELLOW + "You do not have a key!\n");
	return &UnlockedDoor::s_instance;
}

DoorStatus* UnlockedDoor::OpenDoor(Player* _player, Communication* _com) const
{
	assert(_player && _com);
	_com->SendMessage(colors::GREEN + "You have opened the door\n");
	return &OpenedDoor::s_instance;
}

DoorStatus* UnlockedDoor::CloseDoor(Player* _player, Communication* _com) const
{
	assert(_player && _com);
	_com->SendMessage(colors::YELLOW + "The door is already closed\n");
	return &UnlockedDoor::s_instance;
}

//--------------------------OpenedDoor-------------------------------

std::string OpenedDoor::GetName() const 
{
	return "Open Door";
}

void OpenedDoor::WalkThrough(Player* _player, Communication* _com, Junction* _junction)
{
	assert(_player && _com && _junction);
	WalkThroughFunctor walkFunc;
	walkFunc.WalkThrough(_player, _junction);
}

DoorStatus* OpenedDoor::UnlockDoor(Player* _player, Communication* _com) const
{
	assert(_player && _com);
	_com->SendMessage(colors::YELLOW +"The door is open, and cannot be unlocked.\n");	
	return &OpenedDoor::s_instance;
}

DoorStatus* OpenedDoor::LockDoor(Player* _player, Communication* _com) const
{
	assert(_player && _com);
	_com->SendMessage(colors::YELLOW + "The door is open. You need to close it before trying to lock it.\n");
	return &OpenedDoor::s_instance;
}

DoorStatus* OpenedDoor::OpenDoor(Player* _player, Communication* _com) const
{
	assert(_player && _com);
	_com->SendMessage(colors::YELLOW + "The door is already open.\n");
	return &OpenedDoor::s_instance;
}

DoorStatus* OpenedDoor::CloseDoor(Player* _player, Communication* _com) const
{
	assert(_player && _com);
	_com->SendMessage(colors::GREEN +"You have closed the door.\n");
	return &UnlockedDoor::s_instance;
}
	
}
