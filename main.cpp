/* This file is part of the Tome of Concurrency book.
 * (C) Mirko Boehm <mirko@kde.org>
 * Licensed under the GPLv3.
 */

#include <iostream>

#include <QCoreApplication>
#include <QFileInfo>

#include "Exception.h"
#include "Helpers.h"
#include "Process.h"

int main(int argc, char *argv[])
{
    using namespace std;
    try {
        QCoreApplication a(argc, argv);
        const QString copyrightnote = u("%1 - process special instructions to include code samples\n"
                                        "* Author: Mirko Boehm <mirko@kde.org>\n"
                                        "* Licensed under the GPLv3.").arg(a.applicationName());
        const QString usage = u("\nUsage:\n"
                                "%1 <inputfile> <outputfile>\n"
                                "or\n"
                                "%1 --snippet <mode> <sourcefile> <snippet name> <style>\n").arg(a.applicationName());
        if (argc != 3 && argc != 6) {
          std::wcout << copyrightnote.toStdWString() << endl;
          throw Exception(usage);
        }
        // snippet mode
        if(argc == 6)
        {
          if (QString::fromLocal8Bit(argv[1]) == QString("--snippet")) {
            QString position("Unknown position");
            const QString argumentString =
              u("%1,%2,%3,%4")
              .arg(QString::fromLocal8Bit(argv[3]))
              .arg(QString::fromLocal8Bit(argv[4]))
              .arg(QString::fromLocal8Bit(argv[5]))
              .arg(QString::fromLocal8Bit(argv[2]));
            std::wcout << process_snippet(argumentString, position).toStdWString() << std::endl;
          }
          else
            throw Exception(usage);
        }
        else {
          const QString inputfile = QString::fromLocal8Bit(argv[1]);
          const QString outputfile = QString::fromLocal8Bit(argv[2]);
          process(inputfile, outputfile);
        }
   } catch(const Exception& ex) {
        wcout << ex.message().toStdWString() <<endl;
        return 1;
    }
}
