#include "BoggleWindow.h"

#include <QFile>
#include <QHBoxLayout>
#include <QTextEdit>
#include <iostream>

BoggleWindow::BoggleWindow(QWidget *parent)
    : QMainWindow(parent),curWordI(0)
{
    this->setWindowTitle("QBoggle!");
    this->setFixedSize(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);

    me = new WordListWidget(this, "Me");
    computer = new WordListWidget(this, "Computer");
    board = new Board(this);
    console = new Console(this);

    me->setGeometry(20, 20, 230, 300);
    board->setGeometry(230, 0, 300, 300);
    computer->setGeometry(800 - 50 - 200, 20, 230, 300);
    console->setGeometry(30, 320, 740, 260);
    console->write("Welcome to the game Boggle!\n");
    button=new ButtonWidget(this);
    button->setGeometry(20,580,740,50);
    worker=new Worker(board);
    worker->moveToThread(&workerThread);
    connect(button->button1(),SIGNAL(clicked()),button,SLOT(addButton()));
    connect(button->button2(),SIGNAL(clicked()),this,SLOT(restart()));
    connect(button,SIGNAL(addComplete()),this,SLOT(addButton()));
    connect(button,SIGNAL(resetComplete()),this,SLOT(resetButton()));
    connect(worker,SIGNAL(newWord(const string &,const vector<Location> &)),this,SLOT(addWord(const string &,const vector<Location> &)));
    connect(console,SIGNAL(newLineWritten(const QString&)),this,SLOT(checkConsole(const QString&)));
    connect(board,SIGNAL(newButtonClicked(int,int,string)),this,SLOT(checkBoard(int,int,string)));
    workerThread.start();
}

BoggleWindow::~BoggleWindow()
{
    workerThread.quit();
    workerThread.wait();
}

void BoggleWindow::restart()
{
    wordStore.clear();
    locationStore.clear();
    board->shake();
    me->clear();
    computer->clear();
    button->resetButton();
    worker->clear();
    curWordI=0;
    tmpI=0;
}

void BoggleWindow::addWord(const string &strWord ,const vector<Location> &wordLo)
{
    wordStore.push_back(strWord);
    locationStore.push_back(wordLo);
}

void BoggleWindow::checkConsole(const QString& word)
{
    string strW=word.toStdString();
    vector<Location> wordLo;
    if(worker->checkConsole(strW,wordLo))
        humanPaint(word,wordLo);
}

void BoggleWindow::checkBoard(int i,int j,string letter)
{
    if(!tmpLocation.empty())
    {
         Location last=tmpLocation.back();
         if(abs(i-last.x)>1 || abs(j-last.y)>1)
             clearClicked();
    }
    tmpLocation.push_back(Location(i,j));
    tmpWord+=letter;
    if(worker->check(tmpWord))
    {
        humanPaint(QString::fromStdString(tmpWord),tmpLocation);
        clearClicked();
    }
    else if(!worker->checkPrefix(tmpWord))
        clearClicked();
    return;
}

void BoggleWindow::clearClicked()
{
    for(int i=0;i<tmpLocation.size();++i)
        board->recover(tmpLocation[i].x,tmpLocation[i].y);
    tmpLocation.clear();
    tmpWord.clear();
}

void BoggleWindow::humanPaint(const QString &word,const vector<Location> &wordLo)
{
    me->newWord(word);
    board->humanHighLight(wordLo);
}

void BoggleWindow::computerPaint()
{
    if(curWordI==wordStore.size())
    {
        console->append("Computer play over");
        return;
    }
    computer->newWord(QString::fromStdString(wordStore[curWordI]));
    board->computerHighLight(locationStore[curWordI++]);
}

void BoggleWindow::paintRemain()
{
    if(curWordI==wordStore.size())
    {
        console->append("Computer play over");
        return;
    }
    for(;curWordI<wordStore.size();++curWordI)
        computer->newWord(QString::fromStdString(wordStore[curWordI]));
    for(int i=0;i<board->getSize();++i)
        for(int j=0;j<board->getSize();++j)
            board->recover(i,j);
}

void BoggleWindow::addButton()
{
    connect(button->button3(),SIGNAL(clicked()),this,SLOT(computerPaint()));
    connect(button->button4(),SIGNAL(clicked()),this,SLOT(paintRemain()));
    worker->computerPlay();
}

void BoggleWindow::resetButton()
{
    connect(button->button1(),SIGNAL(clicked()),worker,SLOT(computerPlay()));
    connect(button->button1(),SIGNAL(clicked()),button,SLOT(addButton()));
    connect(button->button2(),SIGNAL(clicked()),this,SLOT(restart()));
}
