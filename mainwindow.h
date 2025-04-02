#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QClipboard>
#include <QComboBox>
#include <QVariant>
#include "appcontext.h"
#include "entrypoint.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    AppContext context;
    void onCopyButtonClicked();
    void onTransferButtonClicked();
    void onCurrentSystemComboBoxClicked(int index);
    void onNewSystemComboBoxClicked(int index);
    void updateLabels();
    void warningMessage(Errors status);
    const char* getErrorDescription(Errors status);
    void onCurrentValueLineEditClicked();
    void onReverseButtonClicked();
};

#endif // MAINWINDOW_H
