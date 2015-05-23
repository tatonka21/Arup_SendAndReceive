#include "ofApp.h"

#define RECONNECT_TIME 400

//--------------------------------------------------------------
void ofApp::setup(){
    // we don't want to be running to fast
    ofSetVerticalSync(true);
    ofSetFrameRate(40);
    //testImage.loadImage("gradient.jpg");
    testImage.allocate(1, 400, OF_IMAGE_COLOR);
    fbo.allocate(1, 400);
    //bgPixels.allocate(1, 400, OF_PIXELS_RGB);
    pixels.allocate(1, 400, OF_PIXELS_RGB);
    //texture.allocate(pixels);
    
    
    //create the socket and set to send to 127.0.0.1:11999
    udpConnection.Create();
    // outgoing
    udpConnection.Connect(E682_ADDRESS,5568);
    udpConnection.SetNonBlocking(true);
    udpConnection.SetEnableBroadcast(false);
    udpConnection.SetReuseAddress(true);
    
    //incoming socket and bind to port 8555
    //udpIncoming.Create();
    //udpIncoming.Bind(8555);
    //udpIncoming.SetNonBlocking(true);
    
    TCP.setup(8555);
    TCP.setMessageDelimiter("\n");
    
    setupGUI();
    
}

//--------------------------------------------------------------

void ofApp::setupGUI(){
    categories.setName("Categories");
    colour0.set("Happiness",ofColor(127),ofColor(0,0),ofColor(255));
    colour1.set("Stresslevel",ofColor(127),ofColor(0,0),ofColor(255));
    colour2.set("Workload",ofColor(127),ofColor(0,0),ofColor(255));
    categories.add(speed.set("Speed", 2, 0, 20));
    categories.add(length.set("Size", 2, 0, 10));
    categories.add(pulseSize.set("Pulse Size", 3, 0, 10));
    categories.add(pulseSpeed.set("Pulse Speed", 0.5, 0, 3));
    
    categories.add(colour0);
    categories.add(colour1);
    categories.add(colour2);
    
    triggers.setName("Trigger Simulation");
    triggers.add(trig1.set("Trigger1", false));
    triggers.add(trig1Cat.set("Category1", 0, 0, 2));
    triggers.add(trig1Sent.set("Sentiment1", 128, 0, 512));
    triggers.add(trig2.set("Trigger2", false));
    triggers.add(trig2Cat.set("Category2", 0, 0, 2));
    triggers.add(trig2Sent.set("Sentiment2", 128, 0, 512));
    triggers.add(trig3.set("Trigger3", false));
    triggers.add(trig3Cat.set("Category3", 0, 0, 2));
    triggers.add(trig3Sent.set("Sentiment3", 128, 0, 512));
    triggers.add(trig4.set("Trigger4", false));
    triggers.add(trig4Cat.set("Category4", 0, 0, 2));
    triggers.add(trig4Sent.set("Sentiment4", 128, 0, 512));
    triggers.add(trig5.set("Trigger5", false));
    triggers.add(trig5Cat.set("Category5", 0, 0, 2));
    triggers.add(trig5Sent.set("Sentiment5", 128, 0, 512));
    triggers.add(trig6.set("Trigger6", false));
    triggers.add(trig6Cat.set("Category6", 0, 0, 2));
    triggers.add(trig6Sent.set("Sentiment6", 128, 0, 512));
    triggers.add(trig7.set("Trigger7", false));
    triggers.add(trig7Cat.set("Category7", 0, 0, 2));
    triggers.add(trig7Sent.set("Sentiment7", 128, 0, 512));
    
    
    calibration.setName("Calibration");
    calibration.add(trig1Pos.set("Position 1", 50, 0, 400));
    calibration.add(trig2Pos.set("Position 2", 100, 0, 400));
    calibration.add(trig3Pos.set("Position 3", 150, 0, 400));
    calibration.add(trig4Pos.set("Position 4", 200, 0, 400));
    calibration.add(trig5Pos.set("Position 5", 250, 0, 400));
    calibration.add(trig6Pos.set("Position 6", 300, 0, 400));
    calibration.add(trig7Pos.set("Position 7", 350, 0, 400));
    
    parameters.setName("Settings");
    //parameters.add(london.set(" In London", true));
    parameters.add(brightness.set( "Brightness", 255, 0, 512 ));
    parameters.add(speedRed.set( "Red Speed", 1, 0, 50 ));
    parameters.add(speedGreen.set( "Green Speed", 1, 0, 50 ));
    parameters.add(speedBlue.set( "Blue Speed", 1, 0, 50 ));
    parameters.add(faderRed.set( "Red", 255, 0, 255 ));
    parameters.add(faderGreen.set( "Green", 255, 0, 255 ));
    parameters.add(faderBlue.set( "Blue", 255, 0, 255 ));
    parameters.add(shift.set( "Shift", 100, 0, 255));
    
    parameters.add(categories);
    parameters.add(triggers);

    calibrationParameters.setName("Calibration");
    calibrationParameters.add(calibration);
    
    gui.setup(parameters);
    //gui.setSize(300, 500);
    gui.loadFromFile("settings.xml");
    gui.minimizeAll();

    guiCalibration.setup(calibrationParameters, "calibration.xml" ,230, 400 );
    guiCalibration.loadFromFile("calibration.xml");

}

//--------------------------------------------------------------

// This needs to be before update()
char gammaLUT[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
    2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
    5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
    10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
    17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
    25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
    37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
    51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
    69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
    90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
    115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
    144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
    177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
    215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255
};

char gamma(unsigned char input) {
    return gammaLUT[input];
}


//--------------------------------------------------------------
void ofApp::update(){
    

    receiveTCP();
    checkTriggers();
    generateImage();
    sendUDP();
    
}



//--------------------------------------------------------------

void ofApp::checkTriggers(){
    
    if (trig1 == true){
        Ball tempBall;									// create the ball object
        tempBall.setup(trig1Pos, trig1Cat, trig1Sent);			// setup its initial state
        balls.push_back(tempBall);						// add it to the vector
        trig1.set(false);
    }
    if (trig2 == true){
        Ball tempBall;									// create the ball object
        tempBall.setup(trig2Pos, trig2Cat, trig2Sent);			// setup its initial state
        balls.push_back(tempBall);						// add it to the vector
        trig2.set(false);
    }
    if (trig3 == true){
        Ball tempBall;									// create the ball object
        tempBall.setup(trig3Pos, trig3Cat, trig3Sent);			// setup its initial state
        balls.push_back(tempBall);						// add it to the vector
        trig3.set(false);
    }
    if (trig4 == true){
        Ball tempBall;									// create the ball object
        tempBall.setup(trig4Pos, trig4Cat, trig4Sent);			// setup its initial state
        balls.push_back(tempBall);						// add it to the vector
        trig4.set(false);
    }
    if (trig5 == true){
        Ball tempBall;									// create the ball object
        tempBall.setup(trig5Pos, trig5Cat, trig5Sent);			// setup its initial state
        balls.push_back(tempBall);						// add it to the vector
       trig5.set(false);
    }
    if (trig6 == true){
        Ball tempBall;									// create the ball object
        tempBall.setup(trig6Pos, trig6Cat, trig6Sent);			// setup its initial state
        balls.push_back(tempBall);						// add it to the vector
        trig6.set(false);
    }
    if (trig7 == true){
        Ball tempBall;									// create the ball object
        tempBall.setup(trig7Pos, trig7Cat, trig7Sent);			// setup its initial state
        balls.push_back(tempBall);						// add it to the vector
        trig7.set(false);
    }
    
    
}

//--------------------------------------------------------------

void ofApp::draw(){
    //set background color
    ofBackgroundGradient(ofColor::white, ofColor::gray);
    //testImage.draw(400, 100, 50, 400);
    //ofSetColor(255, 255);
    fbo.draw(500, 100, 50, 400);
    
    /*
    for (int i = 0 ; i<balls.size(); i++) {
        balls[i].draw(categories);
    }
     */
    
    
    ofSetColor(255, 255);
    
    printInformation(230, 25);
    gui.draw();
    guiCalibration.draw();
    
    
}

//--------------------------------------------------------------

void ofApp::generateImage(){
    // Generate the IMAGE
    for (int i = 0; i<400; i++) {
        float colorR = (sin((ofGetElapsedTimeMillis()*speedRed / 1000.f)+(float(i)/10)) / 2.f + 0.5f) * float(brightness)*(faderRed/255.);
        float colorG = (sin(((ofGetElapsedTimeMillis()*speedGreen / 1000.f)+(float(i)/10))  + PI / 3.f) / 2.f + 0.5f) * float(brightness)*(faderGreen/255.);
        float colorB = (sin(((ofGetElapsedTimeMillis()*speedBlue / 1000.f)+(float(i)/10))  + PI * 2.f / 3.f) / 2.f + 0.5f) * float(brightness)*(faderBlue/255.);
        
        colorR = ofClamp(colorR*shift/100 + shift-100, 0, 255);
        colorG = ofClamp(colorG*shift/100 + shift-100, 0, 255);
        colorB = ofClamp(colorB*shift/100 + shift-100, 0, 255);
        
        //pixels.setColor(0, i, );
        testImage.setColor(0, i, ofColor(colorR, colorG, colorB));
    }
        //bgPixels.setColor(0, i, ofColor(colorR, colorG, colorB));
        testImage.update();
        //texture.loadData(bgPixels);
        
        //begin FBO
        fbo.begin();
        //ofSetColor(0, 0, 0, 255);
        //ofRect(0, 0, 50, 400);
        //draw the background image
        //testImage.draw(0,0);
        ofSetColor(255, 255);

        testImage.draw(0, 0, 50, 400);
        
        //lets's calculate and draw the balls:
        for (int i = 0 ; i<balls.size(); i++) {
            balls[i].update(categories);
            balls[i].draw(categories);
        }
        ofSetColor(255, 255);

        //end FBO
        fbo.end();
        
        fbo.readToPixels(pixels);
    
}


//--------------------------------------------------------------

void ofApp::printInformation(int x, int y){
    
    ofPushMatrix();
    ofTranslate(x, y);
    ofSetColor(0, 0, 0);
    ofDrawBitmapString(ofGetTimestampString("%b %f %H:%M:%S"), 0, 0);
    ofDrawBitmapString("Raw Message:", 0, 20);
    ofDrawBitmapString(inMessage, 0, 40);
    ofDrawBitmapString("Mac Address:", 0, 80);
    ofDrawBitmapString(macAddress, 110, 80);
    ofDrawBitmapString("Category:", 0, 100);
    ofDrawBitmapString(ofToString(category), 110, 100);
    ofDrawBitmapString("Sentiment:", 0, 120);
    ofDrawBitmapString(ofToString(sentiment), 110, 120);
    
    ofDrawBitmapString("RFID Tag:", 0, 140);
    ofDrawBitmapString(rfidTag, 110, 140);
    
    ofDrawBitmapString("Object Count: ", 0, 180);
    ofDrawBitmapString(ofToString(balls.size()), 110, 180);
    
    ofDrawBitmapString("Connections: ", 0, 200);
    ofDrawBitmapString(ofToString(TCP.getNumClients()), 110, 200);
    
    ofDrawBitmapString("Framerate: ", 0, 220);
    ofDrawBitmapString(ofToString(ofGetFrameRate()), 110, 220);
    ofPopMatrix();

}

//--------------------------------------------------------------

void ofApp::receiveTCP(){
    
    // for each client lets send them a message letting them know what port
    // they are connected on
    //
    for(int i = 0; i < TCP.getLastID(); i++){
        if( !TCP.isClientConnected(i) )continue;
        
        TCP.send(i, "Hello YUN - Connected on port - "+ofToString(TCP.getClientPort(i)) + " Client ID " + ofToString(i) );
    }

    // Check for messages
    //
    for(unsigned int i = 0; i < (unsigned int)TCP.getLastID(); i++){
        
        if( !TCP.isClientConnected(i) )continue;
        
        //give each client its own color
        ofSetColor(255 - i*30, 255 - i * 20, 100 + i*40);
        
        //calculate where to draw the text
        int xPos = 15;
        int yPos = 80 + (12 * i * 4);
        
        //get the ip and port of the client
        string port = ofToString( TCP.getClientPort(i) );
        string ip   = TCP.getClientIP(i);
        info = "client "+ofToString(i)+" -connected from "+ip+" on port: "+port;
        
        
        //if we don't have a string allocated yet
        //lets create one
        if(i >= storeText.size() ){
            storeText.push_back( string() );
        }
        
        //we only want to update the text we have recieved there is data
        string str = TCP.receive(i);
        
        if(str.length() > 0){
            storeText[i] = str;
            inMessage = str;
        }
        
        // Let's see if the string has comma delimiters
        // We are defining a correct packet by checking for 4 delimited messages
        //
        // We'll print out the data, and trigger some events.
        vector<string> splitString = ofSplitString(str, ",");
        if (splitString.size() == 4){
            
            // Set variables for on screen infomation
            macAddress = splitString[0];
            category = ofToInt(splitString[1]);
            sentiment = ofToInt(splitString[2])/2;
            rfidTag = splitString[3];

            // If it's a proper event let's log it to a file
            // the log file will be created in the data directory
            ofFile file;
            file.open(ofToDataPath("RFIDdata.txt"), ofFile::Append, false);
            file << ofGetTimestampString("%b %f %H:%M:%S") + "," + str + "\n";
            file.close();
            
            
            // And setup our triggers
            if (macAddress == MAC1) {        //  arduino 1
                trig1Cat = category;
                trig1Sent = sentiment;
                trig1 = true;
            }
            if (macAddress == MAC2) {        //  arduino 2
                trig2Cat = category;
                trig2Sent = sentiment;
                trig2 = true;
            }
            if (macAddress == MAC3) {        //  arduino 3
                trig3Cat = category;
                trig3Sent = sentiment;
                trig3 = true;
            }
            if (macAddress == MAC4) {        //  arduino 4
                trig4Cat = category;
                trig4Sent = sentiment;
                trig4 = true;
            }
            if (macAddress == MAC5) {        //  arduino 5
                trig5Cat = category;
                trig5Sent = sentiment;
                trig5 = true;
            }
            if (macAddress == MAC6) {        //  arduino 6
                trig6Cat = category;
                trig6Sent = sentiment;
                trig6= true;
            }
            if (macAddress == MAC7) {        //  arduino 7
                trig7Cat = category;
                trig7Sent = sentiment;
                trig7 = true;
            }
            if (macAddress == "00:00:00:00:00:00") {        //  let's test a bunch
                trig1 = true;
                trig2 = true;
                trig3 = true;
                trig4 = true;
                trig5 = true;
                trig6 = true;
                trig7 = true;
            }
            
        }
        
    }
}

//--------------------------------------------------------------

//--------------------------------------------------------------

void ofApp::sendUDP(){
    
    // Format the packet.
    string message1="";
    string message2="";
    string message3="";
    sequencer++;  // increment sequencer for every packet.
    
    // Build the packet header here. Needs a sequential byte in the middle.
    string messageHeader1 = ofHexToString("001000004153432D45312E3137000000726E00000004C8BC8891A9064403A819A3F86F9FA0B27258000000024E415448414E00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000640000");
    messageHeader1 += sequencer;
    messageHeader1 += ofHexToString ("00");
    messageHeader1 += ofHexToString ("0001");   //universe here
    messageHeader1 += ofHexToString ("720B02A100000001020100");
    
    string messageHeader2 = ofHexToString("001000004153432D45312E3137000000726E00000004C8BC8891A9064403A819A3F86F9FA0B27258000000024E415448414E00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000640000");
    messageHeader2 += sequencer;
    messageHeader2 += ofHexToString ("00");
    messageHeader2 += ofHexToString ("0002");   //universe here
    messageHeader2 += ofHexToString ("720B02A100000001020100");
    
    string messageHeader3 = ofHexToString("001000004153432D45312E3137000000726E00000004C8BC8891A9064403A819A3F86F9FA0B27258000000024E415448414E00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000640000");
    messageHeader3 += sequencer;
    messageHeader3 += ofHexToString ("00");
    messageHeader3 += ofHexToString ("0003");   //universe here
    messageHeader3 += ofHexToString ("720B02A100000001020100");
    // Packet Header built
    
    
    // Now push out one universe of colour
    message1 = messageHeader1;
    message2 = messageHeader2;
    message3 = messageHeader3;
    
    for (int i = 0; i <170; i++){  //get 510 bytes
        message1 += gamma(pixels.getColor(0,i).r);
        message1 += gamma(pixels.getColor(0,i).g);
        message1 += gamma(pixels.getColor(0,i).b);
    }
    
    for (int i = 170; i <340; i++){  //get 510 bytes
        message2 += gamma(pixels.getColor(0,i).r);
        message2 += gamma(pixels.getColor(0,i).g);
        message2 += gamma(pixels.getColor(0,i).b);
    }
    
    for (int i = 340; i <400; i++){  //get 510 bytes
        message3 += gamma(pixels.getColor(0,i).r);
        message3 += gamma(pixels.getColor(0,i).g);
        message3 += gamma(pixels.getColor(0,i).b);
    }
    
    float zero = 0;
    message1 += zero;
    message1 += zero;   // fill in the last two bytes
    message2 += zero;
    message2 += zero;   // fill in the last two bytes
    message3 += zero;
    message3 += zero;   // fill in the last two bytes
    
    
    
    udpConnection.Send(message1.c_str(),message1.length());
    udpConnection.Send(message2.c_str(),message2.length());
    udpConnection.Send(message3.c_str(),message3.length());
}



//--------------------------------------------------------------
void ofApp::exit(){
    gui.saveToFile( "settings.xml" );
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}
