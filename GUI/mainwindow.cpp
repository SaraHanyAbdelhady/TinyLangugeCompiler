#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Define the Dark Theme Style
    QString styleSheet = R"(
        /* Main Window & Dialogs */
        QMainWindow, QDialog, QMessageBox {
            background-color: #2E3440;
            color: #D8DEE9;
        }

        /* Text Areas */
        QTextEdit {
            background-color: #3B4252;
            color: #E5E9F0;
            border: 1px solid #4C566A;
            border-radius: 4px;
            font-family: "Consolas", monospace;
        }

        /* Buttons */
        QPushButton {
            background-color: #4C566A;
            color: #ECEFF4;
            border: 1px solid #434C5E;
            border-radius: 6px;
            padding: 8px 16px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #5E81AC;
            border-color: #81A1C1;
        }
        QPushButton:pressed {
            background-color: #3B4252;
        }

        /* Message Boxes */
        QMessageBox QLabel {
            color: #D8DEE9;
        }
        QMessageBox QPushButton {
            min-width: 80px; /* Make buttons standard size */
        }
    )";

    qApp->setStyleSheet(styleSheet);
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
                .arg(fileName, file.errorString())
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
            ui->textEdit->setText(errorMsg);

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
                .arg(lexeme, typeStr);
        }

        outputText += "-------------------------------\n";
        outputText += QString("Total tokens: %1\n").arg(tokens.size());

        // Display in the label
        ui->textEdit_2->setText(outputText);

    }
    catch (const std::exception& e) {
        // Handle any exceptions
        QString errorMsg = QString("Exception occurred: %1")
                .arg(QString::fromStdString(e.what()));
        ui->textEdit_2->setText(errorMsg);
        QMessageBox::critical(this, "Error", errorMsg);
    }
}


void MainWindow::printASTToText(ASTNode* node, QString& output, int indentLevel) {
    if (!node) return;

    // Create indentation
    QString indent;
    for (int i = 0; i < indentLevel; ++i) indent += "  | ";

    // Add current node details
    output += indent + QString::fromStdString(node->type);
    if (!node->value.empty()) {
        output += " (" + QString::fromStdString(node->value) + ")";
    }
    output += "\n";

    // Recurse for children
    for (ASTNode* child : node->children) {
        printASTToText(child, output, indentLevel + 1);
    }
}
void MainWindow::on_frame3button_clicked() // Corresponds to "Parse the Code"
{
    QString sourceCode = ui->textEdit->toPlainText();
    if (sourceCode.isEmpty()) {
        QMessageBox::warning(this, "Warning", "No code to parse!");
        return;
    }

    std::string codeStr = sourceCode.toStdString();

    try {
        std::vector<Token> tokens = scan(codeStr);

        Parser parser(tokens);
        ASTNode* root = parser.parse();

        QString resultText = "Parsing Successful!\n\nTextual Syntax Tree:\n---------------------\n";
        printASTToText(root, resultText, 0);

        ui->textEdit_2->setText(resultText);

    } catch (const std::exception& e) {
        QString errorMsg = QString("Parser Error:\n%1").arg(e.what());
        ui->textEdit_2->setText(errorMsg);
        QMessageBox::critical(this, "Parser Error", errorMsg);
    }
}

bool MainWindow::isStatement(const std::string& type) {
    return (type == "if" || type == "repeat" || type == "assign" ||
            type == "read" || type == "write");
}

// Corrected helper to distinguish "Else" (Vertical) from "Next Statement" (Horizontal)
void MainWindow::categorizeChildren(ASTNode* parent, std::vector<ASTNode*>& vertical, ASTNode*& horizontal) {
    horizontal = nullptr;
    vertical.clear();

    if (!parent) return;

    // 1. IF Statement: [Cond, Then, (Else), (Next)]
    if (parent->type == "if") {
        // Child 0: Condition (Vertical)
        // Child 1: Then-Part (Vertical)
        // Child 2: Else-Part (Vertical) <-- This is the specific fix
        // Child 3: Next Statement (Horizontal)

        for (size_t i = 0; i < parent->children.size(); ++i) {
            ASTNode* child = parent->children[i];

            // Only treat the child as "Horizontal" (Next Stmt) if it is the
            // 4th child (index 3) or later.
            // This ensures the 3rd child (Index 2, the ELSE part) remains Vertical.
            if (i >= 3 &&  isStatement(child->type)) {
                horizontal = child;
            } else {
                vertical.push_back(child);
            }
        }
    }
    // 2. REPEAT Statement: [Body, Cond, (Next)]
    else if (parent->type == "repeat") {
        if (parent->children.size() > 0) vertical.push_back(parent->children[0]); // Body
        if (parent->children.size() > 1) vertical.push_back(parent->children[1]); // Cond (Until)
        if (parent->children.size() > 2) horizontal = parent->children[2];         // Next Stmt
    }
    // 3. Simple Statements (Assign, Read, Write)
    else if (isStatement(parent->type)) {
        for (ASTNode* child : parent->children) {
            if (isStatement(child->type)) {
                horizontal = child; // The chained statement
            } else {
                vertical.push_back(child); // Expressions/IDs
            }
        }
    }
    // 4. Expressions / Ops (Everything vertical)
    else {
        vertical = parent->children;
    }
}
int MainWindow::getSize(ASTNode* node) {
    if (!node) return 0;

    std::vector<ASTNode*> vertical;
    ASTNode* horizontal = nullptr;
    categorizeChildren(node, vertical, horizontal);

    // Calculate width of vertical children (the subtree below)
    int verticalWidth = 0;
    if (vertical.empty()) {
        verticalWidth = 80; // Minimum width for a node
    } else {
        for (ASTNode* child : vertical) {
            verticalWidth += getSize(child);
        }
    }

    int horizontalWidth = 0;
    if (horizontal) {
        horizontalWidth = 50 + getSize(horizontal);
    }

    return verticalWidth + horizontalWidth;
}

void MainWindow::drawTreeRecursive(QGraphicsScene* scene, ASTNode* node, int x, int y){
    if (!node) return;

    std::vector<ASTNode*> verticalChildren;
    ASTNode* horizontalChild = nullptr;
    categorizeChildren(node, verticalChildren, horizontalChild);

    // Draw Current Node
    int nodeW = 60;
    int nodeH = 40;

    int verticalSubtreeWidth = 0;
    if (verticalChildren.empty()) verticalSubtreeWidth = 80;
    else {
        for(auto* v : verticalChildren) verticalSubtreeWidth += getSize(v);
    }

    int currentCenterX = x + (verticalSubtreeWidth / 2) - (nodeW / 2);

    // Draw ShapeQPen
    QPen linePen(Qt::white);
    linePen.setWidth(2);

    QPen shapePen(Qt::black);
    shapePen.setWidth(2);

    QColor stmtColor("#818896");  // Dark Grey (Matches Buttons)
    QColor opColor("#ECEFF4");    // Bright White/Grey

    QBrush brush = isStatement(node->type) ? QBrush(QColor(stmtColor)) : QBrush(opColor);

    if (isStatement(node->type))
        scene->addRect(currentCenterX, y, nodeW, nodeH, shapePen, brush);
    else
        scene->addEllipse(currentCenterX, y, nodeW, nodeH, shapePen, brush);

    // Draw Text
    QString label = QString::fromStdString(node->type);
    if (!node->value.empty()) label += "\n(" + QString::fromStdString(node->value) + ")";
    QGraphicsTextItem* text = scene->addText(label);
    text->setPos(currentCenterX + (nodeW - text->boundingRect().width())/2,
                 y + (nodeH - text->boundingRect().height())/2);


    // Draw Vertical Children
    int startX = x;
    int childY = y + 100;


    for (ASTNode* child : verticalChildren) {
        int childTotalWidth = getSize(child);

        int childVerticalWidth = 0;
        std::vector<ASTNode*> v_dummy; ASTNode* h_dummy;
        categorizeChildren(child, v_dummy, h_dummy);
        if (v_dummy.empty()) childVerticalWidth = 80;
        else for(auto* v : v_dummy) childVerticalWidth += getSize(v);

        int childCenterX = startX + (childVerticalWidth / 2);

        scene->addLine(currentCenterX + nodeW/2, y + nodeH, childCenterX, childY, linePen);

        drawTreeRecursive(scene, child, startX, childY);

        startX += childTotalWidth; // Move past the entire child structure
    }


    // Draw Horizontal Child
    if (horizontalChild) {
        int hGap = 50;

        int nextNodeX = (verticalChildren.empty()) ? (x + nodeW + hGap) : (startX + hGap);

        int nextVerticalWidth = 0;
        std::vector<ASTNode*> v_next; ASTNode* h_next;
        categorizeChildren(horizontalChild, v_next, h_next);
        if (v_next.empty()) nextVerticalWidth = 80;
        else for(auto* v : v_next) nextVerticalWidth += getSize(v);

        int nextNodeCenterX = nextNodeX + (nextVerticalWidth / 2);

        scene->addLine(currentCenterX + nodeW, y + nodeH/2,
                       nextNodeCenterX - 30, y + nodeH/2, linePen);

        drawTreeRecursive(scene, horizontalChild, nextNodeX, y);
    }
}
void MainWindow::on_treebutton_clicked()
{
    QString sourceCode = ui->textEdit->toPlainText();
    if (sourceCode.isEmpty()) {
        QMessageBox::warning(this, "Warning", "No code to parse!");
        return;
    }

    try {
        std::string codeStr = sourceCode.toStdString();
        std::vector<Token> tokens = scan(codeStr);
        Parser parser(tokens);
        ASTNode* root = parser.parse();

        if (!root) return;

        QDialog* graphWindow = new QDialog(this);
        graphWindow->setWindowTitle("Syntax Tree Visualization");
        graphWindow->resize(1200, 600);

        QGraphicsScene* scene = new QGraphicsScene(graphWindow);
        scene->setBackgroundBrush(QColor("#2E3440"));

        QGraphicsView* view = new QGraphicsView(scene);
        view->setRenderHint(QPainter::Antialiasing);
        // Start drawing at (0,0)
        drawTreeRecursive(scene, root, 0, 0);

        QVBoxLayout* layout = new QVBoxLayout(graphWindow);
        layout->addWidget(view);
        graphWindow->setLayout(layout);
        graphWindow->exec();

    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", QString(e.what()));
    }
}
