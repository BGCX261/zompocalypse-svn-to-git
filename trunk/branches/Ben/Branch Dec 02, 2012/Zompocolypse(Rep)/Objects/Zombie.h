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
		zomb_srcRect.left=48;
		zomb_srcRect.top=64;
		zomb_srcRect.width=24;
		zomb_srcRect.height=32;
		zomb_pt.x=90;
		zomb_pt.y=0;
		time=0;
	}

    virtual void Init(int scale) =0;

	void runTimerEvent(){
		time+=100;
		Draw();
	}

	void giveDamage(int hitP){
		health-=hitP;
		if(health<=0)
			collide();
	}

	//if this function returns true, zombie is removed from the game.
	//otherwise handle all other collisions in this function
	//this function should only return true when the zombie is ready to die.
	bool collide(){
		//short circuit end for efficiency
		if(health<=0)
			return true;
		//end of lane

		//bullet damage

		//after evaluation return
		if(health<=0)
		 return true;
		else
		return false;
	}

protected:
	void Draw(){
		if(time%2000 == 0){
			time=0;
			if(zomb_srcRect.left < 72)
				zomb_srcRect.left+=24;
			else
				zomb_srcRect.left=0;
		}

		zomb_pt.y+= int(vel_y * 5);
		//determine which sprite to draw here
		Gfx_drawImageRegion(ZOMBIE, &zomb_srcRect, &zomb_pt, TRANS_NONE);
	}

	//don't need vel_x b/c zombies only move in one dimension
	float health, vel_y;
	bool collided;
	int time;
	MARect zomb_srcRect;
	MAPoint2d zomb_pt;
};

class SuperZombie : public Zombie{
public:
	SuperZombie(int scale) : Zombie(scale){Init(scale);}

	void Init(int scale){
		health= 2 * scale;
		vel_y=   .2 * scale;
		//set the srcRectangle when we get sprites!


	}
};

class SpeedZombie : public Zombie{
public:
	SpeedZombie(int scale) : Zombie(scale){Init(scale);}

	void Init(int scale){
		health= .8 * scale;
		vel_y=   2 * scale;
	}
};

class RegZombie : public Zombie{
public:
	RegZombie(int scale) : Zombie(scale){Init(scale);}
	void Init(int scale){
		health= 1.5 * scale;
		vel_y=   .5 * scale;
	}

};


#endif /* ZOMBIE_H_ */
