/*
 * Zombie.h
 *
 *  Created on: Nov 5, 2012
 *      Author: Ben Norwood
 */

#ifndef ZOMBIE_H_
#define ZOMBIE_H_

#include <ma.h>
#include <maassert.h>
#include "MAHeaders.h"
#include <MAUtil/Graphics.h>

class Zombie: public MAUtil::TimerListener{

public:
	Zombie(int scale){
		Init();
	}

    void Init(){
		health= 1.5 * scale;
		vel_y=   .5 * scale;
		//set the srcRectangle when we get sprites!
		addTimer(this, 100, -1);
    }
	void runTimerEvent(){
		Draw();
	}

	//if this function returns true, zombie is removed from the game.
	//otherwise handle all other collisions in this function
	//this function should only return true when the zombie is ready to die.
	bool collide(){

		//end of lane

		if(health<=0)
		 return true;


		return false;
	}
private:
	void Draw(){
		//determine which sprite to draw here
		Gfx_drawImageRegion(BOY_IMAGE, &zomb_srcRect, &zombDest_Pt, TRANS_NONE);
	}

	//don't need vel_x b/c zombies only move in one dimension
	float health, vel_y;
	bool collided;
	MARect zomb_srcRect;
	MAPoint2d zombDest_pt;
};

class SuperZombie : public Zombie{
public:
	SuperZombie(int scale) : Zombie(scale){}

	void Init(int scale){
		health= 2 * scale;
		vel_y=   .2 * scale;
		//set the srcRectangle when we get sprites!
		addTimer(this, 100, -1);

	}
};

class SpeedZombie : public Zombie{
public:
	SpeedZombie(int scale){
		health= .8 * scale;
		vel_y=   2 * scale;
		//set the srcRectangle when we get sprites!
		addTimer(this, 100, -1);
	}
};


#endif /* ZOMBIE_H_ */
