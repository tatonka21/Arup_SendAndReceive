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
    
}


void Ball::moveTo(){
    
}

void Ball::update(ofParameterGroup& palette){

    // divide sentiment by 1.28 to get 400 pixels
    if (pos > sentiment/1.28)
        pos = pos - palette.getInt("Speed");
    if (pos < sentiment/1.28)
        pos = pos + palette.getInt("Speed");
}


void Ball::draw(ofParameterGroup& palette){

    switch (category){
        case 0:
            ofSetColor(palette.getColor("Happiness"));
            break;
        case 1:
            ofSetColor(palette.getColor("Stresslevel"));
            break;
        case 2:
            ofSetColor(palette.getColor("Workload"));
            break;
    }
    
    ofCircle(0, pos, palette.getInt("Length"));
}
