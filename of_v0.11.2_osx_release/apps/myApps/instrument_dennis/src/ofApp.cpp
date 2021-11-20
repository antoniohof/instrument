#include "ofApp.h"
#include "ofxPDSPFunctions.h"

// before looking at this check out the basics examples

// audio input example, and UI example
// at the moment on some systems the input comes in distorted,
// this may be a problem of audio input underruns on some systems
// as on OSX and on Linux (with JACK) i've had no problems

//--------------------------------------------------------------
void ofApp::setup(){
    //-------------------GRAPHIC SETUP--------------
    ofDisableAntiAliasing();
    ofBackground(0);
    ofSetVerticalSync(false);
    ofSetFrameRate(30);
    ofSetColor(ofColor(0,100,100));
    ofNoFill();
    ofSetLineWidth(2.0f);
    
    DEBUG_MODE = false;
    //-------------------------PATCHING--------------
    engine.setChannels(1, 2); // input + output channels
    
    float gain = 36.00f;
    // anlayzer
    // patching the scope
    engine.audio_in(0)  >> scope >> engine.blackhole();
    
    // decomment for a longer scope time window
    //scope.set(512*16);
    energyCalc.setup(&freqToPitch.filterBank);

    gui.loadFromFile("analyzer.xml");
    
    numberOfVoices = 12; // 12 notes
    
    
    synth.setup(numberOfVoices);
   // 0.1f >> gateTrigger.in_threshold();
    // engine.audio_in(0) >> dB(12.0f) >> peak1 >> envFollowerPeak >> gateTrigger.in_signal() >> synth.voices[0].in("trig");
    
    // original
    //engine.audio_in(0) >> band.bandGain >> trigger.in("signal");
    //float t = 0.008f;
    //t >> trigger.in("threshold");

    // trigger.out("trig") >> synth.voices[4].in("trig");

    //engine.audio_in(0)  >> peak1 >> envFollowerPeak >> synth.voices[0].in("trig");

    
    for(int i=0; i<numberOfVoices; i++){


        std::string s = std::to_string(i);
        char const *pchar = s.c_str();  //use- char const* as target type


        engine.audio_in(0) >> band.bandGain >> freqToPitch >> engine.blackhole();
        engine.audio_in(0) >> band.bandGain >> energyCalc >> engine.blackhole();

        engine.audio_in(0) >> freqToPitch.out_pitch(pchar) >> synth.voices[i].in("pitch");

            
            
        //engine.audio_in(0) >> energyCalc.out_energy(pchar2) >> synth.voices[i].in("trig");
        
        // testar amanha ou band.RMS aqui
        //band.difference >> trigger.in("signal");
        /*
        engine.audio_in(0) >> band.bandGain >> trigger.in("signal");
        float t = 0.0005f;
        t >> trigger.in("threshold");

        trigger.out("trig") >> energyCalc.out_energy(pchar) >> synth.voices[i].in("trig");
        * */
        
        engine.audio_in(0) >> energyCalc.out_energy(pchar) >> synth.voices[i].in("trig");


    }
     

    
    //engine.audio_in(0) >> freqToPitch >> synth.voices[i].in("pitch");
    synth.ch(0) >> engine.audio_out(0);
    synth.ch(1) >> engine.audio_out(1);
     
    
    

    
    synth.ch(1) >> compressor >> channelGain         >> engine.audio_out(0);
                                        channelGain         >> engine.audio_out(1);
                          compressor >> delaySend >> delayL >> engine.audio_out(0);
                                        delaySend >> delayR >> engine.audio_out(1);
    
     d1_time_ctrl >> delayL.in_time();
     d2_time_ctrl >> delayR.in_time();
    
     d_fb_ctrl >> fb_node >> delayL.in_feedback();
                  fb_node >> delayR.in_feedback();
     d_damp_ctrl >> damp_node >> delayL.in_damping();
                    damp_node >> delayR.in_damping();

     gain_ctrl >> channelFader >> channelGain.in_mod();
     send_ctrl >> sendFader >> delaySend.in_mod();

     comp_threshold_ctrl >> compressor.in_threshold();
     comp_attack_ctrl    >> compressor.in_attack();
     comp_release_ctrl   >> compressor.in_release();
     


    cout<<"finished patching\n";
    
    //----------------------AUDIO SETUP-------------
    
    // start your audio engines!
    engine.listDevices();
    
    engine.setDeviceID(2);
    
    // if listDevices() lists different devices for in and out you need to make something like this
    //engine.setInputDeviceID(0);
    //engine.setOutputDeviceID(1); // a valid output device is required
    
    engine.setup( 48000, 2048, 3);
    
    // GUI -----------------------------------

    // you can use set() to set ofxPDSPValue like ofParameter

   gui.setup("channel strip");

   comp_gui.setName("compressor parameters");
   comp_gui.add( comp_threshold_ctrl.set( "threshold", -20.0f, -50.0f, 0.0f ) );
   comp_gui.add( comp_meter.set("GR meter", 0.0f, 0.0f, -25.0f) );
   comp_gui.add( comp_attack_ctrl.set( "attack (ms)", 10.0f, 1.0f, 60.0f ) );
   comp_gui.add( comp_release_ctrl.set( "release (ms)", 50.0f, 10.0f, 250.0f ) );
   gui.add(comp_gui);

   delay_gui.setName("delays parameters");
   delay_gui.add( send_ctrl.set( "send", -30.0f, -60.0f, 0.0f ) );
   delay_gui.add( d1_time_ctrl.set( "time L (ms)", 200.0f, 5.0f, 800.0f ) );
   delay_gui.add( d2_time_ctrl.set( "time R (ms)", 300.0f, 5.0f, 800.0f ) );
   delay_gui.add( d_fb_ctrl.set( "feedback", 0.5f, 0.0f, 1.0f ) );
   delay_gui.add( d_damp_ctrl.set( "damping", 0.5f, 0.0f, 1.0f ) );
   gui.add(delay_gui);
   
   gui.add(gain_ctrl.set( "channel volume", 0.0f, -30.0f, 12.0f ));
    // setting up analyzer
    
    gui.add( synth.ui );


        
    string name = "analyser ";
  
    band.setup ( engine, name );
  
    gui.add( band.ui );


    gui.setPosition(15, 20);

}

//--------------------------------------------------------------
void ofApp::update(){
    if (DEBUG_MODE) {
    // we use comp_meter to report the gain reduction in dB
    comp_meter.set(compressor.meter_GR());
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    if (DEBUG_MODE) {
    // draw GUI
    gui.draw();
    
    // draws some bars
    ofSetColor(255);
    ofFill();

    ofTranslate(    gui.getPosition().x + 20 + gui.getWidth(),
                gui.getPosition().y );
    ofSetColor(255);
    string name = "band ";
    ofDrawBitmapString( name, 0, 20 );
    ofDrawBitmapString( "rms", 0, 45 );
    ofDrawBitmapString( "peak", 0, 75 );
    ofDrawBitmapString( "onset", 0, 105 );
    
    ofDrawRectangle( 40, 30, 180*band.meter_rms(), 20);
    ofDrawRectangle( 40, 60, 180*band.meter_peak(), 20);
    
    int white = 255 * band.meter_onset();
    white = (white > 255) ? 255 : white;
     
    ofSetColor(white);
    ofDrawRectangle( 40, 90, 180, 20);
    
    ofTranslate(0, 120);
    

    // draws the scope
    ofSetColor(255);
    ofDrawBitmapString( "input scope", 0, 35 );
    scope.draw( 0, 50, 220, 100);
    
     ofPushStyle();
     ofPushMatrix();
     ofTranslate (100,250,0);
     freqToPitch.filterBank.draw(800,400);

     ofPopMatrix();
     ofPopStyle();
    
    ofSetColor(255);

    // draw pitch meters
       int xBase = 10;
       ofDrawBitmapString("osc pitches", xBase, 26);
       for(int i=0; i<12; ++i){
           drawMeter( synth.voices[i].meter_pitch(), 00.f, 120.f, xBase, 30, 20, 200, synth.voices[i].meter_pitch());
           xBase+=40;
       }
       // draw mod envelope meters
       xBase += 20;
       ofDrawBitmapString("mod envs", xBase, 26);
       for(int i=0; i<12; ++i){
           drawMeter( synth.voices[i].meter_mod_env(), 0.05f, 1.0f, xBase, 30, 20, 200, synth.voices[i].meter_pitch());
           xBase+=40;
       }
   }
	std::stringstream strm;
	strm << "fps: " << ofGetFrameRate();
	ofSetWindowTitle(strm.str());
}


void ofApp::drawMeter(float value, float min, float max, int x, int y, int w, int h, int pitch){
    
    float range = max - min;
    int levelY = ( (1.0f - ((value - min) / range) ) * static_cast<float>(h) ) + y;
    ofSetColor(255,255,255);

    ofDrawRectangle(x, y, w, h);
    
    string note = freqToPitch.filterBank.midiToNote(pitch);
    ofSetColor(0,255,0);
    ofDrawBitmapString(note, x, levelY);

    if(value > min && value<max ) ofDrawLine(x, levelY, x+w, levelY);
        
}

void ofApp::exit(){
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    DEBUG_MODE = !DEBUG_MODE;
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

