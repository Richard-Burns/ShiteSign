#include "ofApp.h"

//--------------------------------------------------------------

void ofApp::setup(){
	ofSetVerticalSync(true);

	// Setup and load settings
	ofxXmlSettings settings;
	settings.loadFile("settings.xml");
	string vid = settings.getValue("panel:filename", "null");


	// setup GUI

	gui.setup("panel"); // most of the time you don't need a name but don't forget to call setup
	gui.add(filename.set("filename", vid));
	gui.add(loadFile.setup("Load File"));

	// setup Perspective Pin GUI
	gui.add(topLeftX.set(0.5f));
	topLeftX.setName("Top Left X");
	gui.add(topLeftY.set(0.5f));
	topLeftY.setName("Top Left Y");

	gui.add(topRightX.set(0.5f));
	topRightX.setName("Top Right X");
	gui.add(topRightY.set(0.5f));
	topRightY.setName("Top Right Y");

	gui.add(bottomLeftX.set(0.5f));
	bottomLeftX.setName("bottom Left X");
	gui.add(bottomLeftY.set(0.5f));
	bottomLeftY.setName("bottom Left Y");

	gui.add(bottomRightX.set(0.5f));
	bottomRightX.setName("bottom Right X");
	gui.add(bottomRightY.set(0.5f));
	bottomRightY.setName("bottom Right Y");

	ofHideCursor();
	// Add GUI listeners
	loadFile.addListener(this, &ofApp::LoadFile);

	// setup OSC

	oscReceiver.setup(oscPort);

	ofSetWindowShape(ofGetWidth(), ofGetHeight());
	ofSetBackgroundAuto(false);
	ofSetBackgroundColor(ofColor(0, 0, 0, 255));
	LoadFile();
}

//--------------------------------------------------------------

void ofApp::update(){


	if (!fileLoading && vidPlayer.isInitialized() && vidPlayer.isLoaded()) {
		vidPlayer.update();

		if (vidPlayer.isFrameNew() && !fileLoading) {

			cv::Mat vidMat = ofxCv::toCv(vidPlayer);
			cv::Mat frame;

			std::vector<cv::Point2f> destPoints(4);

			destPoints[0] = cv::Point2f(400.0f, 0.0f);
			destPoints[1] = cv::Point2f(1920.0f, 0.0f);
			destPoints[2] = cv::Point2f(1920.0f, 1080.0f);
			destPoints[3] = cv::Point2f(0.0f, 1080.0f);

			ofxCv::warpPerspective(vidPlayer, img, destPoints);
			ofxCv::toOf(vidMat, img);

		}
	}
	else {
		CheckFileLoad();
	}


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
}

//--------------------------------------------------------------

void ofApp::draw(){
	int width = ofGetWidth();
	int height = ofGetHeight();

	if (img.isAllocated() && vidPlayer.isLoaded()) {
		img.update();
		img.draw(0, 0, width, height);
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
	fileLoading = true;
	vidPlayer.close();
	vidPlayer.load(filename.get());
}

void ofApp::CheckFileLoad() {
	if (vidPlayer.isLoaded()) {
		vidPlayer.play();
		vidPlayer.setLoopState(OF_LOOP_NORMAL);
		fileLoading = false;
	}
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
