QT += widgets \
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
    Product/ReceiverProduct/graphicsreceiverproduct.h \
    Product/ReceiverProduct/receiverproduct.h \
    Product/TransmitterProduct/dialogtransmitterproduct.h \
    Product/TransmitterProduct/graphicstransmitterproduct.h \
    Product/TransmitterProduct/mathematicaltransmitterproduct.h \
    Product/TransmitterProduct/transmitterproduct.h \
    applicationwindow.h

SOURCES += Abstract_Factory/dialogfactory.cpp \
    Abstract_Factory/graphicsfactory.cpp \
    Abstract_Factory/mathematicalfactory.cpp \
    Composite/graphicscomposite.cpp \
    Graphics/patternwindow.cpp \
    Graphics/surface3d.cpp \
    Product/ReceiverProduct/graphicsreceiverproduct.cpp \
    Product/TransmitterProduct/dialogtransmitterproduct.cpp \
    Product/TransmitterProduct/graphicstransmitterproduct.cpp \
    Product/TransmitterProduct/mathematicaltransmitterproduct.cpp \
    applicationwindow.cpp \
    main.cpp

RESOURCES += \
    Ressources.qrc
