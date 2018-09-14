#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

	bool testMode = true;


	int width = 1920;
	int height = 1080;
	enum ofWindowMode screenType = OF_FULLSCREEN;

	if (testMode) {
		width = 1280;
		height = 720;
		screenType = OF_WINDOW;
	}

	ofSetupOpenGL(width, height, screenType);

	ofRunApp(new ofApp());

}
