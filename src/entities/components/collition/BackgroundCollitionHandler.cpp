//
// Created by axel on 28/11/19.
//

#include "BackgroundCollitionHandler.h"

BackgroundCollitionHandler::BackgroundCollitionHandler(CollitionManager* collitionManager,
                                                       list<CollitionBox *>* collitionBoxes) {
    _collitionBoxes = collitionBoxes;
    _collitionManager = collitionManager;
}

BackgroundCollitionHandler::~BackgroundCollitionHandler() {

    for (auto box : *_collitionBoxes){
        delete(box);
    }
    _collitionBoxes->clear();
    delete(_collitionBoxes);
}
