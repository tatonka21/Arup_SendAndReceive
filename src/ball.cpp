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

void Ball::update(){



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
    
    ofCircle(300, pos, 20);
}
