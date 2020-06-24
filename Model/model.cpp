#include "model.h"

Model::Model(WindowModelObservable* windowModelObservale)
{
    m_windowModelObservable = windowModelObservale;
}

Model::~Model(){
    delete [] this;
}

void Model::addMathematicalComponent(MathematicalProduct* mathematicalProduct){
    vector<MathematicalProduct*> tmp;
    string type = mathematicalProduct->getType();
    if(m_mathematicalComponents.count(type)>0){
        tmp = m_mathematicalComponents[type];
        tmp.push_back(mathematicalProduct);
        m_mathematicalComponents[type] = tmp;
     }
    else{
        tmp.push_back(mathematicalProduct);
        m_mathematicalComponents[type] = tmp;
    }
}

void Model::setObservableProducts(){
    for(int i = 0; i < m_mathematicalComponents.count("Receiver"); i++){
        for(int j = 0; j < m_mathematicalComponents.count("Transmitter"); j++){
            //((ProductObservable*)m_mathematicalComponents["Receiver"].at(i))->attachObserver((ProductObserver*)m_mathematicalComponents["Transmitter"].at(j));
            dynamic_cast<ProductObservable*>(m_mathematicalComponents["Receiver"].at(i))->attachObserver(dynamic_cast<ProductObserver*>(m_mathematicalComponents["Transmitter"].at(j)));
        }
    }
}

void Model::setModelObservers(){
    for(int i = 0; i < m_mathematicalComponents.count("Transmitter"); i++){
        ((ModelObserver*)m_mathematicalComponents["Transmitter"].at(i))->attachObservable(this);
    }
}

void Model::launchAlgorithm(AbstractAlgorithmFactory* algorithmFactory){
    cout<<"Algortihm Launched"<<endl;
    m_algorithm = algorithmFactory->createAlgorithm((MathematicalTransmitterProduct*)m_mathematicalComponents["Transmitter"].at(0), (MathematicalReceiverProduct*)m_mathematicalComponents["Receiver"].at(0));
    cout<<"Algorithm created"<<endl;
    //m_algorithm->compute();
    setObservableProducts();
    for(int i = 0; i < m_mathematicalComponents.count("Receiver"); i++){
        cout<<"Observer Notified"<<endl;
        //((MathematicalReceiverProduct*)m_mathematicalComponents["Receiver"].at(i))->notifyObservers();
        dynamic_cast<MathematicalReceiverProduct*>(m_mathematicalComponents["Receiver"].at(i))->notifyObservers();
    }
    MathematicalTransmitterProduct* transmitter = selectTransmitter();

    MathematicalReceiverProduct* receiver = (MathematicalReceiverProduct*)m_mathematicalComponents["Receiver"].at(0);

    cout<<"Transmitter selected"<<endl;


    m_windowModelObservable->modelAnswer(transmitter->getRays().at(0));
    cout<<"Algortihm Launched"<<endl;

}

MathematicalTransmitterProduct* Model::selectTransmitter(){
       MathematicalTransmitterProduct* transmitter = (MathematicalTransmitterProduct*)m_mathematicalComponents["Transmitter"].at(0);
       return transmitter;
}

void Model::notify(MathematicalTransmitterProduct* transmitter){

}

