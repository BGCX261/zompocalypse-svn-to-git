#ifndef _UTIL_H_
#define _UTIL_H_

#include <MAUI/Widget.h>
#include <MAUI/Label.h>
#include <MAUI/Layout.h>
#include <MAUI/ListBox.h>
#include <MAUI/Font.h>

using namespace MAUI;

Font *gFont;
WidgetSkin *gSkin;
WidgetSkin *mSkin;
int scrWidth;
int scrHeight;

void setLabelPadding(Widget *w) {
	w->setPaddingLeft(scrWidth/2-50);
	w->setPaddingBottom(0);
	w->setPaddingRight(0);
	w->setPaddingTop(20);
}

Layout* createMainLayout() {
	Layout *mainLayout = new Layout(0, 0, scrWidth, scrHeight, NULL, 1, 2);

	ListBox* listBox = new ListBox(0, 0, scrWidth, scrHeight, mainLayout, ListBox::LBO_VERTICAL, ListBox::LBA_LINEAR, true);
	listBox->setSkin(gSkin);
	listBox->setPaddingTop(scrHeight-200);
	listBox->setPaddingLeft(5);
	listBox->setPaddingRight(5);

	mainLayout->setSkin(NULL);
	mainLayout->setDrawBackground(true);

	return mainLayout;
}

Label* createLabel(const char *str) {
	Label *label;
	label = new Label(0,0, scrWidth-10, 60, NULL, str, 0, gFont);
	label->setSkin(mSkin);
	setLabelPadding(label);
	return label;
}

Widget* createSoftKeyBar(int height, const char *left, const char *right) {
	Layout *layout = new Layout(0, 0, scrWidth, height, NULL, 2, 1);
	Label *label;

	label = new Label(0,0, scrWidth/2, height, NULL, left, 0, gFont);
	label->setHorizontalAlignment(Label::HA_LEFT);
	label->setDrawBackground(false);
	label->setPaddingLeft(5);
	label->setPaddingBottom(5);
	label->setPaddingRight(5);
	label->setPaddingTop(5);
	layout->add(label);

	label = new Label(0,0, scrWidth/2, height, NULL, right, 0, gFont);
	label->setDrawBackground(false);
	label->setHorizontalAlignment(Label::HA_RIGHT);
	label->setPaddingLeft(scrWidth/2-50);
	label->setPaddingBottom(5);
	label->setPaddingRight(5);
	label->setPaddingTop(5);
	layout->add(label);

	return layout;
}


Layout* createChangeLayout(const char *left, const char *right) {
	Layout *changeLayout = new Layout(0, 0, scrWidth, scrHeight, NULL, 1, 2);


	Widget *softKeys = createSoftKeyBar(30, left, right);
	ListBox* listBox = new ListBox(0, 0, scrWidth, scrHeight-softKeys->getHeight(), changeLayout, ListBox::LBO_VERTICAL, ListBox::LBA_LINEAR, true);
	listBox->setSkin(gSkin);
	listBox->setPaddingLeft(5);
	listBox->setPaddingRight(5);
	listBox->setPaddingTop(15);
	listBox->setPaddingBottom(15);

	changeLayout->add(softKeys);

	changeLayout->setSkin(NULL);
	changeLayout->setDrawBackground(true);
	changeLayout->setBackgroundColor(0);

	return changeLayout;
}



extern Font *gFont;
extern WidgetSkin *gSkin;
extern int scrWidth;
extern int scrHeight;

#endif	//_UTIL_H_
