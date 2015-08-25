#ifndef _CHANGEBGSCREEN_H_
#define _CHANGEBGSCREEN_H_

#include <MAUI/Screen.h>
#include <MAUI/Layout.h>
#include <MAUI/ListBox.h>
#include "Util.h"



using namespace MAUI;

class ChangeBGScreen : public Screen {
public:
	ChangeBGScreen(Screen *previous) : previous(previous) {
		mainLayout = createMainLayout("", "Back");
		this->setMain(mainLayout);
		ListBox* listBox = (ListBox*) mainLayout->getChildren()[0];

		///////////////////////////////////////////////////
						//Code goes here
		///////////////////////////////////////////////////

		softKeys = mainLayout->getChildren()[1];
	}

	~ChangeBGScreen() {}


	void pointerPressEvent(MAPoint2d point) {
		Point p;
		p.set(point.x, point.y);
		if(softKeys->contains(p)) {
			if(softKeys->getChildren()[0]->contains(p)) {
				// Do nothing
			}
			else if(softKeys->getChildren()[1]->contains(p)) {
				previous->show();
			}
		}
	}

	void pointerReleaseEvent(MAPoint2d point) {}

private:
	Screen *previous;
	Layout *mainLayout;
	Widget *softKeys;
};

#endif
