QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4):QT += widgets \
    datavisualization

HEADERS += Abstract_Factory/dialogfactory.h \
    Abstract_Factory/abstractalgorithmfactory.h \
    Abstract_Factory/abstractrayfactory.h \
    Abstract_Factory/buildingfactory.h \
    Abstract_Factory/carfactory.h \
    Abstract_Factory/rayfactory.h \
    Abstract_Factory/raytracingalgorithmfactory.h \
    Abstract_Factory/receiverfactory.h \
    Abstract_Factory/scenefactory.h \
    Abstract_Factory/transmitterfactory.h \
    Abstract_Factory/treefactory.h \
    Graphics/patternwindow.h \
    Graphics/surface3d.h \
    Model/algorithmInterface.h \
    Model/imagesmethod.h \
    Model/model.h \
    Observer/AppInterface.h \
    Model/raytracing.h \
    Observer/dialogobservable.h \
    Observer/dialogobserver.h \
    Observer/modelobservable.h \
    Observer/modelobserver.h \
    Observer/productobservable.h \
    Observer/productobserver.h \
    Observer/sceneobservable.h \
    Observer/sceneobserver.h \
    Observer/windowobserver.h \
    Observer/windowomodelbservable.h \
    Product/BuildingProduct/dialogbuildingproduct.h \
    Product/BuildingProduct/graphicsbuildingproduct.h \
    Product/BuildingProduct/mathematicalbuildingproduct.h \
    Product/CarProduct/carproduct.h \
    Product/CarProduct/dialogcarproduct.h \
    Product/CarProduct/graphicscarproduct.h \
    Product/CarProduct/mathematicalcarproduct.h \
    Product/RayProduct/graphicsrayproduct.h \
    Product/RayProduct/mathematicalrayproduct.h \
    Product/RayProduct/rayproduct.h \
    Product/ReceiverProduct/dialogreceiverproduct.h \
    Product/ReceiverProduct/graphicsreceiverproduct.h \
    Product/ReceiverProduct/mathematicalreceiverproduct.h \
    Product/ReceiverProduct/receiverproduct.h \
    Product/TransmitterProduct/dialogtransmitterproduct.h \
    Product/TransmitterProduct/graphicstransmitterproduct.h \
    Product/TransmitterProduct/mathematicaltransmitterproduct.h \
    Product/TransmitterProduct/transmitterproduct.h \
    Product/TreeProduct/dialogtreeproduct.h \
    Product/TreeProduct/graphicstreeproduct.h \
    Product/TreeProduct/mathematicaltreeproduct.h \
    Product/TreeProduct/treeproduct.h \
    Product/abstractantena.h \
    Product/graphicsproduct.h \
    Product/mathematicalproduct.h \
    Product/sceneproduct.h \
    Share/line.h \
    Share/wall.h \
    applicationwindow.h \
    graphicsmap.h

SOURCES += Abstract_Factory/dialogfactory.cpp \
    Abstract_Factory/buildingfactory.cpp \
    Abstract_Factory/carfactory.cpp \
    Abstract_Factory/rayfactory.cpp \
    Abstract_Factory/raytracingalgorithmfactory.cpp \
    Abstract_Factory/receiverfactory.cpp \
    Abstract_Factory/transmitterfactory.cpp \
    Abstract_Factory/treefactory.cpp \
    Graphics/patternwindow.cpp \
    Graphics/surface3d.cpp \
    Model/imagesmethod.cpp \
    Model/model.cpp \
    Model/raytracing.cpp \
    Product/BuildingProduct/dialogbuildingproduct.cpp \
    Product/BuildingProduct/graphicsbuildingproduct.cpp \
    Product/BuildingProduct/mathematicalbuildingproduct.cpp \
    Product/CarProduct/dialogcarproduct.cpp \
    Product/CarProduct/graphicscarproduct.cpp \
    Product/CarProduct/mathematicalcarproduct.cpp \
    Product/RayProduct/graphicsrayproduct.cpp \
    Product/RayProduct/mathematicalrayproduct.cpp \
    Product/ReceiverProduct/dialogreceiverproduct.cpp \
    Product/ReceiverProduct/graphicsreceiverproduct.cpp \
    Product/ReceiverProduct/mathematicalreceiverproduct.cpp \
    Product/TransmitterProduct/dialogtransmitterproduct.cpp \
    Product/TransmitterProduct/graphicstransmitterproduct.cpp \
    Product/TransmitterProduct/mathematicaltransmitterproduct.cpp \
    Product/TreeProduct/dialogtreeproduct.cpp \
    Product/TreeProduct/graphicstreeproduct.cpp \
    Product/TreeProduct/mathematicaltreeproduct.cpp \
    Share/line.cpp \
    Share/wall.cpp \
    applicationwindow.cpp \
    graphicsmap.cpp \
    main.cpp

RESOURCES += \
    Ressources.qrc

DISTFILES +=
