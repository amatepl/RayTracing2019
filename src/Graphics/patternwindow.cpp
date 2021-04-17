#include "patternwindow.h"

PatternWindow::PatternWindow(TxInterface *dialog)
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
    auto palette = widget->palette();
    palette.setColor(QPalette::Window, Qt::white);
    widget->setPalette(palette);
    QHBoxLayout *hLayout = new QHBoxLayout(widget);
    QVBoxLayout *vLayout = new QVBoxLayout();
    QVBoxLayout *graph_layout = new QVBoxLayout();
    QLabel *label = new QLabel("3D Gain Pattern");
    QFont font;
    font.setPointSize(30);
    label->setFont(font);
    label->setAlignment(Qt::AlignHCenter);
    graph_layout->addWidget(label);
    graph_layout->addWidget(container);
    hLayout->addLayout(graph_layout);
    hLayout->addLayout(vLayout);

    vLayout->setAlignment(Qt::AlignTop);

    widget->setWindowTitle(QStringLiteral("3D pattern"));

    QGroupBox *selectionGroupBox = new QGroupBox(QStringLiteral("Selection Mode"));

    QRadioButton *modeNoneRB = new QRadioButton(widget);
    modeNoneRB->setText(QStringLiteral("No selection"));
    modeNoneRB->setChecked(false);

    QRadioButton *modeItemRB = new QRadioButton(widget);
    modeItemRB->setText(QStringLiteral("Item"));
    modeItemRB->setChecked(false);

    QVBoxLayout *selectionVBox = new QVBoxLayout;
    selectionVBox->addWidget(modeNoneRB);
    selectionVBox->addWidget(modeItemRB);
    selectionGroupBox->setLayout(selectionVBox);


    vLayout->addWidget(selectionGroupBox);

    widget->show();

    Surface3D *modifier = new Surface3D(graph,m_dialog);

    QObject::connect(modeNoneRB, &QRadioButton::toggled,
                     modifier, &Surface3D::toggleModeNone);
    QObject::connect(modeItemRB,  &QRadioButton::toggled,
                     modifier, &Surface3D::toggleModeItem);

    modifier->enablePatternModel();
    modeItemRB->setChecked(true);
}

PatternWindow::~PatternWindow(){

}
