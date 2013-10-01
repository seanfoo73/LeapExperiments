#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

#include "Leap.h"

#include <list>

#include "PlayerFish.h"
#include "EnemyFish.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class LeapListener : public Leap::Listener
{
	public:
		virtual void onInit( const Leap::Controller& leap )
		{
			leap.enableGesture( Leap::Gesture::TYPE_SWIPE );
			leap.enableGesture( Leap::Gesture::TYPE_SCREEN_TAP );
			leap.enableGesture( Leap::Gesture::TYPE_KEY_TAP );
		}
};

class LeapFishyApp : public AppNative {
	public:
		void prepareSettings( Settings* settings );
		void setup();
		void mouseDown( MouseEvent event );	
		void calculateFrameTime();
		void SpawnEnemyFish( int nNum );
		void update();
		void updateFish();
		void processGesture();
		Vec2f normalizeCoords( const Leap::Vector& vec );
		void draw();
		void resetGame();
		void killAllEnemyFish();
		void shutdown();

	private:
		float m_fFrameTime;
		float m_fLastTime;

		PlayerFish* m_pPlayer;

		Leap::Controller m_LeapController;
		LeapListener m_LeapListener;
		Leap::Frame m_LastFrame;

		int m_nMinNumFishes;
		std::list<EnemyFish*>* m_pEnemyFishes;
};

void LeapFishyApp::prepareSettings( Settings* settings )
{
	settings->setWindowSize( 1366, 768 );
	settings->setFrameRate( 60.0f );
}

void LeapFishyApp::setup()
{
	m_LeapController.addListener( m_LeapListener );

	/** timing data */
	m_fLastTime = getElapsedSeconds();
	m_fFrameTime = 0;

	/** player setup */
	m_pPlayer = new PlayerFish();

	/** enemy fish setup */
	m_pEnemyFishes = new std::list<EnemyFish*>();
	m_nMinNumFishes = 10;

	SpawnEnemyFish( m_nMinNumFishes );
}

void LeapFishyApp::mouseDown( MouseEvent event )
{
	resetGame();
}

void LeapFishyApp::calculateFrameTime()
{
	m_fFrameTime = getElapsedSeconds() - m_fLastTime;
	m_fLastTime = getElapsedSeconds();
}

void LeapFishyApp::SpawnEnemyFish( int nNum )
{
	for( int i = 0; i < nNum; i++ )
	{
		m_pEnemyFishes->push_back( new EnemyFish() );
	}
}

void LeapFishyApp::update()
{
	calculateFrameTime();

	processGesture();

	updateFish();

	if( m_pEnemyFishes->size() < m_nMinNumFishes )
	{
		SpawnEnemyFish( m_nMinNumFishes - m_pEnemyFishes->size() );
	}
}

void LeapFishyApp::updateFish()
{
	m_pPlayer->Update( m_fFrameTime );

	for(	std::list<EnemyFish*>::iterator i = m_pEnemyFishes->begin();
			i != m_pEnemyFishes->end();
			)
	{
		(*i)->Update( m_fFrameTime );

		//Check collisions
		if( (*i)->m_CollisionVolume.intersects( m_pPlayer->m_CollisionVolume ) )
		{
			//enemy fish is smaller
			if( (*i)->m_fScaling < m_pPlayer->m_fScaling ) 
			{
				m_pPlayer->Grow( (*i)->m_fScaling / 2.0f );
				(*i)->m_bAlive = false;
			}
			//enemy fish is larger or same size
			else
			{
				resetGame();
				return;
			}
		}

		//Remove Dead fish
		if( !(*i)->m_bAlive )
		{
			delete (*i);
			i = m_pEnemyFishes->erase(i);
		}
		else
		{
			++i;
		}
	}
}

void LeapFishyApp::processGesture()
{
	Leap::Frame frame = m_LeapController.frame();

	if( m_LastFrame == frame )
		return;

	Leap::GestureList gestures =	m_LastFrame.isValid()			?
									frame.gestures( m_LastFrame )	:
									frame.gestures();

	m_LastFrame = frame;

	for( int i = 0; i < gestures.count(); i++ )
	{
		if( gestures[i].type() == Leap::Gesture::TYPE_SWIPE )
		{
			Leap::SwipeGesture swipe = gestures[i];
			Leap::Vector diff = 0.006f*(swipe.position() - swipe.startPosition());
			Vec2f curSwipe(diff.x, -diff.y);
			m_pPlayer->AddVelocity( curSwipe );
		}
		else if(	gestures[i].type() == Leap::Gesture::TYPE_KEY_TAP || 
					gestures[i].type() == Leap::Gesture::TYPE_SCREEN_TAP )
		{
			m_pPlayer->KillVelocity();
		}
	}
}

/** stole this from the gesture demo, this is unsafe because if you run coords through it
multiple times, it will no longer actually be normalized */
Vec2f LeapFishyApp::normalizeCoords( const Leap::Vector& vec ) {
	static const float INTERACTION_CENTER_X = 0;
	static const float INTERACTION_CENTER_Y = 200;
	static const float INTERACTION_CENTER_Z = 0;
	static const float INTERACTION_SIZE = 400;

	Vec2f result;
	result.x = ( (vec.x - INTERACTION_CENTER_X + (INTERACTION_SIZE/2)) / INTERACTION_SIZE ) * app::getWindowWidth();
	result.y = ( 1.0f - (vec.y - INTERACTION_CENTER_Y + (INTERACTION_SIZE/2)) / INTERACTION_SIZE ) * app::getWindowHeight();

	return result;
}

void LeapFishyApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 

	if( m_pPlayer )
		m_pPlayer->Draw();

	for(	std::list<EnemyFish*>::iterator i = m_pEnemyFishes->begin();
			i != m_pEnemyFishes->end();
			++i )
	{
		(*i)->Draw();
	}
}

void LeapFishyApp::shutdown()
{
	m_LeapController.removeListener( m_LeapListener );

	delete m_pPlayer;

	killAllEnemyFish();

	delete m_pEnemyFishes;
}

void LeapFishyApp::killAllEnemyFish()
{
	for(	std::list<EnemyFish*>::iterator i = m_pEnemyFishes->begin();
			i != m_pEnemyFishes->end();
			)
	{
		delete (*i);
		i = m_pEnemyFishes->erase(i);
	}
}

void LeapFishyApp::resetGame()
{
	killAllEnemyFish();

	m_pPlayer->ResetPlayer();

	SpawnEnemyFish( m_nMinNumFishes );
}

CINDER_APP_NATIVE( LeapFishyApp, RendererGl )
