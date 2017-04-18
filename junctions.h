#ifndef __JUNCTIONS_H__
#define __JUNCTIONS_H__

#include <vector>
#include "uncopyable.h"
#include "communications.h"

namespace maze
{
class Room;
class Communication;
class Player;

enum e_Rooms
{
	FIRST = 0,
	SECOND,
	NUM_OF_ROOMS
};

class Junction : private Uncopyable
{
public:	
	Junction(const std::string& _color);
	Junction();
	//~Junction() for Now default.
	
	virtual std::string GetName() const = 0;
	const std::string& GetColour() const;
	virtual void WalkThrough(Player*_player, Communication* _com);
	virtual void UnlockDoor(Player*_player, Communication* _com);
	virtual void LockDoor(Player*_player, Communication* _com);
	virtual void OpenDoor(Player*_player, Communication* _com);
	virtual void CloseDoor(Player*_player, Communication* _com);

	Room* GetOtherRoom(Room* _room);
	void SetRoom(Room* _room);

protected:
	void SendDoorErrorMsg(Communication* _com) const;
	
	const std::string& m_color;

private:
	Room* GetFirstRoom();
	Room* GetSecondRoom();
	void SetFirstRoom(Room* _room);
	void SetSecondRoom(Room* _room);
	
	std::vector<Room*> m_rooms;
};

class Passage : public Junction
{
public:
	//Passage() default.
	//~Passage() default.
	virtual std::string GetName() const;
};

class Wall : public Junction
{
public:
	static  Wall s_instance;
	
public:
	//Wall() default.
	//~Wall() default.
	virtual std::string GetName() const;
	virtual void WalkThrough(Player*_player, Communication* _com);
};

class DoorStatus
{
public:
	virtual std::string GetName() const = 0;
	virtual void WalkThrough(Player*_player, Communication* _com, Junction* _junction) = 0;
	virtual DoorStatus* UnlockDoor(Player*_player, Communication* _com) const= 0;
	virtual DoorStatus* LockDoor(Player*_player, Communication* _com) const= 0 ;
	virtual DoorStatus* OpenDoor(Player*_player, Communication* _com) const= 0;
	virtual DoorStatus* CloseDoor(Player*_player, Communication* _com) const= 0;	
};

class LockedDoor: public DoorStatus
{
public:	
	static LockedDoor s_instance;
public:
	virtual std::string GetName() const;
	virtual void WalkThrough(Player*_player, Communication* _com, Junction* _junction);
	virtual DoorStatus* UnlockDoor(Player*_player, Communication* _com) const;
	virtual DoorStatus* LockDoor(Player*_player, Communication* _com) const;
	virtual DoorStatus* OpenDoor(Player*_player, Communication* _com) const;
	virtual DoorStatus* CloseDoor(Player*_player, Communication* _com) const;	
};

class UnlockedDoor: public DoorStatus
{
public:	
	static UnlockedDoor s_instance;
public:
	virtual std::string GetName() const;
	virtual void WalkThrough(Player*_player, Communication* _com, Junction* _junction);
	virtual DoorStatus* UnlockDoor(Player*_player, Communication* _com) const;
	virtual DoorStatus* LockDoor(Player*_player, Communication* _com) const;
	virtual DoorStatus* OpenDoor(Player*_player, Communication* _com) const;
	virtual DoorStatus* CloseDoor(Player*_player, Communication* _com) const;
};

class OpenedDoor: public DoorStatus
{
public:	
	static OpenedDoor s_instance;
public:
	virtual std::string GetName() const;
	virtual void WalkThrough(Player*_player, Communication* _com, Junction* _junction);
	virtual DoorStatus* UnlockDoor(Player*_player, Communication* _com) const;
	virtual DoorStatus* LockDoor(Player*_player, Communication* _com) const;
	virtual DoorStatus* OpenDoor(Player*_player, Communication* _com) const;
	virtual DoorStatus* CloseDoor(Player*_player, Communication* _com) const;		
};


class Door : public Junction
{
public:
	Door(DoorStatus* _doorStatus, const std::string& _color = colors::DEFAULT_COLOUR);
	//~Door() for Now default.
	virtual std::string GetName() const;
	const std::string& GetColour() const;
	virtual void WalkThrough(Player*_player, Communication* _com);
	virtual void UnlockDoor(Player*_player, Communication* _com);
	virtual void LockDoor(Player*_player, Communication* _com);
	virtual void OpenDoor(Player*_player, Communication* _com);
	virtual void CloseDoor(Player*_player, Communication* _com);
	
private:
	DoorStatus* m_doorStatus;
};

}
#endif /*ifndef __JUNCTIONS_H__*/
