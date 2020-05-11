#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "overview.h"

static const QString data_dir = "data/";
static const QString userdata = "userdata.mps";
static const QString extension = ".mps";
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
    bool check_conditions(QString username, QString password, QString repeated_password);

private:
    Ui::MainWindow *ui;
    Overview *view;
};
#endif // MAINWINDOW_H
