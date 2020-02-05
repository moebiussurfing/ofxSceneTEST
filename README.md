
## Screenshot
![Alt text](/screenshot.jpeg?raw=true "MoebiusSurfing")


## Example
https://github.com/moebiussurfing/ofxGpuMixer/tree/simplified/example2


## Description
This helper addon easily draws a scene with two independent layers of these enabled or disabled 'draw types':

- image 1 (background)
- image 2 (image)
- letters (text) Using two selectable colors or black-and-white mode.
- video (requires ofxHapPlayer and add #define INCLUDE_HAP and the addon)

*The addon does not make any layer blending.* 

The screenshot it's an app made with the https://github.com/jonasfehr/ofxGpuMixer from Jonas Fehr.

There are some key commands in the example:

- 's': show/hide GUI
- 'b': toggle two-colors/b&w modes
- 'r': toggle timer randomizer of the two colors. 


## Features

- gui to change settings.
- auto save/load settings.


## Usage

### ofApp
```
.h
#include "ofxSceneTEST.h"
ofxSceneTEST scene;

.cpp
scene.drawChannel1();//draw 1st layer
scene.drawChannel2();//draw 2nd layer

//short keys
scene.setGuiVisible(!scene.getGuiVisible());
scene.setModeColorsToggle();\n
scene.setModeRandomizeToggle();
```