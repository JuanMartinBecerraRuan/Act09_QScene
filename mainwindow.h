#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include <list>
#include <admin_neuronas.h>
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT
    public:
        QGraphicsScene grafica;
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();
        bool id_repetido(int id);
    private slots:
        void on_pushButton_clicked();
        void on_pushButton_2_clicked();
        void on_pushButton_3_clicked();
        void on_pushButton_4_clicked();
        void on_pushButton_5_clicked();
        void on_tabWidget_tabBarClicked(int index);
        void on_pushButton_6_clicked();
        void on_pushButton_7_clicked();
        void on_pushButton_8_clicked();
        void on_pushButton_9_clicked();

private:
        Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
