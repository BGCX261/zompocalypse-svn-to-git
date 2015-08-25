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
#include "GameOverBro.h"



using namespace MAUI;
using namespace MAUtil;


class PlayScreen : public Screen, public MAUtil::TimerListener
{
public:

	// construstor to create the Play screen
	PlayScreen(Screen *previous) : previous(previous)
	{
		gameOverBro = new GameOverScreen(previous);
		// creates a Play object stuff and then draws a black background
		stuff = new Play(0, 0, scrWidth, scrHeight, NULL);
		stuff->setSkin(gSkin);
		stuff->setDrawBackground(true);

		this->setMain(stuff);
		maxWallHP = stuff->getMaxWallHP();

		int gametime=0;

		listening=false;

		zombieHeight = int(scrHeight *.04);
		buttonsHeight = int(scrHeight *.94);
		gameOverButtonHeight = int(scrHeight * .92);

		inLocationWood = inLocationBullets = false;

	}

	~PlayScreen()
	{
		//delete stuff;
	}


	void pointerPressEvent(MAPoint2d point)
	{
		if (stuff->getGameStart())
		{
			if (!stuff->getGameOver())
			{
				if(!listening)
				{
					Environment::getEnvironment().addTimer(this, 200, -1);
					listening=true;
				}

				// if the user clicks between the stat bar at the top
				// and the buttons at the bottom.
				if (point.y < buttonsHeight && point.y > zombieHeight)
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

					heroPos = stuff->getHeroPos();

					if (heroPos != 2)
					{
						inLocationWood = false;

					}
					if (heroPos != 3)
					{
						inLocationBullets = false;
					}


				}

				// if the user click one of the buttons at the bottom
				if (point.y > buttonsHeight)
				{

					heroPos = stuff->getHeroPos();

					// Menu Button Click
					if (point.x > 0 && point.x < stuff->getLanePos(1))
					{
						Environment::getEnvironment().removeTimer(this);
						listening=false;
						previous->show();
					}
					// Pistol / Shotgun Button Click
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
					if (point.x > stuff->getLanePos(2) && point.x < stuff->getLanePos(3))
					{
						if (heroPos == 2)
						{
							inLocationWood = true;
						}
					}
					// Bullets Resource Click
					if (point.x > stuff->getLanePos(3) && point.x < stuff->getLanePos(4))
					{
						if (heroPos == 3)
						{
							inLocationBullets = true;

						}
					}
					// Shoot Button Click
					if (point.x > stuff->getLanePos(4) && point.x < (scrWidth))
					{
						//stuff->setGameOver(true);
						if(stuff->spawners[heroPos]->container.size()>0 && stuff->getBulletsRes() > 0){
							MAUtil::List<Zombie*>::ListIterator it=stuff->spawners[heroPos]->container.end();
							Zombie *curr=it.prev();
							curr->giveDamage(10);
							if(curr->getHealth()<=0){
								it=stuff->spawners[heroPos]->container.remove(it);
								delete curr;
								stuff->addOneHeroScore();
							}
							stuff->subBulletsRes();
						}
					}
				}

			}

			else //gameover state
			{
				delete stuff;
				stuff = new Play(0, 0, scrWidth, scrHeight, NULL);
				stuff->setSkin(gSkin);
				stuff->setDrawBackground(true);

				this->setMain(stuff);
				maxWallHP = stuff->getMaxWallHP();

				int gametime=0;

				listening=false;

				zombieHeight = int(scrHeight *.04);
				buttonsHeight = int(scrHeight *.94);
				gameOverButtonHeight = int(scrHeight * .92);

				inLocationWood = inLocationBullets = false;
				Environment::getEnvironment().removeTimer(this);
				gameOverBro->show();
			}
		}
		else
		{
			stuff->setGameStart(true);
			stuff->drawWidget();
		}
	}

	void pointerReleaseEvent(MAPoint2d point)
	{

	}

	void runTimerEvent()
	{
		if(!stuff->getGameOver()){
			for(int i=0; i<6; i++){
				  stuff->spawners[i]->setWallHealth(stuff->getWallHealth(i));
				  stuff->spawners[i]->runTimerEvent();
				  if(stuff->spawners[i]->takeAway())
				  {
					  stuff->subWallHealth(i);
				  }

			}

		if(inLocationWood) {
			stuff->addWoodRes();
		}
		if(inLocationBullets) {
			stuff->addBulletsRes();
		}

		stuff->drawWidget();

		gametime+=200;
		}

	}

private:

	Play *stuff;

	Screen *previous;
	Screen *gameOverBro;

	char *wHP[numOfLanes];

	int lanePos[numOfLanes];

	int gametime;

	int heroPos, maxWallHP;
	bool listening, inLocationWood, inLocationBullets;

	int zombieHeight, buttonsHeight, gameOverButtonHeight;

};

#endif
