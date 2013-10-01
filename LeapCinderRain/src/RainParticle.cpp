#include "RainParticle.h"

#include "cinder/Rand.h"

RainParticle::RainParticle( Vec2f loc )
{
	m_vLoc = loc;
	m_vPointTo = Vec2f( app::getWindowWidth()/2, app::getWindowHeight()/2 );	
	m_nShortestDistance = m_vLoc.distanceSquared( m_vPointTo );
	m_vPointTo = m_vPointTo - m_vLoc;
	m_vPointTo.safeNormalize();

	//Magnitude is its speed
	m_vVel = Vec2f( 0.0f, 340.0f );

	//Droplets should be going downwards initially
	m_vDir = m_vVel;
	m_vDir.safeNormalize();

	m_fDropletRadius = Rand::randFloat( 1.0f, 5.0f );

	m_fLength = 15.0f;
	m_fHeadRadius = 6.0f;
	m_fHeadLength = 3.0f;

	m_inBounds = true;
}

RainParticle::~RainParticle()
{
}

void RainParticle::Update( float dT )
{
	m_vLoc += m_vVel * dT;

	CheckInBounds();
}

void RainParticle::CheckInBounds()
{
	if( m_vLoc.x < (0 - app::getWindowWidth() * 0.5 )	||
		m_vLoc.x > (app::getWindowWidth() * 1.5 )		||
		m_vLoc.y < (0 - app::getWindowHeight() * 0.5 )	||
		m_vLoc.y > (app::getWindowHeight() * 1.5 )	)
	{
		m_inBounds = false;
	}
	else
	{
		m_inBounds = true;
	}
}

void RainParticle::Draw()
{
	/** Vector */
	Vec3f p1( m_vLoc, 0.0f );
	Vec3f p2( m_vLoc + m_vDir * m_fLength, 0.0f );
	gl::drawVector( p1, p2, m_fHeadRadius, m_fHeadLength );

	/** Droplet */
	//gl::drawSolidCircle( m_vLoc, 5.0f );
}

void RainParticle::CheckPointTo( Vec2f loc, float fingerRadius )
{
	//"flip" the rain drop
	if( m_vLoc.distanceSquared( loc ) < ( fingerRadius * fingerRadius ) )
	{
		m_vVel *= -1;
		m_vDir = m_vVel;
		m_vDir.safeNormalize();
	}
}

void RainParticle::ClearPointTo()
{
	m_nShortestDistance = -1;
}

bool RainParticle::IsInBounds()
{
	return m_inBounds;
}