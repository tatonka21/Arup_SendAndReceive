#pragma once

#include "ofxNetwork.h"
#include "ofxGui.h"
#include "ofMain.h"
#include "ball.h"

class ofApp : public ofBaseApp{
    
#define MAC1 "90:A2:DA:F9:0D:BE"  // 5TH FLOOR
#define MAC2 "90:A2:DA:FB:1B:33"  // 4TH FLOOR
#define MAC3 "90:A2:DA:FB:11:AE"  // 3RD FLOOR
#define MAC4 "90:A2:DA:F8:5C:71"  // 2ND FLOOR
#define MAC5 "90:A2:DA:F8:5E:68"  // 1ST FLOOR
#define MAC6 "90:A2:DA:F8:5A:5C"  // GROUND FLOOR
#define MAC7 "90:A2:DA:F8:5E:68"  // NOTHING YET

#define E682_ADDRESS "192.168.152.251"
//#define E682_ADDRESS "192.168.1.206"

    
public:
    void setup();
    void update();
    void draw();
    
    void setupGUI();
    void generateImage();
    //void receiveUDP();
    void receiveTCP();
    void sendUDP();
    void printInformation(int x, int y);
    void checkTriggers();
    
    void newBall(int source, int category);

    //char gamma(unsigned char input);
    
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
    ofPixels bgPixels;
    ofPixels pixels;
    ofTexture texture;
    
    ofTrueTypeFont  mono;
    ofTrueTypeFont  monosm;
    vector<ofPoint> stroke;
    
    //Ball cat0, cat1, cat2;
    vector <Ball> balls;
    
    ofParameterGroup parameters;
    
    ofParameterGroup categories;
    ofParameter<ofColor> colour0;
    ofParameter<int> speed;
    ofParameter<int> length;
    ofParameter<int> pulseSize;
    ofParameter<float> pulseSpeed;
    ofParameter<ofColor> colour1;
    ofParameter<ofColor> colour2;

    ofParameterGroup calibration;
    ofParameter<int> trig1Pos;
    ofParameter<int> trig2Pos;
    ofParameter<int> trig3Pos;
    ofParameter<int> trig4Pos;
    ofParameter<int> trig5Pos;
    ofParameter<int> trig6Pos;
    ofParameter<int> trig7Pos;

    ofParameterGroup triggers;
    ofParameter<bool> trig1;
    ofParameter<bool> trig2;
    ofParameter<bool> trig3;
    ofParameter<bool> trig4;
    ofParameter<bool> trig5;
    ofParameter<bool> trig6;
    ofParameter<bool> trig7;
 
    ofParameter<int> trig1Cat;
    ofParameter<int> trig2Cat;
    ofParameter<int> trig3Cat;
    ofParameter<int> trig4Cat;
    ofParameter<int> trig5Cat;
    ofParameter<int> trig6Cat;
    ofParameter<int> trig7Cat;

    ofParameter<int> trig1Sent;
    ofParameter<int> trig2Sent;
    ofParameter<int> trig3Sent;
    ofParameter<int> trig4Sent;
    ofParameter<int> trig5Sent;
    ofParameter<int> trig6Sent;
    ofParameter<int> trig7Sent;

    
    ofParameter<int> brightness, speedRed, speedGreen, speedBlue, faderRed, faderGreen, faderBlue, shift;
    //ofParameter<bool> london;
 
    ofxPanel gui;
 
    char sequencer = 0;
    char *gammaLUT;
    
    
};

