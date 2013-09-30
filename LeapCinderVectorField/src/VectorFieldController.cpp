#include "VectorFieldController.h"

VectorFieldController::VectorFieldController()
{
	m_VectorField = new std::list<VectorParticle*>();
	m_nSpacing = 20;

	for( int x = 0; x < app::getWindowWidth(); x += m_nSpacing )
	{
		for( int y = 0; y < app::getWindowHeight(); y += m_nSpacing )
		{
			m_VectorField->push_back( new VectorParticle( Vec2f( x, y ) ) );
		}
	}
}

VectorFieldController::~VectorFieldController()
{
	for(	std::list<VectorParticle*>::iterator i = m_VectorField->begin();
			i != m_VectorField->end();
			++i )
	{
		delete (*i);
	}

	delete m_VectorField;
}

void VectorFieldController::Update( float dT )
{
	for(	std::list<VectorParticle*>::iterator i = m_VectorField->begin();
			i != m_VectorField->end();
			++i )
	{
		(*i)->Update( dT );
	}
}

void VectorFieldController::Draw()
{
	for(	std::list<VectorParticle*>::iterator i = m_VectorField->begin();
			i != m_VectorField->end();
			++i )
	{
		(*i)->Draw();
	}
}

void VectorFieldController::CheckPointTo( Vec2f loc )
{
	for(	std::list<VectorParticle*>::iterator i = m_VectorField->begin();
			i != m_VectorField->end();
			++i )
	{
		(*i)->CheckPointTo( loc );
	}
}

void VectorFieldController::ClearPointTo()
{
	for(	std::list<VectorParticle*>::iterator i = m_VectorField->begin();
			i != m_VectorField->end();
			++i )
	{
		(*i)->ClearPointTo();
	}
}
