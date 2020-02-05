
## Screenshot
![Alt text](/screenshot.jpeg?raw=true "MoebiusSurfing")


## Example
https://github.com/moebiussurfing/ofxGpuMixer/tree/simplified/example2


## Description
This helper addon easily draws a scene with two independent 'channels/layers' with these enabled or disabled 'draw object types':

- image 1 (background)
- image 2 (image)
- letters (text) Using two text groups with two selectable-colors or black-and-white mode.
- video (requires ofxHapPlayer and add #define INCLUDE_HAP and the addon)

*The addon does not make any layer blending. I made it to help to debug a layer blending addon easily* 

The screenshot's an ofApp made with the https://github.com/jonasfehr/ofxGpuMixer addon from Jonas Fehr.

There are some key commands in the example:

- 's': show/hide GUI
- 'b': toggle two-colors/b&w modes
- 'r': toggle timer randomizer of the two colors. 


## Features

- slow animate zoom of the object types to create 'move flow'.
- GUI to change settings.
- autosave/load settings.


## Usage

### ofApp
```
.h
#include "ofxSceneTEST.h"
ofxSceneTEST scene;

.cpp
scene.drawChannel1();//draw 1st layer
scene.drawChannel2();//draw 2nd layer

//control by code
scene.setGuiVisible(!scene.getGuiVisible());
scene.setModeColorsToggle();
scene.setModeRandomizeToggle();
```
