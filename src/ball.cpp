//
//  ball.cpp
//  SendAndReceive
//
//  Created by Nathan Whitford on 5/15/15.
//
//

#include "ball.h"

Ball::Ball(){

}

void Ball::setup(int _startPos, int _category, int _sentiment){

    pos = _startPos;
    category = _category;
    sentiment = _sentiment;
    pulseUp = true;
    pulse = 0;
    radius = 0;
    delay = 40;
    
}


void Ball::moveTo(){
    
}

void Ball::update(ofParameterGroup& palette){
    
    float size = palette.getFloat("Size");
    float pulseSize = palette.getFloat("Pulse Size");
    float speed = palette.getFloat("Speed");
    float pulseSpeed = palette.getFloat("Pulse Speed");

    if (delay == 0){
    // divide sentiment by 1.28 to get 400 pixels
    if (pos > sentiment/1.28)
        pos = pos - speed;
    if (pos < sentiment/1.28)
        pos = pos + speed;
    }
    
    if (pulseUp)
        pulse = pulse + pulseSpeed;
    if (!pulseUp)
        pulse = pulse - pulseSpeed;
    
    if (pulse < 0 | pulse > pulseSize )
        pulseUp = !pulseUp;
    
    radius = size + pulse;

}


void Ball::draw(ofParameterGroup& palette){

    ofColor c;
    switch (category){
        case 0:
            c = palette.getColor("Happiness");
            break;
        case 1:
            c = palette.getColor("Stresslevel");
            break;
        case 2:
            c= palette.getColor("Workload");
            break;
    }

    if (delay >0) {
        delay--;
    }

    c.setSaturation(c.getSaturation() - c.getSaturation() * delay/30);
    ofLog(OF_LOG_NOTICE, ofToString(c.getSaturation()));
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofSetColor(c);
    for (int i = 10; i > 0; i--){
        ofCircle(0, pos, i*radius);
    }
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
}
