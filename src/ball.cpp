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
    
}


void Ball::moveTo(){
    
}

void Ball::update(ofParameterGroup& palette){
    
    int size = palette.getInt("Size");
    int pulseSize = palette.getInt("Pulse Size");
    int speed = palette.getInt("Speed");
    float pulseSpeed = palette.getFloat("Pulse Speed");

    // divide sentiment by 1.28 to get 400 pixels
    if (pos > sentiment/1.28)
        pos = pos - speed;
    if (pos < sentiment/1.28)
        pos = pos + speed;
    
    if (pulseUp)
        pulse = pulse + pulseSpeed;
    if (!pulseUp)
        pulse = pulse - pulseSpeed;
    
    if (pulse < 0 | pulse > pulseSize )
        pulseUp = !pulseUp;
    
    radius = size + pulse * pulseSpeed;

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

    ofEnableBlendMode(OF_BLENDMODE_ADD);
    c.setBrightness(50);
    ofSetColor(c);
    for (int i = 0; i < 10; i++){
        ofCircle(0, pos, i*radius);
    }
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
}
