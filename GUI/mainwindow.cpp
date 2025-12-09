#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{



    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_frame1button_clicked()
{
    // Open file dialog to let user select a file
    QString fileName = QFileDialog::getOpenFileName(
        this,
        tr("Import File"),                     // Dialog title
        QDir::homePath(),                      // Starting directory
        tr("Text Files (*.txt);;"              // File filters
            "C/C++ Files (*.c *.cpp *.h);;"
            "All Files (*.*)")
    );

    // If user canceled or didn't select a file
    if (fileName.isEmpty()) {
        return;
    }

    // Create QFile object
    QFile file(fileName);

    // Try to open the file in read-only mode
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(
            this,
            tr("Error"),
            tr("Cannot open file %1:\n%2")
                .arg(fileName)
                .arg(file.errorString())
        );
        return;
    }

    // Read the file content
    QTextStream in(&file);
    QString fileContent = in.readAll();

    // Close the file
    file.close();

    // Write file content in textEdit
    ui->textEdit->setPlainText(fileContent);

}

void MainWindow::on_frame2button_clicked()
{
    // Get the text from the text edit (source code entered by user)
    QString sourceCode = ui->textEdit->toPlainText();

    // Check if text edit is empty
    if (sourceCode.isEmpty()) {
        QMessageBox::warning(this, "Warning",
            "Please enter code in the text area or import a file first!");
        return;
    }

    // Convert QString to std::string for the scanner
    std::string codeStr = sourceCode.toStdString();

    try {
        // Call the scanner function
        std::vector<Token> tokens = scan(codeStr);

        // Check for scanner errors
        if (tokens.empty() && !scannerErrorMessage.empty()) {
            // Display error in the label
            QString errorMsg = QString::fromStdString("Scanner Error:\n" + scannerErrorMessage);
            ui->textLabel->setText(errorMsg);

            // Optional: Also show in message box
            QMessageBox::critical(this, "Scanner Error",
                QString::fromStdString(scannerErrorMessage));
            return;
        }

        // Convert tokens to QString format for display
        QString outputText;
        outputText += "Tokens produced by the scanner:\n";
        outputText += "-------------------------------\n";

        for (const auto& token : tokens) {
            QString lexeme = QString::fromStdString(token.lexeme);
            QString typeStr = QString::fromStdString(tokenTypeToString(token.type));

            // Format each token
            outputText += QString("Lexeme: \"%1\", Type: %2\n")
                .arg(lexeme)
                .arg(typeStr);
        }

        outputText += "-------------------------------\n";
        outputText += QString("Total tokens: %1\n").arg(tokens.size());

        // Display in the label
        ui->textLabel->setText(outputText);

    }
    catch (const std::exception& e) {
        // Handle any exceptions
        QString errorMsg = QString("Exception occurred: %1")
                .arg(QString::fromStdString(e.what()));
        ui->textLabel->setText(errorMsg);
        QMessageBox::critical(this, "Error", errorMsg);
    }
}


void MainWindow::on_frame3button_clicked()
{
    // for parser
}

