QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4):QT += widgets \
    datavisualization

HEADERS += Abstract_Factory/dialogfactory.h \
    Abstract_Factory/graphicsfactory.h \
    Abstract_Factory/mathematicalfactory.h \
    Abstract_Factory/scenefactory.h \
    Composite/graphicscomponent.h \
    Composite/graphicscomposite.h \
    Graphics/patternwindow.h \
    Graphics/surface3d.h \
    Observer/dialogobservable.h \
    Observer/dialogobserver.h \
    Observer/sceneobservable.h \
    Observer/sceneobserver.h \
    Observer/windowobservable.h \
    Observer/windowobserver.h \
    Product/BuildingProduct/buildingproduct.h \
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
    Share/line.h \
    applicationwindow.h

SOURCES += Abstract_Factory/dialogfactory.cpp \
    Abstract_Factory/graphicsfactory.cpp \
    Abstract_Factory/mathematicalfactory.cpp \
    Composite/graphicscomposite.cpp \
    Graphics/patternwindow.cpp \
    Graphics/surface3d.cpp \
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
    applicationwindow.cpp \
    main.cpp

RESOURCES += \
    Ressources.qrc

DISTFILES +=
