#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"

#include "Leap.h"
#include "LeapListener.h"

#include "VectorFieldController.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class LeapCinderVectorFieldApp : public AppNative {
	public:
		void prepareSettings( Settings * settings );
		void setup();
		void mouseDown( MouseEvent event );	
		void mouseMove( MouseEvent event );
		void mouseDrag( MouseEvent event );
		void update();
		Vec2f LeapCinderVectorFieldApp::normalizeCoords(const Leap::Vector& vec);
		void processFingers();
		void draw();
		void shutdown();
		
		void calculateFrameTime();

	private:
		gl::Texture m_BGImage;
		float m_fFrameTime;
		float m_fLastTime;

		VectorFieldController* m_VectorField;

		Controller m_LeapController;
		LeapListener m_LeapListener;
};

void LeapCinderVectorFieldApp::prepareSettings( Settings* settings )
{
	settings->setWindowSize( 1366, 768 );
	settings->setFrameRate( 60.0f );
}

void LeapCinderVectorFieldApp::setup()
{
	m_LeapController.addListener( m_LeapListener );

	/** timing data */
	m_fLastTime = getElapsedSeconds();
	m_fFrameTime = 0;

	/** background image */
	//m_BGImage = gl::Texture( loadImage( loadAsset( "testBg.jpg" ) ) );

	/** vector field */
	m_VectorField = new VectorFieldController();
}

void LeapCinderVectorFieldApp::mouseDown( MouseEvent event )
{
	//m_VectorField->ClearPointTo();
	//m_VectorField->CheckPointTo( event.getPos() );
}

void LeapCinderVectorFieldApp::mouseMove( MouseEvent event )
{
	//m_VectorField->ClearPointTo();
	//m_VectorField->CheckPointTo( event.getPos() );
}

void LeapCinderVectorFieldApp::mouseDrag( MouseEvent event )
{
	//m_VectorField->ClearPointTo();
	//m_VectorField->CheckPointTo( event.getPos() );
}


void LeapCinderVectorFieldApp::update()
{
	processFingers();
}

void LeapCinderVectorFieldApp::processFingers()
{
	Leap::Frame frame = m_LeapController.frame();
	Leap::FingerList fingers = frame.fingers();

	m_VectorField->ClearPointTo();

	for( int i = 0; i < fingers.count(); i++ )
	{
		m_VectorField->CheckPointTo( normalizeCoords( fingers[i].tipPosition() ) );
	}
}

/** stole this from the gesture demo, this is unsafe because if you run coords through it
multiple times, it will no longer actually be normalized */
Vec2f LeapCinderVectorFieldApp::normalizeCoords( const Leap::Vector& vec ) {
	static const float INTERACTION_CENTER_X = 0;
	static const float INTERACTION_CENTER_Y = 200;
	static const float INTERACTION_CENTER_Z = 0;
	static const float INTERACTION_SIZE = 400;

	Vec2f result;
	result.x = ( (vec.x - INTERACTION_CENTER_X + (INTERACTION_SIZE/2)) / INTERACTION_SIZE ) * app::getWindowWidth();
	result.y = ( 1.0f - (vec.y - INTERACTION_CENTER_Y + (INTERACTION_SIZE/2)) / INTERACTION_SIZE ) * app::getWindowHeight();

	return result;
}

void LeapCinderVectorFieldApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 

	if( m_BGImage )
		gl::draw( m_BGImage, getWindowBounds() );

	m_VectorField->Draw();
}

void LeapCinderVectorFieldApp::shutdown()
{
	m_LeapController.removeListener( m_LeapListener );
	delete m_VectorField;
}

void LeapCinderVectorFieldApp::calculateFrameTime()
{
	m_fFrameTime = getElapsedSeconds() - m_fLastTime;
	m_fLastTime = getElapsedSeconds();
}

CINDER_APP_NATIVE( LeapCinderVectorFieldApp, RendererGl )
