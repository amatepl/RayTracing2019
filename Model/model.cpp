#include "model.h"

Model::Model(WindowModelObservable* windowModelObservale)
{
    m_windowModelObservable = windowModelObservale;
}

Model::~Model(){
    delete [] this;
}

void Model::setScene(QGraphicsScene*scene, BuildingFactory* buildingFactory, CarFactory* carFactory, ReceiverFactory* receiverfactory){

    /* This will have to change
     */

    m_scene = scene;
    MapGenerator* map = new MapGenerator(m_scene->sceneRect());
    map->setScene(m_scene);
    map->setBuildingFactory(buildingFactory);
    map->setCarFactory(carFactory);
    map->generateMap();
    m_receiverfactory = receiverfactory;
    //m_thread = thread((map->moveCars),ref(*map));
    //m_thread.join();
    m_mathematicalComponents["Building"] = map->getProducts();
    //m_windowModelObservable->modelNotify(map->getProducts());
}

void Model::addMathematicalComponent(MathematicalProduct* mathematicalProduct){

    vector<MathematicalProduct*> tmp;
    string type = mathematicalProduct->getType();
//    cout<<type<<"---------------"<<m_mathematicalComponents.count(type)<<endl;
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
            dynamic_cast<ProductObserver*>(m_mathematicalComponents["Transmitter"].at(i))->attachObservable(dynamic_cast<ProductObservable*>(m_mathematicalComponents["Receiver"].at(j)));
        }
    }
}

void Model::setModelObservers(){
    for(int i = 0; i < m_mathematicalComponents.count("Transmitter"); i++){
        //((ModelObserver*)m_mathematicalComponents["Transmitter"].at(i))->attachObservable(this);
        dynamic_cast<ModelObserver*>(m_mathematicalComponents["Transmitter"].at(i))->attachObservable(this);


    }
}

void Model::launchAlgorithm(AlgorithmInterface *algorithm){

    m_algorithm = algorithm;
    //m_algorithm = algorithmFactory->createAlgorithm((MathematicalTransmitterProduct*)m_mathematicalComponents["Transmitter"].at(0), (MathematicalReceiverProduct*)m_mathematicalComponents["Receiver"].at(0));

    //m_algorithm->compute(m_mathematicalComponents["Transmitter"],m_mathematicalComponents["Receiver"].at(0),m_mathematicalComponents["Builiding"]);
    //setObservableProducts();
    m_algorithm->compute(m_mathematicalComponents, m_receiverfactory);
    setModelObservers();
//    for(int i = 0; i < m_mathematicalComponents.count("Receiver"); i++){
//        //((MathematicalReceiverProduct*)m_mathematicalComponents["Receiver"].at(i))->notifyObservers();
//        dynamic_cast<MathematicalReceiverProduct*>(m_mathematicalComponents["Receiver"].at(i))->notifyObservers();
//    }


//    MathematicalTransmitterProduct* transmitter = selectTransmitter();

//    MathematicalReceiverProduct* receiver = (MathematicalReceiverProduct*)m_mathematicalComponents["Receiver"].at(0);

    //m_windowModelObservable->modelAnswer(transmitter->getRays().at(0));

}

MathematicalTransmitterProduct* Model::selectTransmitter(){
       MathematicalTransmitterProduct* transmitter = (MathematicalTransmitterProduct*)m_mathematicalComponents["Transmitter"].at(0);
       return transmitter;
}

void Model::notify(MathematicalTransmitterProduct* transmitter){
    //cout<<"Notifies"<<endl;
//    cout<<"Number of whole rays: "<< (transmitter->getRays()).size()<<endl;
//    for(int i=0;i<transmitter->getRays().size();i++){
//        for(int j=0;j<transmitter->getRays().at(i)->size();j++){
//            cout<<"whole rays nr: "<<i <<" "<<(transmitter->getRays()).at(i)->at(j).p1().x()<<endl;
//        }
//    }
//    vector<vector<MathematicalRayProduct>*> raysTest = transmitter->getRays();

    m_windowModelObservable->modelNotify(transmitter->getRays());
}

