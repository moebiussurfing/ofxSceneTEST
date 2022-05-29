#pragma once
#include "ofMain.h"

///---------------------------------
///
//#define INCLUDE_HAP
///
//---------------------------------

#define D_OFFSET 125 // displace
#define Z_MIN 1.18 // zoom
#define Z_MAX 9.0
#define T_MIN 60 // speed
#define T_MAX 240

#ifdef INCLUDE_HAP
#include "ofxHapPlayer.h"
#endif

//--

#include "ofxGui.h"
#include "ofxSurfing_ofxGui.h"
#include "ofxSurfingHelpers.h"

class ofxSceneTEST 
{

	// video hap

#ifdef INCLUDE_HAP

private:

	ofxHapPlayer player;
#endif

private:

	// speed

	int timer1 = 400;
	int timer2 = 400;
	int timer3 = 400;

	// size

	float max1 = 5;
	float max2 = 5;
	float max3 = 5;

	// gui

private:

	ofxPanel gui;
	ofParameter<glm::vec2> position_Gui;

	string str1 = "TEST \n ofxFbo \n MixerBlend";
	string str2 = "FBO \n MIXER \n BLENDER";

public:

	//--------------------------------------------------------------
	void setText1(string s) {
		str1 = s;
	}
	//--------------------------------------------------------------
	void setText2(string s) {
		str2 = s;
	}

	// Layers:

private:

	// Background image

	ofImage myBackground;

	// Text

	ofTrueTypeFont font;
	int size;
	int x, y;

	// Image

	ofImage image;

	//-

	ofParameterGroup params{ "SCENE" };
	ofParameterGroup params_Bg{ "BACKGROUND" };
	ofParameterGroup params_Internal{ "INTERNAL" };
	ofParameterGroup params_Translate{ "TRANSLATE" };

	ofParameter<bool> ENABLE_BackgroundColor{ "GLOBAL BACKGROUND", false };
	ofParameter<float> zoom{ "ZOOM", 1.0f, 0.5f, 10.f };
	ofParameter<glm::vec2> position_Offset{ "POSITION OFFSET", glm::vec2(0), glm::vec2(-1920), glm::vec2(1920) };

	ofParameterGroup params_Letters{ "LETTERS" };
	ofParameterGroup params_Extra{ "EXTRA" };
	ofParameterGroup params_Colors{ "COLORS" };
	ofParameter<ofColor> c1, c2, cBg;
	ofParameter<bool> ENABLE_randomizeColors;
	ofParameter<bool> ENABLE_Colors;

	ofParameterGroup params_BW{ "BW" };
	ofParameter<ofColor> cBlack, cWhite;
	ofParameter<bool> ENABLE_BW;
	ofParameter<bool> bReset_BW;

	ofParameterGroup params_Sources{ "SOURCES" };

	ofParameterGroup params_Channel_1{ "CHANNEL 1" };
	ofParameter<bool> ENABLE_ColorBackground_1;
	ofParameter<bool> ENABLE_Image_1_1;
	ofParameter<bool> ENABLE_Letters_1;
	ofParameter<bool> ENABLE_Image_1_2;

#ifdef INCLUDE_HAP
	ofParameter<bool> ENABLE_Video_1;
#endif

	ofParameterGroup params_Channel_2{ "CHANNEL 2" };
	ofParameter<bool> ENABLE_ColorBackground_2;
	ofParameter<bool> ENABLE_Image_2_1;
	ofParameter<bool> ENABLE_Letters_2;
	ofParameter<bool> ENABLE_Image_2_2;

#ifdef INCLUDE_HAP
	ofParameter<bool> ENABLE_Video_2;
#endif

	//-

	string path_Params;
	string path_GLOBAL;

	bool bDISABLE_CALLBACKS;

	ofParameter<bool> bCH1{ "CH1", true };
	ofParameter<bool> bCH2{ "CH2", true };

	// Select what channel to draw when drawAll() is called
	// 0 = standard : all!
	ofParameter<int> sourceIndex{ "Force Source", 0, 0, 4 };
	
	ofParameter<bool> bSmooth{ "SMOOTH", true };
	ofParameter<bool> bReset{ "RESET",false };

public:

	ofParameter<bool> bGui{ "SCENE TEST", true };

	//--------------------------------------------------------------
	void setGuiVisible(bool b)
	{
		bGui = b;
	}
	//--------------------------------------------------------------
	void setToggleGuiVisible()
	{
		bGui = !bGui;
	}

	//--------------------------------------------------------------
	bool getGuiVisible()
	{
		return bGui.get();
	}


	//--------------------------------------------------------------
	ofxSceneTEST()
	{
		ofSetLogLevel("ofxSceneTEST", OF_LOG_NOTICE);

		// path for settings
		path_GLOBAL = "ofxSceneTEST/";

		//out of global folder
		path_Params = path_GLOBAL + "ofxSceneTEST.xml";

		ofAddListener(ofEvents().keyPressed, this, &ofxSceneTEST::keyPressed);

		ofxSurfingHelpers::setThemeDarkMini_ofxGui();

		setup();
	}

	//--------------------------------------------------------------
	~ofxSceneTEST()
	{
		// remove params callbacks listeners
		ofRemoveListener(params.parameterChangedE(), this, &ofxSceneTEST::Changed_params);

		// get gui position before save
		position_Gui = glm::vec2(gui.getPosition());

		// settings
		saveParams(params, path_Params);

		ofRemoveListener(ofEvents().keyPressed, this, &ofxSceneTEST::keyPressed);

		ofRemoveListener(ofEvents().update, this, &ofxSceneTEST::update);
		//ofRemoveListener(ofEvents().draw, this, &ofxSceneTEST::draw);
	}

	//--------------------------------------------------------------
	void doReset()
	{
		bDISABLE_CALLBACKS = true;

		cBg.set(ofColor(32, 255));

		ENABLE_Colors = true;
		ENABLE_randomizeColors = false;

		c1.set(ofColor(64, 255));
		c2.set(ofColor(128, 255));
		cBlack.set(ofColor(0, 255));
		cWhite.set(ofColor(255, 255));

		ENABLE_BW = false;
		ENABLE_ColorBackground_1 = true;

		ENABLE_Image_1_1 = true;
		ENABLE_Letters_1 = false;
		ENABLE_Image_1_2 = false;

		ENABLE_Image_2_1 = false;
		ENABLE_Letters_2 = true;
		ENABLE_Image_2_2 = false;

		bSmooth = false;
		sourceIndex = 0;

		zoom = 1;
		position_Offset = glm::vec2(0, 0);

		bCH1 = false;
		bCH2 = true;

		//bGui = true;
		
		bDISABLE_CALLBACKS = false;

		refreshGui();
	}

	//--------------------------------------------------------------
	void keyPressed(ofKeyEventArgs& eventArgs)
	{
		const int& key = eventArgs.key;
		ofLogNotice(__FUNCTION__) << "'" << (char)key << "' \t\t[" << key << "]";



		// Gui

		if (key == 'G')
		{
			setToggleGuiVisible();
		}
	}

	//--------------------------------------------------------------
	void setup()
	{
		ofLogVerbose(__FUNCTION__) << "called setup";

		//-

		bDISABLE_CALLBACKS = true;

		//-

		// Layers

		// ttf font
		string pathFont;
		pathFont = "assets/fonts/Sequel100Black116.ttf"; size = 60;
		
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

		//--

		// Background

		string pathBg;
		pathBg = "image1.jpg";

		myBackground.load(path_GLOBAL + pathBg);

		//--

		// Image

		string pathImg = path_GLOBAL + "image2.jpg";;
		image.load(pathImg);

		//--

		// Video hap

#ifdef INCLUDE_HAP
		string str = "movies";
		loadVideo(path_GLOBAL + str + "/" + "SampleHap.mov");
		player.setLoopState(OF_LOOP_NORMAL);
#endif

		//--

		cBg.set("BACKGROUND COLOR", ofColor(128, 255), ofColor(0, 0), ofColor(255, 255));

		ENABLE_Colors.set("MODE COLORS", true);
		ENABLE_randomizeColors.set("RANDOMIZER", false);
		c1.set("COLOR 1", ofColor(128, 255), ofColor(0, 0), ofColor(255, 255));
		c2.set("COLOR 2", ofColor(128, 255), ofColor(0, 0), ofColor(255, 255));
		params_Colors.add(c1);
		params_Colors.add(c2);
		params_Colors.add(ENABLE_randomizeColors);

		ENABLE_BW.set("MODE BW", false);
		bReset_BW.set("RESET BW", false);
		bReset_BW.setSerializable(false);
		cBlack.set("BLACK", ofColor(0, 255), ofColor(0, 0), ofColor(255, 255));
		cWhite.set("WHITE", ofColor(255, 255), ofColor(0, 0), ofColor(255, 255));
		cBlack.setSerializable(false);
		cWhite.setSerializable(false);
		params_BW.add(bReset_BW);
		params_BW.add(cBlack);
		params_BW.add(cWhite);

		//--

		ENABLE_ColorBackground_1.set("COLOR BACKGROUND", false);
		ENABLE_Image_1_1.set("IMAGE 1", true);
		ENABLE_Letters_1.set("LETTERS", false);
		ENABLE_Image_1_2.set("IMAGE 2", false);

		params_Channel_1.add(ENABLE_ColorBackground_1);
		params_Channel_1.add(ENABLE_Image_1_1);
		params_Channel_1.add(ENABLE_Image_1_2);

#ifdef INCLUDE_HAP
		ENABLE_Video_1.set("VIDEO", false);
		params_Channel_1.add(ENABLE_Video_1);
#endif
		params_Channel_1.add(ENABLE_Letters_1);

		ENABLE_ColorBackground_2.set("COLOR BACKGROUND", false);
		ENABLE_Image_2_1.set("IMAGE 1", false);
		ENABLE_Letters_2.set("LETTERS", true);
		ENABLE_Image_2_2.set("IMAGE 2", false);

		params_Channel_2.add(ENABLE_ColorBackground_2);
		params_Channel_2.add(ENABLE_Image_2_1);
		params_Channel_2.add(ENABLE_Image_2_2);

#ifdef INCLUDE_HAP
		ENABLE_Video_2.set("VIDEO", false);
		params_Channel_2.add(ENABLE_Video_2);
#endif
		params_Channel_2.add(ENABLE_Letters_2);

		//--
		 
		// Sources
		params_Sources.add(bSmooth);
		params_Sources.add(params_Channel_1);
		params_Sources.add(params_Channel_2);

		//--

		// All Groups
		params_Letters.add(ENABLE_Colors);
		params_Letters.add(ENABLE_BW);
		params_Letters.add(params_Colors);
		params_Letters.add(params_BW);

		params.add(bCH1);
		params.add(bCH2);

		params.add(params_Sources);

		position_Gui.set("GUI POSITION",
			glm::vec2(ofGetWidth() * 0.5f, ofGetHeight() * 0.05f),
			glm::vec2(0, 0),
			glm::vec2(ofGetWidth(), ofGetHeight()));

		params_Bg.add(ENABLE_BackgroundColor);
		params_Bg.add(cBg);
		params_Translate.add(zoom);
		params_Translate.add(position_Offset);
		params_Internal.add(sourceIndex);
		params_Internal.add(position_Gui);
		params_Internal.add(bGui);

		params_Extra.add(params_Letters);
		params_Extra.add(params_Bg);
		params_Extra.add(params_Translate);
		params_Extra.add(params_Internal);
		params_Extra.add(bReset);
		params.add(params_Extra);

		ofAddListener(params.parameterChangedE(), this, &ofxSceneTEST::Changed_params);

		//--

		// Gui

		gui.setup("ofxSceneTEST");
		gui.add(params);

		//-

		// Auto call update and draw linked to ofApp

		ofAddListener(ofEvents().update, this, &ofxSceneTEST::update);
		//ofAddListener(ofEvents().draw, this, &ofxSceneTEST::draw);

		//--

		// Startup

		// settings
		loadParams(params, path_Params);
		//could crash if group vars structure, or name params are modified

		// default gui pos
		gui.setPosition(position_Gui->x, position_Gui->y);

		// collapse
		//gui.minimizeAll();
		refreshGui();

		bDISABLE_CALLBACKS = false;
	}

	//--------------------------------------------------------------
	void update(ofEventArgs& args)
	{
		//ofLogVerbose(__FUNCTION__) << "called update";
	}
	//--------------------------------------------------------------
	void drawGui()
	{
		if (bGui)
		{
			//ofDisableDepthTest();

			//ofLogVerbose(__FUNCTION__) << "called draw";

			//in text mode
			bool bDrawColorCircles = false;
			if (bDrawColorCircles)
				if (ENABLE_Letters_1 || ENABLE_Letters_2)
				{
					int r = 20;
					int x, y;

					//left to the gui
					//x = position_Gui->x - r -10;
					//y = position_Gui->y + 2 * r + 125;

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
					if (ENABLE_BW) ofSetColor(cBlack);
					else ofSetColor(c1);

					ofDrawCircle(x, y, r);

					//2nd line
					if (ENABLE_BW) ofSetColor(cWhite);
					else ofSetColor(c2);

					//ofDrawCircle(x, y + 2.2f * r, r);//vertical aligned
					ofDrawCircle(x + 2.2f * r, y, r);//horizontal aligned

					ofPopStyle();
				}

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

			//--

			//ofDisableDepthTest();

			//scene
			gui.draw();
		}
	}

	// auto draw
	////--------------------------------------------------------------
	//void draw(ofEventArgs& args)
	//{
	//	drawGui();
	//	////ofEnableDepthTest();
	//}

	//--------------------------------------------------------------
	void drawBackground()
	{
		ofClear(cBg);
	}

	//--------------------------------------------------------------
	void drawScene()
	{
		drawAll();
	}

	//--------------------------------------------------------------
	void drawAll()
	{
		//ofEnableAlphaBlending();

		if (sourceIndex == 0)
		{
			if (ENABLE_BackgroundColor) drawBackground();

			if (bCH1) drawChannel1();
			if (bCH2) drawChannel2();
		}
		else
		{
			drawLayer(sourceIndex - 1);
		}
	}

	//--------------------------------------------------------------
	void drawChannel1()///to draw all layers
	{
		//ofEnableDepthTest();

		// background color 
		if (ENABLE_ColorBackground_1)
		{
			drawLayer(LAYER_BACKGROUND_COLOR);
		}

		// text
		if (ENABLE_Letters_1)
		{
			drawLayer(LAYER_LETTERS);
		}

		// background image
		if (ENABLE_Image_1_1)
		{
			drawLayer(LAYER_BACKGROUND_IMAGE);
		}

		// image
		if (ENABLE_Image_1_2)
		{
			drawLayer(LAYER_IMAGE);
		}

		// video hap
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
		//ofEnableDepthTest();

		// background color 
		if (ENABLE_ColorBackground_2)
		{
			drawLayer(LAYER_BACKGROUND_COLOR);
		}

		// text
		if (ENABLE_Letters_2)
		{
			drawLayer(LAYER_LETTERS);
		}

		// color background image
		if (ENABLE_Image_2_1)
		{
			drawLayer(LAYER_BACKGROUND_IMAGE);
		}

		// image background
		if (ENABLE_Image_2_1)
		{
			drawLayer(LAYER_BACKGROUND_IMAGE);
		}

		// image
		if (ENABLE_Image_2_2)
		{
			drawLayer(LAYER_IMAGE);
		}

		// video hap
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
		bDISABLE_CALLBACKS = true;//too avoid crashes
		ENABLE_BW = !ENABLE_BW;
		ENABLE_Colors = !ENABLE_BW;
		bDISABLE_CALLBACKS = false;
	}

	//--------------------------------------------------------------
	void setModeRandomizeToggle()
	{
		ENABLE_randomizeColors = !ENABLE_randomizeColors;
	}

private:
	//--------------------------------------------------------------
	void Changed_params(ofAbstractParameter& e)
	{
		if (!bDISABLE_CALLBACKS)
		{
			string name = e.getName();

			{
				ofLogNotice(__FUNCTION__) << " " << name << " : " << e;

				// filter
				if (name == ENABLE_Colors.getName())
				{
					bDISABLE_CALLBACKS = true;//to avoid crashes
					ENABLE_BW = !ENABLE_Colors;
					bDISABLE_CALLBACKS = false;
				}
				else if (name == ENABLE_BW.getName())
				{
					bDISABLE_CALLBACKS = true;
					ENABLE_Colors = !ENABLE_BW;
					bDISABLE_CALLBACKS = false;
				}
				else if (name == bReset_BW.getName())
				{
					if (bReset_BW)
					{
						bDISABLE_CALLBACKS = true;
						bReset_BW = false;
						cBlack = ofColor(0, 255);
						cWhite = ofColor(255, 255);
						bDISABLE_CALLBACKS = false;
					}
				}
				else if (name == position_Gui.getName())
				{
					position_Gui = glm::vec2(
						MIN(position_Gui.get().x, ofGetWidth() - 210),
						MIN(position_Gui.get().y, ofGetHeight() - 400));

					gui.setPosition(position_Gui->x, position_Gui->y);
				}
				else if (name == bReset.getName() && bReset)
				{
					bDISABLE_CALLBACKS = true;
					bReset = false;
					bDISABLE_CALLBACKS = false;

					doReset();
				}

				else if (name == bCH1.getName())
				{
					refreshGui();
				}
				else if (name == bCH2.getName())
				{
					refreshGui();
				}
			}
		}
	}

	//--------------------------------------------------------------
	void refreshGui()
	{
		// collapse groups
		
		auto& gsc = gui.getGroup(params.getName());
		gsc.minimizeAll();

		auto& ge = gsc.getGroup(params_Extra.getName());

		auto& gl = ge.getGroup(params_Letters.getName());
		auto& gbw = gl.getGroup(params_BW.getName());
		auto& gcol = gl.getGroup(params_Colors.getName());
		
		gl.minimize();
		gbw.minimize();
		gcol.minimize();
		if (ENABLE_Colors)
		{
			gbw.minimize();
			gcol.maximize();
		}
		if (ENABLE_BW)
		{
			gcol.minimize();
			gbw.maximize();
		}

		auto& gBg = ge.getGroup(params_Bg.getName());
		auto& gTr = ge.getGroup(params_Translate.getName());
		auto& gIt = ge.getGroup(params_Internal.getName());
		gBg.minimize();
		gTr.minimize();
		gIt.minimize();
		auto& gPosO = gTr.getGroup(position_Offset.getName());
		gPosO.minimize();

		auto& gPosG = gIt.getGroup(position_Gui.getName());
		gPosG.minimize();

		auto& gs = gsc.getGroup(params_Sources.getName());
		auto& gs1 = gs.getGroup(params_Channel_1.getName());
		auto& gs2 = gs.getGroup(params_Channel_2.getName());
		gs1.minimize();
		gs2.minimize();
		if (bCH1) gs1.maximize();
		if (bCH2) gs2.maximize();

		ge.minimize();
	}

	//--------------------------------------------------------------
	void loadParams(ofParameterGroup& g, string path)
	{
		ofLogNotice(__FUNCTION__) << " : " << path;
		ofXml settings;
		settings.load(path);
		ofDeserialize(settings, g);

		gui.setPosition(position_Gui->x, position_Gui->y);
	}

	//--------------------------------------------------------------
	void saveParams(ofParameterGroup& g, string path)
	{
		ofxSurfingHelpers::CheckFolder(path_GLOBAL);

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

	// scene design
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
		ofTranslate(position_Offset.get());
		//ofTranslate(-ofGetWidth() * zoom - 1, -ofGetHeight() * zoom - 1);
		//ofTranslate(position_Offset.get().x,position_Offset.get().y, -1);
		ofScale(zoom);

		int xOffset, yOffset;
		xOffset = 250;
		yOffset = 400;

		switch (layerType)
		{
		
		case LAYER_BACKGROUND_COLOR:
		{
			drawBackground();
		}
		break;

		case LAYER_BACKGROUND_IMAGE:
		{
			ofPushMatrix();
			{
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

				ofPushMatrix();
				{
					if (!bSmooth) {
						const int MAX_X = 100;
						const int MAX_Y = 200;
						const float MAX_S = 1.02f;
						const float noiseAmnt = 0.07f;
						float scale = ofMap(ofxSurfingHelpers::Bounce(), 0, 1, 1, MAX_S);
						float noise = ofMap(ofxSurfingHelpers::Noise(), -1, 1, -noiseAmnt, noiseAmnt);
						int xOffset = scale * MAX_X;
						int yOffset = scale * MAX_Y;
						ofTranslate(xOffset, 0);

						ofScale(scale + noise);
					}

					//draw
					image.draw(-xHalf, -yHalf, ofGetWidth(), ofGetHeight());
				}
				ofPopMatrix();
			}
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
			xHalf = ofGetWidth() * 0.5;
			yHalf = ofGetHeight() * 0.5;
			ofTranslate(1.5 * xHalf, yHalf);

			//faded zoom
			int frame = ofGetFrameNum() % timer2;
			float s = ofMap(frame, 0, timer2, -1.0, 1.0f);

			if (ofGetFrameNum() % timer2 == 0 && !bSmooth)
			{
				timer2 = ofRandom(T_MIN, T_MAX);
				max2 = ofRandom(Z_MIN, Z_MAX);
			}

			const float noiseAmnt = 0.07f;
			float noise = ofMap(ofxSurfingHelpers::Noise(), -1, 1, -noiseAmnt, noiseAmnt);
			ofScale(1.f + noise);

			ofScale(Z_MIN + max2 * abs(0.1 * glm::sin(s)));

			// draw
			x = -xHalf + xOffset;
			y = -yHalf + yOffset;

			ofPushMatrix();
			{
				// 1st line
				if (ENABLE_BW) ofSetColor(cBlack);
				else ofSetColor(c1);

				if (!bSmooth) {
					const float noiseAmnt = 0.7f;
					float scale = ofMap(ofxSurfingHelpers::Bounce(), 0, 1, 1, 1.08f);
					float noise = ofMap(ofxSurfingHelpers::Noise(), -1, 1, -noiseAmnt, noiseAmnt);
					float xOffset = noise * 200;
					float vOffset = noise * 200;
					ofScale(scale + noise);

					x += xOffset - 50;
					y -= vOffset - 70;
				}

				font.drawString(str1, x, y);

				float _h = font.getStringBoundingBox(str1, x, y).getHeight();

				// 2nd line
				if (ENABLE_BW) ofSetColor(cWhite);
				else ofSetColor(c2);

				if (!bSmooth) {
					float noise2 = ofMap(ofxSurfingHelpers::Noise(), 2, 0.1f, -noiseAmnt, noiseAmnt);
					y -= noise2 * 100;
				}

				font.drawString(str2, x, y + _h + 10);
			}
			ofPopMatrix();

			ofPopMatrix();
			ofPopStyle();
		}
		break;

		case LAYER_IMAGE:
		{
			ofPushMatrix();

			int xHalf, yHalf;
			xHalf = image.getWidth() * 0.5;
			yHalf = image.getHeight() * 0.5;
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
		case LAYER_VIDEO:
		{
			drawVideo();
		}
		break;
#endif
		}

		ofPopMatrix();
	}
		};

