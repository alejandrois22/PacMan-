#include "MapBuilder.h"


MapBuilder::MapBuilder(){
	entityManager = new EntityManager();
	pixelMultiplier = 16;
	boundBoundBlock = ofColor(0,0,0);
	pacman = ofColor(255,255, 0);
	ghostC = ofColor(25, 255,0);
	dotC = ofColor(255, 10, 0);
	bigDotC = ofColor(167, 0, 150);
	cherryC = ofColor(0, 0, 255);
	strawberryC = ofColor(0,255,255);
	pacmanSpriteSheet.load("images/Background.png");
	tempBound.cropFrom(pacmanSpriteSheet, 603,18,16,16);
	bound.push_back(tempBound);//single
	tempBound.cropFrom(pacmanSpriteSheet, 615,37,16,16);
	bound.push_back(tempBound);//single
	tempBound.cropFrom(pacmanSpriteSheet, 635,37,16,16);
	bound.push_back(tempBound);//single
	tempBound.cropFrom(pacmanSpriteSheet, 655,37,16,16);
	bound.push_back(tempBound);//single
	tempBound.cropFrom(pacmanSpriteSheet, 655,57,16,16);
	bound.push_back(tempBound);//single
	tempBound.cropFrom(pacmanSpriteSheet, 655,75,16,16);
	bound.push_back(tempBound);//single
	tempBound.cropFrom(pacmanSpriteSheet, 656,116,16,16);
	bound.push_back(tempBound);//single
	tempBound.cropFrom(pacmanSpriteSheet, 656,136,16,16);
	bound.push_back(tempBound);//single
	tempBound.cropFrom(pacmanSpriteSheet, 655,174,16,16);
	bound.push_back(tempBound);//single
	tempBound.cropFrom(pacmanSpriteSheet, 655,155,16,16);
	bound.push_back(tempBound);//single
	tempBound.cropFrom(pacmanSpriteSheet, 655,192,16,16);
	bound.push_back(tempBound);//single
	tempBound.cropFrom(pacmanSpriteSheet, 664,232,16,16);
	bound.push_back(tempBound);//single
	tempBound.cropFrom(pacmanSpriteSheet, 479,191,16,16);
	bound.push_back(tempBound);//single
	tempBound.cropFrom(pacmanSpriteSheet, 494,191,16,16);
	bound.push_back(tempBound);//single
	tempBound.cropFrom(pacmanSpriteSheet, 479,208,16,16);
	bound.push_back(tempBound);//single
	tempBound.cropFrom(pacmanSpriteSheet, 479,223,16,16);
	bound.push_back(tempBound);//single
}

Map* MapBuilder::createMap(ofImage mapImage){
	int xOffset = (ofGetWidth() - mapImage.getWidth()*pixelMultiplier)/2;
	int yOffset = (ofGetHeight() - mapImage.getHeight()*pixelMultiplier)/2;

	ofPixels pixels = mapImage.getPixels();
	Map* mapInCreation =  new Map(entityManager);
	mapInCreation->setOffsets(pixelMultiplier, xOffset, yOffset);
	vector<vector<int>> maze;
    for (int i = 0; i < mapImage.getWidth(); i++) {
		maze.push_back(vector<int>());
        for (int j = 0; j < mapImage.getHeight(); j++) {
			bool foundWall = false;
            ofColor currentPixel = pixels.getColor(i, j);
            int xPos = i*pixelMultiplier + xOffset;
            int yPos = j*pixelMultiplier + yOffset;

            if(currentPixel == boundBoundBlock){
                BoundBlock* BoundBoundBlock = new BoundBlock(xPos,yPos,pixelMultiplier,pixelMultiplier,getSprite(mapImage,i,j));
                mapInCreation->addBoundBlock(BoundBoundBlock);
				foundWall = true;
            }else if(currentPixel == pacman){
                Player* PacMan = new Player(xPos,yPos,pixelMultiplier,pixelMultiplier, entityManager);
				mapInCreation->setPlayer(PacMan);
            }else if(currentPixel == ghostC){
                GhostSpawner* ghostSpawn = new GhostSpawner(xPos,yPos,pixelMultiplier,pixelMultiplier,entityManager, pacmanSpriteSheet);
                mapInCreation->setGhostSpawner(ghostSpawn);
				mapInCreation-> gx = xPos;
				mapInCreation-> gy = yPos;
            }else if(currentPixel == dotC){
                Dot* dot = new Dot(xPos,yPos,pixelMultiplier,pixelMultiplier, pacmanSpriteSheet);
                mapInCreation->addEntity(dot);
            }else if(currentPixel == bigDotC){
                BigDot* bigDot = new BigDot(xPos,yPos,pixelMultiplier,pixelMultiplier, pacmanSpriteSheet);
                mapInCreation->addEntity(bigDot);
            }else if(currentPixel == strawberryC){
                ShowStrawberry* strawberry = new ShowStrawberry(xPos,yPos,pixelMultiplier,pixelMultiplier, pacmanSpriteSheet);
                mapInCreation->addEntity(strawberry);
            }else if(currentPixel == cherryC){
                ShowCherry* cherry = new ShowCherry(xPos,yPos,pixelMultiplier,pixelMultiplier, pacmanSpriteSheet);
                mapInCreation->addEntity(cherry);
            }	
			maze[i].push_back(foundWall? 0:1);
        }
    }
	mapInCreation->setMaze(maze);
    return mapInCreation;
}

ofImage MapBuilder::getSprite(ofImage mapImage, int i, int j){
	ofColor currentPixel = boundBoundBlock;
	ofPixels pixels = mapImage.getPixels();
	ofColor leftPixel;
	ofColor rightPixel;
	ofColor upPixel;
	ofColor downPixel;
	if (i>0) {
		leftPixel = pixels.getColor(i - 1, j);
	}else{
		leftPixel = pacman;
	}
	if (i<mapImage.getWidth()-1) {
		rightPixel = pixels.getColor(i + 1, j);
	}else{
		rightPixel= pacman;

	}
	if (j>0) {
		upPixel = pixels.getColor(i, j - 1);
	}else{
		upPixel = pacman;

	}
	if (j<mapImage.getHeight()-1) {
		downPixel = pixels.getColor(i, j + 1);
	}else{
		downPixel = pacman;
	}

	if (currentPixel != leftPixel && currentPixel != upPixel && currentPixel != downPixel && currentPixel == rightPixel){

		return bound[1];
	}else if (currentPixel != leftPixel && currentPixel != upPixel && currentPixel == downPixel && currentPixel != rightPixel){

		return bound[2];
	}else if (currentPixel == leftPixel && currentPixel != upPixel && currentPixel != downPixel && currentPixel != rightPixel){

		return bound[3];
	}else if (currentPixel != leftPixel && currentPixel == upPixel && currentPixel != downPixel && currentPixel != rightPixel){

		return bound[4];
	}else if (currentPixel != leftPixel && currentPixel == upPixel && currentPixel == downPixel && currentPixel != rightPixel){

		return bound[5];
	}else if (currentPixel == leftPixel && currentPixel != upPixel && currentPixel != downPixel && currentPixel == rightPixel){

		return bound[6];
	}else if (currentPixel != leftPixel && currentPixel == upPixel && currentPixel != downPixel && currentPixel == rightPixel){

		return bound[7];
	}else if (currentPixel == leftPixel && currentPixel == upPixel && currentPixel != downPixel && currentPixel != rightPixel){

		return bound[8];
	}else if (currentPixel != leftPixel && currentPixel != upPixel && currentPixel == downPixel && currentPixel == rightPixel){

		return bound[9];
	}else if (currentPixel == leftPixel && currentPixel != upPixel && currentPixel == downPixel && currentPixel != rightPixel){

		return bound[10];
	}else if (currentPixel == leftPixel && currentPixel == upPixel && currentPixel == downPixel && currentPixel == rightPixel){

		return bound[11];
	}else if (currentPixel != leftPixel && currentPixel == upPixel && currentPixel == downPixel && currentPixel == rightPixel){

		return bound[12];
	}else if (currentPixel == leftPixel && currentPixel == upPixel && currentPixel == downPixel && currentPixel != rightPixel){

		return bound[13];
	}else if (currentPixel == leftPixel && currentPixel != upPixel && currentPixel == downPixel && currentPixel == rightPixel){

		return bound[14];
	}else if (currentPixel == leftPixel && currentPixel == upPixel && currentPixel != downPixel && currentPixel == rightPixel){

		return bound[15];
	}else{

		return  bound[0];
	}
}