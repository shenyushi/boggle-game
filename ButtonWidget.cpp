#include "ButtonWidget.h"

ButtonWidget::ButtonWidget(QWidget *parent):QWidget (parent)
{
    buttonLayout=new QHBoxLayout;
    computerStart=new QPushButton();
    computerStart->setText("ComputerPlay");
    computerStart->setFixedSize(350,40);
    reset=new QPushButton();
    reset->setText("RESET");
    reset->setFixedSize(350,40);
    QFont font;
    font.setPointSize(20);
    computerStart->setFont(font);
    reset->setFont(font);

    buttonLayout->addWidget(computerStart);
    buttonLayout->addWidget(reset);
    setLayout(buttonLayout);

    next=NULL;
    skip=NULL;
}

void ButtonWidget::addButton()
{
    delete buttonLayout;
    buttonLayout=new QHBoxLayout;
    delete computerStart;
    next=new QPushButton();
    next->setFixedSize(233,40);
    next->setText("Next");
    skip=new QPushButton();
    skip->setFixedSize(233,40);
    skip->setText("Skip");
    QFont font;
    font.setPointSize(20);
    next->setFont(font);
    skip->setFont(font);
    reset->setFixedSize(233,40);
    buttonLayout->addWidget(next,0, Qt::AlignmentFlag::AlignLeft);
    buttonLayout->addWidget(skip,0, Qt::AlignmentFlag::AlignCenter);
    buttonLayout->addWidget(reset,0,Qt::AlignmentFlag::AlignRight);
    setLayout(buttonLayout);
    emit addComplete();
}

void ButtonWidget::resetButton()
{
    if(next!=NULL)
    {
        delete buttonLayout;
        buttonLayout=new QHBoxLayout;
        delete next;
        delete skip;
        next=NULL;
        computerStart=new QPushButton();
        computerStart->setText("ComputerPlay");
        computerStart->setFixedSize(350,40);
        reset->setFixedSize(350,40);
        QFont font;
        font.setPointSize(20);
        computerStart->setFont(font);
        buttonLayout->addWidget(computerStart,0, Qt::AlignmentFlag::AlignLeft);
        buttonLayout->addWidget(reset,0,Qt::AlignmentFlag::AlignRight);
        setLayout(buttonLayout);
        emit resetComplete();
    }
}


