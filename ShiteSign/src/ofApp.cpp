#include "ofApp.h"

//--------------------------------------------------------------

void ofApp::setup(){
	ofSetVerticalSync(true);

	// Setup and load settings
	ofxXmlSettings settings;
	settings.loadFile("settings.xml");

	width = settings.getValue("settings:width", 1920);
	height = settings.getValue("settings:height", 1080);
	oscPort = settings.getValue("settings:oscPort", 8000);


	topLeftX.set("Top Left X", 0, -0.5, 0.5);
	topLeftY.set("Top Left Y", 0, 0.5, -0.5);
	bottomLeftX.set("Bottom Left X", 0, -0.5, 0.5);
	bottomLeftY.set("Bottom Left Y", 1.0, 1.5, 0.5);
	topRightX.set("Top Right X", 1.0, 0.5, 1.5);
	topRightY.set("Top Right Y", 0, 0.5, -0.5);
	bottomRightX.set("Bottom Right X", 1.0, 0.5, 1.5);
	bottomRightY.set("Bottom Right Y", 1.0, 1.5, 0.5);

	string vid = settings.getValue("panel:filename", "null");
	topLeftX = settings.getValue("panel:Top_Left_X", 0);
	topLeftY = settings.getValue("panel:Top_Left_Y", 0);
	topRightX = settings.getValue("panel:Top_Right_X", 1.0f);
	topRightY = settings.getValue("panel:Top_Right_Y", 0);
	bottomLeftX = settings.getValue("panel:Bottom_Left_X", 0);
	bottomLeftY = settings.getValue("panel:Bottom_Left_Y", 1.0f);
	bottomRightX = settings.getValue("panel:Bottom_Right_X", 1.0f);
	bottomRightY = settings.getValue("panel:Bottom_Right_Y", 1.0f);


	// setup GUI

	gui.setup("panel"); // most of the time you don't need a name but don't forget to call setup
	gui.add(filename.set("filename", vid));
	gui.add(loadFile.setup("Load File"));

	gui.add(topLeftX);
	gui.add(topLeftY);
	gui.add(bottomLeftX);
	gui.add(bottomLeftY);
	gui.add(topRightX);
	gui.add(topRightY);
	gui.add(bottomRightX);
	gui.add(bottomRightY);


	ofHideCursor();
	// Add GUI listeners
	loadFile.addListener(this, &ofApp::LoadFile);

	// setup OSC
	LoadFile();
	oscReceiver.setup(oscPort);

	ofSetWindowShape(ofGetWidth(), ofGetHeight());
	ofSetBackgroundAuto(false);
	ofSetBackgroundColor(ofColor(0, 0, 0, 255));
}

//--------------------------------------------------------------

void ofApp::update(){

	while (oscReceiver.hasWaitingMessages()) {

		// get the next message
		ofxOscMessage m;
		oscReceiver.getNextMessage(m);

		// check for mouse moved message
		if (m.getAddress() == "/playvideo") {
			// both the arguments are floats
			filename = m.getArgAsString(0);
			LoadFile();
		}
	}

	if (vidPlayer.isLoaded()) {
		vidPlayer.update();

		if (vidPlayer.isFrameNew()) {

			vidMat = ofxCv::toCv(vidPlayer);
			int vidWidth = vidMat.cols;
			int vidHeight = vidMat.rows;

			std::vector<cv::Point2f> destPoints(4);

			destPoints[0] = cv::Point2f(topLeftX*vidWidth, topLeftY*vidHeight);
			destPoints[1] = cv::Point2f(topRightX*vidWidth, topRightY*vidHeight);
			destPoints[2] = cv::Point2f(bottomRightX*vidWidth, bottomRightY*vidHeight);
			destPoints[3] = cv::Point2f(bottomLeftX*vidWidth, bottomLeftY*vidHeight);

			ofxCv::warpPerspective(vidPlayer, vidMat, destPoints);


			ofxCv::toOf(vidMat, img);

		}

	}

}


//--------------------------------------------------------------

void ofApp::draw(){
	int width = ofGetWidth();
	int height = ofGetHeight();

	if (img.isAllocated()) {
		img.resize(width, height);
		img.update();
		img.draw(0, 0);
	}

	if (showGui) {
		gui.draw();
		ofShowCursor();
	}
	else {
		ofHideCursor();
	}

}

// CUSTOM LISTENERS


void ofApp::LoadFile() {
	img.clear();
	vidPlayer.loadAsync(filename);
	vidPlayer.play();
	vidPlayer.setLoopState(OF_LOOP_NORMAL);
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'm') {
		showGui = !showGui;
	}

	if (key == 's') {
		gui.saveToFile("settings.xml");
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){


}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::exit()
{
	gui.saveToFile("settings.xml");
}
