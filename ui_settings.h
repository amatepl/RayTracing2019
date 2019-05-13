/********************************************************************************
** Form generated from reading UI file 'settings.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGS_H
#define UI_SETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
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
    QLabel *label_6;
    QComboBox *typeComboBox;
    QLabel *label_2;
    QLabel *label;
    QSpinBox *wallThickSpinBox;
    QLabel *label_3;
    QSpinBox *reboundSpin;
    QSpinBox *discretSubBox;
    QLabel *label_4;
    QLabel *label_5;
    QSpinBox *powerSpinBox;
    QSpinBox *speedSpin;
    QCheckBox *diffractBox;
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
        gridLayoutWidget->setGeometry(QRect(0, 60, 1081, 471));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(gridLayoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 1, 1, 1, 1);

        typeComboBox = new QComboBox(gridLayoutWidget);
        typeComboBox->setObjectName(QStringLiteral("typeComboBox"));

        gridLayout->addWidget(typeComboBox, 2, 2, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 3, 1, 1, 1);

        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 2, 1, 1, 1);

        wallThickSpinBox = new QSpinBox(gridLayoutWidget);
        wallThickSpinBox->setObjectName(QStringLiteral("wallThickSpinBox"));
        wallThickSpinBox->setMaximum(500);

        gridLayout->addWidget(wallThickSpinBox, 3, 2, 1, 1);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 5, 1, 1, 1);

        reboundSpin = new QSpinBox(gridLayoutWidget);
        reboundSpin->setObjectName(QStringLiteral("reboundSpin"));
        reboundSpin->setMaximum(5);

        gridLayout->addWidget(reboundSpin, 5, 2, 1, 1);

        discretSubBox = new QSpinBox(gridLayoutWidget);
        discretSubBox->setObjectName(QStringLiteral("discretSubBox"));
        discretSubBox->setMinimum(1);
        discretSubBox->setMaximum(30);

        gridLayout->addWidget(discretSubBox, 6, 2, 1, 1);

        label_4 = new QLabel(gridLayoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 6, 1, 1, 1);

        powerSpinBox = new QSpinBox(gridLayoutWidget);
        powerSpinBox->setObjectName(QStringLiteral("powerSpinBox"));
        powerSpinBox->setMaximum(1000);

        gridLayout->addWidget(powerSpinBox, 1, 2, 1, 1);

        speedSpin = new QSpinBox(gridLayoutWidget);
        speedSpin->setObjectName(QStringLiteral("speedSpin"));
        speedSpin->setMaximum(1000);

        gridLayout->addWidget(speedSpin,4, 2, 1, 1);

        label_5 = new QLabel(gridLayoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 4, 1, 1, 1);

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
        settings->setWindowTitle(QApplication::translate("settings", "Dialog", Q_NULLPTR));
        label_6->setText(QApplication::translate("settings", "Emettor power (W)", Q_NULLPTR));
        typeComboBox->clear();
        typeComboBox->insertItems(0, QStringList()
         << QApplication::translate("settings", "Concrete", Q_NULLPTR)
         << QApplication::translate("settings", "Bricks", Q_NULLPTR)
         << QApplication::translate("settings", "Standard partition wall", Q_NULLPTR)
        );
        label_2->setText(QApplication::translate("settings", "Wall thickness (cm)", Q_NULLPTR));
        label->setText(QApplication::translate("settings", "Wall type", Q_NULLPTR));
        label_3->setText(QApplication::translate("settings", "Amount of rebound (n)", Q_NULLPTR));
        label_4->setText(QApplication::translate("settings", "Square size (set to 10 for a local area of 1m\302\262)", Q_NULLPTR));
        label_5->setText(QApplication::translate("settings","Speed of the receptor (km/h)",Q_NULLPTR));
        resetDefaultsButton->setText(QApplication::translate("settings", "Reset Defaults", Q_NULLPTR));
        applyChangesButton->setText(QApplication::translate("settings", "Apply changes", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class settings: public Ui_settings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGS_H
