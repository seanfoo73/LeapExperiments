#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"

#include "Leap.h";

#include "RainController.h";

using namespace ci;
using namespace ci::app;
using namespace std;

class LeapCinderRainApp : public AppNative {
	public:
		void prepareSettings( Settings * settings );
		void setup();
		void mouseDown( MouseEvent event );	
		Vec2f normalizeCoords(const Leap::Vector& vec);
		void processFingers();
		void update();
		void draw();
		void shutdown();

		void calculateFrameTime();

	private:
		gl::Texture m_BGImage;
		float m_fFrameTime;
		float m_fLastTime;

		RainController* m_Rain;

		Leap::Controller m_LeapController;
		Leap::Listener m_LeapListener;
};

void LeapCinderRainApp::prepareSettings( Settings* settings )
{
	settings->setWindowSize( 1366, 768 );
	settings->setFrameRate( 60.0f );
}

void LeapCinderRainApp::setup()
{
	m_LeapController.addListener( m_LeapListener );

	/** timing data */
	m_fLastTime = getElapsedSeconds();
	m_fFrameTime = 0;

	/** background image */

	/** vector field */
	m_Rain = new RainController();
}

void LeapCinderRainApp::mouseDown( MouseEvent event )
{
}

void LeapCinderRainApp::update()
{
	calculateFrameTime();
	m_Rain->Update( m_fFrameTime );
	processFingers();
}

void LeapCinderRainApp::processFingers()
{
	Leap::Frame frame = m_LeapController.frame();
	Leap::FingerList fingers = frame.fingers();

	m_Rain->ClearPointTo();

	for( int i = 0; i < fingers.count(); i++ )
	{
		m_Rain->CheckPointTo( normalizeCoords( fingers[i].tipPosition() ), 40.0f );
	}
}

/** stole this from the gesture demo, this is unsafe because if you run coords through it
multiple times, it will no longer actually be normalized */
Vec2f LeapCinderRainApp::normalizeCoords( const Leap::Vector& vec ) {
	static const float INTERACTION_CENTER_X = 0;
	static const float INTERACTION_CENTER_Y = 200;
	static const float INTERACTION_CENTER_Z = 0;
	static const float INTERACTION_SIZE = 400;

	Vec2f result;
	result.x = ( (vec.x - INTERACTION_CENTER_X + (INTERACTION_SIZE/2)) / INTERACTION_SIZE ) * app::getWindowWidth();
	result.y = ( 1.0f - (vec.y - INTERACTION_CENTER_Y + (INTERACTION_SIZE/2)) / INTERACTION_SIZE ) * app::getWindowHeight();

	return result;
}

void LeapCinderRainApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 

	m_Rain->Draw();
}

void LeapCinderRainApp::shutdown()
{
	m_LeapController.removeListener( m_LeapListener );
	delete m_Rain;
}

void LeapCinderRainApp::calculateFrameTime()
{
	m_fFrameTime = getElapsedSeconds() - m_fLastTime;
	m_fLastTime = getElapsedSeconds();
}

CINDER_APP_NATIVE( LeapCinderRainApp, RendererGl )
