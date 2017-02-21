#ifndef ADVANCED_SETTINGS_H
#define ADVANCED_SETTINGS_H
#include <QWidget>
#include <QDialog>
#include <QPainter>
#include <QThread>
#include <windows.h>
#include <QDebug>
#include <QPushButton>
#include <QBoxLayout>
#include <QSpinBox>
#include <QLabel>
#include <QMouseEvent>
#include <QRadioButton>

class AdvancedSettings: public QDialog
{
    Q_OBJECT
private:
    QPushButton *submit;
    QLabel *label_steps_prey, *label_steps_predator, *label_fast_prey, *label_fast_predator;
    QSpinBox *sbox_steps_prey, *sbox_steps_predator, *sbox_fast_prey, *sbox_fast_predator;
public:
    AdvancedSettings(unsigned int step_prey, unsigned int step_predator, unsigned int speed_prey, unsigned int speed_predator)
    {
        QVBoxLayout *main_lay = new QVBoxLayout;
        QHBoxLayout *lay_lay = new QHBoxLayout;
        QVBoxLayout *lay_label = new QVBoxLayout;
        label_steps_prey = new QLabel("How long can prey live: ");
        label_steps_predator = new QLabel("How long can predator live: ");
        label_fast_prey = new QLabel("How fast prey will multiply(100/x%): ");
        label_fast_predator = new QLabel("How fast predator will multiply(100/x%): ");
        lay_label->addWidget(label_steps_prey);
        lay_label->addWidget(label_steps_predator);
        lay_label->addWidget(label_fast_prey);
        lay_label->addWidget(label_fast_predator);
        lay_lay->addLayout(lay_label);

        QVBoxLayout *lay_sbox = new QVBoxLayout;
        sbox_steps_prey = new QSpinBox;
        sbox_steps_prey->setValue(step_prey);
        sbox_steps_prey->setRange(1, 99);
        sbox_steps_predator = new QSpinBox;
        sbox_steps_predator->setValue(step_predator);
        sbox_steps_predator->setRange(1, 99);

        sbox_fast_prey = new QSpinBox;
        sbox_fast_prey->setValue(speed_prey);
        sbox_fast_prey->setRange(1, 50);
        sbox_fast_predator = new QSpinBox;
        sbox_fast_predator->setValue(speed_predator);
        sbox_fast_predator->setRange(1, 50);

        lay_sbox->addWidget(sbox_steps_prey);
        lay_sbox->addWidget(sbox_steps_predator);
        lay_sbox->addWidget(sbox_fast_prey);
        lay_sbox->addWidget(sbox_fast_predator);
        lay_lay->addLayout(lay_sbox);

        main_lay->addLayout(lay_lay);
        submit = new QPushButton("Submit");
        connect(submit, SIGNAL(clicked(bool)), this, SLOT(send_info()));
        main_lay->addWidget(submit);
        setLayout(main_lay);
    }
signals:
    void send_all(unsigned int step_prey, unsigned int step_predator, unsigned int speed_prey, unsigned int speed_predator);
public slots:
    void send_info()
    {
        emit send_all(sbox_steps_prey->value(), sbox_steps_predator->value(), sbox_fast_prey->value(), sbox_fast_predator->value());
        close();
    }

};

#endif // ADVANCED_SETTINGS_H
