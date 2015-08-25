#ifndef _CHANGEBGSCREEN_H_
#define _CHANGEBGSCREEN_H_

#include <MAUI/Screen.h>
#include <MAUI/Layout.h>
#include <MAUI/ListBox.h>
#include <MAUI/Image.h>
#include <conprint.h>

#include "MAHeaders.h"
#include "../Util.h"


using namespace MAUI;

class ChangeBGScreen : public Screen {
public:
	ChangeBGScreen(Screen *previous) : previous(previous) {
		HandlePointerEvent = true;

		mDragValues.clear();

		mainLayout = createChangeLayout("Select ", "Back");
		this->setMain(mainLayout);
		ListBox* listBox = (ListBox*) mainLayout->getChildren()[0];
		layout = new Layout(0, 0, scrWidth, scrHeight-mainLayout->getChildren()[1]->getHeight(), listBox, 3, 4);
		layout->setPaddingLeft(-5);
		layout->setPaddingRight(-5);
		layout->setDrawBackground(false);

		currentScreen = 0;

		thisBG = new Image(0, 0, scrWidth, scrHeight-mainLayout->getChildren()[1]->getHeight(), layout, false, false, CHANGEBG0);

		layout->setDrawBackground(true);

		softKeys = mainLayout->getChildren()[1];

	}

	~ChangeBGScreen() {}

	void keyPressEvent(int keyCode, int nativeCode) {
		if(keyCode == MAK_SOFTRIGHT) {
			previous->show();
		}
		if(keyCode == MAK_SOFTLEFT) {
			thisBG->getResource();
			gSkin->setSelectedImage(thisBG->getResource());
			gSkin->setUnselectedImage(thisBG->getResource());
			mainLayout->setDrawBackground(true);
			previous->show();
		}
	}


	void pointerMoveEvent(MAPoint2d point)
	{
		if (HandlePointerEvent)
		{
			mDragValues.add(point.x);
		}
	}

	void pointerPressEvent(MAPoint2d point) {
		if (HandlePointerEvent)
		{

			mDragValues.clear();

			Point p;
			p.set(point.x, point.y);
			if(softKeys->contains(p))
			{
				if(softKeys->getChildren()[0]->contains(p))
				{
					keyPressEvent(MAK_SOFTLEFT, 0);
				}
				else if(softKeys->getChildren()[1]->contains(p))
				{
					keyPressEvent(MAK_SOFTRIGHT, 0);
				}
			}
		}
	}

	void pointerReleaseEvent(MAPoint2d point)
	{
		if (HandlePointerEvent)
		{
			// Check if there are enough drag events for analysis.
			if (5 > mDragValues.size())
			{
				return;
			}

			// Check if drag is from left to right of from right to left.
			bool dragFromLeftToRight = true;
			bool dragFromRightToLeft = true;
			int previousValue = mDragValues[0];
			for (int i = 1; (i < mDragValues.size()) && (dragFromLeftToRight
				|| dragFromRightToLeft); i++)
			{
				int currentValue = mDragValues[i];
				if (previousValue > currentValue)
				{
					dragFromLeftToRight = false;
				}
				if (previousValue < currentValue)
				{
					dragFromRightToLeft = false;
				}

				previousValue = currentValue;
			}

			// If drag is from left to right print the next contact, otherwise
			// close the PIM contacts list.
			if (dragFromLeftToRight)
			{
				this->displayPreviousBG();
			}
			else if (dragFromRightToLeft)
			{
				this->displayNextBG();
			}

			mDragValues.clear();
		}
	}


	void displayNextBG()
	{
		HandlePointerEvent = false;

		if (currentScreen == 0)
		{
			currentScreen += 1;

			layout->clear();

			thisBG = new Image(0, 0, scrWidth, scrHeight-mainLayout->getChildren()[1]->getHeight(), layout, false, false, CHANGEBG1);

			layout->setDrawBackground(true);
		}
		else if(currentScreen == 1)
		{
			currentScreen += 1;

			layout->clear();

			thisBG = new Image(0, 0, scrWidth, scrHeight-mainLayout->getChildren()[1]->getHeight(), layout, false, false, CHANGEBG2);

			layout->setDrawBackground(true);
		}


		HandlePointerEvent = true;
	}


	void displayPreviousBG()
	{
		HandlePointerEvent = false;

		if (currentScreen == 2)
		{
			currentScreen -= 1;

			layout->clear();

			thisBG = new Image(0, 0, scrWidth, scrHeight-mainLayout->getChildren()[1]->getHeight(), layout, false, false, CHANGEBG1);

			layout->setDrawBackground(true);
		}
		else if(currentScreen == 1)
		{
			currentScreen -= 1;

			layout->clear();

			thisBG = new Image(0, 0, scrWidth, scrHeight-mainLayout->getChildren()[1]->getHeight(), layout, false, false, CHANGEBG0);

			layout->setDrawBackground(true);
		}

		HandlePointerEvent = true;
	}


private:
	Screen *previous;
	Layout *mainLayout;
	Widget *softKeys;
	bool HandlePointerEvent;
	Vector<int> mDragValues;
	int currentScreen;
	Layout *layout;
	Image *thisBG;

};

#endif
