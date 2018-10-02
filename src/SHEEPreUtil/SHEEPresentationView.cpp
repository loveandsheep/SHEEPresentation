#include "SHEEPresentationView.h"

void SHEEPresentationView::setup()
{
	font.loadFont("fonts/YuGothB.ttc", SHP_FONT_DEFAULT_SCALE, true, true, 0.3, 0, true);
	font.setLineHeight(SHP_FONT_DEFAULT_SCALE * 1.3);
	font.useProportional(true);

}

void SHEEPresentationView::drawThemeList()
{
}

void SHEEPresentationView::drawPage(int th, int pg)
{
	if (!data) return;
	drawPage(data->getPage(th, pg));
}

void SHEEPresentationView::drawPage(ofPtr<SHEEPre::page> p)
{
	ofSetHexColor(0xE7EFC5);
	ofDrawRectangle(0, 0, data->width, data->height);

	for (auto b : p->blocks)
	{
		for (auto c : b->contents)
		{
			if (c->type == SHEEPre::CTYPE_TEXT)
			{
				ofRectangle area = c->viewArea;
				float textScale = c->textScale / float(SHP_FONT_DEFAULT_SCALE);

				ofPushMatrix();
				int alignType = 0;
				
				ofPushMatrix();
				ofScale(textScale, textScale);
				
				area.x /= textScale;
				area.y /= textScale;
				area.width /= textScale;
				area.height /= textScale;
				ofSetColor(0);
				font.drawString(c->value, area.x, area.y, area.width, area.height, c->alignType);
				ofPopMatrix();
				ofPopMatrix();
			}

			if (c->type == SHEEPre::CTYPE_IMAGE)
			{
				if (c->asset_image)
				{
					ofPtr<ofImage> img = c->asset_image;
					ofRectangle area = c->viewArea;
					ofRectangle texCoord;
					float aspect = area.height / area.width;
					float texWidth = img->getWidth();
					float texHeight = img->getWidth() * aspect;

					if (texHeight > img->getHeight())
					{
						texHeight = img->getHeight();
						texWidth = img->getHeight() / aspect;
					}
					
					texCoord.setFromCenter(img->getWidth() / 2.0, img->getHeight() / 2.0, texWidth, texHeight);


					ofSetColor(255);
					c->asset_image->drawSubsection(area.x, area.y, area.width, area.height, 
													texCoord.x, texCoord.y, texCoord.width, texCoord.height);
				}
			}
		}
	}
}

void SHEEPresentationView::drawGuide(ofPtr<SHEEPre::page> p)
{
	ofPushStyle();
	ofNoFill();
	ofSetColor(0, 100);

	for (auto b : p->blocks)
	{
		for (auto c : b->contents)
		{
			if (c->type == SHEEPre::CTYPE_TEXT)
			{
				ofRectangle const & area = c->viewArea;
				ofDrawRectangle(area);
				ofDrawLine(area.getTopLeft(), area.getBottomRight());
				ofDrawLine(area.getTopRight(), area.getBottomLeft());
			}
		}
	}
	ofPopStyle();
}

void SHEEPresentationView::debugDraw()
{
	string arch = "";
	for (auto t : data->themes)
	{
		arch += "[T:" + t->title + "]\n";
		int pCount = 1;
		for (auto p : t->pages)
		{
			arch += "\tPage : " + ofToString(pCount) + "\n";
			pCount++;
			for (auto b : p->blocks)
			{
				for (auto c : b->contents)
				{
					arch += "\t\t" + ofToString(c->type);
					arch += " - " + ofToString(c->style);
					arch += " - " + c->value;
				}
			}
		}
	}

	ofDrawBitmapStringHighlight(arch, 0, 0);
}