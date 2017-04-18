#include <iostream>
#include "communications.h"

namespace maze
{
	
//--------------------------LocalCommunication-------------------------------

void LocalCommunication::SendMessage(const std::string& _message)
{
	std::cout << colors::LIGHT_BLUE + _message + colors::NORMAL << std::endl;
	return;
}

LocalCommunication::~LocalCommunication()
{
}

//--------------------------------------------------------------------
std::string LocalCommunication::GetMessage()
{
	std::string temp;
	std::cin >> temp;
	return temp;
}

}
