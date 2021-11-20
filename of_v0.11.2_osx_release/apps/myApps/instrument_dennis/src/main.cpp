#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

    ofGLFWWindowSettings msettings;
    msettings.setSize( 1024, 768 );
    msettings.numSamples = 0; 
    auto mainWin = ofCreateWindow( msettings );

    auto app = make_shared<ofApp>();
    ofRunApp( mainWin, app );
    ofRunMainLoop();

}
