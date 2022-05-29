
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::draw() {

	// 1. Draw independent channels 
	// To use as layers to mix/blend with your own code
	//scene.drawBackground();
	//scene.drawChannel1();
	//scene.drawChannel2();

	// 2. Draw all channels 
	// one upon other but without any blending or transparency!
	scene.drawAll();

	//--

	scene.drawGui();
}