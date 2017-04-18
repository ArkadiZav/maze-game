#include <iostream>
#include <string>

#include "commands_container.h"
#include "communications.h"
#include "game.h"
#include "players_pool.h"
#include "map_generator.h"
#include "player_creator_releaser.h"
#include "maze_exceptions.h"

using namespace maze;
using namespace parser_exception;


int main(int argc, char* argv[])
{
	string fileName = "configmap.txt";
	if (2 == argc)
	{
		fileName =  argv[1];
	}
	else if ( 2 < argc)
	{
		cout<<"To many Paramters"<<endl;
		return -1;
	}
	
	try
	{
		MapGenerator generator(fileName);
		Room* firstRoom = generator.Generate();
		PlayerPool playerPool(firstRoom);
		NetworkCommunication<PlayerCreator,PlayerReleaser> com(PlayerCreator(&com, &playerPool),PlayerReleaser(&com, &playerPool));
		DefaultCommandsContainer commandsContainer(&com);
		Game newGame(&commandsContainer, &com, &playerPool);
		newGame.Play();
	}
	catch (parser_exception::WrongFileException _exception)
	{
		cout<<"wrong file name"<<endl;
		return -1;
	}
	catch (junction_exception::WrongJunctionType _exception)
	{
		cout<<"Invalid Junction type"<<endl;
		return -1;
	}
	catch (event_exception::WrongEventType _exception)
	{
		cout<<"Invalid Event type"<<endl;
		return -1;
	}
	
	return 0;
}
