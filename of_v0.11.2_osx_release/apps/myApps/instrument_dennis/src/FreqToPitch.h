
#pragma once

#include "ofxPDSPFunctions.h"

// FreqToPitch.h
// ofxPDSP
// Nicola Pisanti, MIT License, 2016

#include <AbsoluteValue.h>

#include "ofxFilterbank.h"

#define BANDWITH  1.0
#define BUFFER_SIZE 2048
#define LIN2dB(x) (double)(20. * log10(x))
#define SR 48000



    /*!
    @brief Multiply in("signal") for in("mod").
    
    Multiply the in_signal() input for the in_mod() input. If the in_mod() input is running ad control rate and it is equal to 0, the in_signal() branch is not even calculated, saving cpu cycles.

    */
class FreqToPitch : public pdsp::Unit{
    
public:
    
    FreqToPitch();
    
    ~FreqToPitch();
    FreqToPitch(const FreqToPitch& other);
    FreqToPitch& operator=(const FreqToPitch& other);
                
    /*!
    @brief set the default  in("mod") value and returns the unit ready to be patched.
    @param[in] value Value to set for scaling the input signal, Default is 0.0f .
    */
    pdsp::AbsoluteValue val;
    /*!
    @brief Sets "signal" as selected input and returns this Unit ready to be patched. This is the default input. This input is the signal/value to multiply.
    */
    Patchable& in_signal();
    
    /*!
    @brief Sets "mod" as selected input and returns this Unit ready to be patched. Value from in("signal") is multiplied by this value/signal. If the input is running at control rate and it is equal to 0.0f the signal branch is not processed. Defaulot value is 0.0f .
    */
    Patchable & out_pitch(const char * index);

    
    // Patchable & out_energy(const char * index);

    /*!
    @brief Sets "signal" as selected output and returns this Unit ready to be patched. This is the default output. This is the product of in("signal") multiplied by in("mod").
    */
    
    /*!
    @brief returns the value of the input buffer behind in("mod"), updated at control rate. This method is thread safe.
    */
    
    /*!
    @brief returns the value of the output buffer, updated at control rate. This method is thread safe.
    */
    float meter_output() const;
    std::atomic<float> meterOut;



    ofxFilterbank filterBank;

    int    sampleRate;
    int bufferSize;
    int inChan;
    int outChan;
    
    


private:

    
    void prepareUnit ( int expectedBufferSize, double sampleRate ) override;
    
    void releaseResources () override;

    void process (int bufferSize) noexcept override;

    pdsp::OutputNode output0;
    pdsp::OutputNode output1;
    pdsp::OutputNode output2;
    pdsp::OutputNode output3;
    pdsp::OutputNode output4;
    pdsp::OutputNode output5;
    pdsp::OutputNode output6;
    pdsp::OutputNode output7;
    pdsp::OutputNode output8;
    pdsp::OutputNode output9;
    pdsp::OutputNode output10;
    pdsp::OutputNode output11;
    
/*
    pdsp::OutputNode outputEnergy0;
    pdsp::OutputNode outputEnergy1;
    pdsp::OutputNode outputEnergy2;
    pdsp::OutputNode outputEnergy3;
    pdsp::OutputNode outputEnergy4;
    pdsp::OutputNode outputEnergy5;
    pdsp::OutputNode outputEnergy6;
    pdsp::OutputNode outputEnergy7;
    pdsp::OutputNode outputEnergy8;
    pdsp::OutputNode outputEnergy9;
    pdsp::OutputNode outputEnergy10;
    pdsp::OutputNode outputEnergy11;
 */

    pdsp::InputNode input_signal;
        
};
        


