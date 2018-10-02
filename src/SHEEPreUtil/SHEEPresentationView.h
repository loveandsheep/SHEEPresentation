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

�v���[���e�[�V�����r���[
�\���n���Ǘ����邽�߂̃N���X�B
�v���C�摜��A�T���l�C���Ȃǂ̕`��n���\�[�X�������ŊǗ��������B
���C�A�E�g�N���X�Ŏ擾�����z�u�������ƂɃ����_�����O����B

*/