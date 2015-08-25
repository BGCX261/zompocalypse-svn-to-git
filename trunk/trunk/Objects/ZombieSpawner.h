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
#include "Zombie.h"
#include <MAUtil/Graphics.h>
#include <MAUtil/List.h>
#include "../Play.h"

class ZombieSpawner: public MAUtil::TimerListener{
public:
	ZombieSpawner(int laneposx, int laneposy, int lanenum){
		zombieSpawnCount=spawnTime=scale=1;
		time=0;
		//set the srcRectangle when we get sprites!

		zombSpawner_pt.x=laneposx;
		zombSpawner_pt.y=laneposy;
		this->lanenum=lanenum;

	}

	void addListener(){
		Environment::getEnvironment().addTimer(this, 100, -1);

	}

	void removeListerner(){
		Environment::getEnvironment().removeTimer(this);

	}

	~ZombieSpawner(){
		MAUtil::List<Zombie*>::ListIterator it=container.begin();
		Zombie *curr;

		while(it.hasNext())
		{
			curr=it.next();
			delete curr;
			curr=it.next();
		}
		delete curr;
	}

	MAUtil::List<Zombie*>* liveZombies(){
		return &container;
	}



	//Hey so this is an important function.
	//it makes all the zombies do stuff for the most part
	//I haven't determined the proper place to put them
	//all you would have to do is follow the way I determined how to place the zombie spawner
	//i.e. look at the constructor parameters and that would be the lane
	//zombie vertical movement is taken care of just need to make sure they get drawn to screen.
	void runTimerEvent(){
		switch(zombieSpawnCount)
		{
			case 3: if((time%700)==0) container.addFirst(new SuperZombie(scale, zombSpawner_pt.x, zombSpawner_pt.y));
			case 2: if((time%500)==0) container.addFirst(new SpeedZombie(scale, zombSpawner_pt.x, zombSpawner_pt.y));
			case 1: if((time%300)==0) container.addFirst(new RegZombie(scale, zombSpawner_pt.x, zombSpawner_pt.y));
		}

		if(time%10000==0){
			scale+=0.5;
			time=0;
		}

		if(zombieSpawnCount<3 && scale>=8)
		{
			zombieSpawnCount++;
			scale=1;
		}

		//check for collides to update list
		MAUtil::List<Zombie*>::ListIterator it=container.begin();
		Zombie *current;
		while(it.hasNext() && container.size()>=1){
			current=it.next();
			if(current->collide(1)){
				//stuff->subWallHealth(lanenum);
				if(current->getHealth()<=0){
					Zombie *destroy=current;
					it=container.remove(it);
					delete destroy;
				}

			}
		}

		time+=100;
	}

	void Draw(){
		maDrawImage(ZOM_SPAWNER, zombSpawner_pt.x, zombSpawner_pt.y );
		//check for collides to update list
		MAUtil::List<Zombie*>::ListIterator it=container.begin();
		while(it.hasNext() && container.size()>=1){
			Zombie *current=it.next();
			current->Draw();
		}
	}


	MAUtil::List<Zombie*> container;



private:
	//don't need vel_x b/c zombies only move in one dimension
	float scale;
	int zombieSpawnCount, spawnTime, time;
	int lanenum;
	MARect zomb_srcRect;
	MAPoint2d zombSpawner_pt;

};
#endif /* ZOMBIESPAWNER_H_ */
