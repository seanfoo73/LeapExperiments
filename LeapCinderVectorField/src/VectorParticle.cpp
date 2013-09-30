#include "VectorParticle.h"

VectorParticle::VectorParticle( Vec2f loc )
{
	m_vLoc = loc;
	m_vPointTo = Vec2f( app::getWindowWidth()/2, app::getWindowHeight()/2 );	
	m_nShortestDistance = m_vLoc.distanceSquared( m_vPointTo );
	m_vPointTo = m_vPointTo - m_vLoc;
	m_vPointTo.safeNormalize();

	m_fLength = 10.0f;
	m_fHeadRadius = 6.0f;
	m_fHeadLength = 3.0f;
}

VectorParticle::~VectorParticle()
{
}

void VectorParticle::Update( float dT )
{
}

void VectorParticle::CheckPointTo( Vec2f loc )
{
	if( m_nShortestDistance == -1 )
	{
		m_nShortestDistance = m_vLoc.distanceSquared( loc );
		m_vPointTo = loc - m_vLoc;
		m_vPointTo.safeNormalize();
	}
	else
	{
		if( m_vLoc.distanceSquared( loc ) < m_nShortestDistance )
		{
			m_nShortestDistance = m_vLoc.distanceSquared( loc );
			m_vPointTo = loc - m_vLoc;
			m_vPointTo.safeNormalize();
		}
	}
}

void VectorParticle::ClearPointTo()
{
	m_nShortestDistance = -1;
}

void VectorParticle::Draw()
{
	Vec3f p1( m_vLoc, 0.0f );
	Vec3f p2( m_vLoc + m_vPointTo * m_fLength, 0.0f );
	gl::drawVector( p1, p2, m_fHeadRadius, m_fHeadLength );
}