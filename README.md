## Description
Fast&Easy scene drawer (2D image layers with slow movement) to **TEST** and make other addons or to do some image processing.

## Screenshot
![image](/readme_images/Capture1.JPG?raw=true "image")
![image](/readme_images/Capture2.JPG?raw=true "image")

## Overview
This helper addon easily draws a scene with two independent layers of these enabled or disabled 'draw types':

- Image 1 (background)
- Image 2 (image)
- Text letters (Using two selectable colors or black-and-white mode)
- Video (requires ofxHapPlayer and add #define INCLUDE_HAP and the addon)

*The addon does not make any layer Blending/Mixing.* 
* Check the ```/bin/data files```: images and fonts.

## Features
- GUI to tweak settings.
- Auto save/load settings.

## Usage
Look the example: ```/example_ofxSceneTEST```

### ofApp.h
```c++
#include "ofxSceneTEST.h"

ofxSceneTEST scene;
```

### ofApp.cpp
```c++
// allows draw all channels but draws the selected by "Force Source" slider:
scene.drawAll();

// nothing more!

//-

// customize:
//scene.drawChannel1();// draw 1st layer
//scene.drawChannel2();// draw 2nd layer

// other:
//scene.setGuiVisible(!scene.getGuiVisible());
//scene.setModeColorsToggle();
//scene.setModeRandomizeToggle();
```