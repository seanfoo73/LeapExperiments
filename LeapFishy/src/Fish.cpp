#include "Fish.h"

Fish::Fish()
{
	m_fWidth = 5.0f;
	m_fHeight = 3.0f;
	m_fRoundedCornerRadius = 1.0f;

	m_fScaling = 10.0f;

	m_fMinVelocity = 10.0f;
	m_fMaxVelocity = 100.0f;

	m_bAlive = true;
}

Fish::~Fish()
{
}

void Fish::Draw()
{
	m_CollisionVolume = Rectf( m_vLoc, Vec2f( m_vLoc.x + getWidth(), m_vLoc.y + getHeight() ) );
	gl::color( m_Color );
	gl::drawSolidRoundedRect( m_CollisionVolume, m_fRoundedCornerRadius * m_fScaling );
}

float Fish::getWidth()
{
	return m_fWidth * m_fScaling;
}

float Fish::getHeight()
{
	return m_fHeight * m_fScaling;
}