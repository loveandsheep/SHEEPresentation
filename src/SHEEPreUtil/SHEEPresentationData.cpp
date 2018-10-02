#include "SHEEPresentationData.h"

SHEEPresentationData::SHEEPresentationData()
{
}


SHEEPresentationData::~SHEEPresentationData()
{
}

ofPtr<SHEEPre::Theme> SHEEPresentationData::addTheme(string title)
{
	themes.push_back(make_shared<SHEEPre::Theme>(title));
	return themes.back();
}

ofPtr<SHEEPre::page> SHEEPresentationData::addPage(string theme)
{
	for (int t = 0; t < themes.size(); t++)
	{
		if (themes[t]->title == theme) return addPage(t);
	}
	return nullptr;
}

ofPtr<SHEEPre::page> SHEEPresentationData::addPage(int themeIndex)
{
	if (themeIndex < 0 || themes.size() <= themeIndex) return nullptr;
	themes[themeIndex]->pages.push_back(make_shared<SHEEPre::page>());
	return themes[themeIndex]->pages.back();
}

ofPtr<SHEEPre::block> SHEEPresentationData::addBlock(int theme, int page)
{
	ofPtr<SHEEPre::page> p = getPage(theme, page);
	if (!p) return nullptr;
	else
	{
		p->blocks.push_back(make_shared<SHEEPre::block>());
		return p->blocks.back();
	}
}

ofPtr<SHEEPre::content> SHEEPresentationData::addContent(int th, int pg, int bl)
{
	ofPtr<SHEEPre::block> b = getBlock(th, pg, bl);
	if (!b) return nullptr;
	else
	{
		b->contents.push_back(make_shared<SHEEPre::content>());
		return b->contents.back();
	}
}

ofPtr<SHEEPre::Theme> SHEEPresentationData::getTheme(int th)
{
	if (th < 0 || themes.size() <= th) return nullptr;
	else							   return themes[th];
}

ofPtr<SHEEPre::page> SHEEPresentationData::getPage(int th, int pg)
{
	ofPtr<SHEEPre::Theme> t = getTheme(th);
	if (!t) return nullptr;

	if (pg < 0 || t->pages.size() <= pg) return nullptr;
	else								 return t->pages[pg];

}

ofPtr<SHEEPre::block> SHEEPresentationData::getBlock(int th, int pg, int bl)
{
	ofPtr<SHEEPre::Theme> t = getTheme(th);
	if (!t) return nullptr;

	ofPtr<SHEEPre::page> p = getPage(th, pg);
	if (!p) return nullptr;

	if (bl < 0 || p->blocks.size() <= bl) return nullptr;
	else								  return p->blocks[bl];
}

ofPtr<SHEEPre::content> SHEEPresentationData::getContent(int th, int pg, int bl,int ct)
{
	ofPtr<SHEEPre::Theme> t = getTheme(th);
	if (!t) return nullptr;

	ofPtr<SHEEPre::page> p = getPage(th, pg);
	if (!p) return nullptr;

	ofPtr<SHEEPre::block> b = getBlock(th, pg, bl);
	if (!b) return nullptr;

	if (ct < 0 || b->contents.size() <= ct) return nullptr;
	else									return b->contents[ct];
}

void SHEEPresentationData::saveToJSON(string path)
{
	ofxJSON json;

	for (int th = 0; th < themes.size(); th++)
	{
		ofxJSONElement el;
		el["h-title"] = themes[th]->title;

		for (int pg = 0; pg < themes[th]->pages.size(); pg++)
		{
			ofPtr<SHEEPre::page> p = themes[th]->pages[pg];
			el["page"][pg]["Layout"] = "layoutType";//レイアウトタイプの定義数値化

			for (int bl = 0; bl < p->blocks.size(); bl++)
			{
				ofPtr<SHEEPre::block> b = p->blocks[bl];

				for (int ct = 0; ct < b->contents.size(); ct++)
				{
					ofPtr<SHEEPre::content> c = b->contents[ct];
					el["page"][pg]["block"][bl]["content"][ct]["type"] = c->type;
					el["page"][pg]["block"][bl]["content"][ct]["style"] = c->style;
					el["page"][pg]["block"][bl]["content"][ct]["value"] = c->value;
				}
			}
		}

		json["presentation"]["theme"][th] = el;
	}
	json["presentation"]["data-width"] = width;
	json["presentation"]["data-height"] = height;

	json.save(path, true);
}

void SHEEPresentationData::loadFromJSON(string path)
{
	themes.clear();
	//ofBuffer buf = ofBufferFromFile(path);
	//std::wstring wsBuf = utf8_to_wide_winapi(buf.getText());
	//std::string sBuf = wide_to_multi_winapi(wsBuf);

	ofxJSON json;

	if (json.open(path))
	{
		ofxJSON j_themes = json["presentation"]["theme"];
		for (int t = 0; t < j_themes.size(); t++)
		{
			addTheme(utf8_to_shiftJIS(j_themes[t]["h-title"].asString()));
			ofxJSON j_pages = j_themes[t]["page"];
			for (int p = 0; p < j_pages.size(); p++)
			{
				addPage(t);

				ofxJSON j_blocks = j_pages[p]["block"];
				for (int b = 0; b < j_blocks.size(); b++)
				{
					addBlock(t, p);
					ofxJSON j_contents = j_blocks[b]["content"];
					for (int c = 0; c < j_contents.size(); c++)
					{
						ofPtr<SHEEPre::content> cc = addContent(t, p, b);
						cc->type = SHEEPre::contentType(j_contents[c]["type"].asInt());
						cc->style = SHEEPre::contentStyle(j_contents[c]["style"].asInt());
						cc->value = utf8_to_shiftJIS(j_contents[c]["value"].asString());
					}
				}
			}
		}

		width = json["presentation"]["data-width"].asInt();
		height = json["presentation"]["data-height"].asInt();
	}
	else
	{
		addTheme("new Theme");
		addPage(0);
		addBlock(0, 0);
		addContent(0, 0, 0);
		saveToJSON(path);
	}
}