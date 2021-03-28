# gestureAbleton
This app receives OSC messages from Wekinator and maps them to basic Ableton Live controls

Build details:

The app was created using OpenFrameworks release 0.10.0 (2017) on a PC under MS Visual Studio version 15.9.30 (2017)

To set up the project, please use OpenFrameworks projectGenerator, specifying the following add-ons:

ofxAbletonLive, ofxOsc

ofxAbletonLive is an external add-on which can be downloaded from:

https://github.com/genekogan/ofxAbletonLive

After downloading, the top level directory should then be copied into the add-ons folder within the OpenFrameworks directory hierarchy and renamed 'ofxAbletonLive'.

How to run:

On building the gestureAbleton solution, an executable should be generated in your /bin directory (or equivalent directory, depending on your OS).

Please read and follow the ofxAbletonLive instructions given in the above link to facillitate communication with Ableton Live.

With Ableton Live started, and at least three different 'scenes' defined in your Live set, double click on the gestureAbleton executable.   A window should pop up which displays all the parameters available in your Ableton Live set.   Just a small subset of these parameters are made accessible by the gestureAbleton (ie scene selection and 'stop'), but it should be easy to modify my code to control any of the parameters on this list.

It should be possible to start playing each of these 'scenes' by pressing the kepad keys 1-3, and by pressing key 7, the playback should stop.   This verifies communication with Ableton Live.   Next, set up Wekinator with a DTW based project, and at least three gestures defined and trained.   The first three gestures should invoke the defined scenes in your Ableton set, and the fourth gesture should make the sound stop.
