#include "Cube.h"

#include <QHBoxLayout>

Cube::Cube(QWidget *parent) : QWidget(parent)
{
    button = new QPushButton();
    button->setText("");
    //button->setAlignment(Qt::AlignCenter);
    button->setFixedSize(50,50);
    QFont font = button->font();
    font.setPointSize(20);
    button->setFont(font);

    this->setFixedSize(75, 75);
    this->setStyleSheet("background-color: white; border-radius: 15px; border: 2px solid");

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(button);
    setLayout(layout);
}

void Cube::setLetter(QString l)
{
    button->setText(l);
    letter=l.toStdString();
}

void Cube::highLight()
{
    this->setStyleSheet("background-color: grey; border-radius: 15px; border: 2px solid");
}

void Cube::recover()
{
    this->setStyleSheet("background-color: white; border-radius: 15px; border: 2px solid");
}
