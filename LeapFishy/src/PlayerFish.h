#ifndef __PLAYERFISH_H__
#define __PLAYERFISH_H__

#include "Fish.h"

class PlayerFish : public Fish
{
	public:
		PlayerFish();
		~PlayerFish();

		virtual void Update( float dT );

		void AddVelocity( Vec2f vel );
		void KillVelocity();

		void Grow( float growth );

		void ResetPlayer();

	private:
};

#endif /** __PLAYERFISH_H__ */
