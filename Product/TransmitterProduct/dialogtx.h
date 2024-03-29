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
#include <QDialogButtonBox>

#include "txinterface.h"
#include "graphicstx.h"
#include"Graphics/patternwindow.h"

class DialogTx : public QDialog
{
    Q_OBJECT
public:
    DialogTx(TxInterface* mathematicalproduct);
    ~DialogTx() ;

    QWidget *templatePlot(QCustomPlot *plot, QString title, QString xlabel,
                          QString ylabel, bool xlog = false, bool ylog = false);

    /* General Parameters */
    QWidget *createDialog();
    void updateGeneralTab();

    /* Path Loss Tab */
    QWidget *createPathLossTab();
    void updatePathLossTab();

    /* Shadowing Tab */
    QWidget *createShadowingTab();
    void updateShadowingTab();
    void shadowing(map<double, double> shadow);

    /* Cell Range Tab */
    QWidget *createCellRangeTab();

    int getPosX()  {return m_posx->value();}
    int getPosY()  {return m_posy->value();}
    double getOrientation() ;
    char principalOrientation() ;
    unsigned long getFrequency() ;
    unsigned long getBandwidth() ;
    double getPower()  {return m_power->value();}
    int getRow()  {return m_rowBox->value();}
    int getColumn()  {return m_columnBox->value();}
    TxInterface::Kind getKind();

    void setPosX(int posX)  {m_posx->setValue(posX);}
    void setPosY(int posY)  {m_posy->setValue(posY);}
    void setOrientation(double orientation) ;
    void setPrincipalOrientation(char orientation) ;
    void setPower(double power)  {m_power->setValue(power);}
    void setFrequency(unsigned long frequency) ;
    void setBandwidth(unsigned long bandwidth) ;
    void setRow(int row)  {m_rowBox->setValue(row);}
    void setColumn(int column)  {m_columnBox->setValue(column);}
//    virtual void setKind(Kind kind) ;
    void setTxType(TxInterface::Kind kind);
    void newProperties() ;
    void applyProperties();

private:
    /* General Parameters */
//    Kind m_kind;
    QDialogButtonBox *m_buttonbox;
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

    /* Cell Range */
    QVector<double> probability;
    QVector<double> cell_range;

    TxInterface* m_tx;

public slots:
    void buttonBoxClicked(QAbstractButton *button);
    void saveProperties();
    void openPlot();
    void changeModel(QString model);
};

#endif // DIALOGTX_H
