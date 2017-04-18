#ifndef __COMMUNICATION_H__
#define __COMMUNICATION_H__

#include <string>

#include "uncopyable.h"
#include "NetworkHandler.h"
#include "graphics.h"

namespace maze
{
	
class Communication : private Uncopyable
{
public:
	//Communication(); default
	virtual ~Communication() {};
	virtual void SendMessage(const std::string& _message) = 0;
	virtual std::string GetMessage()  = 0;	
	virtual size_t GetId() const {return 0;};
	virtual void SetId(size_t _id) {};	
	virtual void RemoveById(size_t _id) {};
};

class LocalCommunication : public Communication
{
public:
	//LocalCommunication(); default
	~LocalCommunication();
	virtual void SendMessage(const std::string& _message);
	virtual std::string GetMessage();
};

template <class T, class P>
class NetworkCommunication : public Communication
{
public:
	NetworkCommunication(const T& _creator,const P& _releaser);
	~NetworkCommunication();
	virtual void SendMessage(const std::string& _message);
	virtual std::string GetMessage();	
	virtual size_t GetId() const;
	virtual void SetId(size_t _id);
	virtual void RemoveById(size_t _id);
	
private:
	NetworkHandler m_handler;
	size_t m_connectionId;
};

template <class T, class P>
NetworkCommunication<T,P>::NetworkCommunication(const T& _creator,const P& _releaser) : m_handler(5100, _creator, _releaser)
{
	std::string inbuf;
	m_handler.GetInput(&m_connectionId, &inbuf);
}

//--------------------------NetworkCommunication------------------------------

template <class T, class P>
NetworkCommunication<T,P>::~NetworkCommunication()
{
	
}

//--------------------------------------------------------------------
template <class T, class P>
void NetworkCommunication<T,P>::SendMessage(const std::string& _message)
{
	m_handler.PutOutput(m_connectionId, colors::LIGHT_BLUE + _message + colors::NORMAL);
	
	return;
}

//--------------------------------------------------------------------
template <class T, class P>
std::string NetworkCommunication<T,P>::GetMessage()
{
	std::string inbuf;
	m_handler.GetInput(&m_connectionId, &inbuf);
	return inbuf;
}

//--------------------------------------------------------------------
template <class T, class P>
void NetworkCommunication<T,P>::SetId(size_t _id)
{
	m_connectionId = _id;
}

//--------------------------------------------------------------------
template <class T, class P>
size_t NetworkCommunication<T,P>::GetId() const
{
	return m_connectionId;
}

//--------------------------------------------------------------------
template <class T, class P>
void NetworkCommunication<T,P>::RemoveById(size_t _id)
{
	m_handler.FreeSocketInformation(_id);
}

}

#endif /*ifndef __COMMUNICATION_H__*/
