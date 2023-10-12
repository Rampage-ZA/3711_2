#include <QCoreApplication>
#include <QCommandLineParser>
#include "WordCounter.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("WordCount");
    QCoreApplication::setApplicationVersion("1.0");

    QCommandLineParser parser;
    parser.setApplicationDescription("Counts occurrences of specified patterns in text files.");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption flagA("a", "Count words longer than 4 characters that start with a capital letter.");
    QCommandLineOption flagB("b", "Count hyphenated words.");
    QCommandLineOption flagC("c", "Count words that start and end on the same character.");
    QCommandLineOption flagD("d", "Count words that do not start with a vowel.");

    parser.addOption(flagA);
    parser.addOption(flagB);
    parser.addOption(flagC);
    parser.addOption(flagD);

    parser.process(app);

    QStringList files = parser.positionalArguments();
    QString flags;
    if (parser.isSet(flagA)) flags += 'a';
    if (parser.isSet(flagB)) flags += 'b';
    if (parser.isSet(flagC)) flags += 'c';
    if (parser.isSet(flagD)) flags += 'd';

    WordCounter wordCounter;
    wordCounter.countWords(files, flags);

    return 0;
}
