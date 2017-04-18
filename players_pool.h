#ifndef __PLAYER__POOL_H__
#define __PLAYER__POOL_H__

#include <map>

#include "player.h"

namespace maze
{
class Room;

class PlayerPool : private Uncopyable
{
public:
	PlayerPool(Room* _startingRoom); 
	~PlayerPool();
	bool AddPlayer(size_t m_id, const std::string& _name);
	void RemovePlayer(size_t _id);
	Player* GetPlayer(size_t _id);

	class Iterator
	{
		friend class PlayerPool;
		friend bool operator==(const Iterator& _it1, const Iterator& _it2);	
		friend bool operator!=(const Iterator& _it1, const Iterator& _it2);	
	public:
		Iterator(std::map<std::string,Player*> ::iterator _it, const std::map<std::string,Player*>& _pool);
		Iterator operator++();
		Player* operator*() const;
		
	private:
		std::map<std::string,Player*> ::iterator m_it;
		const std::map<std::string,Player*>& m_pool;
	};
	
	Iterator Begin();
	Iterator End();
	

private:
	std::map<size_t, std::string> m_playersBySocket;
	std::map<std::string, Player*> m_playersByName;
	Room* m_startingRoom;
};

}
#endif //__PLAYER__POOL_H__
