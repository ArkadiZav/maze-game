class JunctionType //- Interface
{
	virtual bool WalkThrough(Player* _player, Junction* _junction) = 0;
}

class Passage : public  JunctionType
{
	virtual bool WalkThrough(Player* _player, Junction* _junction);
	{
		Room* nextRoom = _junction->m_rooms[SECOND];
		_player->SetRoom(nextRoom);
		return true;
	}
}

/*class LockedDoor : public  JunctionType
{
	virtual bool WalkThrough(Player* _player, Junction* _junction);
	{
		bool hasKey = _player->GetKey();
		if (!hasKey)
		{
			return false;
		}
		//_junction->m_type = 
		//Room* nextRoom = _junction->m_rooms[SECOND];
		//_player->SetRoom(nextRoom);
		return true;
	}
}*/

enum e_Rooms
{
	FIRST = 0,
	SECOND
};

class Junction
{
	JunctionType* m_type;
	Room* m_rooms[2]; //with e_Rooms
}

enum e_Directions
{
	NORTH = 0,
	EAST,
	SOUTH,
	WEST
};

class Room //- Interface
{
public:
	virtual void Look() = 0;

protected:
	size_t m_numOfPlayers;
	Junction* m_direction[4]; //with e_Directions
};

class RegularRoom : public Room
{

};

class Player
{
	virtual void Play() = 0;
	virtual bool GetKey()
	{
		if (!m_numOfKeys)
		{
			return false;
		}
		--m_numOfKeys;
		return true;
	}	

	std::string m_name;
	size_t m_directionIndex;
	Room* m_currentRoom;
	size_t m_HP;
	size_t m_coins;
	size_t m_numOfKeys;
	char m_attackLevel; 
	char m_defenceLevel;
	map<string, FUNCTOR> m_commands;
};

class Command
{
	virtual operator() (Player* _player) = 0;
}

class Walk: public Command
{
	bool operator()(Player* _player)
	{
		Room* room = _player->GetRoom();
		Junction* junction = room->GetJunction(_player->GetDirection());
		return junction->m_type->WalkThrough(_player);
	}
};

class PrincessDana : public Player
{
	void LovesDor();
	bool RequestSuicicde();
	Fat GetChoclate();
	virtual void Play()
	{
		std:string command;
		m_currentRoom->Look();
		while(1)
		{
			std::cin>>command;
			map<string, FUNCTOR>::iterator it = m_commands.find(command);
			if(m_commands.end() == it)
			{
				std::cout<<"Invalid Command"<<std::endl;
			}
			else
			{
				it->second(this);
			}
		}
	}
};


int main()
{
	Room* firstRoom = CreateMap(); //returns root - first room. create rooms and junctions
	std::string CharacterName = "Dana";
	PrincessDana dana(firstRoom,CharacterName);
	dana.Play();
}
