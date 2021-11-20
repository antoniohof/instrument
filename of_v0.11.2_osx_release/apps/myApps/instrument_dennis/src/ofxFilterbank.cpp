/*
 * Copyright (c) 2015 Leo Zimmerman <leozimmerman@gmail.com>
 */

#include "ofxFilterbank.h"
#include <math.h>
#include <numeric>
#include <iostream>
#include <cmath>
#include "glm/mat4x4.hpp"
#include "ofMathConstants.h"
#include "ofConstants.h"

//--------------------------------------------------------------
void ofxFilterbank::setup(int iBufferSize, int iMidiMin, int iMidiMax, int iChans, float iBw, int iSR, float iGain){

    bufferSize = iBufferSize;
    midiMaxVar = midiMax = iMidiMax;
    midiMinVar = midiMin = iMidiMin;
    channels = iChans;
    bw = iBw;
    sampleRate = iSR;
    gain = iGain;

    pitchDev = 0.0;
    maskAmnt = 0.5f;
    smoothAmnt = 0.5;
    estimateMax = 5.0;
    higherValue = 0.0f;

    treshold = 0.018;
    showAll = true;

    left.assign(bufferSize, 0.0);
	right.assign(bufferSize, 0.0);


    energies.assign(midiMax, 0.0);
    smth_energies.assign(midiMax, 0.0);
    log_smth_energies.assign(midiMax, 0.0);

   fdata=(RESONDATA***)malloc(sizeof(RESONDATA**)*channels);
   for (int i=0; i<channels; i++) {
         fdata[i]=(RESONDATA**)malloc(sizeof(RESONDATA*)*midiMax);
         for (int n=midiMin; n<midiMax; n++){
            double exp = (double)(n-69+pitchDev)/12;
            double frec = pow (2., exp)*440;
            fdata[i][n]=(RESONDATA*)malloc(sizeof(RESONDATA));
            set_reson(frec, bw,fdata[i][n], sampleRate, gain);
            set_reson(frec, bw,fdata[i][n], sampleRate, gain);
        }
    }
    color.set(255);
}
//--------------------------------------------------------------
void ofxFilterbank::setPitchDev(){
    for (int i=0; i<channels; i++) {
        // fdata[i]=(RESONDATA**)malloc(sizeof(RESONDATA*)*midiMax);
         for (int n=midiMin; n<midiMax; n++){
            double exp = (double)(n-69+pitchDev)/12;
            double frec = pow (2., exp)*440;
          //  fdata[i][n]=(RESONDATA*)malloc(sizeof(RESONDATA));
            set_reson(frec, bw,fdata[i][n], sampleRate, gain);
            set_reson(frec, bw,fdata[i][n], sampleRate, gain);
        }
    }
}
//--------------------------------------------------------------
void ofxFilterbank::analyze(float * iBuffer){
    //Reset energies

    for (int n=midiMinVar; n<midiMaxVar; n++){
            energies[n] = 0.0;
    }
     //Process
    for (int i = 0; i < left.size(); i++){
        left[i] = iBuffer[i*channels    ] ;
        right[i]= iBuffer[i*channels + 1];

        for (int n=midiMinVar; n<midiMaxVar;n++){
            float lOutsample = 0.0;
            float rOutsample = 0.0;

            lOutsample = reson(left[i], fdata[0][n]);
            energies[n]  += lOutsample*lOutsample;
            if (channels>1){
                rOutsample = reson(right[i], fdata[1][n]);
                energies[n] += rOutsample*rOutsample;
            }
        }
	 }

	 //Smoothing...

    for (int n=midiMaxVar-1; n>=midiMinVar;n--){
        energies[n] /= (left.size()*channels);
        energies[n] = sqrt(energies[n]);
        smth_energies[n] *= smoothAmnt;
        smth_energies[n] += (1-smoothAmnt) * energies[n];
        ///mask
        if(smth_energies[n]>treshold  && n>midiMinVar+1){
            if (smth_energies[n]>smth_energies[n-1])
                smth_energies[n-1] -= smth_energies[n]*maskAmnt;
            else
                smth_energies[n] -= smth_energies[n-1]*maskAmnt;
    
            if (n>11 /*&& smth_energies[n]>smth_energies[n-12]*0.35*/ )///*
                smth_energies[n] -= smth_energies[n-12]*maskAmnt;
        }
    }

}
//--------------------------------------------------------------
void ofxFilterbank::exit(){
    
    for (int i=0; i<channels; i++) {
        for (int n=midiMin; n<midiMax; n++){
            if (fdata[i][n]!=NULL ) free (fdata[i][n]);
        }
        free (fdata[i]);
    }
    free (fdata);
    
}
//--------------------------------------------------------------
void ofxFilterbank::draw(int w, int h){
    ofSetColor(255);
    ofDrawBitmapString("FB Analysis", 4, 18);
    ofRect(0, 0, w, h);
    float step = (float) w / (midiMaxVar - midiMinVar);
    ofSetLineWidth(3);
    for(int n=midiMinVar; n<midiMaxVar; n++){
        log_smth_energies[n] = LIN2dB (smth_energies[n]);
      
       float ener = ofMap (log_smth_energies[n], -45.0, LIN2dB(estimateMax), 0.0, h, true);
        if(smth_energies[n] > treshold){
            ofSetColor(color);
            ofDrawBitmapString(midiToNote(n), step*(n-midiMinVar), h-ener);
            ofLine(step*(n-midiMinVar), h, step*(n-midiMinVar), h-ener );
            
        }
        else if (showAll){
            ofSetColor(85);
            ofLine(step*(n-midiMinVar), h, step*(n-midiMinVar), h-ener );
        }
    }

    ofSetColor(80);
    float logTresh = LIN2dB(treshold);
    float tres = ofMap(logTresh, -45.0, LIN2dB(estimateMax), 0.0, h);
    ofSetLineWidth(1);
    ofLine(0,h-tres, w, h-tres);
    ofDrawBitmapString("Treshold" , w-80, h-tres);
    
}

float ofxFilterbank::getAverageEnergy() {
    vector<float> energies;

    for(int n=midiMinVar; n<midiMaxVar; n++){
        // log_smth_energies[n] = LIN2dB (smth_energies[n]);
      
       // float ener = ofMap (log_smth_energies[n], -45.0, LIN2dB(estimateMax), 0.0, h, true);
        float energy = smth_energies[n];

        energies.push_back((float)energy);

    }
    float e = average(energies);
    return e;
}

pair<float, float> ofxFilterbank::getFrequency(){
    pair<float, float> pairV;
    float strongEnergy = 0.0f;
    vector<float> values;
    // float step = (float) w / (midiMaxVar - midiMinVar);
    for(int n=midiMinVar; n<midiMaxVar; n++){
        // log_smth_energies[n] = LIN2dB (smth_energies[n]);
      
       // float ener = ofMap (log_smth_energies[n], -45.0, LIN2dB(estimateMax), 0.0, h, true);
        float energy = smth_energies[n];

        if(energy > treshold){
            values.push_back(float(n));
             if (energy > smth_energies[higherValue]) {
                  higherValue = n;
                 strongEnergy = energy;
              }
        }

    }
    //ofLog () << "higher: " << midiToNote(higherValue);
    //ofLog () << smth_energies[higherValue];

    //float logTresh = LIN2dB(treshold);
    //float tres = ofMap(logTresh, -45.0, LIN2dB(estimateMax), 0.0, h);
    float octave = 12.0f;
    pairV = std::make_pair(higherValue,(float)strongEnergy);

    return pairV;//average(values) - 12.0f;
}

vector<pair<int, float>> ofxFilterbank::getFrequencies(){
        
    vector<pair<int, float>> values;
    // float step = (float) w / (midiMaxVar - midiMinVar);
    for(int n=midiMinVar; n<midiMaxVar; n++){
        // log_smth_energies[n] = LIN2dB (smth_energies[n]);
      
       // float ener = ofMap (log_smth_energies[n], -45.0, LIN2dB(estimateMax), 0.0, h, true);
        float energy = smth_energies[n];
        if(!isinf(energy) && !isnan(energy) && energy > treshold){
            pair<int, float> p;
            int pitch = n;
            p = std::make_pair(pitch,(float)energy);
            values.push_back(p);
        }

    }

    //float logTresh = LIN2dB(treshold);
    //float tres = ofMap(logTresh, -45.0, LIN2dB(estimateMax), 0.0, h);
    return values;//average(values) - 12.0f;
}


float ofxFilterbank::average(vector<float> v){
    if(v.empty()){
        return 0;
    }

    //auto const count = static_cast<float>(v.size());
     return accumulate( v.begin(), v.end(), 0.0)/v.size();
    //return reduce(v.begin(), v.end()) / count;
}

float noteToFreq(int note) {
    float a = 440; //frequency of A (coomon value is 440Hz)
    return (a / 32) * pow(2, ((note - 9) / 12.0));
}

float ofxFilterbank::noteToFreq(float note) {
    // uma oitava e 12
    float a = 440.0f; // frequency of A (coomon value is 440Hz) //
    return (a / 32.0f) * pow(2, ((note - 9.0f) / 12.0f));

    
    //result:=base_a4*power(2,(n-57)/12)

}

//--------------------------------------------------------------
string ofxFilterbank::midiToNote(int midi){
    string noteName;
    int mod = midi%12;
    switch (mod){
        case 0: noteName = "C";
                break;
        case 1: noteName = "C#";
                break;
        case 2: noteName = "D";
                break;
        case 3: noteName = "D#";
                break;
        case 4: noteName = "E";
                break;
        case 5: noteName = "F";
                break;
        case 6: noteName = "F#";
                break;
        case 7: noteName = "G";
                break;
        case 8: noteName = "G#";
                break;
        case 9: noteName = "A";
                break;
        case 10: noteName = "Bb";
                break;
        case 11: noteName = "B";
                break;
        default:
                break;

    }
    return (noteName);

}
