#ifndef __RAINPARTICLE_H__
#define __RAINPARTICLE_H__

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;

class RainParticle
{
	public:
		RainParticle( Vec2f loc );
		~RainParticle();

		void Update( float dT );
		void Draw();

		void CheckPointTo( Vec2f loc, float fingerRadius );
		void ClearPointTo();

		bool IsInBounds();

	private:
		void CheckInBounds();

		Vec2f m_vLoc;
		Vec2f m_vPointTo;

		Vec2f m_vVel;
		Vec2f m_vDir;

		float m_fDropletRadius;

		float m_fLength;
		float m_fHeadRadius;
		float m_fHeadLength;

		int m_nShortestDistance;

		bool m_inBounds;
};

#endif /** __RAINPARTICLE_H__ */