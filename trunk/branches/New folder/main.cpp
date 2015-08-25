#include <ma.h>

#include <MAUI/Screen.h>
#include <MAUI/Engine.h>
#include <MAUI/Layout.h>
#include <MAUI/ListBox.h>
#include <MAUI/Label.h>
#include <MAUI/Font.h>
#include <MAUtil/Moblet.h>
#include <conprint.h>

#include "Util.h"
#include "MAHeaders.h"
#include "Screens/PlayScreen.h"
#include "Screens/ChangeBGScreen.h"
#include "Screens/HelpScreen.h"

using namespace MAUtil;
using namespace MAUI;
// This is the Moblet class. This manages the events your application will need, like getting
// key presses and screen touches.
// It also creates an instance of the MAUI::Screen class 'Menu', and shows it on screen.
class MyMoblet : public Moblet
{
public:
    MyMoblet()
    {
    	maScreenSetOrientation(SCREEN_ORIENTATION_LANDSCAPE);
		gFont = new MAUI::Font(RES_FONT);
		gSkin = new WidgetSkin(RES_BG1, RES_BG1, 10, 980, 10, 980, true, true);
		mSkin = new WidgetSkin(RES_SELECTED, RES_UNSELECTED, 16, 32, 16, 32, true, true);
		Engine& engine = Engine::getSingleton();

		MAExtent screenSize = maGetScrSize();
		scrWidth = EXTENT_X(screenSize);
		scrHeight = EXTENT_Y(screenSize);
        mainScreen = new MainScreen(this);
        mainScreen->show();
    }

    virtual ~MyMoblet()
    {
        delete mainScreen;
    }
	void keyPressEvent(int keyCode, int nativeCode)
	{
		if(MAK_0 == keyCode || MAK_BACK == keyCode)
		{
			//Exit on any key press
			maExit(0);
		}
	}

class MainScreen : public Screen {
public:
	MainScreen(MyMoblet *moblet) : moblet(moblet) {
		screens.add(new PlayScreen(this));
		screens.add(new ChangeBGScreen(this));
		screens.add(new HelpScreen(this));

		layout = createMainLayout();
		listBox = (ListBox*) layout->getChildren()[0];

		listBox->add(createLabel("Play Game"));
		listBox->add(createLabel("Change Background"));
		listBox->add(createLabel("Help"));

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
								{
									screens[index]->show();
								}
							}
							else {
								listBox->setSelectedIndex(i);
							}
							break;
						}
					}
				}
			}

private:
	Vector<Screen*> screens;
	ListBox* listBox;
	Layout* layout;
	MyMoblet *moblet;
};


private:
	Screen *mainScreen;
};

extern "C" int MAMain()
{
	MyMoblet *moblet = new MyMoblet();
	MyMoblet::run(moblet);
    return 0;
}
