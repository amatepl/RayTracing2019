#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QWidget>
#include <QSpinBox>


namespace Ui {
class IEEE80211g;
}
class QSpinBox;

class QGraphicsView;

class QGraphicsScene;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void onMouseEvent(const QString &eventName, const QPoint &pos);
    void setMap(QPointF &pos);

private slots:
    void on_commandLinkButton_clicked();
    void on_antena_clicked();
    void on_receiver_clicked();


protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);


private:
    void configureSpinBox(QSpinBox *spinBox, int min, int max) const;

    Ui::IEEE80211g *ui;

    QGraphicsScene *scene;
    QGraphicsEllipseItem *ellipse;
    QGraphicsRectItem *rectangle;
    QGraphicsTextItem *text;
};
#endif // MAINMENU_H
