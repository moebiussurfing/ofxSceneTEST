#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	//draw independent channels to use as layers to mix/blend with your own code
	//scene.drawBackground();
	//scene.drawChannel1();
	//scene.drawChannel2();

	//draw all channels one uppon other without any blending
	scene.drawAll();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	//scene
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
