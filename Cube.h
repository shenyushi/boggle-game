#ifndef CUBE_H
#define CUBE_H

#include <QPushButton>
#include <QWidget>
#include <string>
using namespace std;

class Cube : public QWidget
{
    Q_OBJECT
public:
    explicit Cube(QWidget *parent = nullptr);
    void setLetter(QString l);
    void highLight();
    void recover();
    QPushButton* getButton()const{return button;}
    string getLetter()const{return letter;}

signals:

public slots:

private:
    QPushButton *button;
    string letter;
};

#endif // CUBE_H
