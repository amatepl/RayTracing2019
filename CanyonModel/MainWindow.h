#ifndef IEEE80211G_H
#define IEEE80211G_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QWidget>
#include <QSpinBox>
#include "ui_ieee80211g.h"
#include "room.h"
#include "help.h"
#include "settings.h"
#include "plots.h"

class coverage;

namespace Ui {
class IEEE80211g;
}
class QSpinBox;

class QGraphicsView;

class QGraphicsScene;

class room;

class plots;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void onMouseEvent(const QString &eventName, const QPoint &pos);
    void setMap(QPointF &pos);
    void writePenetrationDepth(map<const char *, int> *text);

private slots:
    void on_commandLinkButton_clicked();
    void on_antena_clicked();
    void on_receiver_clicked();
    void on_helpButton_clicked();
    void on_settingsButton_clicked();
    void on_plotButton_clicked();
    void on_generateCoveragePushButton_clicked();
    void on_clearWorkspaceButton_clicked();


protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);


private:
    void configureSpinBox(QSpinBox *spinBox, int min, int max) const;

    Ui::IEEE80211g *ui;

    room *scene;
    coverage *cov;
    help *scene_help;
    settings *scene_settings;
    plots *scene_plots;
    QGraphicsEllipseItem *ellipse;
    QGraphicsRectItem *rectangle;
    QGraphicsTextItem *text;
};

#endif // IEEE80211G_H
