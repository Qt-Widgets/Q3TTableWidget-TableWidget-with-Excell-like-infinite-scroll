#include "MainWindow.h"
#include <QVBoxLayout>
#include "Q3TTableWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createWidget();
    createLayout();
    createConnection();
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

    m_pTableWidget = new Q3TTableWidget();
    m_pTableDescLabel = new QLabel("Table description");

    showMaximized();
}

void MainWindow::createLayout()
{
    m_pMainLayout = new QVBoxLayout(m_pMainWidget);
    m_pMainLayout->addWidget(m_pTableDescLabel);
    m_pMainLayout->addWidget(m_pTableWidget);
    m_pMainWidget->setLayout(m_pMainLayout);
}

void MainWindow::createConnection()
{
    connect(m_pTableWidget, SIGNAL(rowColumnCountChange(int, int, int, int)), this, SLOT(setRowColumnDescription(int, int, int, int)));
}

void MainWindow::setRowColumnDescription(int actualRowCount, int actualColumnCount, int rowCount, int columnCount)
{
    QString str = QString("actural row: %1, actual column: %2\nrow: %3, col: %4")
                      .arg(actualRowCount).arg(actualColumnCount).arg(rowCount).arg(columnCount);
    m_pTableDescLabel->setText(str);
}


