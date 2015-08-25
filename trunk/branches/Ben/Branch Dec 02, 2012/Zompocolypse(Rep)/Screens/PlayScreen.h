#ifndef _PLAYSCREEN_H_
#define _PLAYSCREEN_H_

#include <MAUI/Screen.h>
#include <MAUI/Layout.h>
#include <MAUI/ListBox.h>
#include "maxtoa.h"
#include <MAUtil/Graphics.h>
#include "../Objects/Zombie.h"

const int numOfLanes = 6;

using namespace MAUI;

class PlayScreen : public Screen, public MAUtil::TimerListener {
public:
	PlayScreen() {

		for(int i = 0; i < numOfLanes; i++)
		{
			lanePos[i] = int(scrWidth * (i * .17));
			printf("srcWidth: %d", scrWidth);
		}


		drawCanvas();
		drawControls();
		drawWalls();

		temp = new RegZombie(1);
		int gametime=0;
		//drawHero(1);
		//drawZombie(2);

		///////////////////////////////////////////////////
						//Code goes here
		///////////////////////////////////////////////////


	}

	void runTimerEvent(){
		gametime+=50;
		if(gametime%100==0){
		  temp->runTimerEvent();
			drawCanvas();
			drawControls();
			drawWalls();
		}

	}
	~PlayScreen() {}


	void pointerPressEvent(MAPoint2d point)
	{

	}

	void pointerReleaseEvent(MAPoint2d point)
	{

	}

	void drawCanvas()
	{
		maSetColor(0);
		maFillRect(0, 0, scrWidth, scrHeight);
	}

	void drawZombie(int position)
	{
		maDrawImage(CHANGEBG2, lanePos[position], int(scrHeight * .07));
	}

	void drawHero(int position)
	{
		maDrawImage(CHANGEBG1, lanePos[position], int(scrHeight * .8));
	}

	void drawWalls()
	{
		for(int i = 0; i < numOfLanes; i++)
		{
			wHP[i] = "0";
		}



		for(int i = 0; i < numOfLanes; i++)
		{
			maDrawImage(WALL, lanePos[i], (scrHeight * .68));

			maDrawText(lanePos[i] + (scrWidth * .06), (scrHeight * .72), wHP[i]);

			//maDrawImage(CHANGEBG1, lanePos[i], (scrHeight * .72));
		}

	}

	void drawControls()
	{
		maSetColor(0xFFFFFF);

		maDrawText(0, 0, "Res:");
		maDrawText((scrWidth / 2), 0, "HP:");
		maDrawText(((scrWidth / 2) + (scrWidth / 4)), 0, "Score:");


		maDrawText(0, int(scrHeight * .91),"Make");
		maDrawText(int(.15 * scrHeight), int(scrHeight * .91),"Change");
		maDrawText(int(.35 * scrHeight), int(scrHeight * .91),"W");
		maDrawText(int(.4 * scrHeight), int(scrHeight * .91),"B");
		maDrawText(int(.45 * scrHeight), int(scrHeight * .91),"FW");
		maDrawText(int(.5 * scrHeight), int(scrHeight * .91),"M");
		maDrawText(int(.6 * scrHeight), int(scrHeight * .91),"Shoot");
	}


private:

	char *wHP[numOfLanes];

	int lanePos[numOfLanes];
	int gametime;

	RegZombie *temp;







};

#endif
