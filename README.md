## Description
Fast&Easy scene drawer (2D image layers with slow/random movement).  
I use this as source to **TEST** and make other addons, or to do some image processing.

## Screenshot
*/example*  
![image](/readme_images/Capture.JPG?raw=true "image")  
*In another project:*  
![image](/readme_images/Capture1.JPG?raw=true "image")  

## Overview
This addon easily draws a scene with two independent layers of these enabled or disabled 'draw types':

- Image 1 (background)
- Image 2 (image)
- Text letters (Using two selectable colors or *black-and-white* mode.)
- Video (requires ofxHapPlayer and add ```#define INCLUDE_HAP``` and the addon.)

*The addon does not make any layer Blending/Mixing.* 
* Check the ```/bin/data``` files: 2 images and 1 font.

## Features
- GUI to Tweak settings.
- Auto Save/Load settings.

## Usage
Look the example: ```/example```

### ofApp.h
```c++
#include "ofxSceneTEST.h"

ofxSceneTEST scene;
```

### ofApp.cpp
```c++
// allows draw all channels but draws the selected by "Force Source" slider:
// (0 is for all. any other to solo each layer.)
scene.drawAll();

// nothing more !

//--

// independent channels:
//scene.drawChannel1();// draw 1st layer
//scene.drawChannel2();// draw 2nd layer

//-

// more:
//scene.setGuiVisible(!scene.getGuiVisible());
//scene.setModeColorsToggle();
//scene.setModeRandomizeToggle();
```