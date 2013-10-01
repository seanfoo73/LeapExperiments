#ifndef __ENEMYFISH_H__
#define __ENEMYFISH_H__

#include "Fish.h"

class EnemyFish : public Fish
{
	public:
		EnemyFish();
		~EnemyFish();

		virtual void Update( float dT );

	private:
};

#endif /** __ENEMYFISH_H__ */