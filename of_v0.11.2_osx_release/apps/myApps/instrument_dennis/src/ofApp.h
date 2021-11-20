#pragma once

#include "ofMain.h"
#include "ofxPDSP.h"
#include "ofxGui.h"
#include "AudioAnalyzerBand.h"
#include "synth.h"
#include "ofxPDSPFunctions.h"
#include "FreqToPitch.h"
#include "EnergyCalc.h"

class ofApp : public ofBaseApp{

    public:
        void setup();
        void update();
        void draw();
	void exit();

        void keyPressed(int key);
        void keyReleased(int key);
        void mouseMoved(int x, int y );
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void mouseEntered(int x, int y);
        void mouseExited(int x, int y);
        void windowResized(int w, int h);
        void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);
        void drawMeter(float value, float min, float max, int x, int y, int w, int h, int pitch);

        // pdsp modules
        pdsp::Engine   engine;
        
        pdsp::Compressor1       compressor;
        
        pdsp::Amp               channelGain;
        pdsp::Amp               delaySend;
        pdsp::Delay             delayL;
        pdsp::Delay             delayR;
        pdsp::PatchNode         fb_node;
        pdsp::PatchNode         damp_node;
        pdsp::DBtoLin           channelFader;
        pdsp::DBtoLin           sendFader;
    
        pdsp::ToGateTrigger     gateTrigger;
        pdsp::FullWavePeakDetector    peak1;
        pdsp::EnvelopeFollower  envFollowerPeak;

        ofxPanel             gui;
        ofParameterGroup     comp_gui;
        ofParameterGroup     delay_gui;

        pdsp::Parameter     d1_time_ctrl;
        pdsp::Parameter     d2_time_ctrl;
        pdsp::Parameter     d_fb_ctrl;
        pdsp::Parameter     d_damp_ctrl;
        pdsp::Parameter     gain_ctrl;
        pdsp::Parameter     send_ctrl;
    
        pdsp::Parameter        comp_threshold_ctrl;
        pdsp::Parameter        comp_attack_ctrl;
        pdsp::Parameter        comp_release_ctrl;
        ofParameter<float>  comp_meter;
    
            

        AudioAnalyzerBand   band;


        pdsp::Scope                 scope;
        pdsp::ToGateTrigger         trigger;
    
    
        FreqToPitch              freqToPitch;
    	EnergyCalc energyCalc;
 
        PolySynth                   synth;
    
        int numberOfVoices;

        
        bool DEBUG_MODE;


};
