#include "Gps.h"

//this is the constructor of the class Gps.
Gps::Gps(Point* p, Point* p2) {//we change
    pS = p;
    pE = p2;
}
//this function start the bfs algo.
queue <CheckPoint*> Gps::start(Grid* g) {
    //take the start point.
    CheckPoint* pSG = g->giving(pS->getX_axis(), pS->getY_axis());
    queue <CheckPoint*> Q1;
    queue <CheckPoint*> Q2;
    //if this is the end point we push it to the queue and return. this is the path.
    if(pSG->getX_axis() == pE->getX_axis() && pSG->getY_axis() == pE->getY_axis()) {
        Q1.push(pSG);
        return Q1;
        //so we start to ask the logic of the algo about this point.
    } else {
        pSG->setIsToched();
        CheckPoint* pointToCheckLeft = g->giving(pSG->getX_axis() - 1, pSG->getY_axis());
        //if we have point we say that we touched her for the check later and push her
        //to the queue (same logic for the next tree if-eim).
        if(pointToCheckLeft != NULL && pointToCheckLeft->exisGetBool()) {
            pointToCheckLeft->setIsToched();
            Q1.push(pointToCheckLeft);
        }
        CheckPoint* pointToCheckUp = g->giving(pSG->getX_axis(), pSG->getY_axis()+1);
        if(pointToCheckUp != NULL && pointToCheckUp->exisGetBool()) {
            pointToCheckUp->setIsToched();
            Q1.push(pointToCheckUp);
        }
        CheckPoint* pointToCheckRight = g->giving(pSG->getX_axis()+1, pSG->getY_axis());
        if(pointToCheckRight != NULL && pointToCheckRight->exisGetBool()) {
            pointToCheckRight->setIsToched();
            Q1.push(pointToCheckRight);
        }
        CheckPoint* pointToCheckDown = g->giving(pSG->getX_axis(), pSG->getY_axis()-1);
        if (pointToCheckDown != NULL && pointToCheckDown->exisGetBool()) {
            pointToCheckDown->setIsToched();
            Q1.push(pointToCheckDown);

        } // push the first point into queue 2, that will give us the path in the end.
        Q2.push(pSG);
    } // we ask to go over the first queue for finding all the point`s that have a connection
    // with other point`s so we put them in queue2, otherwise we don`t.
    while(!Q1.empty()) {
        CheckPoint* pfront = Q1.front();
        Q1.pop();
        // in case the point is the end we push it back to the queue, because
        // we know she build the path.
        //ask for the left n
        CheckPoint *pointToCheckLeft = g->giving((pfront->getX_axis() - 1), pfront->getY_axis());
        if (pointToCheckLeft != NULL && pointToCheckLeft->exisGetBool()) {
            //exist that`s why we ask if some one touched him before
            if (!(g->giving((pfront->getX_axis() - 1), pfront->getY_axis())->getIsTouchd())) {
                //setting in p that he have LN
                g->giving((pfront->getX_axis()), pfront->getY_axis())->setFirstNeighbor(true);
                //setting in LN that some one touched him
                g->giving((pfront->getX_axis() - 1), pfront->getY_axis())->setIsToched();
                //we put him in the queue
                Q1.push(g->giving((pfront->getX_axis() - 1), pfront->getY_axis()));
            }
        }
        //ask for the upper n
        CheckPoint *pointToCheckUp = g->giving((pfront->getX_axis()), pfront->getY_axis() + 1);
        if (pointToCheckUp != NULL && pointToCheckUp->exisGetBool()) {
            //exist that why we ask if some one touched him before
            if (!(g->giving((pfront->getX_axis()), pfront->getY_axis() + 1)->getIsTouchd())) {
                //setting in p that he have UN
                g->giving((pfront->getX_axis()), pfront->getY_axis())->setSecondNeighbor(true);
                //setting in UN that some one touched him
                g->giving((pfront->getX_axis()), pfront->getY_axis() + 1)->setIsToched();
                //we put him in the queue
                Q1.push(g->giving((pfront->getX_axis()), pfront->getY_axis() + 1));
            }
        }
        //ask for the right n
        CheckPoint *pointToCheckRight = g->giving((pfront->getX_axis() + 1), pfront->getY_axis());
        if (pointToCheckRight != NULL && pointToCheckRight->exisGetBool()) {
            //exist that why we ask if some one touched him before
            if (!(g->giving((pfront->getX_axis() + 1), pfront->getY_axis())->getIsTouchd())) {
                //setting in p that he have RN
                g->giving((pfront->getX_axis()), pfront->getY_axis())->setThirdNeighbor(true);
                //setting in RN that some one touched him
                g->giving((pfront->getX_axis() + 1), pfront->getY_axis())->setIsToched();
                //we put him in the queue
                Q1.push(g->giving((pfront->getX_axis() + 1), pfront->getY_axis()));
            }
        }
        //ask for the d n
        CheckPoint *pointToCheckDown = g->giving((pfront->getX_axis()), pfront->getY_axis() - 1);
        if (pointToCheckDown != NULL && pointToCheckDown->exisGetBool()) {
            //exist that why we ask if some one touched him before
            if (!(g->giving((pfront->getX_axis()), pfront->getY_axis() - 1)->getIsTouchd())) {
                //setting in p that he have DN
                g->giving((pfront->getX_axis()), pfront->getY_axis())->setForthNeighbor(true);
                //setting in DN that some one touched him
                g->giving((pfront->getX_axis()), pfront->getY_axis() - 1)->setIsToched();
                //we put him in the queue
                Q1.push(g->giving((pfront->getX_axis()), pfront->getY_axis() - 1));
            }
        } // we make shore that the point have at least one friend and push her to the queue
        // otherwise we say she don`t exist (for checking later).
        if (askNE(*pfront) || (pfront->getX_axis() == pE->getX_axis() &&
                               pfront->getY_axis() == pE->getY_axis())) {
            Q2.push(pfront);
        } else {
            g->giving((pfront->getX_axis()), pfront->getY_axis())->exisSetBool();
        }

    }
    return returnPath(g, Q2);
}
//this function get the queue2, we have there that path, the next logic will take out
//all the point that have no connection(not exist) and return the queue with the path.
queue <CheckPoint*> Gps::returnPath(Grid* g, queue <CheckPoint*> q) {
    int size = q.size()*q.size();
    do {
        CheckPoint* pC = q.front();
        q.pop();
        size--;
        // we ask if the point is one of end or start point, and push it back.
        if((((pC->getX_axis() == pS->getX_axis()) && pC->getY_axis() == pS->getY_axis()))||
           (((pC->getX_axis() == pE->getX_axis()) && pC->getY_axis() == pE->getY_axis()))) {
            q.push(pC);
            //        csize++;
            //size++;
            // otherwise we want to know if the point still have a connection,
            // in that case we push the point back to the path queue.
        } else {
            if(askNE(*pC)) {
                // we ask the point if she have left neighbor.
                if(pC->isFirstNeighborExist()) {
                    // we don`t believe her, so we check if the point really exist
                    //(same logic for the next 4 if-eim).
                    if(g->giving(pC->getX_axis()-1, pC->getY_axis())->exisGetBool()) {
                        q.push(pC);
                        size++;
                        continue;
                    }
                    else{
                        pC->setFirstNeighbor(false);
                    }
                }
                if(pC->isSeondNeighborExist()) {
                    if(g->giving(pC->getX_axis(), pC->getY_axis()+1)->exisGetBool()) {
                        q.push(pC);
                        size++;
                        continue;
                    }
                    else{
                        pC->setSecondNeighbor(false);
                    }

                }
                if(pC->isThirdNeighborExist()) {
                    if(g->giving(pC->getX_axis()+1, pC->getY_axis())->exisGetBool()) {
                        q.push(pC);
                        size++;
                        continue;
                    }
                    else{
                        pC->setThirdNeighbor(false);
                    }
                }
                if(pC->isForthNeighborExist()) {
                    if(g->giving(pC->getX_axis(), pC->getY_axis()-1)->exisGetBool()) {
                        q.push(pC);
                        size++;
                        continue;
                    }
                    else{
                        pC->setForthNeighbor(false);
                    }
                }
                if(!askNE(*pC)){
                    pC->exisSetBool();
                }
                //she don`t have neighbor :(, we pop her from the path queue.
            } else {
                pC->exisSetBool();
                q.pop();
                size--;
            }
        }
    } while (size > 0);
    return getOrganized(q);
}
queue <CheckPoint*> Gps::getOrganized(queue <CheckPoint*> q) {
    CheckPoint* pToCheck = q.front();
    CheckPoint* dummy;
    q.pop();
    while((pToCheck->getX_axis() != this->getEnd()->getX_axis()) ||
          (pToCheck->getY_axis() != this->getEnd()->getY_axis()) ){
        dummy = pToCheck;
        q.push(dummy);
        pToCheck = q.front();
        q.pop();
    }
    q.push(pToCheck);
    return q;
}
// the next function ask to know if some point have at least one connection and return true.
bool Gps::askNE(CheckPoint &pI) {
    if(pI.isFirstNeighborExist() || pI.isSeondNeighborExist() || pI.isForthNeighborExist()
       || pI.isThirdNeighborExist()) {
        return true;
    }
    return false;
}
//this is a getter for the x value of the GPS
int Gps::getX() {
    return this->x;
}
//this is a getter for the Y value of the GPS
int Gps::getY() {
    return this->y;
}
//default constructor
Gps::Gps() {}
//destractor
Gps::~Gps() {

}
//this is a getter method for the gps start point
Point* Gps::getStart(){
    return this->pS;
}
//this is a getter method for the gps end point
Point* Gps::getEnd(){
    return this->pE;
}
//this is a setter method for the gps start point
void Gps::setStart(Point* point){
    this->pS = point;
}
//this is a setter method for the gps end point
void Gps::setEnd(Point* point){
    this->pE = point;
}