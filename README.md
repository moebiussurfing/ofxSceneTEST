## Description
Fast scene drawer (with slow movement) to TEST and make other addons or some image processing.

## Screenshot
![Alt text](/readme_images/screenshot.jpeg?raw=true "MoebiusSurfing")
The screenshot it's an app made with the https://github.com/jonasfehr/ofxGpuMixer from Jonas Fehr.

## Overview
This helper addon easily draws a scene with two independent layers of these enabled or disabled 'draw types':

- Image 1 (background)
- Image 2 (image)
- Letters (text) Using two selectable colors or black-and-white mode.
- Video (requires ofxHapPlayer and add #define INCLUDE_HAP and the addon)

*The addon does not make any layer Blending/Mixing.* 
* Check the /bin/data files: images and fonts.

## Features
- Gui to tweak settings.
- Auto save/load settings.

## Usage
Look the example: ```/example_ofxSceneTEST```

### ofApp
```c++
//.h
#include "ofxSceneTEST.h"
ofxSceneTEST scene;

//.cpp
// allows draw all channels 
// but draws the selected by "Force Source" slider.
scene.drawAll();

// nothing more!

//scene.drawChannel1();// draw 1st layer
//scene.drawChannel2();// draw 2nd layer

//optional
//scene.setGuiVisible(!scene.getGuiVisible());
//scene.setModeColorsToggle();
//scene.setModeRandomizeToggle();
```