//
// Created by axel on 28/11/19.
//

#include "BackgroundCollitionHandler.h"

BackgroundCollitionHandler::BackgroundCollitionHandler(CollitionManager* collitionManager, list<CollitionBox *>* collitionBoxes)

                                                       :CollitionHandler(collitionManager){
    _collitionBoxes = collitionBoxes;
    _blockingCollitionBoxes = collitionBoxes;
}