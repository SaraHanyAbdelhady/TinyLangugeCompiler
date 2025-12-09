/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QFrame *frame1;
    QVBoxLayout *verticalLayout_3;
    QPushButton *frame1button;
    QFrame *frame11;
    QVBoxLayout *verticalLayout_4;
    QLabel *label;
    QTextEdit *textEdit;
    QFrame *frame2;
    QVBoxLayout *verticalLayout_5;
    QPushButton *frame2button;
    QFrame *frame21;
    QLabel *textLabel;
    QFrame *frame3;
    QVBoxLayout *verticalLayout_6;
    QPushButton *frame3button;
    QFrame *frame31;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(989, 700);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        frame1 = new QFrame(centralwidget);
        frame1->setObjectName("frame1");
        frame1->setMaximumSize(QSize(16777215, 678));
        frame1->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        frame1->setFrameShape(QFrame::Shape::StyledPanel);
        frame1->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_3 = new QVBoxLayout(frame1);
        verticalLayout_3->setObjectName("verticalLayout_3");
        frame1button = new QPushButton(frame1);
        frame1button->setObjectName("frame1button");
        frame1button->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: cyan;\n"
"    color: black;\n"
"    border: 1px solid darkblue\n"
"}\n"
"\n"
"/* For hover effect */\n"
"QPushButton:hover {\n"
"    background-color: lightcyan;\n"
"}\n"
"\n"
"/* For pressed state */\n"
"QPushButton:pressed {\n"
"    background-color: darkcyan;\n"
"}"));

        verticalLayout_3->addWidget(frame1button);

        frame11 = new QFrame(frame1);
        frame11->setObjectName("frame11");
        frame11->setMaximumSize(QSize(16777215, 625));
        frame11->setFrameShape(QFrame::Shape::StyledPanel);
        frame11->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_4 = new QVBoxLayout(frame11);
        verticalLayout_4->setObjectName("verticalLayout_4");
        label = new QLabel(frame11);
        label->setObjectName("label");

        verticalLayout_4->addWidget(label);

        textEdit = new QTextEdit(frame11);
        textEdit->setObjectName("textEdit");
        textEdit->setMaximumSize(QSize(16777215, 574));

        verticalLayout_4->addWidget(textEdit);


        verticalLayout_3->addWidget(frame11);


        horizontalLayout->addWidget(frame1, 0, Qt::AlignmentFlag::AlignLeft);

        frame2 = new QFrame(centralwidget);
        frame2->setObjectName("frame2");
        frame2->setMaximumSize(QSize(16777215, 678));
        frame2->setFrameShape(QFrame::Shape::StyledPanel);
        frame2->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_5 = new QVBoxLayout(frame2);
        verticalLayout_5->setObjectName("verticalLayout_5");
        frame2button = new QPushButton(frame2);
        frame2button->setObjectName("frame2button");
        frame2button->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        frame2button->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: cyan;\n"
"    color: black;\n"
"    border: 1px solid darkblue\n"
"}\n"
"\n"
"/* For hover effect */\n"
"QPushButton:hover {\n"
"    background-color: lightcyan;\n"
"}\n"
"\n"
"/* For pressed state */\n"
"QPushButton:pressed {\n"
"    background-color: darkcyan;\n"
"}"));

        verticalLayout_5->addWidget(frame2button);

        frame21 = new QFrame(frame2);
        frame21->setObjectName("frame21");
        frame21->setMaximumSize(QSize(16777215, 625));
        frame21->setFrameShape(QFrame::Shape::StyledPanel);
        frame21->setFrameShadow(QFrame::Shadow::Raised);
        textLabel = new QLabel(frame21);
        textLabel->setObjectName("textLabel");
        textLabel->setGeometry(QRect(10, 60, 321, 541));
        textLabel->setMaximumSize(QSize(16777215, 541));

        verticalLayout_5->addWidget(frame21);


        horizontalLayout->addWidget(frame2);

        frame3 = new QFrame(centralwidget);
        frame3->setObjectName("frame3");
        frame3->setMaximumSize(QSize(16777215, 678));
        frame3->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        frame3->setFrameShape(QFrame::Shape::StyledPanel);
        frame3->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_6 = new QVBoxLayout(frame3);
        verticalLayout_6->setObjectName("verticalLayout_6");
        frame3button = new QPushButton(frame3);
        frame3button->setObjectName("frame3button");
        frame3button->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: cyan;\n"
"    color: black;\n"
"    border: 1px solid darkblue\n"
"}\n"
"\n"
"/* For hover effect */\n"
"QPushButton:hover {\n"
"    background-color: lightcyan;\n"
"}\n"
"\n"
"/* For pressed state */\n"
"QPushButton:pressed {\n"
"    background-color: darkcyan;\n"
"}"));

        verticalLayout_6->addWidget(frame3button);

        frame31 = new QFrame(frame3);
        frame31->setObjectName("frame31");
        frame31->setMaximumSize(QSize(16777215, 625));
        frame31->setFrameShape(QFrame::Shape::StyledPanel);
        frame31->setFrameShadow(QFrame::Shadow::Raised);

        verticalLayout_6->addWidget(frame31);


        horizontalLayout->addWidget(frame3);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 2);
        horizontalLayout->setStretch(2, 2);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        frame1button->setText(QCoreApplication::translate("MainWindow", "Import File", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Type Your Code ", nullptr));
        frame2button->setText(QCoreApplication::translate("MainWindow", "View Scanner Output", nullptr));
        textLabel->setText(QCoreApplication::translate("MainWindow", "Scanner Output", nullptr));
        frame3button->setText(QCoreApplication::translate("MainWindow", "View Parser Output", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
