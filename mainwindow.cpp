#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <fstream>

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), lexemsTable(nullptr), constsTable(nullptr),
    identsTable(nullptr), traceTable(nullptr), automaConfTable(nullptr),
    precedenceTable(nullptr), tracePrecedence(nullptr), rpnTraceTable(nullptr),
    rpnExecutionTraceTable(nullptr), rpnExecutionTrace(nullptr)
{
    ui->setupUi(this);


    if (!precedeneTableConf) {
        precedeneTableConf = new PrecedenceTableFormer::PrecedenceTable(PrecedenceTableFormer().makeTable());
    }

}

MainWindow::~MainWindow()
{
    delete ui;

    if (lexemsTable) {
        delete lexemsTable;
    }

    if (constsTable) {
        delete constsTable;
    }

    if (identsTable) {
        delete identsTable;
    }

    if (traceTable) {
        delete traceTable;
    }

    if (automaConfTable) {
        delete automaConfTable;
    }

    if (precedenceTable) {
        delete precedenceTable;
    }

    if(tracePrecedence) {
        delete tracePrecedence;
    }

    if(lexicalAnalyzerOutput) {
        delete lexicalAnalyzerOutput;
    }

    if(syntaxAnalyzerTrace) {
        delete syntaxAnalyzerTrace;
    }

    if (rpnTraceTable) {
        delete rpnTraceTable;
    }

    if(precedeneTableConf) {
        delete precedeneTableConf;
    }

    if(rpnTrace) {
        delete rpnTrace;
    }

    if (rpnExecutionTrace) {
        delete rpnExecutionTrace;
    }

    if (rpnExecutionTraceTable) {
        delete rpnExecutionTraceTable;
    }

}



void MainWindow::on_processButton_clicked()
{

    if(lexicalAnalyzerOutput) {
        delete lexicalAnalyzerOutput;
    }


    if(syntaxAnalyzerTrace) {
        delete syntaxAnalyzerTrace;
    }

    if(rpnTrace) {
        delete rpnTrace;
    }

    if (rpnExecutionTrace) {
        delete rpnExecutionTrace;
    }

    lexicalAnalyzerOutput = nullptr;
    syntaxAnalyzerTrace = nullptr;
    polis = "";
    rpnExecutionTrace = nullptr;


    this->ui->processButton->setEnabled(false);
    this->ui->programOutput->appendPlainText("Start processing");

    try {

//        AutomaSyntaxAnalyzer syntaxAnalyzer{};
        UpStreamAnalyzer syntaxAnalyzer;
        auto translator = TranslatorFacade{syntaxAnalyzer};
        translator.process(this->ui->plainTextEdit->toPlainText().toStdString());

        lexicalAnalyzerOutput = new LexicalAnalyzerOutput(translator.getLexicalAnalyzerOutput());
        syntaxAnalyzerTrace = new std::vector<UpStreamAnalyzer::TraceItem> (syntaxAnalyzer.getTrace());

        DijkstraRpnGenerator rpnGenerator;

        vector<RpnUnit*> rpn = rpnGenerator.generate(*lexicalAnalyzerOutput);
        rpnTrace = new vector<rpn::LogItem>(rpnGenerator.getLog());

        polis += rpnGenerator.getString(rpn);

        polis += " \n|\n ";

        RpnOptimizer optimizer;
        optimizer.optimize(rpn);

        polis += rpnGenerator.getString(rpn);

        RpnExecuter executor(*lexicalAnalyzerOutput);

        executor.execute(rpn);

        rpnExecutionTrace = new vector<RpnExecuter::LogItem>(executor.getLog());

        for(auto i: rpn) {
            delete i;
        }

    } catch(TranslatorException& e) {
        this->ui->programOutput->appendPlainText(QString::fromStdString(e.getMessage() + " ( row: " + to_string(e.getRow()) + " );"));
    }

    this->ui->programOutput->appendPlainText("Processing was ended");
    this->ui->processButton->setEnabled(true);
}


void MainWindow::on_clrOutput_clicked()
{
    this->ui->programOutput->clear();
}


void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName();

    QFile f( filename );

    if (f.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream in(&f);
        this->ui->plainTextEdit->clear();
        this->ui->plainTextEdit->appendPlainText(in.readAll());
        f.close();
    } else {
        this->ui->programOutput->appendPlainText("ERROR reading file");
    }
}


void MainWindow::on_actionSave_triggered()
{
    QString filename = QFileDialog::getSaveFileName();
    QFile f( filename );

    if (f.open(QFile::WriteOnly | QFile::Text)) {
        QTextStream out(&f);
        out << this->ui->plainTextEdit->toPlainText();
        f.close();
    } else {
        this->ui->programOutput->appendPlainText("ERROR creating file");
    }
}

void MainWindow::showLexemsTable(const LexicalAnalyzerOutput& lexicalAnalyzerOutput)
{
    const auto& lexems = lexicalAnalyzerOutput.getLexems();

    if (lexemsTable) {
        lexemsTable->close();
        delete lexemsTable;
    }

    lexemsTable = new QTableWidget;

    lexemsTable->setRowCount(lexems.size());
    lexemsTable->setColumnCount(5);

    for ( size_t i = 0; i < lexems.size(); i++ ) {
        QTableWidgetItem *rowItem = new QTableWidgetItem(QString::number(lexems[i].row));
        lexemsTable->setItem(i, 0, rowItem);

        QTableWidgetItem *nameItem = new QTableWidgetItem(QString::fromStdString(lexems[i].name));
        lexemsTable->setItem(i, 1, nameItem);

        QTableWidgetItem *codeItem = new QTableWidgetItem(QString::number(lexems[i].code));
        lexemsTable->setItem(i, 2, codeItem);

        if (lexems[i].isIdent) {
            QTableWidgetItem *identCodeItem = new QTableWidgetItem(QString::number(lexems[i].identCode));
            lexemsTable->setItem(i, 3, identCodeItem);
        }

        if (lexems[i].isConst) {
            QTableWidgetItem *constCodeItem = new QTableWidgetItem(QString::number(lexems[i].constCode));
            lexemsTable->setItem(i, 4, constCodeItem);
        }

        if (lexems[i].isMark) {
            QTableWidgetItem *markCodeItem = new QTableWidgetItem(QString::number(lexems[i].markCode));
            lexemsTable->setItem(i, 3, markCodeItem);

            QTableWidgetItem *isMarkItem = new QTableWidgetItem("+");
            lexemsTable->setItem(i, 5, isMarkItem);
        } else {
            QTableWidgetItem *isMarkItem = new QTableWidgetItem("-");
            lexemsTable->setItem(i, 5, isMarkItem);
        }
    }

    lexemsTable->setWindowTitle("Lexems");
    lexemsTable->resize(QSize(700, 600));
    lexemsTable->setHorizontalHeaderLabels({"row", "lexem", "code", "ident/label code", "const code", "is mark"});
    lexemsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    lexemsTable->show();
}




void MainWindow::showConstsTable(const LexicalAnalyzerOutput &lexicalAnalyzerOutput)
{
    const auto& consts = lexicalAnalyzerOutput.getConsts();

    if (constsTable) {
        constsTable->close();
        delete constsTable;
    }

    constsTable = new QTableWidget;

    constsTable->setRowCount(consts.size());
    constsTable->setColumnCount(2);

    for ( size_t i = 0; i < consts.size(); i++ ) {
        QTableWidgetItem *nameItem = new QTableWidgetItem(QString::fromStdString(consts[i].name));
        constsTable->setItem(i, 0, nameItem);

        QTableWidgetItem *typeItem = new QTableWidgetItem(QString::fromStdString(consts[i].type));
        constsTable->setItem(i, 1, typeItem);
    }

    constsTable->setWindowTitle("Consts");
    constsTable->resize(QSize(300, 500));
    constsTable->setHorizontalHeaderLabels({"const", "type"});
    constsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    constsTable->show();
}

void MainWindow::showIdentsTable(const LexicalAnalyzerOutput &lexicalAnalyzerOutput)
{
    const auto& idents = lexicalAnalyzerOutput.getIdents();

    if (identsTable) {
        identsTable->close();
        delete identsTable;
    }

    identsTable = new QTableWidget;

    identsTable->setRowCount(idents.size());
    identsTable->setColumnCount(3);

    for ( size_t i = 0; i < idents.size(); i++ ) {
        QTableWidgetItem *nameItem = new QTableWidgetItem(QString::fromStdString(idents[i].name));
        identsTable->setItem(i, 0, nameItem);

        QTableWidgetItem *typeItem = new QTableWidgetItem(QString::fromStdString(idents[i].type));
        identsTable->setItem(i, 1, typeItem);

        QTableWidgetItem *isLabelItem = new QTableWidgetItem(idents[i].isMark?"+":"-");
        identsTable->setItem(i, 2, isLabelItem);
    }

    identsTable->setWindowTitle("Idents&Labels");
    identsTable->resize(QSize(400, 500));
    identsTable->setHorizontalHeaderLabels({"ident", "type", "is label"});
    identsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    identsTable->show();
}

void MainWindow::showTraceTable(const std::vector<AutomaSyntaxAnalyzer::TraceItem> &trace)
{
    if (traceTable) {
        traceTable->close();
        delete traceTable;
    }

    traceTable = new QTableWidget;

    traceTable->setRowCount(trace.size());
    traceTable->setColumnCount(3);

    for ( size_t i = 0; i < trace.size(); i++ ) {
        QTableWidgetItem *cStateItem = new QTableWidgetItem(QString::number(trace[i].cState));
        traceTable->setItem(i, 0, cStateItem);

        QTableWidgetItem *lexemItem = new QTableWidgetItem(QString::fromStdString(trace[i].lexem));
        traceTable->setItem(i, 1, lexemItem);

        QTableWidgetItem *stackItem = new QTableWidgetItem(QString::fromStdString(trace[i].stack));
        traceTable->setItem(i, 2, stackItem);
    }

    traceTable->setWindowTitle("Trace");
    traceTable->resize(QSize(400, 500));
    traceTable->setHorizontalHeaderLabels({"Cur State", "lexem", "Stack"});
    traceTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    traceTable->show();

}

void MainWindow::showConfTable(const std::vector<AutomaSyntaxAnalyzer::AutomaConfItem> &conf)
{
    if (automaConfTable) {
        automaConfTable->close();
        delete automaConfTable;
    }

    automaConfTable = new QTableWidget;

    automaConfTable->setRowCount(conf.size());
    automaConfTable->setColumnCount(5);


    for ( size_t i = 0; i < conf.size(); i++ ) {
        QString alpha = conf[i].alphaState? QString::number(conf[i].alphaState) : "";
        QTableWidgetItem *alphaStateItem = new QTableWidgetItem(alpha);
        automaConfTable->setItem(i, 0, alphaStateItem);

        QString label = (conf[i].label == -1)? "": QString::number(conf[i].label);
        QTableWidgetItem *labelCodeItem = new QTableWidgetItem(label);
        automaConfTable->setItem(i, 1, labelCodeItem);

        QString beta = (conf[i].betaState == -1)? "": QString::number(conf[i].betaState);
        QTableWidgetItem *betaStateItem = new QTableWidgetItem(beta);
        automaConfTable->setItem(i, 2, betaStateItem);

        QString stack = (conf[i].stack == -1)? "": QString::number(conf[i].stack);
        QTableWidgetItem *stackItem = new QTableWidgetItem(stack);
        automaConfTable->setItem(i, 3, stackItem);

        QTableWidgetItem *semanticSubprItem = new QTableWidgetItem(QString::fromStdString(conf[i].semanticSubpr));
        automaConfTable->setItem(i, 4, semanticSubprItem);
    }

    automaConfTable->setWindowTitle("Config");
    automaConfTable->resize(QSize(800, 500));
    automaConfTable->setHorizontalHeaderLabels({"Alpha", "lexem code", "Beta", "Stack", "Semantic Subpr"});
    automaConfTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    automaConfTable->show();
}

void MainWindow::showPrecedenceTable(const PrecedenceTableFormer::PrecedenceTable &table)
{
    if (precedenceTable) {
        precedenceTable->close();
        delete precedenceTable;
    }

    precedenceTable = new QTableWidget;

    precedenceTable->setRowCount(table.size());
    precedenceTable->setColumnCount(table.size());

    size_t i = 0;

    QStringList labels;
    for ( const auto& [keyL, valL]: table ) {

        labels.push_back(QString().fromStdString(keyL));

        size_t j = 0;
        for ( const auto& [keyR, valR]: valL ) {

            QString relation = "";
            bool isConflict = false;

            if (valR & PrecedenceTableFormer::EQUALS) {
                if(valR ^ PrecedenceTableFormer::EQUALS) {
                    isConflict = true;
                }

                relation += " = ";
            }

            if (valR & PrecedenceTableFormer::LOWWER) {
                if(valR ^ PrecedenceTableFormer::LOWWER) {
                    isConflict = true;
                }

                relation += " < ";
            }

            if (valR & PrecedenceTableFormer::GREATER) {
                if(valR ^ PrecedenceTableFormer::GREATER) {
                    isConflict = true;
                }

                relation += " > ";
            }


            QTableWidgetItem *relationItem = new QTableWidgetItem(relation);

            if (isConflict) {
                relationItem->setBackgroundColor(QColor(255, 0, 0, 100));
            }

            precedenceTable->setItem(i, j, relationItem);
            j++;
        }

        i++;
    }

    precedenceTable->setWindowTitle("Precedeence table");
    precedenceTable->resize(QSize(900, 900));
    precedenceTable->setHorizontalHeaderLabels(labels);
    precedenceTable->setVerticalHeaderLabels(labels);
    precedenceTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    precedenceTable->show();
}

void MainWindow::showTracePrecedence(const std::vector<UpStreamAnalyzer::TraceItem> &trace)
{
    if (tracePrecedence) {
        tracePrecedence->close();
        delete tracePrecedence;
    }

    tracePrecedence = new QTableWidget;

    tracePrecedence->setRowCount(trace.size());
    tracePrecedence->setColumnCount(4);

    size_t i = 0;
    for ( const UpStreamAnalyzer::TraceItem& item: trace ) {

        QTableWidgetItem *stackItem = new QTableWidgetItem(QString::fromStdString(item.stack));
        tracePrecedence->setItem(i, 0, stackItem);

        QTableWidgetItem *relationItem = new QTableWidgetItem(QString::fromStdString(item.relation));
        tracePrecedence->setItem(i, 1, relationItem);

        QTableWidgetItem *inputItem = new QTableWidgetItem(QString::fromStdString(item.input));
        tracePrecedence->setItem(i, 2, inputItem);

        QTableWidgetItem *basisItem = new QTableWidgetItem(QString::fromStdString(item.basis));
        tracePrecedence->setItem(i, 3, basisItem);

        i++;
    }

    tracePrecedence->setWindowTitle("Trace UpStream Syntax Analyzer");
    tracePrecedence->resize(QSize(500, 400));
    tracePrecedence->setHorizontalHeaderLabels({"stack", "relation", "input", "basis"});
    tracePrecedence->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tracePrecedence->show();
}

void MainWindow::showRpnExecutionTable(const std::vector<RpnExecuter::LogItem> &rpnExecutionTrace)
{
    if (rpnExecutionTraceTable) {
        rpnExecutionTraceTable->close();
        delete rpnExecutionTraceTable;
    }

    rpnExecutionTraceTable = new QTableWidget;

    rpnExecutionTraceTable->setRowCount(rpnExecutionTrace.size());
    rpnExecutionTraceTable->setColumnCount(3);

    size_t i = 0;
    for ( const auto& item: rpnExecutionTrace ) {

        QTableWidgetItem *commandN = new QTableWidgetItem(QString::number(item.i));
        rpnExecutionTraceTable->setItem(i, 0, commandN);

        QTableWidgetItem *stackItem = new QTableWidgetItem(QString::fromStdString(item.stack));
        rpnExecutionTraceTable->setItem(i, 1, stackItem);

        QTableWidgetItem *inputItem = new QTableWidgetItem(QString::fromStdString(item.input));
        rpnExecutionTraceTable->setItem(i, 2, inputItem);


        i++;
    }

    rpnExecutionTraceTable->setWindowTitle("RPN execution trace table");
    rpnExecutionTraceTable->resize(QSize(500, 400));
    rpnExecutionTraceTable->setHorizontalHeaderLabels({"command", "stack", "input"});
    rpnExecutionTraceTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    rpnExecutionTraceTable->show();
}



void MainWindow::showRpnTrace(const std::vector<rpn::LogItem> &trace)
{
    if (rpnTraceTable) {
        rpnTraceTable->close();
        delete rpnTraceTable;
    }

    rpnTraceTable = new QTableWidget;

    rpnTraceTable->setRowCount(trace.size());
    rpnTraceTable->setColumnCount(3);

    size_t i = 0;
    for ( const rpn::LogItem& item: trace ) {

        QTableWidgetItem *stackItem = new QTableWidgetItem(QString::fromStdString(item.stack));
        rpnTraceTable->setItem(i, 0, stackItem);

        QTableWidgetItem *relationItem = new QTableWidgetItem(QString::fromStdString(item.input));
        rpnTraceTable->setItem(i, 1, relationItem);

        QTableWidgetItem *inputItem = new QTableWidgetItem(QString::fromStdString(item.rpn));
        rpnTraceTable->setItem(i, 2, inputItem);

        i++;
    }

    rpnTraceTable->setWindowTitle("RPN Trace");
    rpnTraceTable->resize(QSize(600, 400));
    rpnTraceTable->setHorizontalHeaderLabels({"stack", "input", "output"});
    rpnTraceTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    rpnTraceTable->show();
}



void MainWindow::on_actionLexems_Table_triggered()
{
    if (lexicalAnalyzerOutput) {
        showLexemsTable(*lexicalAnalyzerOutput);
    } else {
        QMessageBox msgBox;
        msgBox.setText("Cant open");
        msgBox.exec();
    }
}

void MainWindow::on_actionConstants_Table_triggered()
{
    if (lexicalAnalyzerOutput) {
        showConstsTable(*lexicalAnalyzerOutput);
    } else {
        QMessageBox msgBox;
        msgBox.setText("Cant open");
        msgBox.exec();
    }
}

void MainWindow::on_actionId_Table_triggered()
{
    if (lexicalAnalyzerOutput) {
        showIdentsTable(*lexicalAnalyzerOutput);
    } else {
        QMessageBox msgBox;
        msgBox.setText("Cant open");
        msgBox.exec();
    }
}

void MainWindow::on_actionLexical_Analyzer_Trace_triggered()
{
    if (syntaxAnalyzerTrace) {
        showTracePrecedence(*syntaxAnalyzerTrace);
    } else {
        QMessageBox msgBox;
        msgBox.setText("Cant open");
        msgBox.exec();
    }
}

void MainWindow::on_actionPrecedence_Table_triggered()
{
    if (precedeneTableConf) {
        showPrecedenceTable(*precedeneTableConf);
    } else {
        QMessageBox msgBox;
        msgBox.setText("Cant open");
        msgBox.exec();
    }
}



void MainWindow::on_actionPolis_triggered()
{
    if (polis != "") {
        QMessageBox msgBox;
        msgBox.setText(QString().fromStdString(polis));
        msgBox.exec();
    } else {
        QMessageBox msgBox;
        msgBox.setText("Run first");
        msgBox.exec();
    }
}

void MainWindow::on_actionPolis_trace_triggered()
{
    if (rpnTrace) {
        showRpnTrace(*rpnTrace);
    } else {
        QMessageBox msgBox;
        msgBox.setText("Cant open");
        msgBox.exec();
    }
}

void MainWindow::on_actionPolis_execution_triggered()
{
    if (rpnExecutionTrace) {
        showRpnExecutionTable(*rpnExecutionTrace);
    } else {
        QMessageBox msgBox;
        msgBox.setText("Run first");
        msgBox.exec();
    }
}
