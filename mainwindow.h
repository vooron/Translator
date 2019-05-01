#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include "model/translatorfacade.h"
#include "model/Exceptions/translatorexception.h"
#include "syntaxAnalyzer/automasyntaxanalyzer.h"
#include "syntaxAnalyzer/syntaxanalyzer.h"
#include <syntaxAnalyzer/upstreamanalyzer.h>
#include "lexicalAnalyzer/lexicalanalyzeroutput.h"
#include "rpnGenerator/dijkstrarpngenerator.h"
#include "rpnGenerator/rpnlogger.h"
#include "rpnOptimizer/rpnoptimizer.h"
#include "rpnExecuter/rpnexecuter.h"

#include <string>
#include <vector>

#include <QFileDialog>
#include <QString>
#include <QTableWidget>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_processButton_clicked();

    void on_clrOutput_clicked();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionLexems_Table_triggered();

    void on_actionConstants_Table_triggered();

    void on_actionId_Table_triggered();

    void on_actionLexical_Analyzer_Trace_triggered();

    void on_actionPrecedence_Table_triggered();

    void on_actionPolis_triggered();

    void on_actionPolis_trace_triggered();

    void on_actionPolis_execution_triggered();

private:
    Ui::MainWindow *ui;
    QTableWidget *lexemsTable;
    QTableWidget *constsTable;
    QTableWidget *identsTable;

    QTableWidget *traceTable;
    QTableWidget *automaConfTable;

    QTableWidget *precedenceTable;

    QTableWidget *tracePrecedence;


    QTableWidget *rpnTraceTable;

    QTableWidget *rpnExecutionTraceTable;


    LexicalAnalyzerOutput *lexicalAnalyzerOutput = nullptr;
    std::vector<UpStreamAnalyzer::TraceItem> *syntaxAnalyzerTrace = nullptr;
    PrecedenceTableFormer::PrecedenceTable *precedeneTableConf = nullptr;
    std::vector<rpn::LogItem>* rpnTrace = nullptr;

    std::vector<RpnExecuter::LogItem>* rpnExecutionTrace;

    string polis;


    void showLexemsTable(const LexicalAnalyzerOutput &lexicalAnalyzerOutput);
    void showConstsTable(const LexicalAnalyzerOutput &lexicalAnalyzerOutput);
    void showIdentsTable(const LexicalAnalyzerOutput &lexicalAnalyzerOutput);
    void showRpnTrace(const std::vector<rpn::LogItem> &trace);


    void showTraceTable(const std::vector<AutomaSyntaxAnalyzer::TraceItem> &trace);
    void showConfTable(const std::vector<AutomaSyntaxAnalyzer::AutomaConfItem>& conf);

    void showPrecedenceTable(const PrecedenceTableFormer::PrecedenceTable& conf);

    void showTracePrecedence(const std::vector<UpStreamAnalyzer::TraceItem>& trace);

    void showRpnExecutionTable(const std::vector<RpnExecuter::LogItem>& rpnExecutionTrace);

};

#endif // MAINWINDOW_H
