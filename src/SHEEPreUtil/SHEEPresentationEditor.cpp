#include "SHEEPresentationEditor.h"

void SHEEPresentationEditor::setup()
{
	viewer.setup();
}

void SHEEPresentationEditor::update()
{
	if (data && ofGetFrameNum() % 60 == 0)
	{
		struct stat st;
		stat(ofToDataPath(currentDir + "/data.json", true).c_str(), &st);
		if (lastUpdated < st.st_mtime)
		{
			lastUpdated = st.st_mtime;
			setProjectDir(currentDir);
		}
	}
}

void SHEEPresentationEditor::draw()
{
	ofPushMatrix();
	ofTranslate(100, 100);
	viewer.drawPage(0, 0);
	viewer.drawGuide(data->getPage(0, 0));
	ofPopMatrix();

}


void SHEEPresentationEditor::setProjectDir(string path)
{
	if (!data) data = make_shared<SHEEPresentationData>();
	data->loadFromJSON(path + "/data.json");
	currentDir = path;
	viewer.data = data;

	struct stat st;
	stat(ofToDataPath(currentDir + "/data.json", true).c_str(), &st);
	lastUpdated = st.st_mtime;

	layout.calcLayout(data);
}