#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include <QtMath>
//#include <QtGui/QOffscreenSurface>
//#include <QtGui/QOpenGLContext>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::on_addFile_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::makePlot(QString fileName)
{
//    QString fileName = on_addFile_clicked();
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
       qDebug() << file.errorString();
    }
    QVector<double> col1;
    QVector<double> col2;
    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        col1.append(line.split(',').first().toDouble());
        col2.append(line.split(',').last().toDouble());
    }
    // create graph and assign data to it:
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(col1, col2);
    // give the axes some labels:
    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->customPlot->xAxis->setRange(*std::min_element(col1.begin(), col1.end()), *std::max_element(col1.begin(), col1.end()));
    ui->customPlot->yAxis->setRange(*std::min_element(col2.begin(), col2.end()), *std::max_element(col2.begin(), col2.end()));
    ui->customPlot->replot();
}


void MainWindow::on_addFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open CSV file"), "", tr("CSV files (*.csv)"));
    makePlot(fileName);
}

//void wheelEvent(QWheelEvent *event)
//{
//    float delta = event->angleDelta().y() / 100.f;
//    float distance = m_viewMatrix.column(3).z();
//    distance += delta;
//    m_viewMatrix.setColumn(3, QVector4D(m_panX, -m_panY, distance, 1.f));
//    update();
//}

