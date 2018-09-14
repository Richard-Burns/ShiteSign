#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOsc.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"
#include "ofxXmlSettings.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void exit();

		// Custom Listeners
		bool fileLoading = false;
		void LoadFile();
		void CheckFileLoad();

		// GUI definitions
		bool showGui = false;
		ofxPanel gui;
		ofParameter<string> filename;
		ofxButton loadFile;

		// GUI Perspective Pin definitions
		ofParameter<float> topLeftX;
		ofParameter<float> topLeftY;
		ofParameter<float> topRightX;
		ofParameter<float> topRightY;
		ofParameter<float> bottomLeftX;
		ofParameter<float> bottomLeftY;
		ofParameter<float> bottomRightX;
		ofParameter<float> bottomRightY;

		// OSC definitions
		int oscPort = 8000;
		ofxOscReceiver oscReceiver;

		// Video definitions
		ofVideoPlayer vidPlayer;
		ofImage img;
		ofVideoGrabber cam;
		bool configMode = false;
		
};
