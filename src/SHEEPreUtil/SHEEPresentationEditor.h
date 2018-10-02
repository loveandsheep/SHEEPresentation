#pragma once
#include "ofMain.h"
#include "SHEEPresentationData.h"
#include "SHEEPresentationView.h"

class SHEEPresentationEditor {
public:

	void setProjectDir(string path);

	void setup();
	void update();
	void draw();
	
protected:
	string currentDir;
	time_t lastUpdated;
	ofPtr<SHEEPresentationData> data;

	SHEEPresentationLayout layout;
	SHEEPresentationView viewer;
};