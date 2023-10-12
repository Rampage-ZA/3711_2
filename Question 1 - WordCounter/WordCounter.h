#ifndef WORDCOUNTER_H
#define WORDCOUNTER_H

#include <QString>
#include <QVector>

class WordCounter
{
public:
    WordCounter();

    void countWords(const QStringList& files, const QString& flags);

private:
    int countWordsWithCapital(const QString& text);
    int countHyphenatedWords(const QString& text);
    int countWordsStartEndSame(const QString& text);
    int countWordsNotStartWithVowel(const QString& text);
};

#endif // WORDCOUNTER_H
