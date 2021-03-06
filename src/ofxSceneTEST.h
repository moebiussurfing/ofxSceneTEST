#pragma once
#include "ofMain.h"

///---------------------------------
///
//#define INCLUDE_HAP
///
//---------------------------------

#define D_OFFSET 125//displace
#define Z_MIN 1.18//zoom
#define Z_MAX 9.0
#define T_MIN 60//speed
#define T_MAX 240

#ifdef INCLUDE_HAP
#include "ofxHapPlayer.h"
#endif

//--

#include "ofxGui.h"

class ofxSceneTEST : public ofBaseApp
{
	//video hap
private:
#ifdef INCLUDE_HAP
	ofxHapPlayer player;
#endif

	//speed
	int timer1 = 400;
	int timer2 = 400;
	int timer3 = 400;

	//size
	float max1 = 5;
	float max2 = 5;
	float max3 = 5;

	//gui
private:
	ofxPanel gui;
	ofParameter<glm::vec2> Gui_Position;

	string str1 = "TEST\nofxFbo\nMixerBlend";
	string str2 = "FBO\nMIXER\nBLENDER";

public:
	//--------------------------------------------------------------
	void setText1(string s) {
		str1 = s;
	}
	//--------------------------------------------------------------
	void setText2(string s) {
		str2 = s;
	}

	//layers:
private:

	//background image
	ofImage myBackground;

	//text
	ofTrueTypeFont font;
	int size;
	int x, y;

	//image
	ofImage image;

	//-

	ofParameterGroup params{ "SCENE" };

	ofParameter<bool> ENABLE_BackgroundColor{ "GLOBAL BACKGROUND", false };
	ofParameter<float> zoom{ "ZOOM", 1.0f, 0.5f, 10.f };
	ofParameter<glm::vec2> posOffset{ "POSITION OFFSET", glm::vec2(0), glm::vec2(-1920), glm::vec2(1920) };

	ofParameterGroup params_Letters{ "LETTERS" };
	ofParameterGroup params_Colors{ "COLORS" };
	ofParameter<ofColor> c1, c2, cBg;
	ofParameter<bool> ENABLE_randomizeColors;
	ofParameter<bool> ENABLE_Colors;

	ofParameterGroup params_BW{ "BW" };
	ofParameter<ofColor> cBlack, cWhite;
	ofParameter<bool> ENABLE_BW;
	ofParameter<bool> RESET_BW;

	ofParameterGroup params_SOURCES{ "SOURCES" };

	ofParameterGroup params_Channel1{ "CHANNEL 1" };
	ofParameter<bool> ENABLE_ColorBackground_1;
	ofParameter<bool> ENABLE_Image_1_1;
	ofParameter<bool> ENABLE_Letters_1;
	ofParameter<bool> ENABLE_Image_1_2;
#ifdef INCLUDE_HAP
	ofParameter<bool> ENABLE_Video_1;
#endif

	ofParameterGroup params_Channel2{ "CHANNEL 2" };
	ofParameter<bool> ENABLE_ColorBackground_2;
	ofParameter<bool> ENABLE_Image_2_1;
	ofParameter<bool> ENABLE_Letters_2;
	ofParameter<bool> ENABLE_Image_2_2;
#ifdef INCLUDE_HAP
	ofParameter<bool> ENABLE_Video_2;
#endif

	//-

	string path_Params;
	string GLOBAL_Path;

	bool DISABLE_Callbacks;

	ofParameter<bool> SHOW_Gui{ "GUI", true };

	ofParameter<int> sourceIndex{ "Force Source", 0, 0, 4 };// select what channel to draw whan drawAll is called
	ofParameter<bool> bSmooth{ "Smooth", true };

public:

	//--------------------------------------------------------------
	void setGuiVisible(bool b)
	{
		SHOW_Gui = b;
	}
	//--------------------------------------------------------------
	void setToggleGuiVisible()
	{
		SHOW_Gui = !SHOW_Gui;
	}

	//--------------------------------------------------------------
	bool getGuiVisible()
	{
		return SHOW_Gui.get();
	}

	//--------------------------------------------------------------
	void refreshGui()
	{
		gui.maximizeAll();
		auto &gScn = gui.getGroup("SCENE");
		auto &gSrc = gScn.getGroup("SOURCES");
		auto &ch1 = gSrc.getGroup("CHANNEL 1");
		auto &ch2 = gSrc.getGroup("CHANNEL 2");
		//gSrc.minimize();
		ch2.minimize();

		auto &gLtr = gScn.getGroup("LETTERS");
		auto &Col = gLtr.getGroup("COLORS");
		auto &Bw = gLtr.getGroup("BW");
		Bw.minimize();
		gLtr.minimize();

		auto &gGuiPos = gScn.getGroup("GUI POSITION");
		gGuiPos.minimize();
	}

	//--------------------------------------------------------------
	ofxSceneTEST()
	{
		ofSetLogLevel("ofxSceneTEST", OF_LOG_NOTICE);
		//ofSetLogLevel("ofxSceneTEST", OF_LOG_VERBOSE);

		//path for settings
		GLOBAL_Path = "ofxSceneTEST/";

		//out of global folder
		path_Params = GLOBAL_Path + "scene.xml";
		
		ofAddListener(ofEvents().keyPressed, this, &ofxSceneTEST::keyPressed);

		setup();
	}

	//--------------------------------------------------------------
	~ofxSceneTEST()
	{
		//remove params callbacks listeners
		ofRemoveListener(params.parameterChangedE(), this, &ofxSceneTEST::Changed_params);

		//get gui position before save
		Gui_Position = glm::vec2(gui.getPosition());

		//settings
		saveParams(params, path_Params);
		
		ofRemoveListener(ofEvents().keyPressed, this, &ofxSceneTEST::keyPressed);

		//exit();
	}

	//--------------------------------------------------------------
	void keyPressed(ofKeyEventArgs &eventArgs)
	{
		const int &key = eventArgs.key;
		ofLogNotice(__FUNCTION__) << "'" << (char)key << "' \t\t[" << key << "]";

		////modifiers
		//bool mod_COMMAND = eventArgs.hasModifier(OF_KEY_COMMAND);
		//bool mod_CONTROL = eventArgs.hasModifier(OF_KEY_CONTROL);
		//bool mod_ALT = eventArgs.hasModifier(OF_KEY_ALT);
		//bool mod_SHIFT = eventArgs.hasModifier(OF_KEY_SHIFT);
		//if (false)
		//{
		//	ofLogNotice(__FUNCTION__) << "mod_COMMAND: " << (mod_COMMAND ? "ON" : "OFF");
		//	ofLogNotice(__FUNCTION__) << "mod_CONTROL: " << (mod_CONTROL ? "ON" : "OFF");
		//	ofLogNotice(__FUNCTION__) << "mod_ALT: " << (mod_ALT ? "ON" : "OFF");
		//	ofLogNotice(__FUNCTION__) << "mod_SHIFT: " << (mod_SHIFT ? "ON" : "OFF");
		//}

		//gui
		if (key == 'S')
		{
			setToggleGuiVisible();
		}
	}

	//--------------------------------------------------------------
	void setup()
	{
		ofLogVerbose(__FUNCTION__) << "called setup";

		//-

		DISABLE_Callbacks = true;

		//-

		//ofxGui theme
		//string pathFontGui = GLOBAL_Path + "fonts/overpass-mono-bold.otf";
		string pathFontGui = "assets/fonts/overpass-mono-bold.otf";
		ofFile file(pathFontGui);
		if (file.exists())
		{
			ofLogNotice(__FUNCTION__) << "ofxGui theme: LOADED FONT FILE '" << pathFontGui << "'";
			ofxGuiSetFont(pathFontGui, 9);
		}
		else
		{
			ofLogError(__FUNCTION__) << "ofxGui theme: FONT FILE '" << pathFontGui << "' NOT FOUND!";
			font.load(OF_TTF_SANS, size, true, true);
		}
		ofxGuiSetDefaultHeight(20);
		ofxGuiSetBorderColor(32);
		ofxGuiSetFillColor(ofColor(48));
		ofxGuiSetTextColor(ofColor::white);
		ofxGuiSetHeaderColor(ofColor(24));

		//-

		//layers

		//ttf font
		string pathFont;
		//pathFont = GLOBAL_Path + "fonts/Sequel100Black116.ttf";
		pathFont = "assets/fonts/Sequel100Black116.ttf";
		//pathFont = GLOBAL_Path + "fonts/DSPTRLSuper.ttf"; size = 90;
		//pathFont = GLOBAL_Path + "fonts/overpass-mono-bold.otf";size = 100;
		size = 60;
		bool bLoaded = font.load(pathFont, size, true, true);
		if (bLoaded)
		{
			ofLogNotice(__FUNCTION__) << "ttf font: LOADED FONT FILE '" << pathFont << "'";
		}
		else
		{
			ofLogError(__FUNCTION__) << "ttf font: FONT FILE '" << pathFont << "' NOT FOUND!";
			font.load(OF_TTF_SERIF, size, true, true);
		}
		font.setLineHeight(size + 5);

		//-

		//background
		string pathBg;
		pathBg = "image1.jpg";
		//pathBg = "image2.jpg";
		myBackground.load(GLOBAL_Path + pathBg);

		//image
		string pathImg = GLOBAL_Path + "image2.jpg";;
		image.load(pathImg);

		//video hap
#ifdef INCLUDE_HAP
		string str = "movies";
		loadVideo(GLOBAL_Path + str + "/" + "SampleHap.mov");
		player.setLoopState(OF_LOOP_NORMAL);
#endif

		//-

		cBg.set("BACKGROUND COLOR", ofColor(128, 255), ofColor(0, 0), ofColor(255, 255));

		ENABLE_Colors.set("MODE COLORS", true);
		ENABLE_randomizeColors.set("RANDOMIZER", false);
		c1.set("COLOR 1", ofColor(128, 255), ofColor(0, 0), ofColor(255, 255));
		c2.set("COLOR 2", ofColor(128, 255), ofColor(0, 0), ofColor(255, 255));
		params_Colors.add(c1);
		params_Colors.add(c2);
		params_Colors.add(ENABLE_randomizeColors);

		ENABLE_BW.set("MODE BW", false);
		RESET_BW.set("RESET", false);
		RESET_BW.setSerializable(false);
		cBlack.set("BLACK", ofColor(0, 255), ofColor(0, 0), ofColor(255, 255));
		cWhite.set("WHITE", ofColor(255, 255), ofColor(0, 0), ofColor(255, 255));
		cBlack.setSerializable(false);
		cWhite.setSerializable(false);
		params_BW.add(RESET_BW);
		params_BW.add(cBlack);
		params_BW.add(cWhite);

		ENABLE_ColorBackground_1.set("COLOR BACKGROUND", false);
		ENABLE_Image_1_1.set("IMAGE 1", true);
		ENABLE_Letters_1.set("LETTERS", false);
		ENABLE_Image_1_2.set("IMAGE 2", false);

		params_Channel1.add(ENABLE_ColorBackground_1);
		params_Channel1.add(ENABLE_Image_1_1);
		params_Channel1.add(ENABLE_Image_1_2);
#ifdef INCLUDE_HAP
		ENABLE_Video_1.set("VIDEO", false);
		params_Channel1.add(ENABLE_Video_1);
#endif
		params_Channel1.add(ENABLE_Letters_1);
		params_SOURCES.add(params_Channel1);

		ENABLE_ColorBackground_2.set("COLOR BACKGROUND", false);
		ENABLE_Image_2_1.set("IMAGE 1", false);
		ENABLE_Letters_2.set("LETTERS", true);
		ENABLE_Image_2_2.set("IMAGE 2", false);

		params_Channel2.add(ENABLE_ColorBackground_2);
		params_Channel2.add(ENABLE_Image_2_1);
		params_Channel2.add(ENABLE_Image_2_2);
#ifdef INCLUDE_HAP
		ENABLE_Video_2.set("VIDEO", false);
		params_Channel2.add(ENABLE_Video_2);
#endif
		params_Channel2.add(ENABLE_Letters_2);
		params_SOURCES.add(params_Channel2);

		//all groups
		params_Letters.add(ENABLE_Colors);
		params_Letters.add(ENABLE_BW);
		params_Letters.add(params_Colors);
		params_Letters.add(params_BW);

		params.add(zoom);
		params.add(posOffset);
		params.add(params_SOURCES);
		params.add(params_Letters);

		params.add(ENABLE_BackgroundColor);
		params.add(cBg);

		params.add(SHOW_Gui);
		Gui_Position.set("GUI POSITION",
			glm::vec2(ofGetWidth()*0.5f, ofGetHeight()* 0.05f),
			glm::vec2(0, 0),
			glm::vec2(ofGetWidth(), ofGetHeight()));
		//Gui_Position = glm::vec2(ofGetWindowWidth() - 210, 5);
		params.add(Gui_Position);

		params.add(sourceIndex);
		params.add(bSmooth);

		ofAddListener(params.parameterChangedE(), this, &ofxSceneTEST::Changed_params);

		//-

		//gui
		gui.setup("ofxSceneTEST");
		gui.add(params);

		//default gui pos
		gui.setPosition(Gui_Position->x, Gui_Position->y);

		//collapse
		//gui.getGroup("SCENE").minimize();
		refreshGui();

		//-

		//auto call update and draw linked to ofApp
		ofAddListener(ofEvents().update, this, &ofxSceneTEST::update);
		ofAddListener(ofEvents().draw, this, &ofxSceneTEST::draw);

		//--

		//startup


		//settings
		loadParams(params, path_Params);
		//could crash if group vars structure, or name params are modified

		//TODO: crashes if moved ber load
		DISABLE_Callbacks = false;
	}

	//--------------------------------------------------------------
	void update(ofEventArgs & args)
	{
		//ofLogVerbose(__FUNCTION__) << "called update";
	}

	//--------------------------------------------------------------
	void draw(ofEventArgs & args)
	{
		////ofEnableDepthTest();

		if (SHOW_Gui)
		{
			//ofLogVerbose(__FUNCTION__) << "called draw";

			//in text mode
			if (ENABLE_Letters_1 || ENABLE_Letters_2)
			{
				int r = 20;
				int x, y;

				//left to the gui
				//x = Gui_Position->x - r -10;
				//y = Gui_Position->y + 2 * r + 125;

				//below the gui
				int xPad = 20;
				int yPad = 10;
				ofRectangle wr = gui.getShape();
				x = wr.getBottomLeft().x + r + xPad;
				y = wr.getBottomLeft().y + r + yPad;

				//debug the 2 original colors (without blending)
				//draw 2 circles filled by colors 1 and 2
				ofPushStyle();
				ofFill();

				//1st line
				if (ENABLE_BW)
					ofSetColor(cBlack);
				else
					ofSetColor(c1);

				ofDrawCircle(x, y, r);

				//2nd line
				if (ENABLE_BW)
					ofSetColor(cWhite);
				else
					ofSetColor(c2);

				//ofDrawCircle(x, y + 2.2f * r, r);//vertical aligned
				ofDrawCircle(x + 2.2f * r, y, r);//horizontal aligned

				ofPopStyle();
			}

			//--
	//--

	////TEST: 
	////ofApp background switcher to debug
	//int timer = 60;
	//int frame = ofGetFrameNum() % timer;
	//bool b = ((frame < timer*0.5) ? true : false);
	//if (b)
	//	ofBackground(ofColor::yellow);
	//else
	//	ofBackground(ofColor::green);

	//-
			ofDisableDepthTest();

			//scene
			gui.draw();
		}
	}

	//--------------------------------------------------------------
	void drawBackground()
	{
		ofClear(cBg);
	}

	//--------------------------------------------------------------
	void drawAll()
	{
		if (sourceIndex == 0)
		{
			if (ENABLE_BackgroundColor) drawBackground();

			drawChannel1();
			drawChannel2();//?
		}
		else
		{
			drawLayer(sourceIndex - 1);
		}
	}

	//--------------------------------------------------------------
	void drawChannel1()///to draw all layers
	{
		ofEnableDepthTest();

		//background color 
		if (ENABLE_ColorBackground_1)
		{
			drawLayer(LAYER_BACKGROUND_COLOR);
		}

		//text
		if (ENABLE_Letters_1)
		{
			drawLayer(LAYER_LETTERS);
		}

		//background image
		if (ENABLE_Image_1_1)
		{
			drawLayer(LAYER_BACKGROUND_IMAGE);
		}

		//image
		if (ENABLE_Image_1_2)
		{
			drawLayer(LAYER_IMAGE);
		}

		//video hap
#ifdef INCLUDE_HAP
		if (ENABLE_Video_1)
		{
			drawLayer(LAYER_VIDEO);
		}
#endif
	}

	//--------------------------------------------------------------
	void drawChannel2()
	{
		ofEnableDepthTest();

		//background color 
		if (ENABLE_ColorBackground_2)
		{
			drawLayer(LAYER_BACKGROUND_COLOR);
		}

		//text
		if (ENABLE_Letters_2)
		{
			drawLayer(LAYER_LETTERS);
		}

		//color background image
		if (ENABLE_Image_2_1)
		{
			drawLayer(LAYER_BACKGROUND_IMAGE);
		}

		//image background
		if (ENABLE_Image_2_1)
		{
			drawLayer(LAYER_BACKGROUND_IMAGE);
		}

		//image
		if (ENABLE_Image_2_2)
		{
			drawLayer(LAYER_IMAGE);
		}

		//video hap
#ifdef INCLUDE_HAP
		if (ENABLE_Video_2)
		{
			drawLayer(LAYER_VIDEO);
		}
#endif
	}

	//--------------------------------------------------------------
	void setModeColorsToggle()
	{
		DISABLE_Callbacks = true;//too avoid crashes
		ENABLE_BW = !ENABLE_BW;
		ENABLE_Colors = !ENABLE_BW;
		DISABLE_Callbacks = false;
		updateGui();
	}

	//--------------------------------------------------------------
	void setModeRandomizeToggle()
	{
		ENABLE_randomizeColors = !ENABLE_randomizeColors;
	}

private:
	//--------------------------------------------------------------
	void Changed_params(ofAbstractParameter &e)
	{
		if (!DISABLE_Callbacks)
		{
			string name = e.getName();

			//exclude debugs
			if (name != "exclude"
				&& name != "exclude"
				&& name != "RANDOMIZER"
				)
			{
				ofLogNotice(__FUNCTION__) << "Changed_params: " << name << " : " << e;

				//filter
				if (name == "MODE COLORS")
				{
					DISABLE_Callbacks = true;//too avoid crashes
					ENABLE_BW = !ENABLE_Colors;
					updateGui();
					DISABLE_Callbacks = false;
				}
				else if (name == "MODE BW")
				{
					DISABLE_Callbacks = true;
					ENABLE_Colors = !ENABLE_BW;
					updateGui();
					DISABLE_Callbacks = false;
				}
				else if (name == "RESET")
				{
					if (RESET_BW)
					{
						DISABLE_Callbacks = true;
						RESET_BW = false;
						cBlack = ofColor(0, 255);
						cWhite = ofColor(255, 255);
						DISABLE_Callbacks = false;
					}
				}
				else if (name == "GUI POSITION")
				{
					Gui_Position = glm::vec2(
						MIN(Gui_Position.get().x, ofGetWidth() - 210),
						MIN(Gui_Position.get().y, ofGetHeight() - 400));

					gui.setPosition(Gui_Position->x, Gui_Position->y);
				}

				//-

				////whorkflow
				//if (!ENABLE_BW && !ENABLE_Colors)
				//	ENABLE_Colors = true;//default
				//updateGui();
			}
		}
	}

	//--------------------------------------------------------------
	void updateGui()
	{
		//collapse groups
		auto &g0 = gui.getGroup("SCENE");//1st level
		auto &g1 = g0.getGroup("LETTERS");//1st level
		auto &g11 = g1.getGroup("BW");//2nd level
		auto &g12 = g1.getGroup("COLORS");//2nd level
		g11.minimize();
		g12.minimize();

		if (ENABLE_Colors)
		{
			g11.minimize();
			g12.maximize();
		}
		if (ENABLE_BW)
		{
			g12.minimize();
			g11.maximize();
		}
	}

	//--------------------------------------------------------------
	void loadParams(ofParameterGroup &g, string path)
	{
		ofLogNotice(__FUNCTION__) << " : " << path;
		ofXml settings;
		settings.load(path);
		ofDeserialize(settings, g);

		gui.setPosition(Gui_Position->x, Gui_Position->y);
	}

	//--------------------------------------------------------------
	void saveParams(ofParameterGroup &g, string path)
	{
		ofLogNotice(__FUNCTION__) << " : " << path;
		ofXml settings;
		ofSerialize(settings, g);
		settings.save(path);
	}



private:
#ifdef INCLUDE_HAP
	//video hap
	//--------------------------------------------------------------
	void drawVideo() {
		if (player.isLoaded())
		{
			//draw the video frame
			ofSetColor(255, 255, 255);

			//ofRectangle videoRect(0, 0, player.getWidth(), player.getHeight());

			ofRectangle videoRect(0, 0, ofGetWindowWidth(), ofGetWindowHeight());

			videoRect.scaleTo(ofGetWindowRect());
			player.draw(videoRect.x, videoRect.y, videoRect.width, videoRect.height);
		}
		else
		{
			if (player.getError().length())
			{
				ofDrawBitmapStringHighlight(player.getError(), 20, 20);
			}
			else
			{
				ofDrawBitmapStringHighlight("Movie is loading...", 20, 20);
			}
		}
	}

	//--------------------------------------------------------------
	void loadVideo(std::string movie)
	{
		player.load(movie);
		player.play();
	}
#endif
private:
	//scene design
	//--------------------------------------------------------------
	enum LAYER_Type
	{
		LAYER_BACKGROUND_COLOR,
		LAYER_BACKGROUND_IMAGE,
		LAYER_LETTERS,
		LAYER_IMAGE,
		LAYER_VIDEO
	};

private:
	//--------------------------------------------------------------
	void drawLayer(int layerType)
	{
		ofPushMatrix();
		ofTranslate(posOffset.get());
		//ofTranslate(-ofGetWidth() * zoom - 1, -ofGetHeight() * zoom - 1);
		//ofTranslate(posOffset.get().x,posOffset.get().y, -1);
		ofScale(zoom);

		int xOffset, yOffset;
		xOffset = 250;
		yOffset = 400;

		switch (layerType)
		{

			//-----------------

		case LAYER_BACKGROUND_COLOR:
		{
			drawBackground();
		}
		break;

		case LAYER_BACKGROUND_IMAGE:
		{
			ofPushMatrix();

			int xHalf, yHalf;
			xHalf = myBackground.getWidth();
			yHalf = myBackground.getHeight();
			ofTranslate(xHalf, yHalf);
			ofTranslate(D_OFFSET, D_OFFSET);//focus character

			//faded zoom
			int frame = ofGetFrameNum() % timer1;
			float s = ofMap(frame, 0, timer1, -1.0, 1.0f);

			if (ofGetFrameNum() % timer1 == 0 && !bSmooth)
			{
				max1 = ofRandom(Z_MIN, Z_MAX);
				timer1 = ofRandom(T_MIN, T_MAX);
			}

			ofScale(Z_MIN + max1 * abs(0.1 * glm::sin(s)));

			//draw
			image.draw(-xHalf, -yHalf, ofGetWidth(), ofGetHeight());

			ofPopMatrix();

			// //TEST:
			// //B. background switcher
			// //TODO:
			// int timer = 30;
			// int frame = ofGetFrameNum() % timer;
			// bool b = ((frame < timer*0.5) ? true : false);
			// ofColor c;
			// if (b)
			// 	c.set(ofColor::red);
			// else
			// 	c.set(ofColor::green);
			// ofClear(c.r, c.g, c.b, 255);//fbo works! 
			// //effected letters draws fine into backgroundfboPOST

		}
		break;

		//-----------------
		case LAYER_LETTERS:
		{
			//two text lines
			ofPushStyle();
			ofPushMatrix();

			//timer randomize colors
			if (ENABLE_randomizeColors)
			{
				int frame2 = ofGetFrameNum() % 120;
				if (frame2 == 0)//randomize the 2 colors every timer2 (120) frames
				{
					c1 = ofColor(ofRandom(255), ofRandom(255), ofRandom(255), 255);
					c2 = ofColor(ofRandom(255), ofRandom(255), ofRandom(255), 255);
				}
			}

			int xHalf, yHalf;
			xHalf = ofGetWidth()*0.5;
			yHalf = ofGetHeight()*0.5;
			ofTranslate(1.5 * xHalf, yHalf);

			//faded zoom
			int frame = ofGetFrameNum() % timer2;
			float s = ofMap(frame, 0, timer2, -1.0, 1.0f);

			if (ofGetFrameNum() % timer2 == 0 && !bSmooth)
			{
				timer2 = ofRandom(T_MIN, T_MAX);
				max2 = ofRandom(Z_MIN, Z_MAX);
			}

			ofScale(Z_MIN + max2 * abs(0.1 * glm::sin(s)));

			//draw
			x = -xHalf + xOffset;
			y = -yHalf + yOffset;

			//1st line
			if (ENABLE_BW)
				ofSetColor(cBlack);
			else
				ofSetColor(c1);

			font.drawString(str1, x, y);
			float _h = font.getStringBoundingBox(str1, x, y).getHeight();

			//2nd line
			if (ENABLE_BW)
				ofSetColor(cWhite);
			else
				ofSetColor(c2);

			font.drawString(str2, x, y + _h + 10);

			ofPopMatrix();
			ofPopStyle();
		}
		break;

		//-----------------
		case LAYER_IMAGE:
		{
			ofPushMatrix();

			int xHalf, yHalf;
			xHalf = image.getWidth()*0.5;
			yHalf = image.getHeight()*0.5;
			ofTranslate(xHalf, yHalf);
			ofTranslate(D_OFFSET, D_OFFSET);//focus character

			//fade zoom
			int frame = ofGetFrameNum() % timer3;
			float s = ofMap(frame, 0, timer3, -1.0, 1.0f);
			if (ofGetFrameNum() % timer3 == 0 && !bSmooth)
			{
				timer3 = ofRandom(T_MIN, T_MAX);
				max3 = ofRandom(Z_MIN, Z_MAX);
			}

			ofScale(Z_MIN + max3 * abs(0.1 * glm::sin(s)));

			//draw
			myBackground.draw(-xHalf, -yHalf, ofGetWidth(), ofGetHeight());

			////draw
			//image.draw(-xHalf, -yHalf, ofGetWidth(), ofGetHeight());

			ofPopMatrix();
		}
		break;

#ifdef INCLUDE_HAP
		//-----------------
		case LAYER_VIDEO:
		{
			drawVideo();
		}
		break;
#endif

		//-----------------
		default:
			break;
		}

		ofPopMatrix();
	}
};

