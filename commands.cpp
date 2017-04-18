#include <cassert>

#include "player.h"
#include "communications.h"
#include "junctions.h"
#include "rooms.h"
#include "event.h"
#include "commands.h"


namespace maze
{
	
const EndOfTurnRoutine EndOfTurnRoutine::s_instance;	
const CheckWinningRoutine CheckWinningRoutine::s_instance;
const CheckLosingRoutine CheckLosingRoutine::s_instance;
const CheckLosingRoutineForAll CheckLosingRoutineForAll::s_instance;
	
//--------------------------BASE-CLASS--------------------------------

Command::Command(Communication* _com) : m_com(_com)
{
	assert(_com);
}

//--------------------------------------------------------------------	

Junction* Command::GetJunction(Player*_player)
{
	assert(_player);
	return _player->GetRoom()->GetJunction(_player->GetDirection());
}


//--------------------------------------------------------------------	
	
void Command::SendRoomDescription(Player*_player)
{
	assert(_player);
	Room* room = _player->GetRoom();
	m_com->SendMessage(_player->GetName() + ",  " + room->GetRoomDescription(_player->GetDirectionName()) + "\n");
}	

//--------------------------------------------------------------------	

void Command::SetIdAndSendMessage(Player*_player, const std::string& _msg)
{
	assert(_player);
	m_com->SetId(_player->GetID());
	m_com->SendMessage(_msg);
}

//-----------------------------LOOK-----------------------------------	

Look::Look(Communication* _comm) : Command(_comm)
{
}

//--------------------------------------------------------------------	

const EndOfTurnRoutine& Look::operator()(Player*_player)
{
	assert(_player);
	SendRoomDescription(_player);
	return EndOfTurnRoutine::s_instance;
}

//-----------------------------WALK-----------------------------------	

Walk::Walk(Communication* _comm) : Command(_comm)
{
}

//--------------------------------------------------------------------	

const EndOfTurnRoutine& Walk::operator()(Player*_player)
{
	assert(_player);	
	_player->GetRoom()->RemovePlayerFromRoom(_player);
	GetJunction(_player)->WalkThrough(_player, m_com);
	_player->GetRoom()->AddPlayerToRoom(_player);	

	SendRoomDescription(_player);
	return EndOfTurnRoutine::s_instance;
}


//-----------------------------RIGHT-------------------------------	

Right::Right(Communication* _comm) : Command(_comm)
{
}

//--------------------------------------------------------------------	

const EndOfTurnRoutine&  Right::operator()(Player*_player)
{
	assert(_player);
	_player->TurnRight();
	SendRoomDescription(_player);
	return EndOfTurnRoutine::s_instance;
}

//-----------------------------LEFT-----------------------------------

Left::Left(Communication* _comm) : Command(_comm)
{
	assert(_comm);
}

//--------------------------------------------------------------------	

const EndOfTurnRoutine&  Left::operator()(Player*_player)
{
	assert(_player);
	_player->TurnLeft();
	SendRoomDescription(_player);
	return EndOfTurnRoutine::s_instance;
}

//-----------------------------BACK-----------------------------------

Back::Back(Communication* _comm) : Command(_comm)
{
}

//--------------------------------------------------------------------	

const EndOfTurnRoutine&  Back::operator()(Player*_player)
{
	assert(_player);
	_player->GetRoom()->RemovePlayerFromRoom(_player);
	_player->TurnBack();
	GetJunction(_player)->WalkThrough(_player, m_com);
	_player->GetRoom()->AddPlayerToRoom(_player);
	SendRoomDescription(_player);
	return EndOfTurnRoutine::s_instance;
}

//-----------------------------TAKE-----------------------------------

Take::Take(Communication* _comm) : Command(_comm)
{
	assert(_comm);
}

//--------------------------------------------------------------------	

const EndOfTurnRoutine& Take::operator()(Player*_player)
{
	assert(_player);
	_player->GetRoom()->SetEvent(_player->GetRoom()->GetEvent()->TakeTreasure(_player,m_com));
	return CheckWinningRoutine::s_instance;
}

//-----------------------------OPEN-----------------------------------

Open::Open(Communication* _comm) : Command(_comm)
{
	assert(_comm);
}

//--------------------------------------------------------------------	

const EndOfTurnRoutine& Open::operator()(Player*_player)
{
	assert(_player);
	GetJunction(_player)->OpenDoor(_player, m_com);
	SendRoomDescription(_player);
	return EndOfTurnRoutine::s_instance;
}

//-----------------------------CLOSE----------------------------------

Close::Close(Communication* _comm) : Command(_comm)
{
	assert(_comm);
}

//--------------------------------------------------------------------	

const EndOfTurnRoutine& Close::operator()(Player*_player)
{
	assert(_player);
	GetJunction(_player)->CloseDoor(_player, m_com);
	SendRoomDescription(_player);
	return EndOfTurnRoutine::s_instance;
}

//-----------------------------LOCK-----------------------------------

Lock::Lock(Communication* _comm) : Command(_comm)
{
}

//--------------------------------------------------------------------	

const EndOfTurnRoutine& Lock::operator()(Player*_player)
{
	assert(_player);
	GetJunction(_player)->LockDoor(_player, m_com);
	SendRoomDescription(_player);
	return EndOfTurnRoutine::s_instance;
}

//-----------------------------UNLOCK---------------------------------

Unlock::Unlock(Communication* _comm) : Command(_comm)
{
}

//--------------------------------------------------------------------	

const EndOfTurnRoutine& Unlock::operator()(Player*_player)
{
	assert(_player);
	GetJunction(_player)->UnlockDoor(_player, m_com);
	SendRoomDescription(_player);
	return EndOfTurnRoutine::s_instance;
}

//-----------------------------STATUS---------------------------------

Status::Status(Communication* _comm) : Command(_comm)
{
	assert(_comm);
}

//--------------------------------------------------------------------	

const EndOfTurnRoutine& Status::operator()(Player*_player)
{
	assert(_player);
	std::string msg = "HP: " + std::to_string(_player->GetAttributes().GetHP()) + "\n"
					+ "Coins: " + std::to_string(_player->GetPossesions().GetCoins()) + "\n"
					+ "Keys: " + std::to_string(_player->GetPossesions().GetNumOfKeys()) + "\n"
					+ "Attack Lvl: " + std::to_string(_player->GetAttributes().GetAttack()) + "\n"
					+ "Defence Lvl: " + std::to_string(_player->GetAttributes().GetDefence()) + "\n";
						
	m_com->SendMessage(msg);
	return EndOfTurnRoutine::s_instance;
}


//-----------------------------ATTACK---------------------------------

Attack::Attack(Communication* _comm) : Command(_comm)
{
	assert(_comm);
}

//--------------------------------------------------------------------	

const EndOfTurnRoutine& Attack::operator()(Player* _player)
{
	assert(_player);
	_player->GetRoom()->SetEvent(_player->GetRoom()->GetEvent()->FightMonster(_player, ATTACK_MODIFIER, m_com));
	return CheckLosingRoutine::s_instance;
}

//-----------------------------Rage---------------------------------

Rage::Rage(Communication* _comm) : Command(_comm)
{
	assert(_comm);
}

Player* Rage::GetRandomPlayer(Player* _player)
{
	assert(_player);
	Player* defender = _player->GetRoom()->GetRandomPlayerInRoom();
	while (_player == defender)
	{
		defender = _player->GetRoom()->GetRandomPlayerInRoom();
	}
	return defender;
}

void Rage::SendDamageMessages(Player* _attacker, Player* _defender)
{
	assert(_attacker);
	assert(_defender);
	size_t damage  = _attacker->AttackCharacter(_defender,ATTACK_MODIFIER, m_com);
	SetIdAndSendMessage(_defender,colors::RED + "In his fury " + colors::YELLOW + _attacker->GetName() + colors::RED + " had caused you" + colors::RED + std::to_string(damage) + " points of damage\n");
	SetIdAndSendMessage(_attacker,colors::RED + "In Your fury, you hit " + colors::YELLOW + _defender->GetName() + colors::RED +" for " + std::to_string(damage) + " points of damage\n");
}

void Rage::CheckLosingRotuine(Player* _player)
{
	assert(_player);
	CheckLosingRoutine checklose;
	checklose.Do(_player, m_com, 0);
}

//--------------------------------------------------------------------
const EndOfTurnRoutine& Rage::operator()(Player* _player)
{
	assert(_player);
    srand(time(0));
	Room* thisRoom = _player->GetRoom();
	if(1 < thisRoom->GetNumOfPlayersInRoom())
	{
		_player->GetRoom()->SetEvent(thisRoom->GetEvent()->FightMonster(_player, RAGE_MODIFIER, m_com));
		if(!(rand() % HIT_OTHER_PLAYER_MODIFIER)) 
		{
			Player* defender = GetRandomPlayer(_player);
			SendDamageMessages(_player,defender);
			CheckLosingRotuine(defender);
		}
		return CheckLosingRoutine::s_instance;
	}
	m_com->SendMessage("There is no one to urge you to fight. You cannot rage\n");
	return EndOfTurnRoutine::s_instance;
}

//-----------------------------TALK---------------------------------

Talk::Talk(Communication* _comm) : Command(_comm)
{
	assert(_comm);
}

//--------------------------------------------------------------------	

const EndOfTurnRoutine&  Talk::operator()(Player* _player)
{
	assert(_player);
	if(1 < _player->GetRoom()->GetNumOfPlayersInRoom())
	{
		m_com->SendMessage("Please type your message\n");
		std::string msg= m_com->GetMessage();
		_player->GetRoom()->SendMessageToPlayersInRoom(_player->GetName(), msg, m_com);
		return EndOfTurnRoutine::s_instance;
	}
	m_com->SendMessage("There is no one to talk to. Weirdo...\n");
	return EndOfTurnRoutine::s_instance;
}

//-----------------------------Invalid---------------------------------

Invalid::Invalid(Communication* _comm) : Command(_comm)
{
	assert(_comm);
}

//--------------------------------------------------------------------	

const EndOfTurnRoutine&  Invalid::operator()(Player* _player)
{
	assert(_player);
	m_com->SendMessage(colors::RED + "Invalid Command\n");
	return EndOfTurnRoutine::s_instance;
}

//-----------------------------Quit---------------------------------

Quit::Quit(Communication* _comm) : Command(_comm)
{
	assert(_comm);
}

//--------------------------------------------------------------------	

const EndOfTurnRoutine& Quit::operator()(Player* _player)
{
	assert(_player);
	m_com->SendMessage(colors::RED + "GoodBye\n");
	m_com->RemoveById(_player->GetID());
	return EndOfTurnRoutine::s_instance;
}


//-----------------------------Win---------------------------------

Win::Win(Communication* _comm) : Command(_comm)
{
}

//--------------------------------------------------------------------	

const EndOfTurnRoutine& Win::operator()(Player* _player)
{
	_player->AddCoins(CheckWinningRoutine::VICTORY_COIN_CONDITION, m_com);
	return CheckWinningRoutine::s_instance;
}


//-----------------------------HELP-----------------------------------

Help::Help(Communication* _comm) : Command(_comm)
{
	assert(_comm);
}

//--------------------------------------------------------------------	

const EndOfTurnRoutine&  Help::operator()(Player* _player)
{
	assert(_player);
	std::string help;
	help += "Possible commands are: \n"
	"'look' - Watch current state of room \n"
	"'walk' - Walk into the room you're facing \n"
	"'right' - Turn right \n"
	"'left' - Turn left \n"
	"'open' - Opens a closed door \n"
	"'close' - Closes an open door \n"
	"'unlock' - Unlocks a locked door \n"
	"'lock' - Locks an unlocked, closed door \n"
	"'take' - Takes treasure from room \n"
	"'attack' - Attacks a monster inside room \n"
	"'rage' - Attacks a monster inside room, only available while a fellow quester is in the room\n"
	"'back' - Go back to previous room \n"
	"'status' - Check how your character is doing \n"
	"'talk' - Send a message to fellow quester inside current room \n"
	"'quit' - End game \n";
	m_com->SendMessage(help);
	
	return EndOfTurnRoutine::s_instance;
}

} //namespace maze
