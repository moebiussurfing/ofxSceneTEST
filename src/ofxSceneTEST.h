#pragma once

#include "ofMain.h"

#include "ofxGui.h"

//#define INCLUDE_HAP
#ifdef INCLUDE_HAP
#include "ofxHapPlayer.h"
#endif

class ofxSceneTEST : public ofBaseApp
{

public:

    //video hap
#ifdef INCLUDE_HAP
    ofxHapPlayer player;
#endif

    //gui
    ofxPanel gui;
    ofParameter<glm::vec2> Gui_Position;

    //layers:

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

    ofParameterGroup params_Colors{ "COLORS" };
    ofParameter<ofColor> c1, c2;
    ofParameter<bool> ENABLE_randomizeColors;
    ofParameter<bool> ENABLE_Colors;

    ofParameterGroup params_BW{ "BW" };
    ofParameter<ofColor> cBlack, cWhite;
    ofParameter<bool> ENABLE_BW;
    ofParameter<bool> RESET_BW;

    ofParameterGroup params_SOURCES{ "SOURCES" };

    ofParameterGroup params_Channel1{ "CHANNEL 1" };
    ofParameter<bool> ENABLE_Background_1;
    ofParameter<bool> ENABLE_Letters_1;
    ofParameter<bool> ENABLE_Image_1;
#ifdef INCLUDE_HAP
    ofParameter<bool> ENABLE_Video_1;
#endif

    ofParameterGroup params_Channel2{ "CHANNEL 2" };
    ofParameter<bool> ENABLE_Background_2;
    ofParameter<bool> ENABLE_Letters_2;
    ofParameter<bool> ENABLE_Image_2;
#ifdef INCLUDE_HAP
    ofParameter<bool> ENABLE_Video_2;
#endif

    //-

    string path_Params;
    string GLOBAL_Path;

    bool DISABLE_Callbacks = false;

    ofParameter<bool> SHOW_Gui{ "GUI", true };

    void setGuiVisible(bool b)
    {
        SHOW_Gui = b;
    }
    bool getGuiVisible()
    {
        return SHOW_Gui.get();
    }

    //--------------------------------------------------------------
    ofxSceneTEST()
    {
        //DISABLE_Callbacks = true;

        ofSetLogLevel("ofxSceneTEST", OF_LOG_NOTICE);
        //ofSetLogLevel("ofxSceneTEST", OF_LOG_VERBOSE);

        //path for settings
        GLOBAL_Path = "ofxSceneTEST/";

        //out of global folder
        path_Params = GLOBAL_Path + "scene.xml";

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

        //exit();
    }

    //--------------------------------------------------------------
    void setup()
    {
        ofLogVerbose("ofxSceneTEST") << "called setup";

        //-

        //theme
        string str = GLOBAL_Path + "fonts/overpass-mono-bold.otf";
        ofxGuiSetFont(str, 9);
        ofxGuiSetDefaultHeight(20);
        ofxGuiSetBorderColor(32);
        ofxGuiSetFillColor(ofColor(48));
        ofxGuiSetTextColor(ofColor::white);
        ofxGuiSetHeaderColor(ofColor(24));

        //-

        //layers

        //font
        string pathFont;
        pathFont = "fonts/Sequel100Black116.ttf"; size = 80;
        //pathFont = "fonts/DSPTRLSuper.ttf"; size = 90;
        //pathFont = "fonts/overpass-mono-bold.otf";size = 100;
        font.load(GLOBAL_Path + pathFont, size, true, true);
        font.setLineHeight(size + 5);

        //background
        string pathBg;
        pathBg = "background1.jpg";
        //pathBg = "background3.jpg";
        myBackground.load(GLOBAL_Path + pathBg);

        //image
        string pathImg = GLOBAL_Path + "background3.jpg";;
        image.load(pathImg);

        //video hap
#ifdef INCLUDE_HAP
        loadVideo("movies/SampleHap.mov");
        player.setLoopState(OF_LOOP_NORMAL);
#endif

        //-

        ENABLE_Colors.set("MODE COLORS", true);
        ENABLE_randomizeColors.set("RANDOMIZER", true);
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


        ENABLE_Background_1.set("BACKGROUND", true);
        ENABLE_Letters_1.set("LETTERS", true);
        ENABLE_Image_1.set("IMAGE", false);
        params_Channel1.add(ENABLE_Background_1);
        params_Channel1.add(ENABLE_Letters_1);
        params_Channel1.add(ENABLE_Image_1);
#ifdef INCLUDE_HAP
        ENABLE_Video_1.set("VIDEO", false);
        params_Channel1.add(ENABLE_Video_1);
#endif
        params_SOURCES.add(params_Channel1);

        ENABLE_Background_2.set("BACKGROUND", true);
        ENABLE_Letters_2.set("LETTERS", true);
        ENABLE_Image_2.set("IMAGE", false);
        params_Channel2.add(ENABLE_Background_2);
        params_Channel2.add(ENABLE_Letters_2);
        params_Channel2.add(ENABLE_Image_2);
#ifdef INCLUDE_HAP
        ENABLE_Video_2.set("VIDEO", false);
        params_Channel2.add(ENABLE_Video_2);
#endif
        params_SOURCES.add(params_Channel2);

        //all groups
        params.add(ENABLE_Colors);
        params.add(ENABLE_BW);
        params.add(params_Colors);
        params.add(params_BW);
        params.add(params_SOURCES);

        ofAddListener(params.parameterChangedE(), this, &ofxSceneTEST::Changed_params);

        //-

        //gui
        gui.setup("ofxSceneTEST");
        gui.add(params);

        //default gui pos
        Gui_Position = glm::vec2(ofGetWindowWidth() - 210, 5);
        gui.setPosition(Gui_Position->x, Gui_Position->y);

        //collapse
        gui.getGroup("SCENE").minimize();

        //--

        //startup

        //settings
        loadParams(params, path_Params);
        //could crash if group vars structure, or name params are modified

        //-

        //auto call update and draw linked to ofApp
        ofAddListener(ofEvents().update, this, &ofxSceneTEST::update);
        ofAddListener(ofEvents().draw, this, &ofxSceneTEST::draw);
    }

    //--------------------------------------------------------------
    void update(ofEventArgs & args)
    {
        ofLogVerbose("ofxSceneTEST") << "called update";
    }

    //--------------------------------------------------------------
    void draw(ofEventArgs & args)
    {
        if (SHOW_Gui)
        {
            ofLogVerbose("ofxSceneTEST") << "called draw";

            //in text mode
            if (ENABLE_Letters_1 || ENABLE_Letters_2)
            {
                //debug the 2 original colors (without blending)
                //draw 2 circles filled by colors 1 and 2
                ofPushStyle();
                ofFill();
                int r = 25;
                int x, y;
                x = Gui_Position->x - 2 * r - 10;
                y = Gui_Position->y + 2 * r;

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

                ofDrawCircle(x, y + 2 * r + 10, r);

                ofPopStyle();
            }

            //--

            //scene
            gui.draw();
        }
    }

    //--------------------------------------------------------------
    void drawChannel1()
    {
        //background
        if (ENABLE_Background_1)
        {
            drawLayer(LAYER_BACKGROUND);
        }

        //image
        if (ENABLE_Image_1)
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
        //text
        if (ENABLE_Letters_1)
        {
            drawLayer(LAYER_LETTERS);
        }
    }

    //--------------------------------------------------------------
    void drawChannel2()
    {
        //background
        if (ENABLE_Background_2)
        {
            drawLayer(LAYER_BACKGROUND);
        }

        //image
        if (ENABLE_Image_2)
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
        //text
        if (ENABLE_Letters_2)
        {
            drawLayer(LAYER_LETTERS);
        }
    }

    //--------------------------------------------------------------
    void setModeColorsToggle()
    {
        DISABLE_Callbacks = true;//too avoid crashes
        ENABLE_BW = !ENABLE_BW;
        ENABLE_BW = !ENABLE_Colors;
        DISABLE_Callbacks = false;
        updateGui();
    }

    //--------------------------------------------------------------
    void setModeRandomizeToggle()
    {
        ENABLE_randomizeColors = !ENABLE_randomizeColors;
    }

    //--------------------------------------------------------------
    void Changed_params(ofAbstractParameter &e)
    {
        string name = e.getName();

        //exclude debugs
        if (name != "exclude"
            && name != "exclude"
            && name != "RANDOMIZER"
            && (!DISABLE_Callbacks)//disable callback
            )
        {
            ofLogNotice("ofxSceneTEST") << "Changed_params: " << name << " : " << e;

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

            //-

            ////workflow
            //if (!ENABLE_BW && !ENABLE_Colors)
            //	ENABLE_Colors = true;//default
            //updateGui();
        }
    }

    //--------------------------------------------------------------
    void updateGui()
    {
        //collapse groups
        auto &g0 = gui.getGroup("SCENE");//1st level
        auto &g11 = g0.getGroup("BW");//2nd level
        auto &g12 = g0.getGroup("COLORS");//2nd level
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
        ofLogNotice("ofxSceneTEST") << "loadParams: " << path;
        ofXml settings;
        settings.load(path);
        ofDeserialize(settings, g);

        gui.setPosition(Gui_Position->x, Gui_Position->y);
    }

    //--------------------------------------------------------------
    void saveParams(ofParameterGroup &g, string path)
    {
        ofLogNotice("ofxSceneTEST") << "saveParams: " << path;
        ofXml settings;
        ofSerialize(settings, g);
        settings.save(path);
    }



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

    //scene design
    //--------------------------------------------------------------
    enum LAYER_Type
    {
        LAYER_BACKGROUND,
        LAYER_LETTERS,
        LAYER_IMAGE,
        LAYER_VIDEO
    };

    //--------------------------------------------------------------
    void drawLayer(int layerType)
    {
        switch (layerType)
        {
                //-----------------
            case LAYER_BACKGROUND:
            {
                ofPushMatrix();

                int xHalf, yHalf;
                xHalf = myBackground.getWidth();
                yHalf = myBackground.getHeight();
                ofTranslate(xHalf, yHalf);

                //fade zoom
                int timer = 600;
                int frame = ofGetFrameNum() % timer;
                float s = ofMap(frame, 0, timer, 1.0, 1.25f);
                ofScale(s);
                //draw
                myBackground.draw(-xHalf, -yHalf, ofGetWidth(), ofGetHeight());

                ofPopMatrix();
            }
                break;

                //-----------------
            case LAYER_LETTERS:
            {
                string str1 = "TEST\nofxFbo\nMixerBlend";
                string str2 = "FBO\nMIXER\nBLENDER";

                //timer randomize colors
                if (ENABLE_randomizeColors)
                {
                    int timer2 = 120;
                    int frame2 = ofGetFrameNum() % timer2;
                    if (frame2 == 0)//randomize the 2 colors every timer2 (120) frames
                    {
                        c1 = ofColor(ofRandom(255), ofRandom(255), ofRandom(255), 255);
                        c2 = ofColor(ofRandom(255), ofRandom(255), ofRandom(255), 255);
                    }
                }

                //two text lines
                ofPushStyle();
                ofPushMatrix();

                int xHalf, yHalf;
                xHalf = ofGetWidth()*0.5;
                yHalf = ofGetHeight()*0.5;
                ofTranslate(xHalf, yHalf);

                //fade zoom
                int timer = 60;
                int frame = ofGetFrameNum() % timer;
                float s = ofMap(frame, 0, timer, 1.0, 0.95f);
                ofScale(s);

                //draw
                x = -xHalf + 250;
                y = -yHalf + 250;

                //1st line
                if (ENABLE_BW)
                    ofSetColor(cBlack);
                else
                    ofSetColor(c1);

                font.drawString(str1, x, y);

                //2nd line
                if (ENABLE_BW)
                    ofSetColor(cWhite);
                else
                    ofSetColor(c2);

                font.drawString(str2, x, y + 3 * size + 10);

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

                //fade zoom
                int timer = 200;
                int frame = ofGetFrameNum() % timer;
                float s = ofMap(frame, 0, timer, 1.0, 1.2f);
                ofScale(s);

                //draw
                image.draw(-xHalf, -yHalf, ofGetWidth(), ofGetHeight());

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
    }
};

