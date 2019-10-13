#ifndef BOARD_H
#define BOARD_H

#include "Cube.h"

#include <QWidget>
#include <QSignalMapper>
#include <vector>
#include "Location.h"

class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = nullptr, int size = 5, const QString *cubeLetters = BIG_BOGGLE_CUBES);
    virtual ~Board();
    void shake();
    int getSize()const{return size;}
    string getLetter(int i, int j) const{return cubes[index(i, j)]->getLetter();}
    void humanHighLight(const std::vector<Location>& wordLo);
    void computerHighLight(const std::vector<Location>& wordLo);
    void recover(int i,int j);
signals:
    void newButtonClicked(int i,int j,string letter);
public slots:
private slots:
    void doClicked(int ij);
private:
    int size;
    Cube **cubes;
    QString *letters;
    QSignalMapper *buttonMapper;
    inline int index(int i, int j) const{ return i * size + j; }
    static const QString STANDARD_CUBES[16];
    static const QString BIG_BOGGLE_CUBES[25];
    int wordI,curI;
};

#endif // BOARD_H
