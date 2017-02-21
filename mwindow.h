#ifndef MWINDOW_H
#define MWINDOW_H
#include <QScrollArea>
#include "advanced_settings.h"

class field
{
private:
    unsigned int sizex, sizey;
    unsigned int max_steps, max_steps_prey, speed_prey, speed_predator;
    QVector<QVector<unsigned int> > margin, steps, progress;
protected:

public:
    field(): sizex(10), sizey(10), max_steps(3), max_steps_prey(6), speed_prey(2), speed_predator(5){}

    void set_max_steps(unsigned int &s)
    {
        max_steps = s;
    }
    void set_max_steps_prey(unsigned int &s)
    {
        max_steps_prey = s;
    }
    void set_speed_prey(unsigned int &s)
    {
        speed_prey = s;
    }
    void set_speed_predator(unsigned int &s)
    {
        speed_predator = s;
    }
    unsigned int get_max_steps()
    {
        return max_steps;
    }
    unsigned int get_max_steps_prey()
    {
        return max_steps_prey;
    }
    unsigned int get_speed_prey()
    {
        return speed_prey;
    }
    unsigned int get_speed_predator()
    {
        return speed_predator;
    }


    void set_field(QVector<QVector<unsigned int> > &margin)
    {
        this->margin = margin;
    }

    void gen_field(unsigned int sx = 10, unsigned int sy = 10)
    {
        qDebug()<<"genering";
        if(sizex != sx)
        {
            sizex = sx;
        }
        if(sizey != sy)
        {
            sizey = sy;
        }
        QVector<unsigned int> field, step, prog;
        margin.clear();
        steps.clear();
        progress.clear();

        for(unsigned int i = 0; i < sizex; ++i)
        {
            field.clear();
            step.clear();
            prog.clear();
            for(unsigned int j = 0; j < sizey; ++j)
            {
                unsigned short key = qrand()%7;
                field.append(key > 5 ? 2 : key == 0 ? key : 1);
                step.append(0);
                prog.append(0);
            }
            margin.append(field);
            steps.append(step);
            progress.append(prog);
        }
    }
    void clear_progress()
    {
        for(unsigned int i = 0; i < sizex; ++i)
        {
            for(unsigned int j = 0; j < sizey; ++j)
            {
                progress[i][j] = 0;
            }
        }
    }

    QVector<QVector<unsigned int> > get_field()
    {
        return margin;
    }
    void change_field()
    {
        clear_progress();
        for(unsigned int i = 0; i < sizex; ++i)
        {
            for(unsigned int j = 0; j < sizey; ++j)
            {
                if(margin[i][j] == 2 && !progress[i][j])
                {
                    unsigned short r = qrand() % 5;
                    if(!r && steps[i][j] < max_steps)
                    {
                        r = 10;
                    }
                    int a[4] = {0, 0, 0, 0}, b[4] = {0, 0, 0, 0}, count = 0;
                    if(i > 0 && margin[i-1][j] == 2 || i == 0)
                    {
                       a[0] = 1;
                       count++;
                    }
                    if(i < sizex - 1 && margin[i+1][j] == 2 || i == sizex-1)
                    {
                        a[1] = 1;
                        count++;
                    }
                    if(j > 0 && margin[i][j-1] == 2 || j == 0)
                    {
                        a[2] = 1;
                        count++;
                    }
                    if(j < sizey - 1 && margin[i][j+1] == 2 || j == sizey-1)
                    {
                        a[3] = 1;
                        count++;
                    }

                    if(count > 2 || steps[i][j] > max_steps)
                    {
                        margin[i][j] = 0;
                        steps[i][j] = 0;
                        progress[i][j] = 0;
                    }
                    else
                    {
                        count = 0;
                        bool flag_food = true;
                        for(unsigned short l = 0; l < 4; ++l)
                        {
                            if(!a[l])
                            {
                                switch(l)
                                {
                                    case 0:
                                        if(margin[i-1][j] == 1)
                                        {
                                            b[count++] = l;
                                        }
                                        break;
                                    case 1:
                                        if(margin[i+1][j] == 1)
                                        {
                                            b[count++] = l;
                                        }
                                        break;
                                    case 2:
                                        if(margin[i][j-1] == 1)
                                        {
                                            b[count++] = l;
                                        }
                                        break;
                                    case 3:
                                        if(margin[i][j+1] == 1)
                                        {
                                            b[count++] = l;
                                        }
                                        break;
                                }
                            }
                        }
                        if(!count)
                        {
                            flag_food = false;
                            for(unsigned short l = 0; l < 4; ++l)
                            {
                                if(!a[l])
                                {
                                    b[count++] = l;
                                }
                            }
                        }
                        unsigned short rand1 = qrand() % count;

                        switch(b[rand1])
                        {
                            case 0:
                                {
                                    margin[i][j] = 0;
                                    margin[i-1][j] = 2;
                                    if(!flag_food)
                                    {
                                        steps[i][j]++;
                                    }
                                    else
                                    {
                                        steps[i][j] = 0;
                                    }
                                    steps[i-1][j] = steps[i][j];
                                    steps[i][j] = 0;
                                    progress[i-1][j] = 1;
                                }
                                break;
                            case 1:
                                {
                                    margin[i][j] = 0;
                                    margin[i+1][j] = 2;
                                    if(!flag_food)
                                    {
                                        steps[i][j]++;
                                    }
                                    else
                                    {
                                        steps[i][j] = 0;
                                    }
                                    steps[i+1][j] = steps[i][j];
                                    steps[i][j] = 0;
                                    progress[i+1][j] = 1;
                                }
                                break;
                            case 2:
                                {
                                    margin[i][j] = 0;
                                    margin[i][j-1] = 2;
                                    if(!flag_food)
                                    {
                                        steps[i][j]++;
                                    }
                                    else
                                    {
                                        steps[i][j] = 0;
                                    }
                                    steps[i][j-1] = steps[i][j];
                                    steps[i][j] = 0;
                                    progress[i][j-1] = 1;
                                }
                                break;
                            case 3:
                                {
                                    margin[i][j] = 0;
                                    margin[i][j+1] = 2;
                                    if(!flag_food)
                                    {
                                        steps[i][j]++;
                                    }
                                    else
                                    {
                                        steps[i][j] = 0;
                                    }
                                    steps[i][j+1] = steps[i][j];
                                    steps[i][j] = 0;
                                    progress[i][j+1] = 1;
                                }
                                break;
                        }
                    }

                    if(r == 10)
                    {
                        margin[i][j] = 2;
                    }
                }
                if(margin[i][j] == 1 && !progress[i][j])
                {
                    unsigned short die_count = 0, c[4] = {0,0,0,0};
                    if(i < sizex - 1 && margin[i+1][j] || i == sizex-1)
                    {
                        c[0] = 1;
                        die_count++;
                    }
                    if(i > 0 && margin[i-1][j] || i == 0)
                    {
                        c[1] = 1;
                        die_count++;
                    }
                    if(j < sizey - 1 && margin[i][j+1] || j == sizey-1)
                    {
                        c[2] = 1;
                        die_count++;
                    }
                    if(j > 0 && margin[i][j-1] || j == 0)
                    {
                        c[3] = 1;
                        die_count++;
                    }
                    if(die_count > 2 || steps[i][j] > max_steps_prey)
                    {
                        margin[i][j] = 0;
                        progress[i][j] = 0;
                        steps[i][j] = 0;
                    }
                    else
                    {
                        unsigned short v[4] = {0,0,0,0};
                        die_count = 0;
                        for(unsigned short l = 0; l < 4; ++l)
                        {
                            if(!c[l])
                            {
                                v[die_count++] = l;
                            }
                        }
                        unsigned short r = qrand() % 2, l = qrand() % die_count;

                        //qDebug()<<i<<j<<v[l];
                        switch (v[l]) {
                        case 0:
                            {
                                margin[i+1][j] = 1;
                                margin[i][j] = 0;
                                steps[i+1][j] = steps[i][j]+1;
                                steps[i][j] = 0;
                                progress[i+1][j] = 1;
                            }
                            break;
                        case 1:
                            {
                                margin[i-1][j] = 1;
                                margin[i][j] = 0;
                                steps[i-1][j] = steps[i][j]+1;
                                steps[i][j] = 0;
                                progress[i-1][j] = 1;
                            }
                            break;
                        case 2:
                            {
                                margin[i][j+1] = 1;
                                margin[i][j] = 0;
                                steps[i][j+1] = steps[i][j] + 1;
                                steps[i][j] = 0;
                                progress[i][j+1] = 1;
                            }
                            break;
                        case 3:
                            {
                                margin[i][j-1] = 1;
                                margin[i][j] = 0;
                                steps[i][j-1] = steps[i][j] + 1;
                                steps[i][j] = 0;
                                progress[i][j-1] = 1;
                            }
                            break;
                        default:
                            break;
                        }

                        if(!r)
                        {
                            margin[i][j] = 1;
                        }
                    }
                }
            }
        }
    }
};

class thread_r: public QThread
{
    Q_OBJECT

private:
    field *mobj;

public:
    void set_mobj(field *mobj)
    {
        this->mobj = mobj;
    }

    void run()
    {
        mobj->change_field();
        emit send_changed();
    }

    void sleep_thr(unsigned long i)
    {
        msleep(i);
    }
signals:
    void send_changed();
};

class main_thread: public QThread
{
    Q_OBJECT
private:
    thread_r thr;
    field *mobj;
    unsigned int sleep_time;
public:
    main_thread()
    {
        connect(&thr, SIGNAL(send_changed()), this, SLOT(emit_repaint()));
        sleep_time = 100;
    }
    void set_mobj(field *mobj)
    {
        thr.set_mobj(mobj);
        this->mobj = mobj;
    }
    void set_sleep_time(unsigned int t)
    {
        sleep_time = t;
    }
    unsigned int get_sleep_time()
    {
        return sleep_time;
    }
    void start_sleep(unsigned int t)
    {
        thr.sleep_thr(t);
    }

    void run()
    {
        while(true)
        {
            thr.run();
            thr.sleep_thr(sleep_time);
        }
    }
signals:
    void send_repaint(QVector<QVector<unsigned int> > field);
public slots:
    void emit_repaint()
    {
        emit send_repaint(mobj->get_field());
    }
};

class PaintWidget: public QWidget
{
    Q_OBJECT
private:
    QPainter painter;
    QVector<QVector<unsigned int> > *fieldf;
    unsigned int sizex, sizey;
    unsigned int step;
    bool flag_paint, click_flag, flag_prey;
    int x, y;
public:
    PaintWidget(unsigned int &s, unsigned int &sx, unsigned int &sy)
    {
        flag_prey = true;
        flag_paint = false;
        step = s;
        sizex = sx;
        sizey = sy;

        on_change_size();
    }
    void on_change_size()
    {
        qDebug()<<"Size is changing!"<<sizex;
        setMinimumSize(step*sizex, step*sizey);
        setMaximumSize(step*sizex, step*sizey);
    }

    void set_sizex(const unsigned int &sx)
    {
        sizex = sx;
    }
    void set_sizey(const unsigned int &sy)
    {
        sizey = sy;
    }
    void set_step(const unsigned int &s)
    {
        step = s;
    }
    void set_field(QVector<QVector<unsigned int> > *f)
    {
        fieldf = f;
    }
    QVector<QVector<unsigned int> > get_field()
    {
        return *fieldf;
    }
    void set_flag_paint(const bool f)
    {
        flag_paint = f;
    }

protected:
    void paintEvent(QPaintEvent *event)
    {
        painter.begin(this);

        painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
        for(unsigned int i = 0; i < sizex; ++i)
        {
            for(unsigned int j = 0; j < sizey; ++j)
            {
                if(((*fieldf)[i][j]) == 1)
                {
                    painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));
                    painter.drawEllipse(i*step, j*step, step, step);
                }
                else if((*fieldf)[i][j] == 2)
                {
                    painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
                    painter.drawEllipse(i*step, j*step, step, step);
                }
            }
        }
        painter.end();
    }

    void mouseMoveEvent(QMouseEvent *event)
    {
        if(click_flag)
        {
            unsigned short color;
            if(flag_prey)
            {
                color = 1;
            }
            else
            {
                color = 2;
            }
            int xl = event->pos().x()/step, yl = event->pos().y()/step;
            if((x != xl || y != yl) && xl < sizex && yl < sizey && !((*fieldf)[xl][yl]))
            {
                qDebug()<<event->pos().x()<<event->pos().y();
                x = xl;
                y = yl;

                ((*fieldf)[x][y]) = color;
                qDebug()<<"Pos: "<<x<<y;
                repaint();
            }
        }
    }

    void mouseReleaseEvent(QMouseEvent *event)
    {
        if(flag_paint && event->button() == Qt::LeftButton)
        {
            click_flag = false;
        }
    }

    void mousePressEvent(QMouseEvent *event)
    {
        if(event->button() == Qt::LeftButton)
        {
            click_flag = true;
        }
    }
public slots:
    void predator_clicked()
    {
        flag_prey = false;
    }

    void prey_clicked()
    {
        flag_prey = true;
    }
};

class mwindow: public QWidget
{
    Q_OBJECT

private:
    QVector<QVector<unsigned int> > fieldf;
    field *f;
    unsigned int sizex, sizey;
    unsigned int step;
    main_thread thr;
    QPushButton *restart_button, *paint_button, *clear_field_button, *advansed_button;
    QSpinBox *step_box, *sizex_box, *sizey_box, *sleep_box;
    QLabel *step_label, *size_label, *sleep_label;
    QRadioButton *predator_paint, *prey_paint;
    bool flag_paint, click_flag;
    int x, y;
    AdvancedSettings *new_wind;
    PaintWidget *paint_w;
    QScrollArea *scrl_area;
protected:

public:
    mwindow(){}
    mwindow(field *f, unsigned int &sx, unsigned int &sy)
    {
        sizex = sx;
        sizey = sy;
        step = 14;
        x = 0;
        y = 0;
        flag_paint = false;
        click_flag = false;
        this->f = f;
        start_newthread();
        QHBoxLayout *button_lay = new QHBoxLayout;
        restart_button = new QPushButton("Restart/Apply changes");
        QVBoxLayout *main_lay = new QVBoxLayout;
        button_lay->addWidget(restart_button);
        paint_button = new QPushButton("Paint own field");
        button_lay->addWidget(paint_button);
        clear_field_button = new QPushButton("Clear field");
        clear_field_button->setVisible(false);
        button_lay->addWidget(clear_field_button);
        connect(clear_field_button, SIGNAL(clicked(bool)), this, SLOT(clear_field()));
        predator_paint = new QRadioButton("Predator", this);
        predator_paint->setVisible(false);
        paint_w = new PaintWidget(step, sizex, sizey);
        paint_w->set_field(&fieldf);
        connect(predator_paint, SIGNAL(toggled(bool)), paint_w, SLOT(predator_clicked()));
        button_lay->addWidget(predator_paint);
        prey_paint = new QRadioButton("Prey", this);
        prey_paint->setVisible(false);
        prey_paint->setChecked(true);
        button_lay->addWidget(prey_paint);
        connect(prey_paint, SIGNAL(toggled(bool)), paint_w, SLOT(prey_clicked()));

        /*QVBoxLayout *lay_spv = new QVBoxLayout;
        QHBoxLayout *lay_sph = new QHBoxLayout;
        lay_sph->addStretch(1);
        lay_sph->addWidget(paint_w);
        lay_sph->addStretch(1);

        lay_spv->addStretch(1);
        lay_spv->addLayout(lay_sph);
        lay_spv->addStretch(1);*/

        scrl_area = new QScrollArea;
        scrl_area->setWidget(paint_w);
        scrl_area->setAlignment(Qt::AlignCenter);

        main_lay->addWidget(scrl_area);
        main_lay->addLayout(button_lay);
        connect(paint_button, SIGNAL(clicked(bool)), this, SLOT(start_paint()));

        advansed_button = new QPushButton("Advanced settings");
        connect(advansed_button, SIGNAL(clicked(bool)), this, SLOT(open_new_wind()));
        main_lay->addWidget(advansed_button);

        QHBoxLayout *changes_lay1 = new QHBoxLayout;
        step_label = new QLabel("Size of circles: ");
        changes_lay1->addWidget(step_label);
        step_box = new QSpinBox;
        step_box->setValue(step);
        step_box->setRange(3, 100);
        changes_lay1->addWidget(step_box);
        sleep_label = new QLabel("Speed(ms): ");
        changes_lay1->addWidget(sleep_label);
        sleep_box = new QSpinBox;
        sleep_box->setRange(50, 10000);
        sleep_box->setValue(100);
        changes_lay1->addWidget(sleep_box);

        QHBoxLayout *changes_lay2 = new QHBoxLayout;
        size_label = new QLabel("Number of circles(x*y): ");
        changes_lay2->addWidget(size_label);
        sizex_box = new QSpinBox;
        sizex_box->setValue(sizex);
        sizex_box->setRange(2, 300);
        changes_lay2->addWidget(sizex_box);
        sizey_box = new QSpinBox;
        sizey_box->setValue(sizey);
        sizey_box->setRange(2, 300);
        changes_lay2->addWidget(sizey_box);
        main_lay->addLayout(changes_lay1);
        main_lay->addLayout(changes_lay2);
        setLayout(main_lay);
        connect(restart_button, SIGNAL(clicked(bool)), this, SLOT(restart()));
    }

    void set_size(unsigned int &sx, unsigned int &sy)
    {
        sizex = sx;
        sizey = sy;
    }

    void set_field(QVector<QVector<unsigned int> > f)
    {
        fieldf = f;
        paint_w->set_field(&fieldf);
    }

public slots:
    void start_newthread()
    {
        connect(&thr, SIGNAL(send_repaint(QVector<QVector<unsigned int> >)), this, SLOT(repaint_me(QVector<QVector<unsigned int> >)));
        thr.set_mobj(f);
        thr.start();
    }

    void get_info(unsigned int step_prey, unsigned int step_predator, unsigned int speed_prey, unsigned int speed_predator)
    {
        f->set_max_steps_prey(step_prey);
        f->set_max_steps(step_predator);
        f->set_speed_prey(speed_prey);
        f->set_speed_predator(speed_predator);
    }

    void open_new_wind()
    {
        thr.terminate();
        new_wind = new AdvancedSettings(f->get_max_steps_prey(), f->get_max_steps(), f->get_speed_prey(), f->get_speed_predator());
        connect(new_wind, SIGNAL(send_all(uint,uint,uint,uint)), this, SLOT(get_info(uint,uint,uint,uint)));
        connect(new_wind, SIGNAL(finished(int)), this, SLOT(start_newthread()));
        new_wind->setModal(true);
        new_wind->show();
    }

    void repaint_me(QVector<QVector<unsigned int> > field)
    {
        set_field(field);
        paint_w->repaint();
    }
    void restart()
    {
        bool flag_change_size = false;
        if(thr.get_sleep_time() != sleep_box->value())
        {
            thr.set_sleep_time(sleep_box->value());
        }
        if(flag_paint)
        {
            flag_paint = false;
            paint_w->set_flag_paint(flag_paint);
            clear_field_button->setVisible(false);
            predator_paint->setVisible(false);
            prey_paint->setVisible(false);

            sizex_box->setEnabled(true);
            sizey_box->setEnabled(true);
            step_box->setEnabled(true);
            f->set_field(fieldf);
            start_newthread();
        }
        else
        {
            if(step != step_box->value())
            {
                step = step_box->value();
                paint_w->set_step(step_box->value());
                flag_change_size = true;
            }
            if(sizex != sizex_box->value())
            {
                sizex = sizex_box->value();
                paint_w->set_sizex(sizex_box->value());
                flag_change_size = true;
            }
            if(sizey != sizey_box->value())
            {
                sizey = sizey_box->value();
                paint_w->set_sizey(sizey_box->value());
                flag_change_size = true;
            }
            f->gen_field(sizex, sizey);
            set_field(f->get_field());
        }
        if(flag_change_size)
        {
            paint_w->on_change_size();
        }
    }

    void start_paint()
    {
        flag_paint = true;
        paint_w->set_flag_paint(flag_paint);
        clear_field_button->setVisible(true);
        predator_paint->setVisible(true);
        prey_paint->setVisible(true);
        sizex_box->setEnabled(false);
        sizey_box->setEnabled(false);
        step_box->setEnabled(false);
        thr.terminate();
    }
    void clear_field()
    {
        for(unsigned int i = 0; i < sizex; ++i)
        {
            for(unsigned int j = 0; j < sizey; ++j)
            {
                fieldf[i][j] = 0;
            }
        }
        f->set_field(fieldf);
        paint_w->set_field(&fieldf);
        paint_w->repaint();
    }
};

#endif // MWINDOW_H
