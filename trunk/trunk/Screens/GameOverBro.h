#ifndef _GAMEOVERBRO_H_
#define _GAMEOVERBRO_H_

#include <MAUI/Screen.h>
#include <MAUI/Layout.h>
#include <MAUI/ListBox.h>
#include <MAUI/Image.h>
#include <mastdlib.h>
#include <conprint.h>

#include "MAHeaders.h"

#include "../Util.h"

using namespace MAUI;
using namespace MAUtil;


class GameOverScreen : public Screen
{
public:
	GameOverScreen(Screen *previous) : previous(previous)
	{
		mainLayout = createChangeLayout("", "Menu");
		this->setMain(mainLayout);
		ListBox* listBox = (ListBox*) mainLayout->getChildren()[0];
		layout = new Layout(0, 0, scrWidth, scrHeight-mainLayout->getChildren()[1]->getHeight(), listBox, 3, 4);
		layout->setPaddingLeft(-5);
		layout->setPaddingRight(-5);
		layout->setDrawBackground(false);
		softKeys = mainLayout->getChildren()[1];

		new Image(0, 0, scrWidth, scrHeight-mainLayout->getChildren()[1]->getHeight(), layout, false, false, GAMEOVER);
	}

	~GameOverScreen() {}

	void keyPressEvent(int keyCode, int nativeCode) {
		if(keyCode == MAK_SOFTRIGHT) {
			previous->show();
		}
	}

	void pointerPressEvent(MAPoint2d point) {
			Point p;
			p.set(point.x, point.y);
			if(softKeys->contains(p))
			{
				if(softKeys->getChildren()[0]->contains(p))
				{
					// Do nothing
				}
				else if(softKeys->getChildren()[1]->contains(p))
				{
					keyPressEvent(MAK_SOFTRIGHT, 0);
				}
			}
		}

private:
	Screen *previous;
	Layout *mainLayout;
	Widget *softKeys;
	Layout *layout;

};

#endif
