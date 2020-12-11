## Description
Fast scene drawer (with slow movement) to TEST and make other addons or some image processing.

## Screenshot
![Alt text](/readme_images/screenshot.jpeg?raw=true "MoebiusSurfing")

## Overview
This helper addon easily draws a scene with two independent layers of these enabled or disabled 'draw types':

- Image 1 (background)
- Image 2 (image)
- Letters (text) Using two selectable colors or black-and-white mode.
- Video (requires ofxHapPlayer and add #define INCLUDE_HAP and the addon)

*The addon does not make any layer blending.* 

The screenshot it's an app made with the https://github.com/jonasfehr/ofxGpuMixer from Jonas Fehr.

There are some key commands in the example:

- 'S': show/hide GUI
- 'b': toggle two-colors/b&w modes
- 'r': toggle timer randomizer of the two colors. 


## Features

- Gui to change settings.
- Auto save/load settings.


## Usage
Look the example: ```example_ofxSceneTEST```

### ofApp
```c++
//.h
#include "ofxSceneTEST.h"
ofxSceneTEST scene;

//.cpp
scene.drawChannel1();// draw 1st layer
scene.drawChannel2();// draw 2nd layer
scene.drawAll();// draw all channels but the selected by "Force Source" slider.

//optional
scene.setGuiVisible(!scene.getGuiVisible());
scene.setModeColorsToggle();
scene.setModeRandomizeToggle();
```