#pragma once
#include "ofMain.h"

class SHEEPreImage : public ofImage {
	time_t m_time;
};

class SHEEPresentationAssets {

public:

	ofPtr<SHEEPreImage> getImage(string name);

	unordered_map<string, ofPtr<SHEEPreImage> > images;
	
};