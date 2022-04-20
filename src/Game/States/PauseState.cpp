#include "PauseState.h"
#include "GameState.h"

PauseState::PauseState() {
	resumeButton = new Button(ofGetWidth()/2-32, ofGetHeight()/2, 64, 50, "Resume Game?");
	vector<ofImage> rightAnimframes;
    ofImage temp;
	for(int i=0; i<3; i++){
        temp.cropFrom(img1, i*16, 0, 16, 16);
        rightAnimframes.push_back(temp);
    }
	anim = new Animation(10,rightAnimframes);

}
void PauseState::tick() {
	resumeButton->tick();
	anim->tick();
	if(resumeButton->wasPressed()){
		setNextState("Game");
		setFinished(true);

	}
}

void PauseState::render() {
	string title = "Paused";
	ofDrawBitmapString(title, ofGetWidth()/2-4*title.size(), ofGetHeight()/2-300, 50);
	ofSetBackgroundColor(0, 0, 0);
	ofSetColor(256, 256, 256);
	anim->getCurrentFrame().draw(ofGetWidth()/2-50, ofGetHeight()/2-100, 100, 100);
	resumeButton->render();


}

void PauseState::keyPressed(int key){
	
}

void PauseState::mousePressed(int x, int y, int button){
	resumeButton->mousePressed(x, y);
}
   
void PauseState::reset(){
	setFinished(false);
	setNextState("Game");
	resumeButton->reset();
}

void PauseState::setScore(int sc){
    score = sc;
}

PauseState::~PauseState(){
	delete resumeButton;
	delete startButton;
	delete anim;
}