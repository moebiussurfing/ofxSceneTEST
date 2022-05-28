
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::draw() {

	// Draw independent channels 
	// to use as layers to mix/blend with your own code
	//scene.drawBackground();
	//scene.drawChannel1();
	//scene.drawChannel2();

	// Draw all channels 
	// one upon other without any blending
	scene.drawAll();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	// Show scene
	if (key == 's')
	{
		scene.setGuiVisible(!scene.getGuiVisible());
	}
	else if (key == 'b')
	{
		scene.setModeColorsToggle();
	}
	else if (key == 'r')
	{
		scene.setModeRandomizeToggle();
	}
}