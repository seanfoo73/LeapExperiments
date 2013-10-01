#ifndef __FISH_H__
#define __FISH_H__

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

#include "cinder/Rect.h"

using namespace ci;
using namespace ci::app;

class Fish
{
	public:
		Fish();
		virtual ~Fish();

		virtual void Update( float dT ) = 0;

		void Draw();

		float getWidth();
		float getHeight();

		Vec2f m_vLoc;
		Vec2f m_vVel;

		float m_fScaling;

		float m_fMinVelocity;
		float m_fMaxVelocity;

		Color m_Color;

		bool m_bAlive;

		Rectf m_CollisionVolume;

		float m_fWidth;
		float m_fHeight;
		float m_fRoundedCornerRadius;
};

#endif /** __FISH_H__ */
