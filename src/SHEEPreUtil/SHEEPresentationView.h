#pragma once

#include "ofMain.h"
#include "ofxTrueTypeFontUL2.h"
#include "SHEEPresentationLayout.h"
#include "SHEEPresentationData.h"


class SHEEPresentationView {
public:
	ofPtr<SHEEPresentationData> data;

	void setup();

	void drawThemeList();
	void drawThemeBlock(int th);
	void drawPageBlock(int th, int pg);

	void drawPage(int th, int pg);
	void drawPage(ofPtr<SHEEPre::page> p);
	void drawGuide(ofPtr<SHEEPre::page> p);

	void debugDraw();

	ofxTrueTypeFontUL2 font;
};

/*

プレゼンテーションビュー
表示系を管理するためのクラス。
プレイ画像や、サムネイルなどの描画系リソースをここで管理したい。
レイアウトクラスで取得した配置情報をもとにレンダリングする。

*/