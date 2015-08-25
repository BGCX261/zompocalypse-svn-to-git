/*
 * hero.h
 *
 *  Created on: Nov 2, 2012
 *      Author: Ben Norwood
 */

#ifndef HERO_H_
#define HERO_H_

#include <ma.h>
#include <maassert.h>
#include "MAHeaders.h"
#include <MAUtil/Graphics.h>

class Hero{

	public:
	  HeroObject getHero(){
		  if(leObject==NULL)
		  {
		    leObject= new HeroObject();
		    return leObject;
		  }
		  else
		    return leObject;
	  }

	protected:
	Hero(){
		leObject=NULL;
	}

	class HeroObject: public MAUtil::KeyListener, public MAUtil::PointerListener, public MAUtil::TimerListener{
		public:
			HeroObject(int x, int y){
				if( x>=0 && y>=0){ //in proper bounds for drawing set place
					destinationPt.x=x;
					destinationPt.y=y;
				}
				health=10;
				currentWeapon=wood=iron=bullets=food=0;
				vel_x=10;
				//SET the srcRectangle size when we get an image to work with

				addTimer(this, 50, -1);
			}

			void pointerPressEvent(MAPoint2d p){

				//determine what character is going to do based on position
				//if it is not function specific then it is a destination for character

				hero_destinationPt=p;

			}

			void runTimerEvent(){
				//determine lane give an integer representation
				if((currPt-hero_destinationPt)>=10)
				 currPt.x+=vel_x;
				else
				 currPt.x-=vel_x;

				Draw();
			}

		private:
			int  vel_x;
			int health, currentWeapon;
			int wood, iron, food, bullets;

			MARect hero_srcRect;
			MAPoint2d hero_destinationPt, currPt;

			void Draw(){
				//determine which sprite to draw here
				Gfx_drawImageRegion(BOY_IMAGE, &hero_srcRect, &hero_destinationPt, TRANS_NONE);

						}
	};
	private:
	static HeroObject leObject;
};

#endif /* HERO_H_ */
