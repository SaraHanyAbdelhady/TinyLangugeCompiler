/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *frame1button;
    QPushButton *frame2button;
    QPushButton *frame3button;
    QPushButton *treebutton;
    QTextEdit *textEdit;
    QTextEdit *textEdit_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(736, 437);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        frame1button = new QPushButton(centralwidget);
        frame1button->setObjectName("frame1button");

        horizontalLayout_2->addWidget(frame1button);

        frame2button = new QPushButton(centralwidget);
        frame2button->setObjectName("frame2button");

        horizontalLayout_2->addWidget(frame2button);

        frame3button = new QPushButton(centralwidget);
        frame3button->setObjectName("frame3button");

        horizontalLayout_2->addWidget(frame3button);

        treebutton = new QPushButton(centralwidget);
        treebutton->setObjectName("treebutton");

        horizontalLayout_2->addWidget(treebutton);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName("textEdit");

        gridLayout->addWidget(textEdit, 0, 0, 1, 1);

        textEdit_2 = new QTextEdit(centralwidget);
        textEdit_2->setObjectName("textEdit_2");

        gridLayout->addWidget(textEdit_2, 2, 0, 1, 1);


        horizontalLayout->addLayout(gridLayout);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Tiny Language Compiler", nullptr));
        frame1button->setText(QCoreApplication::translate("MainWindow", "Import File", nullptr));
        frame2button->setText(QCoreApplication::translate("MainWindow", "Scan the Code", nullptr));
        frame3button->setText(QCoreApplication::translate("MainWindow", "Parse the Code", nullptr));
        treebutton->setText(QCoreApplication::translate("MainWindow", "Show Syntax Tree", nullptr));
        textEdit->setDocumentTitle(QCoreApplication::translate("MainWindow", "Enter your Code here", nullptr));
        textEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Enter your Code here", nullptr));
        textEdit_2->setPlaceholderText(QCoreApplication::translate("MainWindow", "Output will appear here", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
