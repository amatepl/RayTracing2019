/********************************************************************************
** Form generated from reading UI file 'settings.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGS_H
#define UI_SETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
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
    QLabel *label_4;
    QSpinBox *reboundSpin;
    QLabel *label_2;
    QSpinBox *wallThickSpinBox;
    QLabel *label_6;
    QComboBox *typeComboBox;
    QLabel *label_3;
    QSpinBox *discretSubBox;
    QLabel *label;
    QSpinBox *powerSpinBox;
    QPushButton *resetDefaultsButton;
    QPushButton *applyChangesButton;
    QSpinBox *spinBox;

    void setupUi(QDialog *settings)
    {
        if (settings->objectName().isEmpty())
            settings->setObjectName(QString::fromUtf8("settings"));
        settings->resize(1064, 577);
        okBox = new QDialogButtonBox(settings);
        okBox->setObjectName(QString::fromUtf8("okBox"));
        okBox->setGeometry(QRect(990, 540, 81, 31));
        okBox->setOrientation(Qt::Horizontal);
        okBox->setStandardButtons(QDialogButtonBox::Close);
        gridLayoutWidget = new QWidget(settings);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 0, 1061, 411));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setHorizontalSpacing(6);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(gridLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 6, 1, 1, 1);

        reboundSpin = new QSpinBox(gridLayoutWidget);
        reboundSpin->setObjectName(QString::fromUtf8("reboundSpin"));
        reboundSpin->setMaximum(5);

        gridLayout->addWidget(reboundSpin, 5, 2, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 4, 1, 1, 1);

        wallThickSpinBox = new QSpinBox(gridLayoutWidget);
        wallThickSpinBox->setObjectName(QString::fromUtf8("wallThickSpinBox"));
        wallThickSpinBox->setMaximum(500);

        gridLayout->addWidget(wallThickSpinBox, 4, 2, 1, 1);

        label_6 = new QLabel(gridLayoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 1, 1, 1, 1);

        typeComboBox = new QComboBox(gridLayoutWidget);
        typeComboBox->addItem(QString());
        typeComboBox->addItem(QString());
        typeComboBox->addItem(QString());
        typeComboBox->setObjectName(QString::fromUtf8("typeComboBox"));

        gridLayout->addWidget(typeComboBox, 2, 2, 1, 1);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 5, 1, 1, 1);

        discretSubBox = new QSpinBox(gridLayoutWidget);
        discretSubBox->setObjectName(QString::fromUtf8("discretSubBox"));
        discretSubBox->setMinimum(1);
        discretSubBox->setMaximum(30);

        gridLayout->addWidget(discretSubBox, 6, 2, 1, 1);

        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 2, 1, 1, 1);

        powerSpinBox = new QSpinBox(gridLayoutWidget);
        powerSpinBox->setObjectName(QString::fromUtf8("powerSpinBox"));
        powerSpinBox->setMaximum(1000);

        gridLayout->addWidget(powerSpinBox, 1, 2, 1, 1);

        resetDefaultsButton = new QPushButton(settings);
        resetDefaultsButton->setObjectName(QString::fromUtf8("resetDefaultsButton"));
        resetDefaultsButton->setGeometry(QRect(710, 540, 151, 31));
        applyChangesButton = new QPushButton(settings);
        applyChangesButton->setObjectName(QString::fromUtf8("applyChangesButton"));
        applyChangesButton->setGeometry(QRect(870, 540, 111, 31));
        spinBox = new QSpinBox(settings);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setGeometry(QRect(530, 440, 48, 26));

        retranslateUi(settings);
        QObject::connect(okBox, SIGNAL(accepted()), settings, SLOT(accept()));
        QObject::connect(okBox, SIGNAL(rejected()), settings, SLOT(reject()));

        QMetaObject::connectSlotsByName(settings);
    } // setupUi

    void retranslateUi(QDialog *settings)
    {
        settings->setWindowTitle(QCoreApplication::translate("settings", "Dialog", nullptr));
        label_4->setText(QCoreApplication::translate("settings", "Square size (set to 10 for a local area of 1m\302\262)", nullptr));
        label_2->setText(QCoreApplication::translate("settings", "Wall thickness (cm)", nullptr));
        label_6->setText(QCoreApplication::translate("settings", "Emettor power (W)", nullptr));
        typeComboBox->setItemText(0, QCoreApplication::translate("settings", "Concrete", nullptr));
        typeComboBox->setItemText(1, QCoreApplication::translate("settings", "Bricks", nullptr));
        typeComboBox->setItemText(2, QCoreApplication::translate("settings", "Standard partition wall", nullptr));

        label_3->setText(QCoreApplication::translate("settings", "Amount of rebound (n)", nullptr));
        label->setText(QCoreApplication::translate("settings", "Wall type", nullptr));
        resetDefaultsButton->setText(QCoreApplication::translate("settings", "Reset Defaults", nullptr));
        applyChangesButton->setText(QCoreApplication::translate("settings", "Apply changes", nullptr));
    } // retranslateUi

};

namespace Ui {
    class settings: public Ui_settings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGS_H
