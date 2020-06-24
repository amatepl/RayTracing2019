#ifndef DIALOGBUILDINGPRODUCT_H
#define DIALOGBUILDINGPRODUCT_H


#include <QObject>
#include <QDialog>
#include <QIcon>
#include <QPushButton>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QComboBox>
#include <QTextEdit>

#include "mathematicalbuildingproduct.h"
#include "graphicsbuildingproduct.h"

class MathematicalBuildingProduct;

class DialogBuildingProduct : public QDialog
{
    Q_OBJECT
public:
    DialogBuildingProduct(MathematicalBuildingProduct* mathematicalproduct);
    ~DialogBuildingProduct() override;

    void createDialog();
    int getPosX();
    int getPosY();
    double getConductivity();
    double getPermittivity();
    std::string getModel();
    QVector<QPointF> getExtremities();
    void setPosX(int posX);
    void setPosY(int posY);
    void setConductivity(double sigma);
    void setPermittivity(double eps);
    void setModel(std::string model);
    void setExtremities(QVector<QPointF> extremities);
    void writeExtremities();

private:
    MathematicalBuildingProduct *m_mathematicalproduct;
    std::string m_model;
    QComboBox *m_modelBox;
    QSpinBox *m_posx,*m_posy;
    QDoubleSpinBox *m_orientation, *m_conductivity, *m_permittivity;
    QSpinBox *m_pointX, *m_pointY;
    QVector <QPointF> m_points;
    QTextEdit *m_extremitiesViewer;

public slots:
    void newProperties();
    void changeModel(QString model);
    void addExtremities();
    void removeExtremities();
};
#endif // DIALOGBUILDINGPRODUCT_H
