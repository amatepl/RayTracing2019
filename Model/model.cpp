#include "model.h"

Model::Model(WindowModelObservable* windowModelObservale)
{
    m_windowModelObservable = windowModelObservale;
}

Model::~Model()
{
    delete [] this;
}

void Model::setScene(QGraphicsScene*scene, BuildingFactory* buildingFactory,
                     TreeFactory *treeFactory, CarFactory* carFactory,
                     ReceiverFactory* receiverfactory)
{

    /* This will have to change
     */

    m_scene = scene;
    MapGenerator* map = new MapGenerator(m_scene->sceneRect());
    m_mapGenerator = map;
    map->setScene(m_scene);
    map->setBuildingFactory(buildingFactory);
    map->setCarFactory(carFactory);
    map->setTreeFactory(treeFactory);

//    map->generateMap();
    m_receiverfactory = receiverfactory;

//    generateMap();

//    m_mathematicalComponents["Building"] = map->getProducts();

//    m_windowModelObservable->modelNotify(map->getProducts());
}

void Model::addMathematicalComponent(MathematicalProduct* mathematicalProduct)
{

    vector<MathematicalProduct*> tmp;
    string type = mathematicalProduct->getType();
//    cout<<type<<"---------------"<<m_mathematicalComponents.count(type)<<endl;
    if(m_mathematicalComponents.count(type)>0) {
        tmp = m_mathematicalComponents[type];
        tmp.push_back(mathematicalProduct);
        m_mathematicalComponents[type] = tmp;
    } else {
        tmp.push_back(mathematicalProduct);
        m_mathematicalComponents[type] = tmp;
    }
}

void Model::removeMathematicalComponent(MathematicalProduct *mathematicalProduct){
    vector<MathematicalProduct*> tmp;
    string type = mathematicalProduct->getType();
    if(m_mathematicalComponents.count(type)>0) {
        tmp = m_mathematicalComponents[type];
        vector<MathematicalProduct*>::iterator it;
        int i = 0;
        for (it = tmp.begin() ; it <= tmp.end(); it++){
            if (tmp.at(i) == mathematicalProduct){
                tmp.erase(it);
                i--;
            }
            i++;
        }
        m_mathematicalComponents[type] = tmp;
    }
}

void Model::setObservableProducts()
{
    for(unsigned i = 0; i < m_mathematicalComponents.count("Receiver"); i++) {
        for(unsigned j = 0; j < m_mathematicalComponents.count("Transmitter"); j++) {
            dynamic_cast<ProductObservable*>(m_mathematicalComponents["Receiver"].at(i))->attachObserver(
                dynamic_cast<ProductObserver*>(m_mathematicalComponents["Transmitter"].at(j)));
            dynamic_cast<ProductObserver*>(m_mathematicalComponents["Transmitter"].at(i))->attachObservable(
                dynamic_cast<QPointF*>(m_mathematicalComponents["Receiver"].at(j)));
        }
    }
}

void Model::setModelObservers()
{
    if (m_mathematicalComponents["Transmitter"].size() > 0){
        for(unsigned i = 0; i < m_mathematicalComponents.count("Transmitter"); i++) {
            //((ModelObserver*)m_mathematicalComponents["Transmitter"].at(i))->attachObservable(this);
            dynamic_cast<ModelObserver*>(m_mathematicalComponents["Transmitter"].at(i))->attachObservable(this);

        }
    }
}

void Model::launchAlgorithm(AlgorithmInterface *algorithm)
{

    m_algorithm = algorithm;


//    m_algorithm->compute(m_mathematicalComponents["Transmitter"],
//                         m_mathematicalComponents["Receiver"].at(0),
//                         m_mathematicalComponents["Builiding"]);
//    setObservableProducts();

    m_algorithm->compute(m_mathematicalComponents, m_receiverfactory);
    setModelObservers();
//    for(int i = 0; i < m_mathematicalComponents.count("Receiver"); i++){
//        //((Rx*)m_mathematicalComponents["Receiver"].at(i))->notifyObservers();
//        dynamic_cast<Rx*>(m_mathematicalComponents["Receiver"].at(i))->notifyObservers();
//    }


//    Tx* transmitter = selectTransmitter();

//    Rx* receiver = (Rx*)m_mathematicalComponents["Receiver"].at(0);

    //m_windowModelObservable->modelAnswer(transmitter->getRays().at(0));

}

void Model::startCars()
{
    m_mapGenerator->startCars();
}


Tx* Model::selectTransmitter()
{
    Tx* transmitter = (Tx*)
            m_mathematicalComponents["Transmitter"].at(0);
    return transmitter;
}

void Model::notify(Tx* transmitter)
{
    //cout<<"Notifies"<<endl;
//    cout<<"Number of whole rays: "<< (transmitter->getRays()).size()<<endl;
//    for(int i=0;i<transmitter->getRays().size();i++){
//        for(int j=0;j<transmitter->getRays().at(i)->size();j++){
//            cout<<"whole rays nr: "<<i <<" "<<(transmitter->getRays()).at(i)->at(j).p1().x()<<endl;
//        }
//    }
//    vector<vector<Ray>*> raysTest = transmitter->getRays();

    m_windowModelObservable->modelNotify(transmitter->getRays());
}

void Model::generateMap(unsigned h, unsigned w, unsigned cars, unsigned wstrs, unsigned strsGap, double px_to_meter)
{
    m_mapGenerator->generateMap(h, w, cars, wstrs, strsGap, px_to_meter);
    vector<MathematicalProduct *> mapProducts = m_mapGenerator->getProducts();
    for (unsigned i = 0; i < mapProducts.size(); i++) {
        string type = mapProducts.at(i)->getType();
        m_mathematicalComponents[type].push_back(mapProducts.at(i));
    }
}

void Model::clear()
{
    m_mathematicalComponents.clear();
}

void Model::clearWorkspace()
{
//    delete m_mapGenerator;

    for (auto &objType: m_mathematicalComponents) {
        for(auto &obj: objType.second){
            delete obj;
        }
    }
    m_mathematicalComponents.clear();
    m_mapGenerator->clear();
}
