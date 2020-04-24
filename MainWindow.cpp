#include "MainWindow.h"
#include <QVBoxLayout>
#include "Q3TTableWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

}

MainWindow::~MainWindow()
{

}

void MainWindow::createWidget()
{
    //QMainWindow不能增加添加布局，所以先定义一个QWidget
    m_pMainWidget = new QWidget(this);
    //把定义的QWidget设置为当前QMainWindow的主窗口
    this->setCentralWidget(m_pMainWidget);

    m_pMainLayout = new QVBoxLayout(m_pMainWidget);
    m_pTableWidget = new Q3TTableWidget(nullptr);
    showMaximized();
}

void MainWindow::createLayout()
{

    m_pMainLayout->addWidget()

    m_pMainWidget->setLayout(m_pMainLayout);
}

void MainWindow::createConnection()
{

}


