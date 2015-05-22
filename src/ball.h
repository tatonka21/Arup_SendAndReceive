//
//  ball.h
//  SendAndReceive
//
//  Created by Nathan Whitford on 5/15/15.
//
//

#ifndef ball_h
#define ball_h

#include "ofParameterGroup.h"
#include "ofParameter.h"
#include "ofMain.h"

class Ball {
public:
    // Constructor
    Ball();
    
    // Methods
    void setup(int startPos, int category, int sentiment);
    void moveTo();
    void update();
    void draw(ofParameterGroup& palette);
    
    // Properties
    int pos;
    
    int category;
    int sentiment;
    
 
};
#endif