
#include "FreqToPitch.h"


FreqToPitch::FreqToPitch(){
    meterOut.store(0.0f);

        // pitch detection
      int ticksPerBuffer = 8;
      bufferSize = BUFFER_SIZE; //pdBlock-64
      inChan  = 1;
      outChan = 0;
      sampleRate = SR;

      int midiMin = 48;
      int midiMax = 84;
      
      filterBank.setup(bufferSize, midiMin, midiMax, inChan, BANDWITH, sampleRate, 3.0);
      filterBank.setColor(ofColor::orange);
    
    
      // soundStream.setup(this, outChan, inChan, sampleRate, bufferSize, ticksPerBuffer);
    
        addInput("signal", input_signal);
        //addOutput("signal", output);
    

        addOutput("pitch0", output0 );
        addOutput("pitch1", output1 );
        addOutput("pitch2", output2 );
        addOutput("pitch3", output3 );
        addOutput("pitch4", output4 );
        addOutput("pitch5", output5 );
        addOutput("pitch6", output6 );
        addOutput("pitch7", output7 );
        addOutput("pitch8", output8 );
        addOutput("pitch9", output9 );
        addOutput("pitch10", output10 );
        addOutput("pitch11", output11 );
/*
        addOutput("energy0", outputEnergy0 );
        addOutput("energy1", outputEnergy1 );
        addOutput("energy2", outputEnergy2 );
        addOutput("energy3", outputEnergy3 );
        addOutput("energy4", outputEnergy4 );
        addOutput("energy5", outputEnergy5 );
        addOutput("energy6", outputEnergy6 );
        addOutput("energy7", outputEnergy7 );
        addOutput("energy8", outputEnergy8 );
        addOutput("energy9", outputEnergy9 );
        addOutput("energy10", outputEnergy10 );
        addOutput("energy11", outputEnergy11 );
*/
    
    updateOutputNodes();

    for (int i = 0; i < getOutputsList ().size(); i++) {
        ofLog() << "out:" <<getOutputsList ()[i];
    };

    
        if(dynamicConstruction){
            prepareToPlay(globalBufferSize, globalSampleRate);
        }
    

}

FreqToPitch::~FreqToPitch(){
    
}
float FreqToPitch::meter_output() const{
    return meterOut.load();
}

FreqToPitch::FreqToPitch(const FreqToPitch & other) : FreqToPitch(){
    std::cout<<"[pdsp] warning! amp copy constructed\n";
    pdsp::pdsp_trace();
}
 
FreqToPitch& FreqToPitch::operator=(const FreqToPitch& other){
    return *this;
    std::cout<<"[pdsp] warning! amp moved constructed\n";
    pdsp::pdsp_trace();
}



pdsp::Patchable& FreqToPitch::in_signal(){
    return in("signal");
}

 

void FreqToPitch::prepareUnit ( int expectedBufferSize, double sampleRate ) {

}

void FreqToPitch::releaseResources () {

}

pdsp::Patchable& FreqToPitch::out_pitch(const char * index){
    std::string buf("pitch");
    buf.append(index);
    const char* ccx = buf.c_str();
    ofLog () << "char:" << ccx;
    return out(ccx);
}


void FreqToPitch::process (int bufferSize) noexcept {
    

    
    int signalState;

    
    const float* signalBuffer = processInput(input_signal, signalState);
    
    
    bool user_buffer = false;
    
    //Analyze Input Buffer with ofxFilterbank
    
     filterBank.analyze((float*)signalBuffer);
    
    //(filterBank.getRightBuffer()[0]);//pdsp::f2p(*signalBuffer);
    vector<pair<int, float>> feqs = filterBank.getFrequencies();
    vector<int> actives;
    for(int i = 0; i < feqs.size(); i++) {
        int n = feqs[i].first;
        float e = feqs[i].second;
        int mod = n%12;
        
            //outputsPitch[mod] = n;
            //outputsEnergy[mod] = e;
            actives.push_back(mod);
        int freq = n; //mod + 48.0f; // makes everythuing in the same octave
            //e = 0.0f;
            switch (mod) {
                case 0: {
                    if (user_buffer) {
                            float* outputBuffer0 = getOutputBufferToFill(output0);
                            //ofx_Aeq_Zero(outputBuffer0, bufferSize);
                            outputBuffer0[0] = freq;
                    }
                    
                    setControlRateOutput(output0, freq);
                    // setControlRateOutput(outputEnergy0, *signalBuffer);
                    break;
                }
                case 1: {
                    if (user_buffer) {

                        float* outputBuffer1 = getOutputBufferToFill(output1);
                        //ofx_Aeq_Zero(outputBuffer0, bufferSize);
                        outputBuffer1[0] = freq;
                    }
                    setControlRateOutput(output1, freq);

                    //setControlRateOutput(outputEnergy1, *signalBuffer);
                    break;
                }
                case 2:
                {
                    if (user_buffer) {

                        float* outputBuffer2 = getOutputBufferToFill(output2);
                        //ofx_Aeq_Zero(outputBuffer2, bufferSize);
                        outputBuffer2[0] = (signalBuffer[0] * e);
                    }
                    setControlRateOutput(output2, freq);
                    break;
                }
                case 3: {
                    if (user_buffer) {

                      float* outputBuffer3 = getOutputBufferToFill(output3);
                    //ofx_Aeq_Zero(outputBuffer2, bufferSize);
                    outputBuffer3[0] = (signalBuffer[0] * e);
                    }
                    setControlRateOutput(output3, freq);
                    //setControlRateOutput(outputEnergy3, *signalBuffer);
                    break;
                }
                case 4: {
                    if (user_buffer) {

                    float* outputBuffer4 = getOutputBufferToFill(output4);
                    //ofx_Aeq_Zero(outputBuffer2, bufferSize);
                    outputBuffer4[0] = (signalBuffer[0] * e);
                    }
                    setControlRateOutput(output4, freq);
                    //setControlRateOutput(outputEnergy4, *signalBuffer);
                    break;
                }
                case 5: {
                    if (user_buffer) {

                    float* outputBuffer5 = getOutputBufferToFill(output5);
                    //ofx_Aeq_Zero(outputBuffer2, bufferSize);
                    outputBuffer5[0] = (signalBuffer[0] * e);
                    }
                    setControlRateOutput(output5, freq);
                    //setControlRateOutput(outputEnergy5, *signalBuffer);
                    break;
                    
                }
                case 6: {
                    if (user_buffer) {

                    float* outputBuffer6 = getOutputBufferToFill(output6);
                    //ofx_Aeq_Zero(outputBuffer2, bufferSize);
                    outputBuffer6[0] = (signalBuffer[0] * e);
                    }
                    setControlRateOutput(output6, freq);
                    //setControlRateOutput(outputEnergy6, *signalBuffer);
                    break;
                }
                case 7:{
                    if (user_buffer) {

                        float* outputBuffer7 = getOutputBufferToFill(output7);
                        //ofx_Aeq_Zero(outputBuffer2, bufferSize);
                        outputBuffer7[0] = (signalBuffer[0] * e);
                    }
                    setControlRateOutput(output7, freq);
                    //setControlRateOutput(outputEnergy7, *signalBuffer);
                    break;
                }
                case 8: {
                    if (user_buffer) {

                    float* outputBuffer8 = getOutputBufferToFill(output8);
                    //ofx_Aeq_Zero(outputBuffer2, bufferSize);
                    outputBuffer8[0] = (signalBuffer[0] * e);
                    }
                   // float* outputBuffer8 = getOutputBufferToFill(outputEnergy8);
                    //ofx_Aeq_Zero(outputBuffer8, bufferSize);
                   // outputBuffer8[0] = (signalBuffer[0] * e);
                    setControlRateOutput(output8, freq);
                    //setControlRateOutput(outputEnergy8, *signalBuffer);
                    break;
                }
                case 9: {
                    if (user_buffer) {

                        float* outputBuffer9 = getOutputBufferToFill(output9);
                        //ofx_Aeq_Zero(outputBuffer2, bufferSize);
                        outputBuffer9[0] = (signalBuffer[0] * e);
                    }
                   // float* outputBuffer7 = getOutputBufferToFill(outputEnergy9);
                    //ofx_Aeq_Zero(outputBuffer7, bufferSize);
                   // outputBuffer7[0] = (signalBuffer[0] * e);
                    setControlRateOutput(output9, freq);
                    //setControlRateOutput(outputEnergy9, *signalBuffer);
                    break;
                }
                case 10: {
                    if (user_buffer) {

                        float* outputBuffer10 = getOutputBufferToFill(output10);
                        //ofx_Aeq_Zero(outputBuffer2, bufferSize);
                        outputBuffer10[0] = (signalBuffer[0] * e);
                    }
                    //float* outputBuffer10 = getOutputBufferToFill(outputEnergy10);
                    //ofx_Aeq_Zero(outputBuffer10, bufferSize);
                    //outputBuffer10[0] = (signalBuffer[0] * e);
                    setControlRateOutput(output10, freq);
                    //setControlRateOutput(outputEnergy10, *signalBuffer);
                    break;
                }
                case 11: {
                    if (user_buffer) {

                        float* outputBuffer11 = getOutputBufferToFill(output11);
                        //ofx_Aeq_Zero(outputBuffer2, bufferSize);
                        outputBuffer11[0] = (signalBuffer[0] * e);
                    }
                    //float* outputBuffer11 = getOutputBufferToFill(outputEnergy11);
                    //ofx_Aeq_Zero(outputBuffer11, bufferSize);
                    //outputBuffer11[0] = (signalBuffer[0] * e);
                    setControlRateOutput(output11, freq);
                    //setControlRateOutput(outputEnergy11, *signalBuffer);
                    break;
                }
                default:
                    break;
            }
            
        }

        vector<int> inactives;
        for(int i = 0; i < 12; i++) {
            if(std::find(actives.begin(), actives.end(), i) != actives.end()) {
                /* v contains x */
            } else {
                inactives.push_back(i);
            }
        }
    
     

      
        //ofLog () << "actives size:" << actives.size();

    
        //ofLog () << "inactives size:" << inactives.size();
        
        //}
    
    float offPitch = -100.0f;
    
        for(int i = 0; i < inactives.size(); i++) {
            switch (inactives[i]) {
                case 0: {
                    setControlRateOutput(output0, offPitch);


                    //setControlRateOutput(outputEnergy0, 0);
                    break;
                }
                case 1: {
                    setControlRateOutput(output1, offPitch);


                    //setControlRateOutput(outputEnergy1, *signalBuffer);
                    break;
                }
                case 2:
                {
                    setControlRateOutput(output2, offPitch);


                    break;
                }
                case 3: {
                     setControlRateOutput(output3, offPitch);

                    break;
                }
                case 4: {
                    setControlRateOutput(output4, offPitch);

                    break;
                }
                case 5: {
                    setControlRateOutput(output5, offPitch);

                    break;
                    
                }
                case 6: {
                    setControlRateOutput(output6, offPitch);

                    break;
                }
                case 7:{
                    setControlRateOutput(output7, offPitch);

                    break;
                }
                case 8: {
                    setControlRateOutput(output8, offPitch);
                    break;
                }
                case 9: {
                    setControlRateOutput(output9, offPitch);

                    break;
                }
                case 10: {
                    setControlRateOutput(output10, offPitch);

                    break;
                }
                case 11: {
                    setControlRateOutput(output11, offPitch);

                    break;
                }
                default:
                    break;
            }
        }
     
        

    
    
    // setControlRateOutput(output9, 100.0f);
    //setControlRateOutput(output9, 100.0f);
    //setControlRateOutput(outputEnergy9, 50.0f);
    //setControlRateOutput(outputEnergy9, 50.0f);
    //filterBank.midiToNote(out);
      //setControlRateOutput(output1, out);
}
