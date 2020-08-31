QT       += core gui \
    gui widgets

greaterThan(QT_MAJOR_VERSION, 4):QT += widgets printsupport \
    datavisualization

CONFIG += c++1z

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
    Graphics/abstractpattern.h \
    Graphics/interfererencepattern.h \
    Graphics/patternwindow.h \
    Graphics/surface3d.h \
    Model/algorithmInterface.h \
    Model/coverage.h \
    Model/imagesmethod.h \
    Model/mapgenerator.h \
    Model/model.h \
    Observer/AppInterface.h \
    Model/raytracing.h \
    Observer/modelobservable.h \
    Observer/modelobserver.h \
    Observer/movingobstacle.h \
    Observer/productobservable.h \
    Observer/productobserver.h \
    Observer/sceneobservable.h \
    Observer/sceneobserver.h \
    Observer/windowobserver.h \
    Observer/windowomodelbservable.h \
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
    Product/TransmitterProduct/antenadiffraction.h \
    Product/TransmitterProduct/dialogtransmitterproduct.h \
    Product/TransmitterProduct/graphicstransmitterproduct.h \
    Product/TransmitterProduct/mathematicaltransmitterproduct.h \
    Product/TransmitterProduct/transmitterimage.h \
    Product/TransmitterProduct/transmitterproduct.h \
    Product/TreeProduct/dialogtreeproduct.h \
    Product/TreeProduct/graphicstreeproduct.h \
    Product/TreeProduct/mathematicaltreeproduct.h \
    Product/TreeProduct/treeproduct.h \
    Product/abstractantena.h \
    Product/graphicsproduct.h \
    Product/mathematicalproduct.h \
    Product/sceneproduct.h \
    Share/drafts.h \
    Share/line.h \
    Share/moveablegraphics.h \
    Share/params.h \
    Share/reflectiveobstacle.h \
    Share/rxdatahandler.h \
    Share/wall.h \
    Share/wholeray.h \
    Widget/infowidget.h \
    Widget/toolbox.h \
    applicationwindow.h \
    graphicsmap.h \
    qcustomplot.h

SOURCES += Abstract_Factory/dialogfactory.cpp \
    Abstract_Factory/buildingfactory.cpp \
    Abstract_Factory/carfactory.cpp \
    Abstract_Factory/rayfactory.cpp \
    Abstract_Factory/raytracingalgorithmfactory.cpp \
    Abstract_Factory/receiverfactory.cpp \
    Abstract_Factory/transmitterfactory.cpp \
    Abstract_Factory/treefactory.cpp \
    Graphics/interfererencepattern.cpp \
    Graphics/patternwindow.cpp \
    Graphics/surface3d.cpp \
    Model/coverage.cpp \
    Model/imagesmethod.cpp \
    Model/mapgenerator.cpp \
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
    Product/TransmitterProduct/antenadiffraction.cpp \
    Product/TransmitterProduct/dialogtransmitterproduct.cpp \
    Product/TransmitterProduct/graphicstransmitterproduct.cpp \
    Product/TransmitterProduct/mathematicaltransmitterproduct.cpp \
    Product/TransmitterProduct/transmitterimage.cpp \
    Product/TreeProduct/dialogtreeproduct.cpp \
    Product/TreeProduct/graphicstreeproduct.cpp \
    Product/TreeProduct/mathematicaltreeproduct.cpp \
    Product/TreeProduct/treeparams.cpp \
    Product/abstractantena.cpp \
    Share/line.cpp \
    Share/reflectiveobstacle.cpp \
    Share/rxdatahandler.cpp \
    Share/wall.cpp \
    Share/wholeray.cpp \
    Widget/infowidget.cpp \
    Widget/toolbox.cpp \
    applicationwindow.cpp \
    graphicsmap.cpp \
    main.cpp \
    qcustomplot.cpp

RESOURCES += \
    Ressources.qrc

DISTFILES +=

INCLUDEPATH += /usr/local/GSL/include \
    /usr/local/boost_1_74_0

QMAKE_CXXFLAGS += -Wno-deprecated


#INCLUDEPATH += /usr/local/Cellar/boost/1.73.0/include/boost
#LIBS += /usr/local/Cellar/boost/1.73.0/lib -libboost_math_c99
