#include "mainwindow.h"
#include <QApplication>



//#define TEST_MODE

#include <tests/dijkstratest.h>
#include <tests/semanticanalyzertest.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#ifndef TEST_MODE
    MainWindow w;
    w.setWindowTitle("Translator");
    w.show();
#else

    START_TEST_CASE {

        DijrstraTest dijkstraTest;
        SemanticAnalyzerTest semanticAnalyzerTest;

        dijkstraTest.test();
        semanticAnalyzerTest.test();

    } END_TEST_CASE

#endif


    return a.exec();
}
