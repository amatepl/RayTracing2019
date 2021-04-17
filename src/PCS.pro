QT       += core gui \
    gui widgets

greaterThan(QT_MAJOR_VERSION, 4):QT += widgets printsupport \
    datavisualization

CONFIG += c++1z

HEADERS += Abstract_Factory/abstractalgorithmfactory.h \
    Abstract_Factory/abstractrayfactory.h \
    Abstract_Factory/buildingfactory.h \
    Abstract_Factory/carfactory.h \
    Abstract_Factory/dialogfactory.h \
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
    Model/model.cpp.orig \
    Model/model.h \
    Model/raytracing.cpp.orig \
    Model/raytracing.h \
    Observer/AppInterface.h \
    Observer/modelobservable.h \
    Observer/modelobserver.h \
    Observer/movingobstacle.h \
    Observer/productobservable.h \
    Observer/productobserver.h \
    Observer/sceneobservable.h \
    Observer/sceneobserver.h \
    Observer/windowobservable.h \
    Observer/windowobserver.h \
    Observer/windowomodelbservable.h \
    Product/BuildingProduct/building.h \
    Product/BuildingProduct/buildingproduct.h \
    Product/BuildingProduct/dialogbuildingproduct.h \
    Product/BuildingProduct/graphicsbuilding.h \
    Product/CarProduct/car.h \
    Product/CarProduct/carproduct.h \
    Product/CarProduct/dialogcarproduct.h \
    Product/CarProduct/graphicscarproduct.h \
    Product/RayProduct/graphicsray.h \
    Product/RayProduct/ray.h \
    Product/RayProduct/rayproduct.h \
    Product/ReceiverProduct/dialogrx.h \
    Product/ReceiverProduct/graphicsrx.h \
    Product/ReceiverProduct/receiverproduct.h \
    Product/ReceiverProduct/rx.h \
    Product/TransmitterProduct/antenadiffraction.h \
    Product/TransmitterProduct/dialogtx.h \
    Product/TransmitterProduct/graphicstx.h \
    Product/TransmitterProduct/mathematicaltransmitterproduct.cpp.orig \
    Product/TransmitterProduct/mathematicaltransmitterproduct.h.orig \
    Product/TransmitterProduct/tx.h \
    Product/TransmitterProduct/tximg.h \
    Product/TransmitterProduct/txinterface.h \
    Product/TreeProduct/dialogtreeproduct.h \
    Product/TreeProduct/graphicstreeproduct.h \
    Product/TreeProduct/mathematicaltreeproduct.h \
    Product/TreeProduct/treeproduct.h \
    Product/abstractantena.h \
    Product/graphicsheatmap.h \
    Product/graphicsproduct.h \
    Product/heatmap.h \
    Product/mathematicalproduct.h \
    Product/sceneproduct.h \
    Share/chdata.h \
    Share/dialogfctry.h \
    Share/drafts.h \
    Share/line.h \
    Share/moveablegraphics.h \
    Share/params.h \
    Share/physics.h \
    Share/reflectiveobstacle.h \
    Share/rxdatahandler.h \
    Share/wall.h \
    Share/wholeray.h \
    Widget/graphics_view_zoom.h \
    Widget/infobar.h \
    Widget/infowidget.h \
    Widget/toolbox.h \
    applicationwindow.h \
    graphicsmap.h \
    logicinterface.h \
    qcustomplot/qcustomplot.h \


SOURCES += Abstract_Factory/buildingfactory.cpp \
    Abstract_Factory/carfactory.cpp \
    Abstract_Factory/dialogfactory.cpp \
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
    Product/BuildingProduct/building.cpp \
    Product/BuildingProduct/dialogbuildingproduct.cpp \
    Product/BuildingProduct/graphicsbuilding.cpp \
    Product/CarProduct/car.cpp \
    Product/CarProduct/dialogcarproduct.cpp \
    Product/CarProduct/graphicscarproduct.cpp \
    Product/RayProduct/graphicsray.cpp \
    Product/RayProduct/ray.cpp \
    Product/ReceiverProduct/dialogrx.cpp \
    Product/ReceiverProduct/graphicsrx.cpp \
    Product/ReceiverProduct/rx.cpp \
    Product/TransmitterProduct/antenadiffraction.cpp \
    Product/TransmitterProduct/dialogtx.cpp \
    Product/TransmitterProduct/graphicstx.cpp \
    Product/TransmitterProduct/tx.cpp \
    Product/TransmitterProduct/tximg.cpp \
    Product/TreeProduct/dialogtreeproduct.cpp \
    Product/TreeProduct/graphicstreeproduct.cpp \
    Product/TreeProduct/mathematicaltreeproduct.cpp \
    Product/TreeProduct/treeparams.cpp \
    Product/abstractantena.cpp \
    Product/graphicsheatmap.cpp \
    Product/heatmap.cpp \
    Share/line.cpp \
    Share/physics.cpp \
    Share/reflectiveobstacle.cpp \
    Share/rxdatahandler.cpp \
    Share/wall.cpp \
    Share/wholeray.cpp \
    Widget/graphics_view_zoom.cpp \
    Widget/infobar.cpp \
    Widget/infowidget.cpp \
    Widget/toolbox.cpp \
    applicationwindow.cpp \
    graphicsmap.cpp \
    main.cpp \
    qcustomplot/qcustomplot.cpp \


RESOURCES += \
    ../Ressources.qrc

DISTFILES += \
    PCS.uxf

INCLUDEPATH += /usr/local/GSL/include \
    /usr/local/boost_1_74_0 \
    /usr/local/eigen/Eigen \
    /usr/local/eigen/unsupported/Eigen

QMAKE_CXXFLAGS += -Wno-deprecated


#INCLUDEPATH += /usr/local/Cellar/boost/1.73.0/include/boost
#LIBS += /usr/local/Cellar/boost/1.73.0/lib -libboost_math_c99
