#-------------------------------------------------
#
# Project created by QtCreator 2018-11-13T20:19:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Translator
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++17 \
          testlib

QMAKE_CXXFLAGS += /std:c++17

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    IO/fileinputstream.cpp \
    lexicalAnalyzer/statesdiagram.cpp \
    lexicalAnalyzer/lexicalanalyzer.cpp \
    lexicalAnalyzer/inputlexemtable.cpp \
    codeeditor.cpp \
    IO/stringinputstream.cpp \
    syntaxAnalyzer/recursivesyntaxanalyzer.cpp \
    model/translatorfacade.cpp \
    symanticAnalyzer/semanticanalyzer.cpp \
    syntaxAnalyzer/automasyntaxanalyzer.cpp \
    syntaxAnalyzer/precedencetableformer.cpp \
    syntaxAnalyzer/upstreamanalyzer.cpp \
    rpnGenerator/uniquelabelsgenerator.cpp

HEADERS += \
        mainwindow.h \
    lexicalAnalyzer/Exceptions/lexemnotfoundexception.h \
    lexicalAnalyzer/Exceptions/lexicalerror.h \
    IO/inputstream.h \
    IO/fileinputstream.h \
    IO/Exceptions/filenotfoundexception.h \
    IO/Exceptions/endoffileexception.h \
    lexicalAnalyzer/algorythm.h \
    lexicalAnalyzer/statesdiagram.h \
    syntaxAnalyzer/Exceptions/syntaxiserror.h \
    symanticAnalyzer/Exceptions/symanticerror.h \
    lexicalAnalyzer/lexicalanalyzer.h \
    lexicalAnalyzer/utils.h \
    lexicalAnalyzer/lexicalanalyzeroutput.h \
    lexicalAnalyzer/inputlexemtable.h \
    codeeditor.h \
    model/Exceptions/translatorexception.h \
    IO/stringinputstream.h \
    symanticAnalyzer/utils.h \
    syntaxAnalyzer/recursivesyntaxanalyzer.h \
    model/translatorfacade.h \
    syntaxAnalyzer/syntaxanalyzer.h \
    symanticAnalyzer/semanticanalyzer.h \
    syntaxAnalyzer/automasyntaxanalyzer.h \
    syntaxAnalyzer/precedencetableformer.h \
    syntaxAnalyzer/upstreamanalyzer.h \
    IO/jsonparcer.h \
    rpnGenerator/dijkstrarpngenerator.h \
    rpnGenerator/rpnunit.h \
    rpnGenerator/inputitem.h \
    rpnGenerator/openbracketinputitem.h \
    rpnGenerator/closebracketinputitem.h \
    rpnGenerator/inputitemfactory.h \
    tests/dijkstratest.h \
    tests/testcase.h \
    rpnGenerator/skippedinputitem.h \
    rpnGenerator/operatorendinginputitem.h \
    rpnGenerator/booleanliteralinputitem.h \
    rpnGenerator/doinputitem.h \
    rpnGenerator/uniquelabelsgenerator.h \
    rpnGenerator/whileinputitem.h \
    rpnGenerator/cycleoperatorendinginputitem.h \
    rpnGenerator/ifinputitem.h \
    rpnGenerator/theninputitem.h \
    rpnGenerator/instreaminputitem.h \
    rpnGenerator/outstreaminputitem.h \
    rpnGenerator/rpnlogger.h \
    rpnGenerator/condstatementendinginputitem.h \
    rpnOptimizer/rpnoptimizer.h \
    rpnExecuter/rpnexecuter.h \
    tests/semanticanalyzertest.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
