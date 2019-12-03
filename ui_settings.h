/********************************************************************************
** Form generated from reading UI file 'settings.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGS_H
#define UI_SETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_settings
{
public:
    QDialogButtonBox *okBox;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QSpinBox *discretSubBox;
    QLabel *label;
    QSpinBox *wallThickSpinBox;
    QLabel *label_2;
    QLabel *label_3;
    QComboBox *typeComboBox;
    QLabel *label_6;
    QLabel *label_4;
    QSpinBox *powerSpinBox;
    QLabel *label_5;
    QSpinBox *reboundSpin;
    QLabel *label_7;
    QComboBox *directionBox;
    QDoubleSpinBox *speedBox;
    QPushButton *resetDefaultsButton;
    QPushButton *applyChangesButton;

    void setupUi(QDialog *settings)
    {
        if (settings->objectName().isEmpty())
            settings->setObjectName(QStringLiteral("settings"));
        settings->resize(1081, 576);
        okBox = new QDialogButtonBox(settings);
        okBox->setObjectName(QStringLiteral("okBox"));
        okBox->setGeometry(QRect(990, 540, 81, 31));
        okBox->setOrientation(Qt::Horizontal);
        okBox->setStandardButtons(QDialogButtonBox::Close);
        gridLayoutWidget = new QWidget(settings);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 0, 1061, 481));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        discretSubBox = new QSpinBox(gridLayoutWidget);
        discretSubBox->setObjectName(QStringLiteral("discretSubBox"));
        discretSubBox->setMinimum(1);
        discretSubBox->setMaximum(30);

        gridLayout->addWidget(discretSubBox, 8, 2, 1, 1);

        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 4, 1, 1, 1);

        wallThickSpinBox = new QSpinBox(gridLayoutWidget);
        wallThickSpinBox->setObjectName(QStringLiteral("wallThickSpinBox"));
        wallThickSpinBox->setMaximum(500);

        gridLayout->addWidget(wallThickSpinBox, 6, 2, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 6, 1, 1, 1);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 7, 1, 1, 1);

        typeComboBox = new QComboBox(gridLayoutWidget);
        typeComboBox->setObjectName(QStringLiteral("typeComboBox"));

        gridLayout->addWidget(typeComboBox, 4, 2, 1, 1);

        label_6 = new QLabel(gridLayoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 1, 1, 1, 1);

        label_4 = new QLabel(gridLayoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 8, 1, 1, 1);

        powerSpinBox = new QSpinBox(gridLayoutWidget);
        powerSpinBox->setObjectName(QStringLiteral("powerSpinBox"));
        powerSpinBox->setMaximum(1000);

        gridLayout->addWidget(powerSpinBox, 1, 2, 1, 1);

        label_5 = new QLabel(gridLayoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setMaximumSize(QSize(530, 30));

        gridLayout->addWidget(label_5, 2, 1, 1, 1);

        reboundSpin = new QSpinBox(gridLayoutWidget);
        reboundSpin->setObjectName(QStringLiteral("reboundSpin"));
        reboundSpin->setMaximum(5);

        gridLayout->addWidget(reboundSpin, 7, 2, 1, 1);

        label_7 = new QLabel(gridLayoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 3, 1, 1, 1);

        directionBox = new QComboBox(gridLayoutWidget);
        directionBox->setObjectName(QStringLiteral("directionBox"));

        gridLayout->addWidget(directionBox, 3, 2, 1, 1);

        speedBox = new QDoubleSpinBox(gridLayoutWidget);
        speedBox->setObjectName(QStringLiteral("speedBox"));

        gridLayout->addWidget(speedBox, 2, 2, 1, 1);

        label_5->raise();
        label_6->raise();
        typeComboBox->raise();
        label_2->raise();
        label->raise();
        wallThickSpinBox->raise();
        label_3->raise();
        reboundSpin->raise();
        discretSubBox->raise();
        label_4->raise();
        powerSpinBox->raise();
        speedBox->raise();
        label_7->raise();
        directionBox->raise();
        resetDefaultsButton = new QPushButton(settings);
        resetDefaultsButton->setObjectName(QStringLiteral("resetDefaultsButton"));
        resetDefaultsButton->setGeometry(QRect(710, 540, 151, 31));
        applyChangesButton = new QPushButton(settings);
        applyChangesButton->setObjectName(QStringLiteral("applyChangesButton"));
        applyChangesButton->setGeometry(QRect(870, 540, 111, 31));

        retranslateUi(settings);
        QObject::connect(okBox, SIGNAL(accepted()), settings, SLOT(accept()));
        QObject::connect(okBox, SIGNAL(rejected()), settings, SLOT(reject()));

        QMetaObject::connectSlotsByName(settings);
    } // setupUi

    void retranslateUi(QDialog *settings)
    {
        settings->setWindowTitle(QApplication::translate("settings", "Dialog", 0));
        label->setText(QApplication::translate("settings", "Wall type", 0));
        label_2->setText(QApplication::translate("settings", "Wall thickness (cm)", 0));
        label_3->setText(QApplication::translate("settings", "Amount of rebound (n)", 0));
        typeComboBox->clear();
        typeComboBox->insertItems(0, QStringList()
         << QApplication::translate("settings", "Concrete", 0)
         << QApplication::translate("settings", "Bricks", 0)
         << QApplication::translate("settings", "Standard partition wall", 0)
        );
        label_6->setText(QApplication::translate("settings", "Emettor power (W)", 0));
        label_4->setText(QApplication::translate("settings", "Square size (set to 10 for a local area of 1m\302\262)", 0));
        label_5->setText(QApplication::translate("settings", "Speed of the receptor (km/h)", 0));
        label_7->setText(QApplication::translate("settings", "Direction of the receptor", 0));
        directionBox->clear();
        directionBox->insertItems(0, QStringList()
         << QApplication::translate("settings", "East", 0)
         << QApplication::translate("settings", "West", 0)
         << QApplication::translate("settings", "North", 0)
         << QApplication::translate("settings", "South", 0)
        );
        resetDefaultsButton->setText(QApplication::translate("settings", "Reset Defaults", 0));
        applyChangesButton->setText(QApplication::translate("settings", "Apply changes", 0));
    } // retranslateUi

};

namespace Ui {
    class settings: public Ui_settings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGS_H
