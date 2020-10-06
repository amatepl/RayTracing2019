#ifndef DIALOGTX_H
#define DIALOGTX_H

#include <QObject>
#include <QDialog>
#include <QIcon>
#include <QPushButton>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QComboBox>
#include <qcustomplot.h>

#include "txinterface.h"
#include "graphicstx.h"
#include"Graphics/patternwindow.h"

class DialogTx : public QDialog
{
    Q_OBJECT
public:
    DialogTx(TxInterface* mathematicalproduct);
    ~DialogTx() ;

    /* General Parameters */
    QWidget *createDialog();
    void updateGeneralTab();

    /* Path Loss Tab */
    QWidget *createPathLossTab();
    void updatePathLossTab();

    /* Shadowing Tab */
    QWidget *createShadowingTab();
    void updateShadowingTab();

    int getPosX()  {return m_posx->value();}
    int getPosY()  {return m_posy->value();}
    double getOrientation() ;
    char principalOrientation() ;
    unsigned long getFrequency() ;
    unsigned long getBandwidth() ;
    double getPower()  {return m_power->value();}
    int getRow()  {return m_rowBox->value();}
    int getColumn()  {return m_columnBox->value();}
//    Kind getKind()  {return m_kind;}

    void setPosX(int posX)  {m_posx->setValue(posX);}
    void setPosY(int posY)  {m_posy->setValue(posY);}
    void setOrientation(double orientation) ;
    void setPrincipalOrientation(char orientation) ;
    void setPower(double power)  {m_power->setValue(power);}
    void setFrequency(unsigned long frequency) ;
    void setBandwidth(unsigned long bandwidth) ;
//    void setRow(int row)  {m_rowBox->setValue(row); m_row = row;}
//    void setColumn(int column)  {m_columnBox->setValue(column); m_column = column;}
//    virtual void setKind(Kind kind) ;
    void setTxType(ph::TxType type);
    void newProperties() ;

private:
    /* General Parameters */
//    Kind m_kind;
    QComboBox *m_modelBox;
    QSpinBox *m_posx,*m_posy,*m_rowBox,*m_columnBox,*m_pr_orientationValue;
    QDoubleSpinBox *m_orientationValue;
    QDoubleSpinBox *m_frequencyValue;
    QDoubleSpinBox *m_bwvalue;
    QDoubleSpinBox *m_power;
    QComboBox *m_frequencyorder;
    QComboBox *m_bworder;
    QTabWidget *m_tabwidget;

    /* Path Loss Tab */

    QVector<double> Prx;
    QVector<double> path_loss;
    QVector<double> friis_loss;
    QVector<double> D;
    QVector<double> Prx_model;
    QVector<double> path_loss_model;
    QVector<double> D_model;
    double m,b,r,fading_variability, min_prx; //Path loss slope and intercept and regression coefficient

    QCustomPlot *m_pathLossPlot;
    QCustomPlot *m_pathLossModelPlot;

    /* Shadowing Tab */
    QCustomPlot *m_shadowingPlot;

    TxInterface* m_tx;

public slots:
    void saveProperties();
    void openPlot();
    void changeModel(QString model);
};

#endif // DIALOGTX_H
