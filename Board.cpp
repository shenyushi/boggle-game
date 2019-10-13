#include "Board.h"
#include "Cube.h"
#include <QTime>
#include <QGridLayout>


const QString Board::STANDARD_CUBES[16]  = {
        "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
        "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
        "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
        "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

const QString Board::BIG_BOGGLE_CUBES[25]  = {
        "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
        "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
        "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
        "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
        "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

Board::Board(QWidget *parent, int size, const QString *cubeLetters) : QWidget(parent)
{
    this->size = size;
    this->cubes = new Cube*[size * size];
    this->letters = new QString[size * size];
    for (int i = 0; i < size * size; ++i)
        this->letters[i] = cubeLetters[i];
    this->buttonMapper=new QSignalMapper(this);

    QGridLayout *layout = new QGridLayout();
    layout->setMargin(20);
    layout->setSpacing(10);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            this->cubes[index(i, j)] = new Cube(this);
            layout->addWidget(this->cubes[index(i, j)], i, j, Qt::AlignmentFlag::AlignCenter);
            connect(cubes[index(i,j)]->getButton(),SIGNAL(clicked()),buttonMapper,SLOT(map()));
            buttonMapper->setMapping(cubes[index(i,j)]->getButton(),10*i+j);
        }
    }
    shake();
    connect(buttonMapper,SIGNAL(mapped(int)),this,SLOT(doClicked(int)));
    setLayout(layout);
}

Board::~Board()
{
    if (cubes) delete[] cubes;
    if (letters) delete[] letters;
}

void Board::shake()
{
    srand(time(NULL));
    for (int i = 0; i < letters->size(); ++i)
    {
        int ran = rand() % (letters->size() - i);
        QString tmp = letters[i];
        letters[i] = letters[i + ran];
        letters[i + ran] = tmp;
    }
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            int ran = rand() % 6;
            QChar tmp=this->letters[index(i, j)].at(ran);
            if(tmp=='Q')
                this->cubes[index(i, j)]->setLetter("QU");
            else
                this->cubes[index(i, j)]->setLetter(tmp);
            this->cubes[index(i, j)]->recover();
        }
    }
    /*cubes[index(1,3)]->setLetter("QU");
    cubes[index(1,2)]->setLetter("I");                //////////////// test Q letter
    cubes[index(1,1)]->setLetter("C");
    cubes[index(1,0)]->setLetter("K");*/
}

void Board::doClicked(int ij)
{
    int i=ij/10,j=ij%10;
    cubes[index(i,j)]->highLight();
    emit newButtonClicked(i,j,cubes[index(i,j)]->getLetter());
}

void Board::recover(int i, int j)
{
    cubes[index(i,j)]->recover();
}

void Board::humanHighLight(const std::vector<Location>& wordLo)
{
    for(int i=0;i<wordLo.size();++i)
    {
        cubes[index(wordLo[i].x,wordLo[i].y)]->highLight();
        repaint();
        QTime time;
        time.start();
        while(time.elapsed()<80);
    }
    repaint();
    QTime time;
    time.start();
    while(time.elapsed()<120);
    for(int i=0;i<wordLo.size();++i)
    {
        cubes[index(wordLo[i].x,wordLo[i].y)]->recover();
        repaint();
        QTime time;
        time.start();
        while(time.elapsed()<80);
    }
}

void Board::computerHighLight(const std::vector<Location>& wordLo)
{
    for(int i=0;i<size;++i)
        for(int j=0;j<size;++j)
            cubes[index(i,j)]->recover();
    repaint();
    for(int i=0;i<wordLo.size();++i)
    {
        cubes[index(wordLo[i].x,wordLo[i].y)]->highLight();
        repaint();
        QTime time;
        time.start();
        while(time.elapsed()<80);
    }
}
