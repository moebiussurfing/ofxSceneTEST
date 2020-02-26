
## Screenshot
![Image](/sceenshot1.JPG?raw=true "example2")


## Description
This helper addon easily draws an animated testing scene with two independent 'channels/layers' with these enabled or disabled 'draw object types':

- background color
- image 1 (background)
- image 2 (image)
- letters (text) Using two text groups with two selectable-colors or black-and-white mode.
- video (requires ofxHapPlayer and add #define INCLUDE_HAP and the addon)

*The addon does not make any layer blending. I made it to help to debug a layer blending addon easily* 


## Features

- slow animate zoom of the object types to create 'move-flow'.
- GUI to change settings.
- autosave/load settings.

There are some key commands in the example:

- 's': show/hide GUI
- 'b': toggle two-colors/b&w modes
- 'r': toggle timer randomizer of the two colors. 


## Why?

This add-on can be helpful when developing your own code/addon to forget about drawing stuff and start focusing on what you want: to code processing or layering of drawn layers.


## Requires

- ofxGui
- included images, video and fonts into '/data/ofxSceneTEST'

## Usage

### ofApp
```
.h
#include "ofxSceneTEST.h"
ofxSceneTEST scene;

.cpp
//independent layers
scene.drawBackground();
scene.drawChannel1();//draw 1st layer
scene.drawChannel2();//draw 2nd layer

//or
scene.drawAll();//draw both layers without any blendind

//control by code
scene.setGuiVisible(!scene.getGuiVisible());
scene.setModeColorsToggle();
scene.setModeRandomizeToggle();
```


## Tested systems
- macOS
- Windows


## TODO:

- add 3d objects to the scene.