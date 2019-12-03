#include "Receiver.h"

Receiver::Receiver(QPointF pos, AbstractScene *scene,Mode myMode):QPointF(pos), m_scene(scene)
{
    m_mode = myMode;
    switch(myMode){
        case RayTracing:addToScene();
    }
}

Receiver::~Receiver(void){
    m_scene->clearRays();
}

void Receiver::addAntenaImage(ReceiverObserver* antenaImage){
    m_antenaImages.push_back(antenaImage);
}

void Receiver::addToScene()
{
    m_graphicsReceiver = new GraphicsReceiver(QPointF(0,0),this);
    m_graphicsReceiver->setPos(*this);
    m_scene->addToScene(m_graphicsReceiver);

}

void Receiver::moveToPosition(const QPointF &pos){
    m_scene->clearRays();
    m_scene->clearEMFIeld();
    setX(pos.x());
    setY(pos.y());
    m_wholeRays.clear();
    m_wholeRays.shrink_to_fit();
    notifyObservers();
}

void Receiver::notifyObservers(){
    foreach(ReceiverObserver* observer, m_antenaImages){
        observer->notifyObserver(*this);
    }
    switch(m_mode){
        case RayTracing:m_scene->drawChosenRays();
    }

}

void Receiver::addWholeRay(vector<ray> *wholeRay){
    m_wholeRays.push_back(wholeRay);
    //addWholeRayToScene(wholeRay);
    switch(m_mode){
        case RayTracing:m_scene->drawRays(wholeRay);
    }
    m_scene->computeEMField(wholeRay);
}

void Receiver::addRaysToScene(){
    for(int i = 0;i<m_wholeRays.size();i++){
        for(int j = 0;j<m_wholeRays.at(i)->size();j++){
            QGraphicsLineItem *graphicsRay = new QGraphicsLineItem(m_wholeRays.at(i)->at(j));
            m_scene->addToScene(graphicsRay);
        }
    }
}

void Receiver::addWholeRayToScene(vector<ray> *wholeRay){
    for(int j = 0;j<wholeRay->size();j++){
        QGraphicsLineItem *graphicsRay = new QGraphicsLineItem(wholeRay->at(j));
        m_scene->addToScene(graphicsRay);
    }
}

