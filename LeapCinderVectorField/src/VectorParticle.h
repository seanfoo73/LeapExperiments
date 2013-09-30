#ifndef __VECTORPARTICLE_H__
#define __VECTORPARTICLE_H__

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;

class VectorParticle
{
	public:
		VectorParticle( Vec2f loc );
		~VectorParticle();

		void Update( float dT );
		void Draw();

		void CheckPointTo( Vec2f loc );
		void ClearPointTo();

	private:
		Vec2f m_vLoc;
		Vec2f m_vPointTo;

		float m_fLength;
		float m_fHeadRadius;
		float m_fHeadLength;

		int m_nShortestDistance;
};

#endif /** __VECTORPARTICLE_H__ */
