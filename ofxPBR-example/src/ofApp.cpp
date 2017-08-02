#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(0);
	ofSetVerticalSync(false);

    ofDisableArbTex();
    
    cam.setupPerspective(false, 60, 1, 5000);

	scene = bind(&ofApp::renderScene, this);

    cubeMap.load("Barce_Rooftop_C_3k.jpg", 1024, true, "filteredMapCache");
    pbr.setup(scene, &cam, 2048);
    pbr.setCubeMap(&cubeMap);
	pbr.setDrawEnvironment(true);
    
    render.load("ofxPBRShaders/default2.vert", "ofxPBRShaders/default2.frag");
    
	light.setup();
	//light.setEnable(true);
 //   light.setLightType(LightType_Directional);
 //   light.setPosition(-500, 1000, 500);
 //   light.lookAt(ofVec3f(0));
	//light.setScale(1.0);
	//light.setColor(ofFloatColor(1.0));
	//light.setShadowType(ShadowType_Hard);
//	//light.setSpotLightDistance(5000);
//	//light.setSpotLightCutoff(45);
//	//light.setSpotLightFactor(5.0);
////    light.setPointLightRadius(5000);
//    light.setNearClip(1.0);
//    light.setFarClip(5000);
	pbr.addLight(&light);

	//light2.setup();
    //light2.setLightType(LightType_Directional);
    //light2.setPosition(1500, 1000, 1500);
    //light2.lookAt(ofVec3f(0));
    //light2.setScale(1.5);
    //light2.setColor(ofFloatColor(1.0));
    //light2.setShadowType(ShadowType_Hard);
    //pbr.addLight(&light2);
    
    cubeMap.setEnvLevel(0.3);
}

//--------------------------------------------------------------
void ofApp::update(){
	light.setPosition(-1000 * sin(ofGetElapsedTimef()), 1000, 1000 * cos(ofGetElapsedTimef()));
	light.lookAt(ofVec3f(0));

	light2.setPosition(1000 * sin(ofGetElapsedTimef()), 500, -1000 * cos(ofGetElapsedTimef()));
	light2.lookAt(ofVec3f(0));
}

//--------------------------------------------------------------
void ofApp::draw(){
	prevTime = ofGetElapsedTimef();

	pbr.updateDepthMaps();

	cam.begin();
	pbr.renderScene();
	cam.end();

	pbr.getDepthMap(0)->draw(0, 0, 256, 256);

    ofSetWindowTitle(ofToString(ofGetFrameRate()));
	float t = ofGetElapsedTimef() - prevTime;
	ofDrawBitmapString(ofToString(t), 20, 20);
}

//--------------------------------------------------------------
void ofApp::renderScene(){
	ofEnableDepthTest();
	//glEnable(GL_CULL_FACE);
    pbr.beginCustomRenderer(&render);
    {
        material.roughness = 0.25;
        material.metallic = 0.0;
        material.begin(&pbr);
		//glCullFace(GL_BACK);
        ofDrawBox(0, -40, 0, 2000, 10, 2000);
        material.end();
        
		//glCullFace(GL_FRONT);
        for(int i=0;i<10;i++){
            material.roughness = float(i) / 9.0;
            for(int j=0;j<10;j++){
                material.metallic = float(j) / 9.0;
                material.begin(&pbr);
                ofDrawSphere(i * 100 - 450, 0, j * 100 - 450, 35);
//                ofDrawBox(i * 100 - 450, 0, j * 100 - 450, 35, 100, 35);
                material.end();
            }
        }
	}
	pbr.endCustomRenderer();
	//glDisable(GL_CULL_FACE);
	ofDisableDepthTest();
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
