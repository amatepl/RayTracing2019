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
#include <QDialogButtonBox>

//#include "mathematicalbuildingproduct.h"
#include "graphicsbuilding.h"
#include "buildingproduct.h"

class DialogBuildingProduct : public QDialog, public BuildingProduct
{
    Q_OBJECT
public:
    DialogBuildingProduct(BuildingProduct* mathematicalproduct);
    ~DialogBuildingProduct() override;

    void createDialog();
    int getPosX() override;
    int getPosY() override;
    double getConductivity() override;
    double getPermittivity() override;
    QVector<QPointF> getExtremities() override;
    void setPosX(int posX) override;
    void setPosY(int posY) override;
    void setConductivity(double sigma) override;
    void setPermittivity(double eps) override;
    void setModel(std::string model) override;
    std::string getModel() override {return m_model;}
    void setExtremities(QVector<QPointF> extremities) override;
    void newProperties() override;
    void applyProperties();
    void writeExtremities();

private:
    QDialogButtonBox *m_buttonbox;
    BuildingProduct *m_mathematicalproduct;
    std::string m_model;
    QComboBox *m_modelBox;
    QSpinBox *m_posx,*m_posy;
    QDoubleSpinBox *m_orientation, *m_conductivity, *m_permittivity;
    QSpinBox *m_pointX, *m_pointY;
    QVector <QPointF> m_extremities;
    QTextEdit *m_extremitiesViewer;
    QPointF initialpos;

public slots:
    void saveProperties();
    void changeModel(QString model);
    void addExtremities();
    void removeExtremities();
    void buttonBoxClicked(QAbstractButton *button);
};
#endif // DIALOGBUILDINGPRODUCT_H
