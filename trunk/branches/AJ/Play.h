#ifndef _PLAY_H_
#define _PLAY_H_

#include "MAUI/Widget.h"
#include "Screens/PlayScreen.h"

const int numOfLanes = 6;

using namespace MAUI;


class Play : public Widget
{

public:

	// constructor which creates the initial play screen widget
	Play(int x, int y, int width, int height, Widget *parent ) : Widget( x, y, width, height, parent)
	{
		// sets the beginning of each lane
		for(int i = 0; i < numOfLanes; i++)
		{
			lanePos[i] = int(scrWidth * (i * .17));
			wHP[i] = 0;
		}

		for(int i = 0; i < numOfLanes - 1; i++)
		{
			middleLanePos[i] = int((lanePos[i] + lanePos[i + 1]) / 2);
		}

		middleLanePos[numOfLanes - 1] = int((lanePos[numOfLanes - 1] + scrWidth) / 2);

		// sets the starting values for all the attributes
		heroPos = heroScore = wood = bullets = foodWater = metal = 0;

		zombiePos = 0;

		maxWallHP = heroHP = maxHeroHP = 10;
		maxHeroScore = 100;
		maxRes = 9;
		maxWood = 10;

		isGameOver = false;

		pistol = true;


		wallImageSize = EXTENT_X(maGetImageSize(WALL));
		tombstoneImageSize = EXTENT_X(maGetImageSize(ZOM_SPAWNER));
		heroImageSize = EXTENT_X(maGetImageSize(ZOMBIE));
		zombieImageSize = EXTENT_X(maGetImageSize(ZOMBIE));



		// Draw the Play Screen
		drawWidget();
	}


// Game Over

	// if the Hero dies...
	void gameOver()
	{
		// Draw a black screen
		drawCanvas();

		// Draw the Game Over Screen
		maDrawImage(GAMEOVER, 0, 0);


		maSetColor(0xFFFFFF);

		// Draw the Restart and Menu Buttons
		maDrawText(int(scrWidth * .1), int(scrHeight * .93), "Restart");
		maDrawText(int(scrWidth * .7), int(scrHeight * .93), "Menu");

		maUpdateScreen();
	}

	// returns the statues of isGameOver
	bool getGameOver()
	{
		return isGameOver;
	}

	// sets Game Over to the passed value
	void setGameOver(bool isItOverYet)
	{
		isGameOver = isItOverYet;
	}





// draw functions


	// draws a black screen in order to be able redraw all the elements and simulate movement
	void drawCanvas()
	{
		maSetColor(0);
		maFillRect(0, 0, scrWidth, scrHeight);
	}

	// draws the stat bar at the top as well as all the buttons on the bottom.
	void drawControls()
	{
		//draw BackGround Image
		//maDrawImage(CHANGEBG0, 0, int(scrHeight * .06));
		//maFillRect(0, int(scrHeight * .91), scrWidth, scrHeight);
		//maFillRect(0, int(scrHeight * .72), scrWidth, int(scrHeight * .08));


		// sets the text color to white.
		maSetColor(0xFFFFFF);

		// draw the tombstones
		for(int i = 0; i < numOfLanes; i++)
		{
			maDrawImage(ZOM_SPAWNER, int(middleLanePos[i]- (tombstoneImageSize / 2)), int(scrHeight * .07));
		}

		// draws the vertical walls in the lanes
		for(int j = 1; j < numOfLanes; j++)
		{
			for(int k = 2; k < 7; k++)
			{
				maDrawImage(VWALL, lanePos[j], int(scrHeight * (k * .1)));
			}
		}


		char *resBuffer = new char [15];
		char *HPBuffer = new char [10];
		char *scoreBuffer = new char [15];

		sprintf(resBuffer, "Res:%i %i %i %i", wood, bullets, foodWater, metal);
		sprintf(HPBuffer, "HP:%i", heroHP);
		sprintf(scoreBuffer, "Score:%i", heroScore);


		// draw the top stats bar
		maDrawText(0, 0, resBuffer);
		maDrawText(int(scrWidth * .45), 0, HPBuffer);
		maDrawText(int(scrWidth * .65), 0, scoreBuffer);



		// draws the bottom button bar

		maDrawImage(MENU, 0, int(scrHeight * .91));
		//maDrawText(int(.15 * scrHeight), int(scrHeight * .91),"Change");

		if (pistol)
		{
			//maDrawImage(PISTOL, int(.2 * scrWidth), int(scrHeight * .91));
			maDrawImage(PISTOL, lanePos[1], int(scrHeight * .91));
		}

		else
		{
			//maDrawImage(SHOTGUN, int(.2 * scrWidth), int(scrHeight * .91));
			maDrawImage(SHOTGUN, lanePos[1], int(scrHeight * .91));
		}


		if (maxWood > 0)
		{
			//maDrawImage(WOOD, int(.4 * scrWidth), int(scrHeight * .91));
			maDrawImage(WOOD, lanePos[2], int(scrHeight * .91));
		}

		//maDrawImage(BULLETS, int(.5 * scrWidth), int(scrHeight * .91));
		maDrawImage(BULLETS, middleLanePos[2], int(scrHeight * .91));

		//maDrawImage(FOODWATER, int(.6 * scrWidth), int(scrHeight * .91));
		maDrawImage(FOODWATER, lanePos[3], int(scrHeight * .91));

		//maDrawImage(METAL, int(.7 * scrWidth), int(scrHeight * .91));
		maDrawImage(METAL, middleLanePos[3], int(scrHeight * .91));

		//maDrawImage(SHOOT, int(.8 * scrWidth), int(scrHeight * .91));
		maDrawImage(SHOOT, lanePos[4], int(scrHeight * .91));

	}

	// if the wall health > 0, the wall will be drawn with its health below.
	void drawWalls()
	{

		char *wHPBuffer = new char [2];

		// draws the walls and their health
		for(int i = 0; i < numOfLanes; i++)
		{
			sprintf(wHPBuffer, "%i", wHP[i]);

			if (wHP[i] != 0)
			{
				maDrawImage(WALL, int(middleLanePos[i] - (wallImageSize / 2)), int(scrHeight * .68));
				maDrawText(middleLanePos[i] - 7, int(scrHeight * .72), wHPBuffer);
			}
		}

	}

	// draws the hero in the lane passed
	void drawHero(int lane)
	{
		maDrawImage(ZOMBIE, int(middleLanePos[lane] - (heroImageSize / 2)), int(scrHeight * .8));
	}

	// draws the zombie in the lane passed
	void drawZombie(int lane)
	{
		maDrawImage(ZOMBIE, int(middleLanePos[lane] - (zombieImageSize / 2)), int(scrHeight * .07));
	}


	// calls the main drawing functions so I can call this one function
	// instead of calling them all separately.
	void drawWidget()
	{
		// if the hero is still alive
		if (!isGameOver)
		{
			drawCanvas();
			drawControls();
			drawWalls();
			drawHero(heroPos);

			drawZombie(zombiePos);

			// updates the screen allowing everything to be redrawn
			maUpdateScreen();
		}

		else
		{
			gameOver();
		}
	}





// Hero stuff


	// returns the lane that the hero is in
	int getHeroPos()
	{
		return heroPos;
	}

	// sets the lane the hero is in
	void setHeroPos(int hero_Pos)
	{
		heroPos = hero_Pos;
	}

	// returns the hero's Health
	int getHeroHP()
	{
		return heroHP;
	}

	// Increases the Hero's Health by 1
	void addHeroHealth()
	{
		if (heroHP < maxHeroHP)
		{
			heroHP++;
		}
	}

	// Decreases the Hero's health by 1
	void subHeroHealth()
	{
		if (heroHP > 1)
		{
			heroHP--;
		}
		else
		{
			isGameOver = true;
		}
	}




// Lanes

	// returns the beginning position of the lane
	int getLanePos(int lane)
	{
		return lanePos[lane];
	}

	// returns the middle position of the lane
	int getMiddleLanePos(int lane)
	{
		return middleLanePos[lane];
	}






	void setZombiePos(int zombie_Pos)
	{
		zombiePos = zombie_Pos;
	}





// Walls


	// returns the passed lanes wall health
	int getWallHealth(int wallPos)
	{
		return wHP[wallPos];
	}

	// adds 1 to the passed lanes wall health
	void addWallHealth(int wallPos)
	{
		if (wHP[wallPos] < maxWallHP && wood > 0)
		{
			wHP[wallPos]++;
		}
	}

	// subtracts 1 from the passed lanes wall health
	void subWallHealth(int wallPos)
	{
		if (wHP[wallPos] > 0)
		{
			wHP[wallPos]--;
		}

	}








// Resources:


	// returns the Wood Resource Amount
	int getWoodRes()
	{
		return wood;
	}

	// adds 1 to the Wood Resource Amount
	void addWoodRes()
	{
		if (wood < maxRes && maxWood > 0)
		{
			wood++;
			maxWood--;
		}
	}

	// subtracts 1 from the Wood Resource Amount
	//	A.K.A. Reinforce Wall
	void subWoodRes()
	{
		if (wood > 0)
		{
			wood--;
		}
	}


	// returns the Bullets Resource Amount
	int getBulletsRes()
	{
		return bullets;
	}

	// adds 1 to the Bullets Resource Amount
	void addBulletsRes()
	{
		if (bullets < maxRes)
		{
			bullets++;
		}
	}

	// subtracts 1 from the Bullets Resource Amount
	// A.K.A. Shoot
	void subBulletsRes()
	{
		if (bullets > 0)
		{
			bullets--;
		}
	}


	// returns the FoodWater Resource Amount
	int getFoodWaterRes()
	{
		return foodWater;
	}

	// adds 1 to the FoodWater Resource Amount
	void addFoodWaterRes()
	{
		if (foodWater < maxRes)
		{
			foodWater++;
		}
	}

	// subtracts 1 from the FoodWater Resource Amount
	void subFoodWaterRes()
	{
		if (foodWater > 0)
		{
			foodWater--;
		}
	}


	// returns the Metal Resource Amount
	int getMetalRes()
	{
		return metal;
	}

	// adds 1 to the Wood Metal Amount
	void addMetalRes()
	{
		if (metal < maxRes)
		{
			metal++;
		}
	}

	// subtracts 1 from the Metal Resource Amount
	void subMetalRes()
	{
		if (metal > 0)
		{
			metal--;
		}
	}





// Max Values


	// returns the maximun amount of health the hero can have
	int getMaxHeroHP()
	{
		return maxHeroHP;
	}

	// returns the maximum score the hero can have
	int getMaxHeroScore()
	{
		return maxHeroScore;
	}

	//returns the maximum amount of health a wall can have
	int getMaxWallHP()
	{
		return maxWallHP;
	}

	//returns the maximun amount that a resource can be
	int getMaxRes()
	{
		return maxRes;
	}




// Change Weapons

	void setPistol(bool value)
	{
		pistol = value;
	}

	bool getPistol()
	{
		return pistol;
	}





protected:

	bool pistol;

	int wHP[numOfLanes];

	int lanePos[numOfLanes];

	int middleLanePos[numOfLanes];

	int heroPos, heroHP, heroScore;

	int  wood, bullets, foodWater, metal, maxWood;

	int maxWallHP, maxHeroScore, maxHeroHP, maxRes;

	int zombiePos;

	bool isGameOver;

	int wallImageSize, tombstoneImageSize, heroImageSize, zombieImageSize;


};

#endif
