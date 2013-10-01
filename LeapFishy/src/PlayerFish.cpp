#include "PlayerFish.h"

PlayerFish::PlayerFish()
{
	m_vLoc = Vec2f( app::getWindowWidth() / 2, app::getWindowHeight() / 2 );
	m_Color = Color( 255.0f/255.0f, 127.0f/255.0f, 80.0f/255.0f );	//Coral
}

PlayerFish::~PlayerFish()
{
}

void PlayerFish::Update( float dT )
{
	m_vLoc += m_vVel * dT;

	if( m_vLoc.x < 0 || m_vLoc.x+getWidth() > app::getWindowWidth() )
	{
		m_vVel.x = -m_vVel.x;
	}

	if( m_vLoc.y < 0 || m_vLoc.y+getHeight() > app::getWindowHeight() )
	{
		m_vVel.y = -m_vVel.y;
	}
}

void PlayerFish::AddVelocity( Vec2f vel )
{
	m_vVel += vel;
}

void PlayerFish::KillVelocity()
{
	m_vVel = Vec2f( 0.0f, 0.0f );
}
