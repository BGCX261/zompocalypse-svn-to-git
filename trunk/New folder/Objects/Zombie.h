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
	bool blocked;
	Zombie(float scale, int posx, int posy){
		zomb_srcRect.left=48;
		zomb_srcRect.top=64;
		zomb_srcRect.width=24;
		zomb_srcRect.height=32;
		zomb_pt.x=posx;
		zomb_pt.y=posy;
		blocked=false;
		time=0;
	}

    virtual void Init(int scale) =0;

	void runTimerEvent(){

		time+=100;
		this->Draw();
	}

	void giveDamage(int hitP){
		health-=hitP;
		//if(health<=0)
			//collide();
	}

	//if this function returns true, zombie is removed from the game.
	//otherwise handle all other collisions in this function
	//this function should only return true when the zombie is ready to die.
	bool collide(int wall){
		//end of lane
		if((zomb_pt.y+40 >= scrHeight * .77) && wall>0 && !blocked){
			blocked=true;
			return true;
		}

		//bullet damage

		return false;
	}

	float getHealth(){
		return health;
	}

	void Draw(){
		time+=100;
		if(!blocked){
		  zomb_pt.y+= int(vel_y * 5);
		}
		else
			zomb_pt.y= int(scrHeight * .77) - 40;
		//determine which sprite to draw here
		maDrawImage(ZOMBIE, zomb_pt.x, zomb_pt.y);
		//maDrawImage(ZOMBIE, zomb_pt.x, zomb_pt.y);
	}

protected:
	//don't need vel_x b/c zombies only move in one dimension
	float health, vel_y;

	int time;
	MARect zomb_srcRect;
	MAPoint2d zomb_pt;
};

class SuperZombie : public Zombie{
public:
	SuperZombie(int scale, int posx, int posy) : Zombie(scale, posx, posy){Init(scale);}

	void Init(int scale){
		health= 2 * scale;
		vel_y=   1.2 * scale;
		//set the srcRectangle when we get sprites!


	}
};

class SpeedZombie : public Zombie{
public:
	SpeedZombie(int scale, int posx, int posy) : Zombie(scale, posx, posy){Init(scale);}

	void Init(int scale){
		health= .8 * scale;
		vel_y=   1.8 * scale;
	}
};

class RegZombie : public Zombie{
public:
	RegZombie(int scale, int posx, int posy) : Zombie(scale, posx, posy){Init(scale);}
	void Init(int scale){
		health= 1.5 * scale;
		vel_y=   1.2 * scale;
	}

};


#endif /* ZOMBIE_H_ */
