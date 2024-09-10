#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
public:


    QPushButton *w;
};

class Simple
{
private:
    static Simple *sim;
    Simple(){
    }
public:
    static Simple* getInstance(){
        if(sim == nullptr)
            sim = new Simple();
        return sim;
    }

};
#endif // MAINWINDOW_H
