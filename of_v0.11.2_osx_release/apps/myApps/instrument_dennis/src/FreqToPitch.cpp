
#include "FreqToPitch.h"


FreqToPitch::FreqToPitch(){
    
        // pitch detection
      int ticksPerBuffer = 8;
      bufferSize = BUFFER_SIZE; //pdBlock-64
      inChan  = 1;
      outChan = 0;
      sampleRate = SR;

      int midiMin = 21;
      int midiMax = 108;
      
      filterBank.setup(bufferSize, midiMin, midiMax, inChan, BANDWITH, sampleRate, 3.0);
      filterBank.setColor(ofColor::orange);

      // soundStream.setup(this, outChan, inChan, sampleRate, bufferSize, ticksPerBuffer);
    
        addInput("signal", input_signal);
        addOutput("signal", output);
        updateOutputNodes();
    
    
        meter.store(0.0f);
        meterOut.store(0.0f);
    
        
    
    
        if(dynamicConstruction){
                prepareToPlay(globalBufferSize, globalSampleRate);
        }
}

FreqToPitch::~FreqToPitch(){
    
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


float FreqToPitch::meter_output() const{
    return meterOut.load();
}


pdsp::Patchable& FreqToPitch::in_signal(){
    return in("signal");
}

pdsp::Patchable& FreqToPitch::out_signal(){
    return out("signal");
}
 

void FreqToPitch::prepareUnit ( int expectedBufferSize, double sampleRate ) {

}

void FreqToPitch::releaseResources () {

}

void FreqToPitch::process (int bufferSize) noexcept {
    
    int signalState;

    
    const float* signalBuffer = processInput(input_signal, signalState);
    
    
    //Analyze Input Buffer with ofxFilterbank
    
    
     filterBank.analyze((float*)signalBuffer);
    

    
    //(filterBank.getRightBuffer()[0]);//pdsp::f2p(*signalBuffer);
    float out = filterBank.getFrequency();
    ofLog () << out;

      setControlRateOutput(output, out);
      meterOut.store(out);

        /*
    if ( modBuffer[0] == 0.0f && modState != pdsp::AudioRate ){

        setOutputToZero(output);
        meterOut.store(0.0f);
             
    }else{
           
        int signalState;
        const float* signalBuffer = processInput(input_signal, signalState);

        int switcher = signalState + modState*4;

                //process audio rate
        switch ( switcher & 42 ) {
        case 0:  // signal control rate, mod control rate
            {
                float out = modBuffer[0]*signalBuffer[0];
                setControlRateOutput(output, out);
                meterOut.store(out);
            }
                break;
        case 2:  // signal audio rate, mod control rate
            {
                float* outputBuffer = getOutputBufferToFill(output);
                ofx_Aeq_BmulS(outputBuffer, signalBuffer, modBuffer[0], bufferSize);
                meterOut.store(outputBuffer[0]);
            }
                break;
        case 8:  // signal control rate, mod audio rate
            {
                float* outputBuffer = getOutputBufferToFill(output);
                ofx_Aeq_BmulS(outputBuffer, modBuffer, signalBuffer[0], bufferSize);
                meterOut.store(outputBuffer[0]);
            }
                break;
        case 10: // signal audio rate, mod audio rate
            {
                float* outputBuffer = getOutputBufferToFill(output);
                ofx_Aeq_BmulC(outputBuffer, signalBuffer, modBuffer, bufferSize);
                meterOut.store(outputBuffer[0]);
            }
        default: break;
        }

        
        
    }
         */
    
}
