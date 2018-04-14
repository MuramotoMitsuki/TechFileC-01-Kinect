#pragma once

#include "ofMain.h"

#include "ofxKinect.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofxKinect kinect;
    ofImage cameraImage;//RGBカメラの映像
    ofImage depthImage;//赤外線カメラによる深度映像
    
    ofParameter<int> radius;//int型のGui用のパラメーターを用意
    ofxPanel gui;//Guiの外枠(各UIを格納するためのパネルを定義する)
    
    ofParameter<int> near;//int型のGui用のパラメータを用意(kinectの描画範囲の下限)
    ofParameter<int> far;//int型のGui用のパラメータを用意(kinectの描画範囲の上限)
    
    ofImage maskedImage;//指定範囲内の画像を出力するofImage
    
    ofParameter<ofColor> color;
};
