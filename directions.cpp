#include "directions.h"

namespace maze
{

const North North::s_instance;
const East East::s_instance;
const South South::s_instance;
const West West::s_instance;
	
//--------------------------North--------------------------------
const std::string North::GetName() const 
{
	return "North";
}
const Direction& North::TurnLeft() const 
{
	return West::s_instance;
}
const Direction& North::TurnRight() const 
{
	return East::s_instance;
}

const Direction& North::TurnBack() const
{
	return South::s_instance;
}

//--------------------------East--------------------------------
const std::string East::GetName() const 
{
	return "East";
}
const Direction& East::TurnLeft() const 
{
	return North::s_instance;
}
const Direction& East::TurnRight() const 
{
	return South::s_instance;
}

const  Direction& East::TurnBack() const
{
	return West::s_instance;
}

//--------------------------South--------------------------------
const std::string South::GetName() const 
{
	return "South";
}
const Direction& South::TurnLeft() const 
{
	return East::s_instance;
}
const Direction& South::TurnRight() const 
{
	return West::s_instance;
}

const  Direction& South::TurnBack() const
{
	return North::s_instance;
}

//--------------------------West--------------------------------
const std::string West::GetName() const 
{
	return "West";
}
const Direction& West::TurnLeft() const 
{
	return South::s_instance;
}
const Direction& West::TurnRight() const 
{
	return North::s_instance;
}

const  Direction& West::TurnBack() const
{
	return East::s_instance;
}

}	
