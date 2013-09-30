#ifndef __LEAPLISTENER_H__
#define __LEAPLISTENER_H__

#include "Leap.h"
#include "cinder/app/AppNative.h"

using namespace Leap;
using namespace ci;
using namespace ci::app;

class LeapListener : public Listener
{
	public:
		LeapListener();
		~LeapListener();
	private:
};

#endif /** __LEAPLISTENER_H__ */
