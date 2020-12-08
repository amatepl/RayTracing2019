    #include "infowidget.h"

InfoWidget::InfoWidget(QWidget* parent):QWidget(parent)
{
    createInfoGroup();
    createEditGeneral();
    createMapGroup();
    createRayGroup();
    createCoverageGroup();

    QGridLayout *main_layout = new QGridLayout(this);
    main_layout->addWidget(info_group, 0, 0);
    main_layout->addWidget(edit_group, 0, 1);
    main_layout->addWidget(map_group, 0, 2);
    main_layout->addWidget(ray_group, 0, 3);
    main_layout->addWidget(coverage_group, 0, 4);

//    main_layout->setColumnStretch(0,5);
//    main_layout->setColumnStretch(1,5);
//    main_layout->setColumnStretch(2,5);
//    main_layout->setColumnStretch(3,5);
//    main_layout->setColumnStretch(4,5);
    this->setLayout(main_layout);
}

void InfoWidget::createInfoGroup(){
    info_group = new QGroupBox("General Informations",this);
    info_group->setFixedWidth(300);
    QFormLayout* info_layout = new QFormLayout(info_group);
    scene_pos = new QLabel("Map position: ( " + QString::number(0) + " , " + QString::number(0) + " )", info_group);
//    power_rx = new QLabel("Power received [dBm]: " + QString::number(0), info_group);
//    distance = new QLabel("Transmitter distance [m]: " + QString::number(0), info_group);
//    snr = new QLabel("Signal-to-noise ration [dB]: " + QString::number(0), info_group);
//    delay_spread = new QLabel("Delay spread [ns]: " + QString::number(0), info_group);
//    rice_factor = new QLabel("Rice factor [dB]: " + QString::number(0), info_group);
//    coherence_bw = new QLabel("Coherence bandwidth [MHz]: " + QString::number(0), info_group);
//    coherence_time = new QLabel("Coherence time [\u03bcs]: " + QString::number(0), info_group);
//    angular_spread = new QLabel("Angular spread [rad]: " + QString::number(0), info_group);
//    doppler_spread = new QLabel("Doppler Spread [rad/s]: " + QString::number(0), info_group);

    info_layout->addRow(scene_pos);
//    info_layout->addRow(power_rx);
//    info_layout->addRow(distance);
//    info_layout->addRow(snr);
//    info_layout->addRow(delay_spread);
//    info_layout->addRow(rice_factor);
//    info_layout->addRow(coherence_bw);
//    info_layout->addRow(coherence_time);
//    info_layout->addRow(angular_spread);
//    info_layout->addRow(doppler_spread);

    info_group->setLayout(info_layout);
}

void InfoWidget::createEditGeneral(){
    edit_group = new QGroupBox("Edit Informations", this);
    QGridLayout *edit_layout = new QGridLayout(edit_group);

    frequency = new QDoubleSpinBox(edit_group);
    frequency->setRange(0.00,999.00);
    frequency->setAccelerated(true);
    bandwidth = new QDoubleSpinBox(edit_group);
    bandwidth->setRange(0.00,999.00);
    bandwidth->setAccelerated(true);
    frequency_order = new QComboBox(edit_group);
    frequency_order->addItem("kHz");
    frequency_order->addItem("MHz");
    frequency_order->addItem("GHz");
    bandwidth_order = new QComboBox(edit_group);
    bandwidth_order->addItem("kHz");
    bandwidth_order->addItem("MHz");
    bandwidth_order->addItem("GHz");
    QHBoxLayout *f = new QHBoxLayout;
    f->addWidget(frequency);
    f->addWidget(frequency_order);
    QFormLayout *f_layout = new QFormLayout;
    f_layout->addRow("Frequency: ", f);
    QHBoxLayout *b = new QHBoxLayout;
    b->addWidget(bandwidth);
    b->addWidget(bandwidth_order);
    QFormLayout *b_layout = new QFormLayout;
    b_layout->addRow("Bandwidth: ",b);

    all_same = new QCheckBox("Same Properties For all", edit_group);
//    generate_map = new QPushButton("Generate Map", edit_group);
    clear_workspace = new QPushButton("Clear Workspace", edit_group);
    connect(clear_workspace,&QPushButton::clicked,this,&InfoWidget::sendClear);

    edit_layout->addLayout(f_layout,0,0);
    edit_layout->addLayout(b_layout,0,1);
    edit_layout->addWidget(all_same,1,0);
//    edit_layout->addWidget(generate_map,2,0);
    edit_layout->addWidget(clear_workspace,2,1);

    edit_group->setLayout(edit_layout);

    /* Initial values */
    frequency->setValue(26);
    frequency_order->setCurrentIndex(2);
    bandwidth->setValue(100);
    bandwidth_order->setCurrentIndex(1);
}

void InfoWidget::createRayGroup(){
    ray_group = new QGroupBox("Ray-Tracing",this);
    ray_group->setFixedWidth(200);
    launch_raytracing = new QPushButton(QIcon(QPixmap(":/Images/playButton.png")),"Launch Ray-Tracing");
    // Ray Tracing informations and edition
    QGridLayout* ray_layout = new QGridLayout(ray_group);
    ray_layout->addWidget(launch_raytracing, 0, 0, Qt::AlignTop);
    connect(launch_raytracing,&QPushButton::clicked,this,&InfoWidget::sendLaunchRayTracing);

    clear_raytracing = new QPushButton(QIcon(QPixmap(":/Images/Delete.png")),"Clear");
    connect(clear_raytracing, &QPushButton::clicked, this, &InfoWidget::sendClearRayTracing);
    ray_layout->addWidget(clear_raytracing, 1, 0, Qt::AlignTop);

    rflctns_ray = new QSpinBox(ray_group);
    rflctns_ray->setRange(0.00,999.00);
    rflctns_ray->setAccelerated(true);
    QHBoxLayout *f = new QHBoxLayout;
    f->addWidget(rflctns_ray);
    QFormLayout *f_layout = new QFormLayout;
    f_layout->addRow("Reflections: ", f);
    ray_layout->addLayout(f_layout, 2, 0, Qt::AlignTop);


    ray_group->setLayout(ray_layout);

    /* Initial values */
    rflctns_ray->setValue(3);
}

void InfoWidget::createCoverageGroup(){
    coverage_group = new QGroupBox("Coverage", this);
    coverage_group->setFixedWidth(200);
    launch_coverage = new QPushButton(QIcon(QPixmap(":/Images/playButton.png")),"Launch coverage");
    // Coverage informations and edition
    QGridLayout *coverage_layout = new QGridLayout(coverage_group);
    coverage_layout->addWidget(launch_coverage, 0, 0, Qt::AlignTop);
    connect(launch_coverage,&QPushButton::clicked,this,&InfoWidget::sendLaunchCoverage);

    clear_coverage = new QPushButton(QIcon(QPixmap(":/Images/Delete.png")),"Clear");
    connect(clear_coverage, &QPushButton::clicked, this, &InfoWidget::sendClearCoverage);
    coverage_layout->addWidget(clear_coverage, 1, 0, Qt::AlignTop);

    rflctns_cov = new QSpinBox(ray_group);
    rflctns_cov->setRange(0.00,999.00);
    rflctns_cov->setAccelerated(true);

    QFormLayout *f_layout = new QFormLayout;
    f_layout->addRow("Reflections: ", rflctns_cov);

    cov_dnsty = new QDoubleSpinBox(ray_group);
    cov_dnsty->setRange(0.00,1.00);
    cov_dnsty->setStepType(QAbstractSpinBox::AdaptiveDecimalStepType);
    cov_dnsty->setAccelerated(true);

    f_layout->addRow("Density [1/m]: ", cov_dnsty);

    coverage_layout->addLayout(f_layout, 2, 0, Qt::AlignTop);

    m_eFieldDisp = new QLabel("|E| [...]: ", this);
    coverage_layout->addWidget(m_eFieldDisp, 3, 0);

    coverage_group->setLayout(coverage_layout);

    rflctns_cov->setValue(3);
    cov_dnsty->setValue(0.5);
}

void InfoWidget::updateCoverageGroup(double eField)
{
    m_eFieldDisp->setText("|E| [...]: " + QString::number(eField));
}

void InfoWidget::printValue(double value)
{
    cout<< value << endl;
}

void InfoWidget::createMapGroup()
{
    map_group = new QGroupBox("Map", this);
    map_group->setFixedWidth(230);
    QGridLayout *map_layout = new QGridLayout;

    generate_map = new QPushButton("Generate Map");
    map_layout->addWidget(generate_map, 0, 0, Qt::AlignTop);

    start_cars = new QPushButton("Start/Stop cars");
    map_layout->addWidget(start_cars, 1, 0, Qt::AlignTop);
    connect(start_cars,&QPushButton::clicked,this,&InfoWidget::sendStartCars);

    st_dnsty = new QSpinBox(map_group);
    st_dnsty->setRange(0, 999);
    st_dnsty->setAccelerated(true);
    connect(st_dnsty, QOverload<int>::of(&QSpinBox::valueChanged), this, &InfoWidget::printValue);

    QFormLayout *f_layout = new QFormLayout;
    f_layout->addRow("Distance Between Streets: ", st_dnsty);

    st_width = new QSpinBox(map_group);
    st_width->setRange(0, 999);
    st_width->setAccelerated(true);

    f_layout->addRow("Street's width: ", st_width);

    car_dnsty = new QSpinBox(map_group);
    car_dnsty->setRange(0, 999);
    car_dnsty->setAccelerated(true);

    f_layout->addRow("Cars Density: ", car_dnsty);

    QGridLayout *size_layout = new QGridLayout;

    QLabel *size = new QLabel("Size:");

    size_layout->addWidget(size, 0, 0);

    QLabel *h = new QLabel("h");
    size_layout->addWidget(h, 0, 1);

    height = new QSpinBox(map_group);
    height->setRange(0, 9999);
    height->setAccelerated(true);

    size_layout->addWidget(height, 0, 2);
//    f_layout->addRow("Cars Density: ", height);

    QLabel *w = new QLabel("w");
    size_layout->addWidget(w, 0, 3);

    width = new QSpinBox(map_group);
    width->setRange(0, 9999);
    width->setAccelerated(true);
    size_layout->addWidget(width, 0, 4);

//    f_layout->addRow("Size: ", size_layout);
//    f_layout->addRow("Cars Density: ", width);
    map_layout->addLayout(size_layout, 3, 0, Qt::AlignTop);

    map_layout->addLayout(f_layout, 2, 0, Qt::AlignTop);

    connect(generate_map, &QPushButton::clicked, this, &InfoWidget::sendGenerateMap);

    map_group->setLayout(map_layout);

    height->setValue(500);
    width->setValue(500);
    st_dnsty->setValue(200);
    st_width->setValue(20);

}

void InfoWidget::changeScenePos(int x, int y)
{
    scene_pos->setText("Map position: ( " + QString::number(x) + " , " + QString::number(y) + " )");
}

void InfoWidget::changePower(double power)
{
    power_rx->setText("Power received [dBm]: " + QString::number(power));
}

void InfoWidget::changeDistance(double distance)
{
    this->distance->setText("Transmitter distance [m]: " + QString::number(distance));
}

void InfoWidget::changeSnr(double snr)
{
    this->snr->setText("Signal-to-noise ration [dB]: " + QString::number(snr));
}

void InfoWidget::changeDelaySpread(double delay)
{
    delay_spread->setText("Delay spread [ns]: " + QString::number(delay));
}

void InfoWidget::changeRiceFactor(double rice)
{
    rice_factor->setText("Rice factor [dB]: " + QString::number(rice));
}

void InfoWidget::changeCoherenceBandwidth(double coherence)
{
    coherence_bw->setText("Coherence bandwidth [MHz]: " + QString::number(coherence));
}

void InfoWidget::changeAngularSpread (double angularSpread)
{
    angular_spread->setText("Angular Spread [rad]: " + QString::number(angularSpread));
}

void InfoWidget::changeDopplerSpread (double dopplerSpread)
{
    doppler_spread->setText("Doppler Spread [rad/s]: " + QString::number(dopplerSpread));
}

void InfoWidget::reset(){
//    power_rx->setText("Power received [dBm]: " + QString::number(0));
//    this->distance->setText("Transmitter distance [m]: " + QString::number(0));
//    this->snr->setText("Signal-to-noise ration [dB]: " + QString::number(0));
//    delay_spread->setText("Delay spread [ns]: " + QString::number(0));
//    rice_factor->setText("Rice factor [dB]: " + QString::number(0));
//    coherence_bw->setText("Coherence bandwidth [MHz]: " + QString::number(0));
//    angular_spread->setText("Angular spread: " + QString::number(0));
}

// ---------- SLOTS ----------
void InfoWidget::sendLaunchRayTracing(){
    rayTracing(rflctns_ray->value());
    launch_raytracing->setEnabled(false);
    launch_coverage->setEnabled(false);
}

void InfoWidget::sendClearRayTracing()
{
    clearRayTracing();
    launch_raytracing->setEnabled(true);
    launch_coverage->setEnabled(true);
}

void InfoWidget::sendLaunchCoverage(){
    coverage(rflctns_cov->value(), cov_dnsty->value());
    launch_raytracing->setEnabled(false);
    launch_coverage->setEnabled(false);
}

void InfoWidget::sendClearCoverage()
{
    clearCoverage();
    launch_raytracing->setEnabled(true);
    launch_coverage->setEnabled(true);
}

void InfoWidget::sendClear(){
    clear();
    launch_raytracing->setEnabled(true);
    launch_coverage->setEnabled(true);
}

void InfoWidget::sendStartCars()
{
    startCars();
}

void InfoWidget::sendGenerateMap()
{
    generateMap(height->value(), width->value(), car_dnsty->value(), st_width->value(), st_dnsty->value());
}

void InfoWidget::updateEField(double eField)
{
    updateCoverageGroup(eField);
}
