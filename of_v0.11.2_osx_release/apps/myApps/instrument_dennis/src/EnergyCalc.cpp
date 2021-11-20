
#include "EnergyCalc.h"

#include "ofxFilterbank.h"

EnergyCalc::EnergyCalc(){
    
        addInput("signal", input_signal);
        //addOutput("signal", output);
    
    

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

    
        updateOutputNodes();
    
    
        meter.store(0.0f);
        meterOut.store(0.0f);
    
        
        if(dynamicConstruction){
                prepareToPlay(globalBufferSize, globalSampleRate);
        }
}

EnergyCalc::~EnergyCalc(){
    
}

EnergyCalc::EnergyCalc(const EnergyCalc & other) : EnergyCalc(){
    std::cout<<"[pdsp] warning! amp copy constructed\n";
    pdsp::pdsp_trace();
}
 
EnergyCalc& EnergyCalc::operator=(const EnergyCalc& other){
    return *this;
    std::cout<<"[pdsp] warning! amp moved constructed\n";
    pdsp::pdsp_trace();
}


float EnergyCalc::meter_output() const{
    return meterOut.load();
}


pdsp::Patchable& EnergyCalc::in_signal(){
    return in("signal");
}

pdsp::Patchable& EnergyCalc::out_energy(const char * index){
    std::string buf("energy");
    buf.append(index);
    const char* ccx = buf.c_str();
    return out(ccx);
}

void EnergyCalc::prepareUnit ( int expectedBufferSize, double sampleRate ) {
    
}

void EnergyCalc::setup ( ofxFilterbank * instance ) {
    filterBank = instance;
}

void EnergyCalc::releaseResources () {

}


void EnergyCalc::process (int bufferSize) noexcept {
    

    
    int signalState;

    
    const float* signalBuffer = processInput(input_signal, signalState);
    
    
    //(filterBank.getRightBuffer()[0]);//pdsp::f2p(*signalBuffer);
    vector<pair<int, float>> feqs = filterBank->getFrequencies();
    vector<int> actives;
    for(int i = 0; i < feqs.size(); i++) {
        int n = feqs[i].first;
        float e = feqs[i].second * 1.0f;
        int mod = n%12;

            //outputsPitch[mod] = n;
            //outputsEnergy[mod] = e;
            actives.push_back(mod);
            //e = 0.0f;
            switch (mod) {
                case 0: {
                    float* outputBuffer0 = getOutputBufferToFill(outputEnergy0);
                    //ofx_Aeq_Zero(outputBuffer0, bufferSize);
                    outputBuffer0[0] = (signalBuffer[0] * e);
                    
                    // setControlRateOutput(outputEnergy0, *signalBuffer);
                    break;
                }
                case 1: {
                    float* outputBuffer1 = getOutputBufferToFill(outputEnergy1);
                    //ofx_Aeq_Zero(outputBuffer1, bufferSize);
                    outputBuffer1[0] = (signalBuffer[0] * e);

                    //setControlRateOutput(outputEnergy1, *signalBuffer);
                    break;
                }
                case 2:
                {
                    float* outputBuffer2 = getOutputBufferToFill(outputEnergy2);
                    //ofx_Aeq_Zero(outputBuffer2, bufferSize);
                    outputBuffer2[0] = (signalBuffer[0] * e);
                    break;
                }
                case 3: {
                    float* outputBuffer3 = getOutputBufferToFill(outputEnergy3);
                    //ofx_Aeq_Zero(outputBuffer3, bufferSize);
                    outputBuffer3[0] = (signalBuffer[0] * e);
                    //setControlRateOutput(outputEnergy3, *signalBuffer);
                    break;
                }
                case 4: {
                    float* outputBuffer4 = getOutputBufferToFill(outputEnergy4);
                    //ofx_Aeq_Zero(outputBuffer4, bufferSize);
                    outputBuffer4[0] = (signalBuffer[0] * e);
                    //setControlRateOutput(outputEnergy4, *signalBuffer);
                    break;
                }
                case 5: {
                    float* outputBuffer5 = getOutputBufferToFill(outputEnergy5);
                    //ofx_Aeq_Zero(outputBuffer5, bufferSize);
                    outputBuffer5[0] = (signalBuffer[0] * e);
                    //setControlRateOutput(outputEnergy5, *signalBuffer);
                    break;
                    
                }
                case 6: {
                    float* outputBuffer6 = getOutputBufferToFill(outputEnergy6);
                    //ofx_Aeq_Zero(outputBuffer6, bufferSize);
                    outputBuffer6[0] = (signalBuffer[0] * e);
                    //setControlRateOutput(outputEnergy6, *signalBuffer);
                    break;
                }
                case 7:{
                    float* outputBuffer7 = getOutputBufferToFill(outputEnergy7);
                    //ofx_Aeq_Zero(outputBuffer7, bufferSize);
                    outputBuffer7[0] = (signalBuffer[0] * e);
                    //setControlRateOutput(outputEnergy7, *signalBuffer);
                    break;
                }
                case 8: {
                    float* outputBuffer8 = getOutputBufferToFill(outputEnergy8);
                    //ofx_Aeq_Zero(outputBuffer8, bufferSize);
                    outputBuffer8[0] = (signalBuffer[0] * e);
                    //setControlRateOutput(outputEnergy8, *signalBuffer);
                    break;
                }
                case 9: {
                    float* outputBuffer7 = getOutputBufferToFill(outputEnergy9);
                    //ofx_Aeq_Zero(outputBuffer7, bufferSize);
                    outputBuffer7[0] = (signalBuffer[0] * e);
                    //setControlRateOutput(outputEnergy9, *signalBuffer);
                    break;
                }
                case 10: {
                    float* outputBuffer10 = getOutputBufferToFill(outputEnergy10);
                    //ofx_Aeq_Zero(outputBuffer10, bufferSize);
                    outputBuffer10[0] = (signalBuffer[0] * e);
                    //setControlRateOutput(outputEnergy10, *signalBuffer);
                    break;
                }
                case 11: {
                    float* outputBuffer11 = getOutputBufferToFill(outputEnergy11);
                    //ofx_Aeq_Zero(outputBuffer11, bufferSize);
                    outputBuffer11[0] = (signalBuffer[0] * e);
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
    
     

        //}
    
        for(int i = 0; i < inactives.size(); i++) {
            switch (inactives[i]) {
                case 0: {
                    float* outputBuffer0 = getOutputBufferToFill(outputEnergy0);
                    ofx_Aeq_Zero(outputBuffer0, bufferSize);
                    outputBuffer0[0] = (0);
                    setOutputToZero(outputEnergy0);

                    //setControlRateOutput(outputEnergy0, 0);
                    break;
                }
                case 1: {
                    float* outputBuffer1 = getOutputBufferToFill(outputEnergy1);
                    ofx_Aeq_Zero(outputBuffer1, bufferSize);
                    outputBuffer1[0] = (0);
                    //setControlRateOutput(outputEnergy1, 0);
                    setOutputToZero(outputEnergy1);

                    //setControlRateOutput(outputEnergy1, *signalBuffer);
                    break;
                }
                case 2:
                {
                    float* outputBuffer2 = getOutputBufferToFill(outputEnergy2);
                    ofx_Aeq_Zero(outputBuffer2, bufferSize);
                    outputBuffer2[0] = 0;
                    setOutputToZero(outputEnergy2);

                    break;
                }
                case 3: {
                    float* outputBuffer3 = getOutputBufferToFill(outputEnergy3);
                    ofx_Aeq_Zero(outputBuffer3, bufferSize);
                    outputBuffer3[0] = 0;
                    setOutputToZero(outputEnergy3);
                    break;
                }
                case 4: {
                    float* outputBuffer4 = getOutputBufferToFill(outputEnergy4);
                    ofx_Aeq_Zero(outputBuffer4, bufferSize);
                    outputBuffer4[0] = 0;
                    setOutputToZero(outputEnergy4);
                    break;
                }
                case 5: {
                    float* outputBuffer5 = getOutputBufferToFill(outputEnergy5);
                    ofx_Aeq_Zero(outputBuffer5, bufferSize);
                    outputBuffer5[0] = 0;
                    setOutputToZero(outputEnergy5);
                    break;
                    
                }
                case 6: {
                    float* outputBuffer6 = getOutputBufferToFill(outputEnergy6);
                    ofx_Aeq_Zero(outputBuffer6, bufferSize);
                    outputBuffer6[0] = 0;
                    setOutputToZero(outputEnergy6);
                    break;
                }
                case 7:{
                    float* outputBuffer7 = getOutputBufferToFill(outputEnergy7);
                    ofx_Aeq_Zero(outputBuffer7, bufferSize);
                    outputBuffer7[0] = 0;
                    setOutputToZero(outputEnergy7);
                    break;
                }
                case 8: {
                    float* outputBuffer8 = getOutputBufferToFill(outputEnergy8);
                    ofx_Aeq_Zero(outputBuffer8, bufferSize);
                    outputBuffer8[0] = 0;
                    setOutputToZero(outputEnergy8);
                    break;
                }
                case 9: {
                    float* outputBuffer7 = getOutputBufferToFill(outputEnergy9);
                    ofx_Aeq_Zero(outputBuffer7, bufferSize);
                    outputBuffer7[0] = 0;
                    setOutputToZero(outputEnergy9);
                    break;
                }
                case 10: {
                    float* outputBuffer10 = getOutputBufferToFill(outputEnergy10);
                    ofx_Aeq_Zero(outputBuffer10, bufferSize);
                    outputBuffer10[0] = 0;
                    setOutputToZero(outputEnergy10);
                    break;
                }
                case 11: {
                    float* outputBuffer11 = getOutputBufferToFill(outputEnergy11);
                    ofx_Aeq_Zero(outputBuffer11, bufferSize);
                    outputBuffer11[0] = 0;
                    setOutputToZero(outputEnergy11);
                    //setControlRateOutput(outputEnergy11, *signalBuffer);
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

