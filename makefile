CC = g++
INC = ./networkhandler/
CFLAGS = -g -c -ansi -pedantic -Wno-deprecated -Werror -Wall -std=c++11 -I $(INC)

OBJS = main_game.o rooms.o junctions.o player.o game.o communications.o treasure.o NetworkHandler.o commands.o attributes.o graphics.o monster.o event.o players_pool.o directions.o end_of_turn_routine.o map_generator.o tokenizer.o commands_container.o

rimon_rulz: $(OBJS)
	$(CC) -o rimon_rulz $(OBJS)

main_game.o: main_game.cpp game.h communications.h players_pool.h map_generator.h commands_container.h player_creator_releaser.h maze_exceptions.h
	$(CC) -o main_game.o $(CFLAGS) main_game.cpp

players_pool.o: players_pool.cpp players_pool.h
	$(CC) -o players_pool.o $(CFLAGS) players_pool.cpp

graphics.o: graphics.cpp communications.h graphics.h
	$(CC) -o graphics.o $(CFLAGS) graphics.cpp
	
NetworkHandler.o: $(INC)NetworkHandler.cpp $(INC)NetworkHandler.h
	$(CC) -o NetworkHandler.o $(CFLAGS) $(INC)NetworkHandler.cpp

communications.o: communications.cpp communications.h uncopyable.h $(INC)NetworkHandler.h
	$(CC) -o communications.o $(CFLAGS) communications.cpp
	
junctions.o: junctions.cpp junctions.h player.h uncopyable.h communications.h
	$(CC) -o junctions.o $(CFLAGS) junctions.cpp
	
rooms.o: rooms.cpp rooms.h uncopyable.h communications.h monster.h directions.h event.h
	$(CC) -o rooms.o $(CFLAGS) rooms.cpp
	
directions.o: directions.h directions.cpp
	$(CC) -o directions.o $(CFLAGS) directions.cpp
	
monster.o: monster.cpp monster.h player.h
	$(CC) -o monster.o $(CFLAGS) monster.cpp

player.o: player.cpp player.h rooms.h communications.h directions.h treasure.h
	$(CC) -o player.o $(CFLAGS) player.cpp

event.o: event.cpp event.h communications.h treasure.h
	$(CC) -o event.o $(CFLAGS) event.cpp
	
game.o: game.cpp game.h uncopyable.h communications.h rooms.h players_pool.h commands_container.h
	$(CC) -o game.o $(CFLAGS) game.cpp
	
treasure.o: treasure.cpp treasure.h uncopyable.h 
	$(CC) -o treasure.o $(CFLAGS) treasure.cpp

end_of_turn_routine.o: end_of_turn_routine.cpp end_of_turn_routine.h communications.h players_pool.h
	$(CC) -o end_of_turn_routine.o $(CFLAGS) end_of_turn_routine.cpp
	
commands_container.o: commands_container.cpp commands_container.h commands.h uncopyable.h
	$(CC) -o commands_container.o $(CFLAGS) commands_container.cpp
	
commands.o: commands.cpp commands.h uncopyable.h player.h communications.h junctions.h rooms.h
	$(CC) -o commands.o $(CFLAGS) commands.cpp
	
attributes.o: attributes.cpp attributes.h uncopyable.h
	$(CC) -o attributes.o $(CFLAGS) attributes.cpp
	
map_generator.o: map_generator.h map_generator.cpp rooms.h uncopyable.h monster.h event.h junctions.h monster.h treasure.h tokenizer.h directions.h maze_exceptions.h
	$(CC) -o map_generator.o $(CFLAGS) map_generator.cpp
	
tokenizer.o: tokenizer.h tokenizer.cpp
	$(CC) -o tokenizer.o $(CFLAGS) tokenizer.cpp
	
clean :
	rm -f $(OBJS) rimon_rulz *~ 	
	
rebuild : clean rimon_rulz	
