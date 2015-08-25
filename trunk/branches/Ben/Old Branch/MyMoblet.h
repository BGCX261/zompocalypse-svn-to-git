#ifndef _MAUIEX_H_
#define _MAUIEX_H_

#include <ma.h>

#include "MAHeaders.h"

#include <MAUI/Screen.h>
#include <MAUI/Engine.h>
#include <MAUI/Font.h>
#include <MAUI/Label.h>
#include <MAUI/ListBox.h>
#include <MAUI/Layout.h>
#include <MAUtil/Moblet.h>
#include <MAUI/Image.h>

#include "PlayScreen.h"
#include "ChangeBGScreen.h"
#include "HelpScreen.h"
#include "Util.h"

#include <conprint.h>

using namespace MAUI;
using namespace MAUtil;


class MyMoblet : public Moblet  {
public:

	MyMoblet() {
		gFont = new MAUI::Font(RES_FONT);
		gSkin = new WidgetSkin(RES_SELECTED, RES_UNSELECTED, 16, 32, 16, 32, true, true);
		Engine& engine = Engine::getSingleton();
		engine.setDefaultFont(gFont);
		engine.setDefaultSkin(gSkin);

		MAExtent screenSize = maGetScrSize();
		scrWidth = EXTENT_X(screenSize);
		scrHeight = EXTENT_Y(screenSize);
		mainScreen = new MainScreen(this);
		mainScreen->show();

	}


	void closeEvent() {
		// do destruction here
		delete mainScreen;
	}


	class MainScreen : public Screen {
	public:
		MainScreen(MyMoblet *moblet) : moblet(moblet) {
			screens.add(new PlayScreen(this));
			screens.add(new ChangeBGScreen(this));
			screens.add(new HelpScreen(this));

			layout = createMainLayout("Select", "Exit");
			listBox = (ListBox*) layout->getChildren()[0];

			listBox->add(createLabel("Play Game"));
			listBox->add(createLabel("Change Background"));
			listBox->add(createLabel("Help"));


			softKeys = layout->getChildren()[1];

			this->setMain(layout);
		}

		~MainScreen() {
			delete layout;
			for(int i = 0; i < screens.size(); i++) delete screens[i];
		}


		void pointerPressEvent(MAPoint2d point) {
			Point p;
			p.set(point.x, point.y);
			if(listBox->contains(p)) {
				for(int i = 0; i < listBox->getChildren().size(); i++) {
					if(listBox->getChildren()[i]->contains(p)) {
						int index = listBox->getSelectedIndex();
						if(index == i) {
							int index = listBox->getSelectedIndex();
							if(index == screens.size()+1) {
								moblet->closeEvent();
								moblet->close();
							}
							else
								screens[index]->show();
						}
						else {
							listBox->setSelectedIndex(i);
						}
						break;
					}
				}
			}
			else if(softKeys->contains(p)) {
				if(softKeys->getChildren()[0]->contains(p)) {
					int index = listBox->getSelectedIndex();
					if(index == screens.size()+1) {
						moblet->closeEvent();
						moblet->close();
					}
					else
						screens[index]->show();
				}
				else if(softKeys->getChildren()[1]->contains(p)) {
					moblet->closeEvent();
					moblet->close();
				}
			}
		}

		void pointerReleaseEvent(MAPoint2d point) {}

	private:
		Vector<Screen*> screens;
		ListBox* listBox;
		Layout* layout;
		Widget *softKeys;
		MyMoblet *moblet;
	};


private:
	Screen *mainScreen;
};

#endif
