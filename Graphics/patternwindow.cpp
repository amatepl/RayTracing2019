#include "patternwindow.h"

PatternWindow::PatternWindow(DialogTransmitterProduct *dialog)
{
    m_dialog = dialog;
    Q3DSurface *graph = new Q3DSurface();
    QWidget *container = QWidget::createWindowContainer(graph);


    if (!graph->hasContext()) {
        QMessageBox msgBox;
        msgBox.setText("Couldn't initialize the OpenGL context.");
        msgBox.exec();
    }

    QSize screenSize = graph->screen()->size();
    container->setMinimumSize(QSize(screenSize.width() / 2, screenSize.height() / 1.6));
    container->setMaximumSize(screenSize);
    container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    container->setFocusPolicy(Qt::StrongFocus);

    QWidget *widget = new QWidget;
    QHBoxLayout *hLayout = new QHBoxLayout(widget);
    QVBoxLayout *vLayout = new QVBoxLayout();
    hLayout->addWidget(container, 1);
    hLayout->addLayout(vLayout);
    vLayout->setAlignment(Qt::AlignTop);

    widget->setWindowTitle(QStringLiteral("3D pattern"));

    QGroupBox *modelGroupBox = new QGroupBox(QStringLiteral("Model"));

    QRadioButton *patternModelRB = new QRadioButton(widget);
    patternModelRB->setText(QStringLiteral("Pattern"));
    patternModelRB->setChecked(false);

    QVBoxLayout *modelVBox = new QVBoxLayout;
    modelVBox->addWidget(patternModelRB);
    modelGroupBox->setLayout(modelVBox);

    QGroupBox *selectionGroupBox = new QGroupBox(QStringLiteral("Selection Mode"));

    QRadioButton *modeNoneRB = new QRadioButton(widget);
    modeNoneRB->setText(QStringLiteral("No selection"));
    modeNoneRB->setChecked(false);

    QRadioButton *modeItemRB = new QRadioButton(widget);
    modeItemRB->setText(QStringLiteral("Item"));
    modeItemRB->setChecked(false);

    QRadioButton *modeSliceRowRB = new QRadioButton(widget);
    modeSliceRowRB->setText(QStringLiteral("Row Slice"));
    modeSliceRowRB->setChecked(false);

    QRadioButton *modeSliceColumnRB = new QRadioButton(widget);
    modeSliceColumnRB->setText(QStringLiteral("Column Slice"));
    modeSliceColumnRB->setChecked(false);

    QVBoxLayout *selectionVBox = new QVBoxLayout;
    selectionVBox->addWidget(modeNoneRB);
    selectionVBox->addWidget(modeItemRB);
    selectionVBox->addWidget(modeSliceRowRB);
    selectionVBox->addWidget(modeSliceColumnRB);
    selectionGroupBox->setLayout(selectionVBox);

    QSlider *axisMinSliderTheta = new QSlider(Qt::Horizontal, widget);
    axisMinSliderTheta->setMinimum(0);
    axisMinSliderTheta->setTickInterval(1);
    axisMinSliderTheta->setEnabled(true);
    QSlider *axisMaxSliderTheta = new QSlider(Qt::Horizontal, widget);
    axisMaxSliderTheta->setMinimum(1);
    axisMaxSliderTheta->setTickInterval(1);
    axisMaxSliderTheta->setEnabled(true);
    QSlider *axisMinSliderY = new QSlider(Qt::Horizontal, widget);
    axisMinSliderY->setMinimum(0);
    axisMinSliderY->setTickInterval(1);
    axisMinSliderY->setEnabled(true);
    QSlider *axisMaxSliderY = new QSlider(Qt::Horizontal, widget);
    axisMaxSliderY->setMinimum(1);
    axisMaxSliderY->setTickInterval(1);
    axisMaxSliderY->setEnabled(true);

    QComboBox *themeList = new QComboBox(widget);
    themeList->addItem(QStringLiteral("Qt"));
    themeList->addItem(QStringLiteral("Primary Colors"));
    themeList->addItem(QStringLiteral("Digia"));
    themeList->addItem(QStringLiteral("Stone Moss"));
    themeList->addItem(QStringLiteral("Army Blue"));
    themeList->addItem(QStringLiteral("Retro"));
    themeList->addItem(QStringLiteral("Ebony"));
    themeList->addItem(QStringLiteral("Isabelle"));

    QGroupBox *colorGroupBox = new QGroupBox(QStringLiteral("Custom gradient"));

    QLinearGradient grBtoY(0, 0, 1, 100);
    grBtoY.setColorAt(1.0, Qt::black);
    grBtoY.setColorAt(0.67, Qt::blue);
    grBtoY.setColorAt(0.33, Qt::red);
    grBtoY.setColorAt(0.0, Qt::yellow);
    QPixmap pm(24, 100);
    QPainter pmp(&pm);
    pmp.setBrush(QBrush(grBtoY));
    pmp.setPen(Qt::NoPen);
    pmp.drawRect(0, 0, 24, 100);
    QPushButton *gradientBtoYPB = new QPushButton(widget);
    gradientBtoYPB->setIcon(QIcon(pm));
    gradientBtoYPB->setIconSize(QSize(24, 100));

    QLinearGradient grGtoR(0, 0, 1, 100);
    grGtoR.setColorAt(1.0, Qt::darkGreen);
    grGtoR.setColorAt(0.5, Qt::yellow);
    grGtoR.setColorAt(0.2, Qt::red);
    grGtoR.setColorAt(0.0, Qt::darkRed);
    pmp.setBrush(QBrush(grGtoR));
    pmp.drawRect(0, 0, 24, 100);
    QPushButton *gradientGtoRPB = new QPushButton(widget);
    gradientGtoRPB->setIcon(QIcon(pm));
    gradientGtoRPB->setIconSize(QSize(24, 100));

    QHBoxLayout *colorHBox = new QHBoxLayout;
    colorHBox->addWidget(gradientBtoYPB);
    colorHBox->addWidget(gradientGtoRPB);
    colorGroupBox->setLayout(colorHBox);

    vLayout->addWidget(modelGroupBox);
    vLayout->addWidget(selectionGroupBox);
    vLayout->addWidget(new QLabel(QStringLiteral("Column range")));
    vLayout->addWidget(axisMinSliderTheta);
    vLayout->addWidget(axisMaxSliderTheta);
    vLayout->addWidget(new QLabel(QStringLiteral("Row range")));
    vLayout->addWidget(axisMinSliderY);
    vLayout->addWidget(axisMaxSliderY);
    vLayout->addWidget(new QLabel(QStringLiteral("Theme")));
    vLayout->addWidget(themeList);
    vLayout->addWidget(colorGroupBox);

    widget->show();

    Surface3D *modifier = new Surface3D(graph,m_dialog);

    QObject::connect(patternModelRB, &QRadioButton::toggled,
                     modifier, &Surface3D::enablePatternModel);
    QObject::connect(modeNoneRB, &QRadioButton::toggled,
                     modifier, &Surface3D::toggleModeNone);
    QObject::connect(modeItemRB,  &QRadioButton::toggled,
                     modifier, &Surface3D::toggleModeItem);
    QObject::connect(modeSliceRowRB,  &QRadioButton::toggled,
                     modifier, &Surface3D::toggleModeSliceRow);
    QObject::connect(modeSliceColumnRB,  &QRadioButton::toggled,
                     modifier, &Surface3D::toggleModeSliceColumn);
    QObject::connect(axisMinSliderTheta, &QSlider::valueChanged,
                     modifier, &Surface3D::adjustThetaMin);
    QObject::connect(axisMaxSliderTheta, &QSlider::valueChanged,
                     modifier, &Surface3D::adjustThetaMax);
    QObject::connect(axisMinSliderY, &QSlider::valueChanged,
                     modifier, &Surface3D::adjustYMin);
    QObject::connect(axisMaxSliderY, &QSlider::valueChanged,
                     modifier, &Surface3D::adjustYMax);
    QObject::connect(themeList, SIGNAL(currentIndexChanged(int)),
                     modifier, SLOT(changeTheme(int)));
    QObject::connect(gradientBtoYPB, &QPushButton::pressed,
                     modifier, &Surface3D::setBlackToYellowGradient);
    QObject::connect(gradientGtoRPB, &QPushButton::pressed,
                     modifier, &Surface3D::setGreenToRedGradient);

    modifier->setAxisMinSliderTheta(axisMinSliderTheta);
    modifier->setAxisMaxSliderTheta(axisMaxSliderTheta);
    modifier->setAxisMinSliderY(axisMinSliderY);
    modifier->setAxisMaxSliderY(axisMaxSliderY);

    patternModelRB->setChecked(true);
    modeItemRB->setChecked(true);
    themeList->setCurrentIndex(2);
}

PatternWindow::~PatternWindow(){

}

void PatternWindow::update(){

}
