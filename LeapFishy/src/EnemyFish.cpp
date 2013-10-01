#include "EnemyFish.h"

#include "cinder/Rand.h"

EnemyFish::EnemyFish()
{
	int spawnSide = Rand::randInt( 0, 2 );
	m_fScaling = Rand::randFloat( 0.0f, 50.0f );
	//Spawn Left Side
	if( spawnSide == 0 )
	{
		m_vLoc = Vec2f( 0 , Rand::randFloat( 0.0f, app::getWindowHeight()-getHeight() ) );
		m_vVel = Vec2f( Rand::randFloat( m_fMinVelocity, m_fMaxVelocity ), 0.0f );
	}
	//Spawn Right Side
	else						
	{
		m_vLoc = Vec2f( app::getWindowWidth() - getWidth() , Rand::randFloat( 0.0f, app::getWindowHeight()-getHeight() ) );
		m_vVel = Vec2f( -Rand::randFloat( m_fMinVelocity, m_fMaxVelocity ), 0.0f );
	}

	m_Color = Color( 100.0f/255.0f, 149.0f/255.0f, 237.0f/255.0f );	//cornflower blue
}

EnemyFish::~EnemyFish()
{
}

void EnemyFish::Update( float dT )
{
	m_vLoc += m_vVel * dT;

	//spawned left
	if( m_vVel.x > 0 && m_vLoc.x > app::getWindowWidth() * 1.5 )
	{
		m_bAlive = false;
	}
	//spawned right
	else if( m_vVel.x < 0 && m_vLoc.x < -app::getWindowWidth() * 1.5 )
	{
		m_bAlive = false;
	}
}
