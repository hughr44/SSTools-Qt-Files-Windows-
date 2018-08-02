#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void submitMapping(QStringList);
    bool invalidInt(QString);
    bool invalidDec(QString);
    bool invalidDate(QString);
    bool invalidBool(QString);
    bool invalidString(QString, QString);

private:
    Ui::MainWindow *ui;

private slots:
    void weight_selected();
    void length_selected();
    void convertUnit_pressed();
    void dimensionalWeight_pressed();
    void girth_pressed();
    void button_pressed();
    void openFile_pressed();
    void mapping_pressed();
    void display_pressed();
    void newFile_pressed();
    void fileType_pressed();
    void help_pressed();
};

#endif // MAINWINDOW_H
