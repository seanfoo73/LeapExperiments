#ifndef __VECTORFIELDCONTROLLER_H__
#define __VECTORFIELDCONTROLLER_H__

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

#include "VectorParticle.h"

#include <list>

using namespace ci;
using namespace ci::app;

class VectorFieldController
{
	public:
		VectorFieldController();
		~VectorFieldController();

		void Update( float dT );
		void Draw();

		void CheckPointTo( Vec2f loc );
		void ClearPointTo();

	private:
		std::list<VectorParticle*>* m_VectorField;

		int m_nSpacing;
};

#endif /** __VECTORFIELDCONTROLLER_H__ */
