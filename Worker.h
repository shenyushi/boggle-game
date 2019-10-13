#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include "Board.h"
#include "lexicon.h"
#include "Location.h"
#include <vector>
#include <string>
using namespace std;

class Worker:public QObject
{
    Q_OBJECT
private:
    Board *board;
    Lexicon *lex;
    vector<string> usedWord;
    int size;

    bool isUsed(const string &str) const;
    bool humanFind(const string &word,vector<Location> &wordLo);
    bool humanFind(const string &word,int curI,vector<Location> &wordLo, bool *used);
    void computerFind(vector<Location> &wordLo, string &word, bool *used);
public:
    Worker(Board *b);
    ~Worker();
    bool checkConsole(const string &str,vector<Location> &wordLo);
    bool checkPrefix(const string &str);
    bool check(const string &str);
    void clear(){usedWord.clear();}
public slots:
    void computerPlay();
signals:
    void newWord(const string &word ,const vector<Location> &wordLo);
};
#endif // WORKER_H
