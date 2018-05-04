#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//#include "convex_hull_funtion.h"
#include <QMainWindow>
#include <QPainter>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_draw_clicked();

private:
    Ui::MainWindow *ui;
    QPainter *q;
    QPixmap *pixmap;
};

#endif // MAINWINDOW_H
