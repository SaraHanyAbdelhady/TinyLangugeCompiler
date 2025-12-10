#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStatusBar>
#include <QTextEdit>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDir>
#include <QTextEdit>
#include <QLabel>
#include <QMessageBox>
#include <QString>
#include <vector>
#include <string>
#include <QDialog>
#include <QVBoxLayout>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>

#include "Scanner.h"
#include "ASTNode.h"
#include "parser.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void printASTToText(ASTNode*, QString&, int);
    bool isStatement(const std::string&);
    void categorizeChildren(ASTNode*, std::vector<ASTNode*>&, ASTNode*&);
    int getSize(ASTNode* node);
    void drawTreeRecursive(QGraphicsScene*, ASTNode*, int, int);

private slots:
    void on_frame1button_clicked();

    void on_frame2button_clicked();

    void on_frame3button_clicked();

    void on_treebutton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
