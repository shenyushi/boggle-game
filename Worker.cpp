#include "Worker.h"

Worker::Worker(Board *b):board(b),size(b->getSize())
{
    QFile qFile(":/res/EnglishWords.txt");
    if (!qFile.open(QIODevice::ReadOnly))
        throw new std::runtime_error("Resource file not found!");
    lex = new Lexicon(qFile);
}
Worker::~Worker()
{

}

bool Worker::isUsed(const string &str) const
{
    for (unsigned long long int i = 0; i < usedWord.size(); ++i)
        if (usedWord[i] == str)
            return true;
    return false;
}

void Worker::computerPlay()
{
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            bool *used = new bool[size * size];
            for (int i = 0; i < size; ++i)
                for (int j = 0; j < size; ++j)
                    used[i * size + j] = false;
            string word;
            vector<Location> wordLo={Location(i,j)};
            computerFind(wordLo, word, used);
            delete []used;
        }
    }
}

void Worker::computerFind(vector<Location> &wordLo, string &word, bool *used)
{
    Location cur=wordLo.back();
    word+=board->getLetter(cur.x, cur.y);
    used[size * cur.x + cur.y] = true;
    if (lex->contains(word) && word.size() >= 4 && !isUsed(word))
    {
        usedWord.push_back(word);
        emit newWord(word,wordLo);
    }
    if (lex->containsPrefix(word))
    {
        if (cur.x != 0 && !used[size * (cur.x - 1) + cur.y])
        {
            wordLo.push_back(Location(cur.x-1,cur.y));
            computerFind(wordLo, word, used);
            if (cur.y != 0 && !used[size * (cur.x - 1) + cur.y - 1])
            {
                wordLo.push_back(Location(cur.x-1,cur.y-1));
                computerFind(wordLo, word, used);
            }
            if (cur.y != size - 1 && !used[size * (cur.x - 1) + cur.y + 1])
            {
                wordLo.push_back(Location(cur.x-1,cur.y+1));
                computerFind(wordLo, word, used);
            }
        }
        if (cur.x != size - 1 && !used[size * (cur.x + 1) + cur.y])
        {
            wordLo.push_back(Location(cur.x+1,cur.y));
            computerFind(wordLo, word, used);
            if (cur.y != 0 && !used[size * (cur.x + 1) + cur.y - 1])
            {
                wordLo.push_back(Location(cur.x+1,cur.y-1));
                computerFind(wordLo, word, used);
            }
            if (cur.y != size - 1 && !used[size * (cur.x + 1) + cur.y + 1])
            {
                wordLo.push_back(Location(cur.x+1,cur.y+1));
                computerFind(wordLo, word, used);
            }
        }
        if (cur.y != 0 && !used[size * cur.x + cur.y - 1])
        {
            wordLo.push_back(Location(cur.x,cur.y-1));
            computerFind(wordLo, word, used);
        }
        if (cur.y != size - 1 && !used[size * cur.x + cur.y + 1])
        {
            wordLo.push_back(Location(cur.x,cur.y+1));
            computerFind(wordLo, word, used);
        }
    }
    word.pop_back();
    wordLo.pop_back();
    used[size * cur.x + cur.y] = false;
}

bool Worker::checkConsole(const string &str,vector<Location> &wordLo)
{
    if(isUsed(str) && !lex->contains(str))
        return false;
    if(humanFind(str,wordLo))
    {
        usedWord.push_back(str);
        return true;
    }
    return false;
}

bool Worker::humanFind(const string &word,vector<Location> &wordLo)
{
    string Word;
    for(int i=0;i<word.size();++i)
    {
        if(word[i]>='a' && word[i]<='z')
            Word.push_back(word[i]-'a'+'A');
        else
            Word.push_back(word[i]);
    }
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (board->getLetter(i, j)[0] == Word[0])
            {
                bool *used = new bool[size * size];
                for (int i = 0; i < size; ++i)
                    for (int j = 0; j < size; ++j)
                        used[size * i + j] = false;
                wordLo.push_back(Location(i,j));
                bool flag = humanFind(Word,0,wordLo,used);
                delete[] used;
                if (flag)
                    return true;
            }
        }
    }
    return false;
}

bool Worker::humanFind(const string &word,int curI,vector<Location> &wordLo, bool *used)
{
    int Qhead=word[curI]=='Q'?1:0;
    Location cur=wordLo.back();
    if (board->getLetter(cur.x, cur.y)[0] != word[curI])
    {
        wordLo.pop_back();
        return false;
    }
    used[size * cur.x + cur.y] = true;
    if (curI + 1+Qhead == word.size())
        return true;
    if (cur.x != 0)
    {
        wordLo.push_back(Location(cur.x-1,cur.y));
        if (!used[size * (cur.x - 1) + cur.y] && humanFind(word, curI + 1+Qhead, wordLo ,used))
            return true;
        if (cur.y != 0 && !used[size * (cur.x - 1) + cur.y - 1])
        {
            wordLo.push_back(Location(cur.x-1,cur.y-1));
            if(humanFind(word, curI + 1+Qhead, wordLo,used))
                return true;
        }
        if (cur.y != size-1 && !used[size * (cur.x - 1) + cur.y + 1])
        {
            wordLo.push_back(Location(cur.x-1,cur.y+1));
            if(humanFind(word, curI + 1+Qhead, wordLo,used))
                return true;
        }
    }
    if (cur.x != size - 1)
    {
        wordLo.push_back(Location(cur.x+1,cur.y));
        if (!used[size * (cur.x + 1) + cur.y] && humanFind(word, curI + 1+Qhead,wordLo, used))
            return true;
        if (cur.y != 0 && !used[size * (cur.x + 1) + cur.y - 1] )
        {
            wordLo.push_back(Location(cur.x+1,cur.y-1));
            if(humanFind(word, curI + 1+Qhead, wordLo, used))
                return true;
        }
        if (cur.y != size-1 && !used[size * (cur.x + 1) + cur.y + 1] )
        {
            wordLo.push_back(Location(cur.x+1,cur.y+1));
            if(humanFind(word, curI + 1+Qhead, wordLo, used))
                return true;
        }
    }
    if (cur.y != 0 && !used[size * cur.x + cur.y - 1])
    {
        wordLo.push_back(Location(cur.x,cur.y-1));
        if(humanFind(word, curI + 1+Qhead, wordLo,used))
            return true;
    }
    if (cur.y != size-1 && !used[size * cur.x + cur.y + 1])
    {
        wordLo.push_back(Location(cur.x,cur.y+1));
        if(humanFind(word, curI + 1+Qhead, wordLo,used))
            return true;
    }
    used[size * cur.x + cur.y] = false;
    wordLo.pop_back();
    return false;
}

bool Worker::checkPrefix(const string &str)
{
    return lex->containsPrefix(str);
}

bool Worker::check(const string&str)
{
    bool flag=  !isUsed(str) && str.size()>=4 && lex->contains(str);
    if(flag)
        usedWord.push_back(str);
    return flag;
}
