#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    kinect.setRegistration(true);
    kinect.init();
    kinect.open();
    if(!kinect.isConnected()){
        ofSystemAlertDialog("Serial Error:Kinect is not connected. Check a USB port then push space bar.");
    }
    //Guiの設定
    ofxGuiSetDefaultWidth(300);
    ofxGuiSetDefaultHeight(18);
    gui.setup("Depth Masking Control");//表示するパネル名を指定して、メインとなるパネル部分を初期化して生成
    gui.setPosition(10,10);
    //gui.add(radius.set("Radius",0,0,255));//(スライダー名,初期値,最小値,最大値)
    gui.add(near.set("near",0,0,255));
    gui.add(far.set("far",255,0,255));
    
    gui.add(color.set("color",ofColor(255,255,255,255),ofColor(0,0,0,0),ofColor(255,255,255,255)));
}

//--------------------------------------------------------------
void ofApp::update(){
    kinect.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    //kinect.draw(0,0,ofGetWidth(),ofGetHeight());カラーカメラで取得した映像を描画
    if(kinect.isFrameNew()){
        cameraImage.setFromPixels(kinect.getPixels().getData(), kinect.width, kinect.height, OF_IMAGE_COLOR);
        //用意したcameraImageに画像をセット
        //setFromPixels(kinect.getPixels(配列による画像データ).配列による画像の幅, 配列による画像の高さ,イメージタイプ)
        //Kinectで取得した画像をのちに操作するためにsetFromPixels()を使って、
        //ofImageのオブジェクトであるcameraImageを更新して、映像を出力する。
        depthImage.setFromPixels(kinect.getDepthPixels().getData(), kinect.width, kinect.height, OF_IMAGE_GRAYSCALE);
        
        unsigned char * cameraPixels = cameraImage.getPixels().getData();//RGM画像の配列のデータ
        unsigned char * depthPixels = depthImage.getPixels().getData();//深度画像の配列データ
        maskedImage.allocate(kinect.width, kinect.height, OF_IMAGE_COLOR);//maskedImageにメモリを割り当てる
        unsigned char * maskedPixels = maskedImage. getPixels(). getData();//マスク画像の配列データ
        for (int i=0; i<kinect.width*kinect.height; i++) {//配列数分、for文を回す
            if ((255-far.get()<depthPixels[i]) && (depthPixels[i] < 255-near.get())) {//指定範囲内の距離のpixelの時
                maskedPixels[i*3] = cameraPixels[i*3+1];
                maskedPixels[i*3+1] = cameraPixels[i*3+1];
                maskedPixels[i*3+2] = cameraPixels[i*3+2];
            } else{
                maskedPixels[i*3] = 0;
                maskedPixels[i*3+1] = 0;
                maskedPixels[i*3+2] = 0;
            }
        }
        maskedImage.setFromPixels(maskedPixels, kinect.width, kinect.height, OF_IMAGE_COLOR);
    }
    cameraImage.draw(0, 0, kinect.width,kinect.height);
    depthImage.draw(0,kinect.height,kinect.width/2,kinect.height/2);
    ofSetColor(color);
    maskedImage.draw(kinect.width/2, kinect.height, kinect.width/2,kinect.height/2);
    ofSetColor(255);
    //ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, radius.get());//ofParameterの変数.get()でパラメーターの値が取得できる
    
    //ofxGuiを描画
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case ' ':
            kinect.init();
            kinect.open();
            if(!kinect.isConnected()){
                ofSystemAlertDialog("Serial Error: Kinect is not connected. Check a USB port then push space bar.");
            }
            break;
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
