#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	// by default, connect to AbletonLive on local machine
	live.setup();

	// can also connect over the network if IP address specified, e.g.
	//live.setup("192.168.1.15");

	// lastly you can provide a callback method (with no arguments)
	// to be called once live has finished parsing, as in the following:
	//live.setup(this, &ofApp::myCallbackMethod);
	//live.setup("192.168.1.15", this, &ofApp::myCallbackMethod);
	//live.setup("localhost", this, &ofApp::myCallbackMethod);

	// ofxAbletonLive takes a few seconds to get all the data over OSC from Ableton.
	// during this time, parameters aren't visible yet or accessible.
	// you can check the status by calling live.isLoaded(), or as described above,
	// you can pass a callback method to the setup

	receive.setup(PORT);

}

//--------------------------------------------------------------
void ofApp::update(){
	// don't forget to run this! otherwise no OSC messages will be received
	live.update();

	// receive gestures and map to Ableton controls
	while (receive.hasWaitingMessages()) {
		ofxOscMessage m;
		receive.getNextMessage(&m);

		if (m.getAddress() == "/wek/outputs") {
			std::cout << "number of arguments: " << m.getNumArgs() << endl;

			string msgString;
			msgString = m.getAddress();
			msgString += ":";
			for (size_t i = 0; i < m.getNumArgs(); i++) {

				// get the argument type
				msgString += " ";
				msgString += m.getArgTypeName(i);
				msgString += ":";

				// display the argument - make sure we get the right type
				if (m.getArgType(i) == OFXOSC_TYPE_INT32) {
					msgString += ofToString(m.getArgAsInt32(i));
				}
				else if (m.getArgType(i) == OFXOSC_TYPE_FLOAT) {
					msgString += ofToString(m.getArgAsFloat(i));
				}
				else if (m.getArgType(i) == OFXOSC_TYPE_STRING) {
					msgString += m.getArgAsString(i);
				}
				else {
					msgString += "argument type: " + m.getArgTypeName(i);
				}
			}
			cout << "message: " << msgString << endl;

			// test for gesture 0
			if (m.getArgAsFloat(0) < threshold) {
				live.selectScene(0); // play scene 1
			}

			// test for gesture 1
			else if (m.getArgAsFloat(1) < threshold) {
				live.selectScene(1); // play scene 2
			}

			// test for gesture 2
			else if (m.getArgAsFloat(2) < threshold) {
				live.selectScene(2); // play scene 3
			}

			// test for gesture 3
			else if (m.getArgAsFloat(3) < threshold) {
				live.stop(); // stop playing
			}
		}
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(0);

	// this draw method prints all of the relevant info from ofxAbletonLive
	// you can also call live.drawDebugView() to do the same

	// you can check if Live has finished loading all parameters since setup was called
	if (!live.isLoaded()) {
		ofDrawBitmapString("ofxAbletonLive has not loaded yet!", 100, 100);
		return;
	}

	// now that live is fully loaded, we can print all the parameters to the screen

	ofDrawBitmapString(live.getTrackString(), 10, 15);
	int x = 200;

	map<int, ofxAbletonLiveTrack*>::iterator it = live.getTracks().begin();
	for (; it != live.getTracks().end(); ++it)
	{
		string trackString = "Track " + ofToString(it->first) + ": \"" + it->second->getName() + "\"\n";
		trackString += it->second->getDevicesInfo();
		trackString += it->second->getClipsInfo();

		map<int, ofxAbletonLiveDevice*>::iterator itd = it->second->getDevices().begin();
		for (; itd != it->second->getDevices().end(); ++itd) {
			trackString += itd->second->getParametersInfo();
		}

		ofDrawBitmapString(trackString, x, 15);
		x += 300;
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	// keyboard driven parallel control facility

	// select first scene
	if (key == '0')
	{
		live.play();
	}

	// select first scene
	if (key == '1')
	{
		live.selectScene(0);
	}
	
	// select second scene
	else if (key == '2')
	{
		live.selectScene(1);
	}

	// select third scene
	else if (key == '3')
	{
		live.selectScene(2);
	}

	// stop
	else if (key == '7')
	{
		live.stop();
	}

	// get info
	else if (key == '9')
	{
		// you can print all the available parameters to the console
		live.printAll();

		// or just the tracks
		live.printTracks();
	}

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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
