QT += widgets

HEADERS += dialog/antennadialog.h \
    dialog/buildingdialog.h \
    dialog/walldialog.h \
    dialogableobject.h \
    mainwindow.h \
    mapview.h \
    model/antennamodel.h \
    model/buildingmodel.h \
    model/wallmodel.h \
    usableobject.h \
    view/antennaview.h \
    view/buildingview.h \
    view/wallview.h \
    viewableobject.h

SOURCES += dialog/antennadialog.cpp \
    dialog/buildingdialog.cpp \
    dialog/walldialog.cpp \
    main.cpp \
    mainwindow.cpp \
    mapview.cpp \
    model/antennamodel.cpp \
    model/buildingmodel.cpp \
    model/wallmodel.cpp \
    view/antennaview.cpp \
    view/buildingview.cpp \
    view/wallview.cpp

RESOURCES += \
    Ressources.qrc
