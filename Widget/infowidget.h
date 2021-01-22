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
#include <QEvent>

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
    void updateCoverageGroup(double eField);
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

    bool eventFilter(QObject *obj, QEvent *event);

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
    QPushButton *clear_raytracing;
    QSpinBox *rflctns_ray;

    // Coverage
    QGroupBox *coverage_group;
    QPushButton *launch_coverage;
    QPushButton *clear_coverage;
    QSpinBox *rflctns_cov;
    QDoubleSpinBox *cov_dnsty;
    QLabel *m_eFieldDisp;
    QComboBox *cov_type;

    // Map
    QGroupBox *map_group;
    QPushButton *generate_map;
    QPushButton * start_cars;
    QSpinBox *car_dnsty;
    QSpinBox *st_dnsty;
    QSpinBox *st_width;
    QSpinBox *height;
    QSpinBox *width;
    QSpinBox *min_st_dist;
    QSpinBox *max_st_dist;
    QSpinBox *min_st_w;
    QSpinBox *max_st_w;
    QSpinBox *min_car;
    QSpinBox *max_car;
    QDoubleSpinBox *px_to_meter;

signals:
    void rayTracing(unsigned reflectionsNbr);
    void clearRayTracing();
    void coverage(unsigned reflectionsNbr, double dnsty, int type);
    void clearCoverage();
    void clear();
    void startCars();
//    void generateMap(unsigned h, unsigned w, unsigned cars, unsigned strs, unsigned strsGap);
    void generateMap(unsigned h, unsigned w,
                     unsigned min_cars, unsigned max_cars,
                     unsigned min_st_dist, unsigned max_st_dist,
                     unsigned min_st_w, unsigned max_st_w,
                     double px_to_meter);
//    void antenas(double fq, double bw, bool modifyAll);
    void hovered(const string &str);

public slots:
    void sendLaunchRayTracing();
    void sendClearRayTracing();
    void sendLaunchCoverage();
    void sendClearCoverage();
    void sendClear();
    void sendStartCars();
    void printValue(double value);  // For tests
    void sendGenerateMap();
    void updateEField(double eField);
//    void sendAntennas();
};

#endif // INFOWIDGET_H
