#include "WordCounter.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QRegularExpression>

WordCounter::WordCounter()
{
}

void WordCounter::countWords(const QStringList& files, const QString& flags)
{
    static QRegularExpression punctuation("\\p{P}"); // Matches any punctuation character
//    static QRegularExpression whitespace("^\\s+|\\s+$"); // Matches leading or trailing whitespace

    bool flagA = flags.contains('a');
    bool flagB = flags.contains('b');
    bool flagC = flags.contains('c');
    bool flagD = flags.contains('d');

    for (const QString& file : files) {
        QFile inputFile(file);
        if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Error opening file:" << file;
            continue;
        }

        QTextStream in(&inputFile);
        QString fileText = in.readAll();
        inputFile.close();

        // Remove punctuation and leading/trailing whitespace
        fileText = fileText.replace(punctuation, "").trimmed();

        if (flagA || flags.isEmpty()) {
            int countA = countWordsWithCapital(fileText);
            qDebug() << "File:" << file << "- Words longer than 4 characters and start with a capital letter:" << countA;
        }

        if (flagB || flags.isEmpty()) {
            int countB = countHyphenatedWords(fileText);
            qDebug() << "File:" << file << "- Hyphenated words:" << countB;
        }

        if (flagC || flags.isEmpty()) {
            int countC = countWordsStartEndSame(fileText);
            qDebug() << "File:" << file << "- Words that start and end on the same character:" << countC;
        }

        if (flagD || flags.isEmpty()) {
            int countD = countWordsNotStartWithVowel(fileText);
            qDebug() << "File:" << file << "- Words that do not start with a vowel:" << countD;
        }
    }
}

int WordCounter::countWordsWithCapital(const QString& text)
{
    static QRegularExpression pattern("\\b[A-Z][A-Za-z]{4,}\\b");
    QRegularExpressionMatchIterator iterator = pattern.globalMatch(text);
    int count = 0;

    while (iterator.hasNext()) {
        iterator.next();
        count++;
    }

    return count;
}

int WordCounter::countHyphenatedWords(const QString& text)
{
    static QRegularExpression pattern2("[A-Za-z][-][A-Za-z]");
    QRegularExpressionMatchIterator iterator = pattern2.globalMatch(text);
    int count = 0;

    while (iterator.hasNext()) {
        iterator.next();
        count++;
    }

    return count;
}

int WordCounter::countWordsStartEndSame(const QString& text)
{
    static QRegularExpression pattern3("\\b([A-Za-z])\\w*\\1\\b");
    QRegularExpressionMatchIterator iterator = pattern3.globalMatch(text);
    int count = 0;

    while (iterator.hasNext()) {
        iterator.next();
        count++;
    }

    return count;
}

int WordCounter::countWordsNotStartWithVowel(const QString& text)
{
    static QRegularExpression pattern4("\\b[^aeiouAEIOU]\\w+\\b");
    QRegularExpressionMatchIterator iterator = pattern4.globalMatch(text);
    int count = 0;

    while (iterator.hasNext()) {
        iterator.next();
        count++;
    }

    return count;
}
