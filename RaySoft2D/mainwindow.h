#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include <QFormLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QGroupBox>
#include <QToolButton>
#include <QButtonGroup>
#include <QToolBar>
#include <QComboBox>
#include <QMenu>
#include <QMenuBar>
#include <QAction>

#include "mapview.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    public:
        explicit MainWindow(QWidget *parent = nullptr);

        void sceneScaleChanged(const QString &scale);
        void generateToolBar();
        void generateCentralWidget();
        void createActions();
        void createMenus();

    protected:

    private:
        MapView *newScene;
        QGraphicsView *map;
        QLineEdit *powTx;
        QLineEdit *powRx;
        QLineEdit *distance;
        QLineEdit *snr;
        QLineEdit *delaySpread;
        QLineEdit *coherenceBw;
        QLineEdit *riceFactor;
        QLineEdit *coherenceTime;
        QFormLayout *channelFormLayout;
        QGroupBox *channelProperties;
        QPushButton *quit;
        QPushButton *launch;
        QHBoxLayout *buttonWindow;
        QGridLayout *mainLayout;
        QWidget *mainWidget;
        QButtonGroup *modeButton;
        QToolBar *modeToolBar;
        QComboBox *sceneScaleCombo;  

        QAction *exitAction;
        QAction *toFrontAction;
        QAction *sendBackAction;
        QAction *deleteAction;

        QMenu *itemMenu;

    private slots:
        void bringToFront();
        void sendToBack();
        void deleteItem();
        void itemInserted();
        void modeButtonClicked(int id);
        void modeButtonChoice(int);
};

#endif // MAINWINDOW_H
