#ifndef BUTTONWIDGET_H
#define BUTTONWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>

class ButtonWidget:public QWidget
{
    Q_OBJECT
private:
    QHBoxLayout *buttonLayout;
    QPushButton *computerStart;
    QPushButton *reset;
    QPushButton *next;
    QPushButton *skip;

public:
    explicit ButtonWidget(QWidget *parent=nullptr);
    const QPushButton* button1()const {return computerStart;}
    const QPushButton* button2()const {return reset;}
    const QPushButton* button3()const {return next;}
    const QPushButton* button4()const {return skip;}
    void resetButton();
signals:
    void addComplete();
    void resetComplete();
public slots:
    void addButton();
};

#endif // BUTTONWIDGET_H
