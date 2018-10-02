#include "SHEEPresentationAssets.h"

ofPtr<SHEEPreImage> SHEEPresentationAssets::getImage(string name)
{
	if (images.find(name) != images.end()) return images[name];

	else
	{
		ofPtr<SHEEPreImage> im = make_shared<SHEEPreImage>();
		im->load(name);
		images[name] = im;
		return im;
	}
}