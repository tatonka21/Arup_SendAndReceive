#pragma once

#include "ofxNetwork.h"
#include "ofxGui.h"
#include "ofMain.h"
#include "ball.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void generateImage();
    //void receiveUDP();
    void receiveTCP();
    void sendUDP();
    
    void checkTriggers();
    
    void newBall(int source, int category);
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void exit();
    
    ofxUDPManager udpConnection;
    //ofxUDPManager udpIncoming;
    ofxTCPServer TCP;
    
    vector <string> storeText;
    
    string inMessage;
    string macAddress;
    int category;
    int sentiment;
    string rfidTag;
    string info;
    
    ofImage testImage;
    ofFbo fbo;
    
    ofTrueTypeFont  mono;
    ofTrueTypeFont  monosm;
    vector<ofPoint> stroke;
    
    //Ball cat0, cat1, cat2;
    vector <Ball> balls;
    
    ofParameterGroup parameters;
    
    ofParameterGroup categories;
    ofParameter<ofColor> colour0;
    ofParameter<int> speed0;
    ofParameter<int> length0;
    ofParameter<ofColor> colour1;
    ofParameter<int> speed1;
    ofParameter<int> length1;
    ofParameter<ofColor> colour2;
    ofParameter<int> speed2;
    ofParameter<int> length2;

    ofParameterGroup calibration;
    ofParameter<int> trig1Pos;
    ofParameter<int> trig2Pos;
    ofParameter<int> trig3Pos;
    ofParameter<int> trig4Pos;
    ofParameter<int> trig5Pos;
    ofParameter<int> trig6Pos;

    ofParameterGroup testing;
    ofParameter<bool> trig1;
    ofParameter<bool> trig2;
    ofParameter<bool> trig3;
    ofParameter<bool> trig4;
    ofParameter<bool> trig5;
    ofParameter<bool> trig6;
 
    ofParameter<int> trig1Cat;
    ofParameter<int> trig2Cat;
    ofParameter<int> trig3Cat;
    ofParameter<int> trig4Cat;
    ofParameter<int> trig5Cat;
    ofParameter<int> trig6Cat;

    ofParameter<int> trig1Sent;
    ofParameter<int> trig2Sent;
    ofParameter<int> trig3Sent;
    ofParameter<int> trig4Sent;
    ofParameter<int> trig5Sent;
    ofParameter<int> trig6Sent;

    
    ofParameter<int> brightness, speedRed, speedGreen, speedBlue, faderRed, faderGreen, faderBlue, shift;
 
    ofxPanel gui;
 
    char sequencer = 0;
    
    
};

