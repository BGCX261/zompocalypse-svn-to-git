#ifndef _PLAYSCREEN_H_
#define _PLAYSCREEN_H_

#include <MAUI/Screen.h>
#include <MAUI/Layout.h>
#include <MAUI/ListBox.h>
#include <MAUI/Image.h>

#include <conprint.h>

#include "MAHeaders.h"

#include "../Util.h"
#include "../Play.h"

#include "../Objects/Zombie.h"
//#include "../Objects/ZombieSpawner.h"
//#include "../Objects/Hero.h"
//#include "../Objects/Bullet.h"


using namespace MAUI;
using namespace MAUtil;

class PlayScreen : public Screen, public MAUtil::TimerListener
{
public:

	// construstor to create the Play screen
	PlayScreen(Screen *previous) : previous(previous)
	{
		// creates a Play object stuff and then draws a black background
		stuff = new Play(0, 0, scrWidth, scrHeight, NULL);
		stuff->setDrawBackground(true);
		this->setMain(stuff);

		maxWallHP = stuff->getMaxWallHP();




		//temp = new RegZombie(1);
		//int gametime=0;

		Environment::getEnvironment().addTimer(this, 1000, -1);

	}

	~PlayScreen()
	{
		//delete stuff;
	}


	void pointerPressEvent(MAPoint2d point)
	{
		if (stuff->getGameOver() == false)
		{

			// if the user clicks between the stat bar at the top
			// and the buttons at the bottom.
			if (point.y < (scrHeight * .91) && point.y > (scrHeight * .07))
			{
				heroPos = stuff->getHeroPos();

				// Lane 0 Click
				if (stuff->getLanePos(0) < point.x && point.x < stuff->getLanePos(1))
				{
					// if the hero is already in the lane build a wall if the user has wood
					if (heroPos == 0)
					{
						if (stuff->getWallHealth(0) < maxWallHP)
						{
							stuff->addWallHealth(0);
							stuff->subWoodRes();
						}
					}

					else
					{
						stuff->setHeroPos(0);
					}

				}
				// Lane 1 Click
				if (stuff->getLanePos(1) < point.x && point.x < stuff->getLanePos(2))
				{
					// if the hero is already in the lane build a wall if the user has wood
					if (heroPos == 1)
					{
						if (stuff->getWallHealth(1) < maxWallHP)
						{
							stuff->addWallHealth(1);
							stuff->subWoodRes();
						}
					}

					else
					{
						stuff->setHeroPos(1);
					}
				}
				// Lane 2 Click
				if (stuff->getLanePos(2) < point.x && point.x < stuff->getLanePos(3))
				{
					// if the hero is already in the lane build a wall if the user has wood
					if (heroPos == 2)
					{
						if (stuff->getWallHealth(2) < maxWallHP)
						{
							stuff->addWallHealth(2);
							stuff->subWoodRes();
						}
					}

					else
					{
						stuff->setHeroPos(2);
					}
				}
				// Lane 3 Click
				if (stuff->getLanePos(3) < point.x && point.x < stuff->getLanePos(4))
				{
					// if the hero is already in the lane build a wall if the user has wood
					if (heroPos == 3)
					{
						if (stuff->getWallHealth(3) < maxWallHP)
						{
							stuff->addWallHealth(3);
							stuff->subWoodRes();
						}
					}

					else
					{
						stuff->setHeroPos(3);
					}
				}
				// Lane 4 Click
				if (stuff->getLanePos(4) < point.x && point.x < stuff->getLanePos(5))
				{
					// if the hero is already in the lane build a wall if the user has wood
					if (heroPos == 4)
					{
						if (stuff->getWallHealth(4) < maxWallHP)
							{
								stuff->addWallHealth(4);
								stuff->subWoodRes();
							}
					}

					else
					{
						stuff->setHeroPos(4);
					}
				}
				// Lane 5 Click
				if (stuff->getLanePos(5) < point.x && point.x < scrWidth)
				{
					// if the hero is already in the lane build a wall if the user has wood
					if (heroPos == 5)
					{
						if (stuff->getWallHealth(5) < maxWallHP)
						{
							stuff->addWallHealth(5);
							stuff->subWoodRes();
						}
					}

					else
					{
						stuff->setHeroPos(5);
					}
				}
			}

			// if the user click one of the buttons at the bottom
			if (point.y > (scrHeight * .91))
			{

				heroPos = stuff->getHeroPos();

				// Menu Button Click
				//if (point.x > 0 && point.x < (scrWidth * .2))
				if (point.x > 0 && point.x < stuff->getLanePos(1))
				{
					stuff->setZombiePos(0);
				}
				// Pistol / Shotgun Button Click
				//if (point.x > (scrWidth * .2) && point.x < (scrWidth * .4))
				if (point.x > stuff->getLanePos(1) && point.x < stuff->getLanePos(2))
				{
					stuff->setZombiePos(1);

					if (stuff->getPistol())
					{
						stuff->setPistol(false);
					}

					else
					{
						stuff->setPistol(true);
					}

				}
				// Wood Resource Click
				//if (point.x > (scrWidth * .4) && point.x < (scrWidth * .5))
				if (point.x > stuff->getLanePos(2) && point.x < stuff->getMiddleLanePos(2))
				{
					if (heroPos == 2)
					{
						stuff->addWoodRes();
					}
				}
				// Bullets Resource Click
				//if (point.x > (scrWidth * .5) && point.x < (scrWidth * .6))
				if (point.x > stuff->getMiddleLanePos(2) && point.x < stuff->getLanePos(3))
				{
					if (heroPos == 2)
					{
						stuff->addBulletsRes();
					}
				}
				//Food/Water Resource Click
				//if (point.x > (scrWidth * .6) && point.x < (scrWidth * .7))
				if (point.x > stuff->getLanePos(3) && point.x < stuff->getMiddleLanePos(3))
				{
					if (heroPos == 3)
					{
						stuff->addFoodWaterRes();
					}
				}
				// Metal Resource Click
				//if (point.x > (scrWidth * .7) && point.x < (scrWidth * .8))
				if (point.x > stuff->getMiddleLanePos(3) && point.x < stuff->getLanePos(4))
				{
					if (heroPos == 3)
					{
						stuff->addMetalRes();
					}
				}
				// Shoot Button Click
				//if (point.x > (scrWidth * .8) && point.x < (scrWidth))
				if (point.x > stuff->getLanePos(4) && point.x < (scrWidth))
				{
					stuff->subHeroHealth();
				}
			}

			stuff->drawWidget();
		}

		else
		{
			// If the user clicks a button in the Game Over Screen
			if (point.y > (scrHeight * .92))
			{
				// user click on restart game
				if (point.x < (scrWidth / 2))
				{
					stuff = new Play(0, 0, scrWidth, scrHeight, NULL);
					//stuff->setDrawBackground(true);
				}

				// user click on Menu option
				if (point.x > (scrWidth / 2))
				{
					stuff = new Play(0, 0, scrWidth, scrHeight, NULL);
					previous->show();
				}
			}
		}
	}

	void pointerReleaseEvent(MAPoint2d point)
	{

	}

	void runTimerEvent()
	{
		//stuff->addMetalRes();
		//stuff->drawWidget();

	//	gametime+=50;
	//	if(gametime%100==0){
	//	  temp->runTimerEvent();
	//		updateScreen();
	//	}
	}

private:

	Play *stuff;

	Screen *previous;

	char *wHP[numOfLanes];

	int lanePos[numOfLanes];

	int gametime;

	int heroPos, maxWallHP;

	//RegZombie *temp;

};

#endif
