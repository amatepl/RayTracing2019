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

#include "buildingproduct.h"
#include "graphicsbuildingproduct.h"
#include "Abstract_Factory/dialogfactory.h"
#include "Graphics/patternwindow.h"

class DialogFactory;

class DialogBuildingProduct : public QDialog, public BuildingProduct
{
    Q_OBJECT
public:
    DialogBuildingProduct(BuildingProduct* graphic, DialogFactory* dialogfactory);
    ~DialogBuildingProduct() override;

    void createDialog();

    int getPosX() override;
    int getPosY() override;
    double getOrientation() override;
    double getConductivity() override;
    double getPermittivity() override;
    int getModel() override;
    QVector<QPointF> getExtremities() override;

    void setPosX(int posX) override;
    void setPosY(int posY) override;
    void setOrientation(double orientation) override;
    void setConductivity(double sigma) override;
    void setPermittivity(double eps) override;
    void setModel(int model) override;
    void setExtremities(QVector<QPointF> extremities) override;

    void writeExtremities();

private:
    Model m_model;
    QComboBox *m_modelBox;
    QSpinBox *m_posx,*m_posy;
    QDoubleSpinBox *m_orientation, *m_conductivity, *m_permittivity;
    DialogFactory *m_dialogfactory;
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
