#include "model.h"

Model::Model()
{

}

Model::~Model(){
    delete [] this;
}

void Model::addMathematicalComponent(string type, MathematicalProduct* mathematicalComponent){
    vector<MathematicalProduct*> tmp;
    if(m_mathematicalComponents.count(type)>0){
        tmp = m_mathematicalComponents[type];
        tmp.push_back(mathematicalComponent);
        m_mathematicalComponents[type] = tmp;
     }
    else{
        tmp.push_back(mathematicalComponent);
        m_mathematicalComponents[type] = tmp;
    }
}

void Model::setObservableProducts(){

    for(int i = 0; i < m_mathematicalComponents.count("InsertReceiver"); i++){
        for(int j = 0; j < m_mathematicalComponents.count("InsertTransmitter"); j++){
            ((ProductObservable*)m_mathematicalComponents["InsertReceiver"].at(i))->attachObserver((ProductObserver*)m_mathematicalComponents["InsertTransmitter"].at(j));
        }
    }
}
