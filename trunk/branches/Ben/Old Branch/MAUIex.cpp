#include "MyMoblet.h"

extern "C" int MAMain() {
	MyMoblet *moblet = new MyMoblet();
	MyMoblet::run(moblet);
	return 0;
}
