#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "overview.h"

static constexpr char userdata[] = "userdata.mps";
static constexpr char extension[] = ".mps";
static constexpr char semiclon = ';';

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
    void clear_all_fields();

    void on_pushButton_login_clicked();

    void on_pushButton_signUp_clicked();

private:
    Ui::MainWindow *ui;
    Overview *view;
};
#endif // MAINWINDOW_H
