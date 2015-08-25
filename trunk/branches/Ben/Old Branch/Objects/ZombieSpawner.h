/*
 * ZombieSpawner.h
 *
 *  Created on: Nov 5, 2012
 *      Author: Ben Norwood
 */

#ifndef ZOMBIESPAWNER_H_
#define ZOMBIESPAWNER_H_

#include <ma.h>
#include <maassert.h>
#include "MAHeaders.h"
#include <MAUtil/Graphics.h>
#include <MAUtil/List.h>

class ZombieSpawner: public MAUtil::TimerListener{
public:
	ZombieSpawner(){
		zombieSpawnCount=spawnTime=scale=1;
		time=0;
		//set the srcRectangle when we get sprites!
		addTimer(this, 50, -1);
		Draw();

	}
	~ZombieSpawner(){
		MAUtil::List<Zombie*>::iterator it=container.begin();
		Zombie *prev=it.next();
		Zombie *curr=it.next();
		while(it.hasNext())
		{
		 delete prev;
	     prev=curr;
		 curr=it.next();
	    }
	    delete curr;
	}

	void runTimerEvent(){

		switch(zombieSpawnCount)
		{
			case 3: if((time%50) ==0) container.addFirst(new Zombie(scale));
			case 2: if((time%100)==0) container.addFirst(new Zombie(scale));
			case 1: if((time%150)==0) container.addFirst(new Zombie(scale));
		}

		if(time%10000==0)
			scale+=0.5;
		if(zombieSpawnCount<3 && scale>=10)
		{
			zombieSpawnCount++;
			scale=1;
		}

		//check for collides to update list
		MAUtil::List<Zombie*>::iterator it=container.begin();

		//priming loop for container
		  Zombie *current=it.next();
		while(it.hasNext() && container.size()<1){
			if(current->collide()){
				Zombie *destroy=current;
				current=it.next();
				it=container.remove(it.prev());
				delete destroy;
			}
		}

		time+=50;
	}
private:
	void Draw(){
		//determine which sprite to draw here
		Gfx_drawImageRegion(BOY_IMAGE, &zomb_srcRect, &zombSpawner_Pt, TRANS_NONE);
	}

	//don't need vel_x b/c zombies only move in one dimension
	float scale;
	int zombieSpawnCount, spawnTime, time;
	MARect zomb_srcRect;
	MAPoint2d zombSpawner_pt;

	MAUtil::List<Zombie*> container;

};
#endif /* ZOMBIESPAWNER_H_ */
