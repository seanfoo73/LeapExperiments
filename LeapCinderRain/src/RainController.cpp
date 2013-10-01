#include "RainController.h"

#include "cinder/Rand.h"

RainController::RainController()
{
	m_RainDrops = new std::list<RainParticle*>();

	m_nSpacing = 20;
	m_fLastRain = 0.0f;
	m_fRainInterval = 0.1f;

	MakeItRain( 40 );
}

RainController::~RainController()
{
	for(	std::list<RainParticle*>::iterator i = m_RainDrops->begin();
			i != m_RainDrops->end();
			++i )
	{
		delete (*i);
	}
	delete m_RainDrops;
}

void RainController::Update( float dT )
{
	m_fLastRain += dT;
	if( m_fLastRain >= m_fRainInterval )
	{
		//Make it rain
		MakeItRain( 40 );

		m_fLastRain = 0.0f;
	}

	for(	std::list<RainParticle*>::iterator i = m_RainDrops->begin();
			i != m_RainDrops->end();
			++i )
	{
		(*i)->Update( dT );

		if( !(*i)->IsInBounds() )
		{
			delete (*i);
			i = m_RainDrops->erase( i );
		}
	}

	char strBuf[64];
	sprintf(strBuf, "Num RainDrops: %d\r", m_RainDrops->size());
	OutputDebugStringA((const char*)strBuf);
}

void RainController::MakeItRain( int numDroplets )
{
	int x;
	int y;

	for( int i = 0; i < numDroplets; i++ )
	{
		x = Rand::randFloat( 0.0f, app::getWindowWidth() );
		y = Rand::randFloat( -50.0f, 0.0f );
		m_RainDrops->push_back( new RainParticle( Vec2f( x, y ) ) );
	}
}

void RainController::Draw()
{
	for(	std::list<RainParticle*>::iterator i = m_RainDrops->begin();
			i != m_RainDrops->end();
			++i )
	{
		(*i)->Draw();
	}
}

void RainController::CheckPointTo( Vec2f loc, float fingerRadius )
{
	for(	std::list<RainParticle*>::iterator i = m_RainDrops->begin();
			i != m_RainDrops->end();
			++i )
	{
		(*i)->CheckPointTo( loc, fingerRadius );
	}
}

void RainController::ClearPointTo()
{
	for(	std::list<RainParticle*>::iterator i = m_RainDrops->begin();
			i != m_RainDrops->end();
			++i )
	{
		(*i)->ClearPointTo();
	}
}