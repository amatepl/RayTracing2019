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
#include <iostream>

using namespace std;

class InfoWidget: public QWidget
{
    Q_OBJECT;
public:
    InfoWidget(QWidget *parent = nullptr);
    void createInfoGroup();
    void createEditGeneral();
    void createRayGroup();
    void createCoverageGroup();
    void createMapGroup();

    void changeScenePos(int x, int y);
    void changePower(double power);
    void changeDistance(double distance);
    void changeSnr(double snr);
    void changeDelaySpread(double delay);
    void changeRiceFactor(double rice);
    void changeCoherenceBandwidth(double coherence);
    void changeAngularSpread(double angularSpread);
    void changeDopplerSpread(double dopplerSpread);
    void reset();



private:
    QGridLayout *main_layout;

    // Info
    QGroupBox *info_group;
    QLabel *scene_pos;
    QLabel *power_rx;
    QLabel *distance;
    QLabel *snr;
    QLabel *delay_spread;
    QLabel *rice_factor;
    QLabel *coherence_bw;
    QLabel *coherence_time;
    QLabel *angular_spread;
    QLabel *doppler_spread;

    // Antena
    QGroupBox *edit_group;
    QDoubleSpinBox *frequency;
    QComboBox *frequency_order;
    QDoubleSpinBox *bandwidth;
    QComboBox *bandwidth_order;
    QDoubleSpinBox *target_snr;
    QDoubleSpinBox *noise_figure;
    QCheckBox *all_same;
    QPushButton *clear_workspace;

    // Ray Tracing
    QGroupBox *ray_group;
    QPushButton *launch_raytracing;
    QSpinBox *rflctns_ray;

    // Coverage
    QGroupBox *coverage_group;
    QPushButton *launch_coverage;
    QSpinBox *rflctns_cov;
    QSpinBox *cov_dnsty;

    // Map
    QGroupBox *map_group;
    QPushButton *generate_map;
    QPushButton * start_cars;
    QSpinBox *car_dnsty;
    QSpinBox *st_dnsty;
    QSpinBox *height;
    QSpinBox *width;

signals:
    void rayTracing();
    void coverage();
    void clear();
    void startCars();

public slots:
    void sendLaunchRayTracing();
    void sendLaunchCoverage();
    void sendClear();
    void sendStartCars();
    void printValue(double value);  // For tests
};

#endif // INFOWIDGET_H
