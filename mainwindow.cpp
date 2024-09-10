#include <QPushButton>
#include <QGridLayout>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
     w = new QPushButton(tr("Start"), this);
     auto mainLayout = new QGridLayout;
     mainLayout->addWidget(w, 4, 0, 1, 5);
     setLayout(mainLayout);
}

MainWindow::~MainWindow()
{

}
