#pragma once
#include "ofMain.h"
#include "SHEEPresentationData.h"

class SHEEPresentationLayout {
public:

	void calcLayout(ofPtr<SHEEPresentationData> data);
	void calcLayout(ofPtr<SHEEPresentationData> data, int th, int pg);
};