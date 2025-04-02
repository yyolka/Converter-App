#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(ui->copyButton, &QPushButton::clicked, this, &MainWindow::onCopyButtonClicked);
    connect(ui->reverseButton, &QPushButton::clicked, this, &MainWindow::onReverseButtonClicked);
    connect(ui->transferButton, &QPushButton::clicked, this, &MainWindow::onTransferButtonClicked);
    connect(ui->currentSystemComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onCurrentSystemComboBoxClicked);
    connect(ui->newSystemComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onNewSystemComboBoxClicked);
    connect(ui->currentNumberLineEdit, &QLineEdit::textChanged, this, &MainWindow::onCurrentValueLineEditClicked);
    doOperation(Initialization, &context, NULL);
    updateLabels();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onCopyButtonClicked() {
    QGuiApplication::clipboard()->setText(QString::fromStdString(context.newValue));
}

void MainWindow::onReverseButtonClicked() {
    doOperation(ReverseSystems, &context, NULL);
    updateLabels();
}

void MainWindow::warningMessage(Errors status) {
    QMessageBox::information(this, "Уведомление", getErrorDescription(status));
}

void MainWindow::onCurrentSystemComboBoxClicked(int index) {
    AppParams* param = (AppParams*) malloc(sizeof(AppParams));
    param->newSystem = ui->currentSystemComboBox->itemText(index).toInt();
    doOperation(UpdateCurrentNumberSystem, &context, param);
    free(param);
}

void MainWindow::onNewSystemComboBoxClicked(int index) {
    AppParams* param = (AppParams*) malloc(sizeof(AppParams));
    param->newSystem = ui->newSystemComboBox->itemText(index).toInt();
    doOperation(UpdateNewNumberSystem, &context, param);
    free(param);
}

void MainWindow::updateLabels() {
    ui->currentNumberLineEdit->setText(QString::fromStdString(context.currentValue));
    ui->finalNumberLineEdit->setText(QString::fromStdString(context.newValue));
    int indexC = ui->currentSystemComboBox->findText(QString::number(context.currentNumberSystem));
    ui->currentSystemComboBox->setCurrentIndex(indexC);
    int indexN = ui->newSystemComboBox->findText(QString::number(context.newNumberSystem));
    ui->newSystemComboBox->setCurrentIndex(indexN);
}

void MainWindow::onTransferButtonClicked() {
    Errors error = doOperation(Transfer, &context, NULL);
    if (error != Ok) {
        warningMessage(error);
    }
    updateLabels();
}

const char* MainWindow::getErrorDescription(Errors status) {
    const char* description;
    switch (status) {
    case NotBin:
        description = "Неправильный ввод: введите число двоичной системы счисления :(";
        break;
    case NotHex:
        description = "Неправильный ввод: введите число шестнадцатеричной системы счисления :(";
        break;
    case NotDec:
        description = "Неправильный ввод: введите число десятичной системы счисления :(";
        break;
    case TooLong:
        description = "Неправильный ввод: число слишком большое :((";
        break;
    case Ok:
        description = "\0";
        break;
    }
    return description;
}

void MainWindow::onCurrentValueLineEditClicked() {
    if (strlen(ui->currentNumberLineEdit->text().toStdString().c_str()) < MAX_LENGTH) {
        AppParams* param = (AppParams*) malloc(sizeof(AppParams));
        strcpy(param->newValue, ui->currentNumberLineEdit->text().toStdString().c_str());
        doOperation(UpdateCurrentNumber, &context, param);
        free(param);
    }
    else
        warningMessage(TooLong);
}


