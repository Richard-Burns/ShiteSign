#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	int width = 1920;
	int height = 1080;
	ofSetupOpenGL(width,height, OF_FULLSCREEN);

	ofRunApp(new ofApp());

}
