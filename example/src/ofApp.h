#pragma once
#include "ofMain.h"

#include "ofxSceneTEST.h"

class ofApp : public ofBaseApp {

public:

	void draw();
	void keyPressed(int key);

	ofxSceneTEST scene;
};