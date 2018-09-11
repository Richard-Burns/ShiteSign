#include "ofApp.h"
#include "ofxOpenCv.h"
#include "ofxXmlSettings.h"

ofVideoPlayer vidPlayer;
cv::Mat frame;
ofVideoGrabber grabber;
bool configMode = false;

//--------------------------------------------------------------
void ofApp::setup(){

	ofxXmlSettings settings;
	settings.loadFile("settings.xml");
	string vid = settings.getValue("settings:filename", "null");
	ofHideCursor();
	
	vidPlayer.load(vid);
	vidPlayer.play();
	vidPlayer.setLoopState(OF_LOOP_NORMAL);

	ofSetWindowShape(ofGetWidth(), ofGetHeight());
	ofSetBackgroundAuto(false);
}
//--------------------------------------------------------------
void ofApp::update(){
	vidPlayer.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	int width = ofGetWidth();
	int height = ofGetHeight();



	vidPlayer.draw(0, 0, width, height);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
