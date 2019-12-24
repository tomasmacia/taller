//
// Created by axel on 25/11/19.
//

#include <iostream>
#include <algorithm>
#include "CollitionBox.h"
#include "../../entityHierarchy/Entity.h"
#include "../ScreenPosition.h"

CollitionBox::CollitionBox(int centerX, int centerY, int centerZ, int w, int h, int d, int id, bool visual) {

    this->visual = visual;

    this->w = w;
    this->h = h;
    this->d = d;
    this->id = id;

    center = new Point(centerX,centerY,centerZ);
    calculateAndAssignCorners(center->x, center->y, center->z);
    calculateCandidates();
    lastMove = candidateMoves->front();
}

void CollitionBox::calculateAndAssignCorners(int centerX, int centerY, int centerZ) {

    corners = new vector<Point*>();

    corners->push_back(new Point(center->x - w/2, center->y - h/2, center->z - d/2));
    corners->push_back(new Point(center->x - w/2, center->y - h/2, center->z + d/2));
    corners->push_back(new Point(center->x - w/2, center->y + h/2, center->z - d/2));       //esta es la esquina que le importa al SDL
    corners->push_back(new Point(center->x - w/2, center->y + h/2, center->z + d/2));
    corners->push_back(new Point(center->x + w/2, center->y - h/2, center->z - d/2));
    corners->push_back(new Point(center->x + w/2, center->y - h/2, center->z + d/2));
    corners->push_back(new Point(center->x + w/2, center->y + h/2, center->z - d/2));       //esta es la esquina que le importa al SDL
    corners->push_back(new Point(center->x + w/2, center->y + h/2, center->z + d/2));
}

bool CollitionBox::anyCornerIntersectsWith(CollitionBox* query) {

    for (auto corner : *corners){
        if (query->hasInsideItsVolume(corner)){
            /*
            string path;
            if (query->getOwner()->isScreen()) {
                path = "screen";
            }
            else{
                int i = 0;
                for (auto s : query->getOwner()->generateSendable()){
                    if (i == 2){
                        path = s->_renderable->getPath();
                    }
                    i++;
                }
            }

            cout<<"corner colliding: from: "<<path<<" ,x: "<<corner->x<<" ,y: "<<corner->y<<" ,z: "<<corner->z<<endl;*/
            return true;
        }
    }
    return false;
}

bool CollitionBox::hasInsideItsVolume(Point* corner){

    int xMin,yMin,zMin,xMax,yMax,zMax;

    if (corners->at(0)->x <= corners->at(7)->x){
        xMin = corners->at(0)->x;
        xMax = corners->at(7)->x;
    }
    else{
        xMin = corners->at(7)->x;
        xMax = corners->at(0)->x;
    }

    yMin = corners->at(0)->y;
    zMin = corners->at(0)->z;
    yMax = corners->at(0)->y + h;
    zMax = corners->at(0)->z + d;

    return  (xMin <= corner->x && corner->x <= xMax)
            &&
            (yMin <= corner->y && corner->y <= yMax)
            &&
            (zMin <= corner->z && corner->z <= zMax);
}

void CollitionBox::moveBy(int xAmount, int yAmount, int zAmount) {

    for (auto corner : *corners){
        corner->moveBy(xAmount,yAmount,zAmount);
    }
    center->moveBy(xAmount,yAmount,zAmount);
}

void CollitionBox::moveBy(Point delta) {

    for (auto corner : *corners){
        corner->moveBy(delta);
    }
    center->moveBy(delta);
}

void CollitionBox::dragToRight(int amount) {
    moveBy(amount, 0, 0);
}

bool CollitionBox::arrived() {
    bool result = lastMove->isZero();
    return result;
}

void CollitionBox::moveOneUnitInTheDirectionOf(Point* destination) {

    center->save();

    int minDistance = center->distanceWith(destination);
    int distance = center->distanceWith(destination);
    Point* bestMove = candidateMoves->front();
    bool inDiscardedMoves;

    for (auto* candidateMove : *candidateMoves){

        inDiscardedMoves = (std::find(discardedMoves->begin(), discardedMoves->end(), candidateMove) != discardedMoves->end());

        if (!inDiscardedMoves){
            center->plus(*candidateMove);
            distance = center->distanceWith(destination);
            if (distance <= minDistance){
                minDistance = distance;
                bestMove = candidateMove;
            }
            center->restore();
        }
    }

    moveBy(*bestMove);
    lastMove = bestMove;
}

Entity *CollitionBox::getOwner() {
    return owner;
}

void CollitionBox::setOwner(Entity *owner) {
    this->owner = owner;
}

bool CollitionBox::intersectsWith(CollitionBox *query) {
    return this->anyCornerIntersectsWith(query) || query->anyCornerIntersectsWith(this);
}

Sendable *CollitionBox::generateSendable() {

    if (screenPosition->onScreen()){

        //int x = screenPosition->getXWithPos(corners->at(2)) + (screenPosition->getWidth() - w)/2;
        //int y = screenPosition->getYWithPos(corners->at(2)) + (screenPosition->getHeight() - h)/2;

        int x,y;

        if (corners->at(0)->x <= corners->at(7)->x){
            x = screenPosition->getXWithPos(corners->at(2));
            y = screenPosition->getYWithPos(corners->at(2));
        }
        else{
            x = screenPosition->getXWithPos(corners->at(6));
            y = screenPosition->getYWithPos(corners->at(6));
        }

        return new Sendable(new Renderable("resources/sprites/fondo_amarillo.png",Rect(0,0,w,h),Rect(x,y,w,h),false), nullptr);
    }
    else{
        return new Sendable(nullptr, nullptr);
    }
}

void CollitionBox::setScreenPosition(ScreenPosition *screenPosition) {
    this->screenPosition = screenPosition;
}

void CollitionBox::calculateCandidates() {

    candidateMoves = new list<Point*>();
    discardedMoves = new list<Point*>();
    //oposites = new map<Point*,Point*>();

    auto m1 = new Point(-1,0,0);
    auto m2 = new Point(0,-1,0);
    auto m3 = new Point(0,0,-1);
    auto m4 = new Point(0,0,0);
    auto m5 = new Point(1,0,0);
    auto m6 = new Point(0,1,0);
    auto m7 = new Point(0,0,1);

    candidateMoves->push_back(m1);
    candidateMoves->push_back(m2);
    candidateMoves->push_back(m3);
    candidateMoves->push_back(m4);
    candidateMoves->push_back(m5);
    candidateMoves->push_back(m6);
    candidateMoves->push_back(m7);

    /*
    oposites->insert({m1,m5});
    oposites->insert({m2,m6});
    oposites->insert({m3,m7});
    oposites->insert({m4,m4});
    oposites->insert({m5,m1});
    oposites->insert({m6,m2});
    oposites->insert({m7,m3});
     */
}

void CollitionBox::restorePreviousPosition() {
    moveBy(center->delta().oposite());
}

void CollitionBox::discardLastMoveAsCandidate() {
    discardedMoves->push_back(lastMove);
}

Point *CollitionBox::getCenter() {
    return center;
}

void CollitionBox::clearDiscardedMoves() {
    discardedMoves->clear();
}

void CollitionBox::setAt(int x, int y, int z) {
    moveBy(x - center->x,y - center->y,z - center->z);
}

void CollitionBox::reflectInXRespectTo(Point *point) {

    //cout<<"reflexion: "<<endl;
    //cout<<"antes: "<<center->x<<endl;
    for (auto corner : *corners){
        corner->applyHomothetyInX(-1, point);
    }
    center->applyHomothetyInX(-1, point);
    //cout<<"desp: "<<center->x<<endl;
}

int CollitionBox::getWidth() {
    return w;
}

void CollitionBox::adaptWidthToRespectTo(int newWidth, Point* point) {

    float scale = (float)newWidth / (float)w;

    //cout<<"cambio de arma: "<<endl;
    //cout<<"w: "<<w<<endl;
    //cout<<"newWidth: "<<newWidth<<endl;
    //cout<<"scale: "<<scale<<endl;
    for (auto corner : *corners){
        corner->applyHomothetyInX(scale,point);
    }
    center->applyHomothetyInX(scale,point);

    w = newWidth;
    //cout<<"modified w: "<<w<<endl;
}

CollitionBox::~CollitionBox() {

    for (auto c : *corners){
        delete(c);
    }
    corners->clear();
    delete (center);
    for (auto c : *candidateMoves){
        delete(c);
    }
    candidateMoves->clear();
    delete(candidateMoves);
    delete (discardedMoves);
}
