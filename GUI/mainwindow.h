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

#include "Scanner.h"

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

private slots:
    void on_frame1button_clicked();

    void on_frame2button_clicked();

    void on_frame3button_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
