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
	vidPlayer.update();
	CheckFileLoad();

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
	if (vidPlayer.isLoaded()) {
		vidPlayer.draw(0, 0, width, height);
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
