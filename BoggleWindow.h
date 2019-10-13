#ifndef BOGGLEWINDOW_H
#define BOGGLEWINDOW_H

#include "Board.h"
#include "Console.h"
#include "WordListWidget.h"
#include "ButtonWidget.h"
#include "Worker.h"
#include <QMainWindow>
#include <QThread>

class BoggleWindow : public QMainWindow
{
    Q_OBJECT

public:
    BoggleWindow(QWidget *parent = 0);
    ~BoggleWindow();
private:
    WordListWidget *me;
    WordListWidget *computer;
    Board *board;
    Console *console;
    ButtonWidget *button;
    Worker *worker;
    QThread workerThread;

    int curWordI;
    vector<vector<Location>> locationStore;
    vector<string> wordStore;

    int tmpI;
    vector<Location> tmpLocation;
    string tmpWord;

    static const int BOGGLE_WINDOW_WIDTH = 800;
    static const int BOGGLE_WINDOW_HEIGHT = 650;
    void humanPaint(const QString &word,const vector<Location> &wordLo);

private slots:
    void restart();
    void addWord(const string &word ,const vector<Location> &wordL);
    void checkConsole(const QString&);
    void checkBoard(int i,int j,string letter);
    void clearClicked();
    void paintRemain();
    void computerPaint();
    void addButton();
    void resetButton();
};

#endif // BOGGLEWINDOW_H
