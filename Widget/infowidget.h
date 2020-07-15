#ifndef INFOWIDGET_H
#define INFOWIDGET_H

#include <QObject>
#include <QWidget>
#include <QLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QComboBox>

class InfoWidget: public QWidget
{
    Q_OBJECT;
public:
    InfoWidget(QWidget *parent = nullptr);
    void createInfoGroup();
    void createEditGeneral();
    void createRayGroup();
    void createCoverageGroup();

    void changeScenePos(int x, int y);
    void changePower(double power);
    void changeDistance(double distance);
    void changeSnr(double snr);
    void changeDelaySpread(double delay);
    void changeRiceFactor(double rice);
    void changeCoherenceBandwidth(double coherence);
    void reset();

private:
    QGridLayout *main_layout;

    QGroupBox *info_group;
    QLabel *scene_pos;
    QLabel *power_rx;
    QLabel *distance;
    QLabel *snr;
    QLabel *delay_spread;
    QLabel *rice_factor;
    QLabel *coherence_bw;
    QLabel *coherence_time;

    QGroupBox *edit_group;
    QDoubleSpinBox *frequency;
    QComboBox *frequency_order;
    QDoubleSpinBox *bandwidth;
    QComboBox *bandwidth_order;
    QDoubleSpinBox *target_snr;
    QDoubleSpinBox *noise_figure;
    QCheckBox *all_same;
    QPushButton *generate_map;
    QPushButton *clear_workspace;

    QGroupBox *ray_group;
    QPushButton *launch_raytracing;

    QGroupBox *coverage_group;
    QPushButton *launch_coverage;

signals:
    void rayTracing();
    void coverage();

public slots:
    void sendLaunchRayTracing();
    void sendLaunchCoverage();
};

#endif // INFOWIDGET_H
