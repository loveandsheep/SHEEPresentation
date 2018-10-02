#include "SHEEPresentationLayout.h"


void SHEEPresentationLayout::calcLayout(ofPtr<SHEEPresentationData> data)
{
	for (int t = 0; t < data->themes.size(); t++)
	{
		for (int p = 0; p < data->themes[t]->pages.size(); p++)
		{
			calcLayout(data, t, p);
		}
	}
}

void SHEEPresentationLayout::calcLayout(ofPtr<SHEEPresentationData> data, int th, int pg)
{
	ofPtr<SHEEPre::page> p = data->getPage(th, pg);
	if (!p) return;

	vector<ofPtr<SHEEPre::content> > cs;

	for (auto b : p->blocks) 
		for (auto c : b->contents)
			cs.push_back(c);

	for (int i = 0; i < cs.size(); i++)
	{
		//1.レイアウトのブロックを定義する
		cs[i]->viewArea.setFromCenter(data->width / 2.0, data->height / (cs.size() * 2) * (i * 2 + 1),
			data->width * 0.9, data->height / (cs.size()) * 0.9);

		//2.要素ごとにオプションの定義を定める
		if (cs[i]->type == SHEEPre::CTYPE_TEXT)
		{
			if (cs[i]->style == SHEEPre::STYLE_THEME) cs[i]->textScale = 36;
			if (cs[i]->style == SHEEPre::STYLE_DETAIL) cs[i]->textScale = 16;
		}

		if (cs[i]->type == SHEEPre::CTYPE_IMAGE)
		{
			cs[i]->asset_image = data->assets.getImage(cs[i]->value);
		}

	}


}