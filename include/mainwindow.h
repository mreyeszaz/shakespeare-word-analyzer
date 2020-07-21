#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_btn_find_clicked();

    void onSpinBoxValueChanged();

    void on_btn_search_bar_clicked();

    void on_btn_return_p2_clicked();

    void on_btn_find_p2_clicked();

private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
