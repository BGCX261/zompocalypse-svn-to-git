/*
 * Bullet.h
 *
 *  Created on: Nov 30, 2012
 *      Author: Ben Norwood
 */

#ifndef BULLET_H_
#define BULLET_H_

#include <ma.h>
#include <maassert.h>
#include "MAHeaders.h"
#include <MAUtil/Graphics.h>

class Bullet{
public:
	Bullet(){

	}

	boolean Collide(){

	}
private:
	MARect bullet_srcRect;
	MAPoint2d bulletDest_pt;
};


#endif /* BULLET_H_ */
