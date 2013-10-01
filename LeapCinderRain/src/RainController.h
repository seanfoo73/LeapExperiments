#ifndef __RAINCONTROLLER_H__
#define __RAINCONTROLLER_H__

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

#include "RainParticle.h"

#include <list>

using namespace ci;
using namespace ci::app;

class RainController
{
	public:
		RainController();
		~RainController();

		void Update( float dT );
		void MakeItRain( int numDroplets );
		void Draw();

		void CheckPointTo( Vec2f loc, float fingerRadius );
		void ClearPointTo();

	private:
		std::list<RainParticle*>* m_RainDrops;
		
		float m_fRainInterval;
		float m_fLastRain;

		int m_nSpacing;
};

#endif /** __RAINCONTROLLER_H__ */
