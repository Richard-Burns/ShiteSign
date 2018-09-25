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

		// OSC definitions
		int oscPort = 8000;
		ofxOscReceiver oscReceiver;

		int width = 1920;
		int height = 1080;

		ofParameter<float> topLeftX = 0.0f;
		ofParameter<float> topLeftY = 0.0f;
		ofParameter<float> topRightX = 1.0f;
		ofParameter<float> topRightY = 0.0f;
		ofParameter<float> bottomLeftX = 0.0f;
		ofParameter<float> bottomLeftY = 1.0f;
		ofParameter<float> bottomRightX = 1.0f;
		ofParameter<float> bottomRightY = 1.0f;

		// Video definitions
		ofVideoPlayer vidPlayer;
		ofImage img;
		cv::Mat vidMat;
		ofVideoGrabber cam;
		bool configMode = false;
		
};
