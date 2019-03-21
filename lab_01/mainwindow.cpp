#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    Argument empty;
    action(empty, exit_);
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    int canvasWidth = width() - 200;
    int canvasHeight = height();

    p.fillRect(0, 0, canvasWidth, canvasHeight, Qt::white);

    Painter paint = {&p, canvasWidth, canvasHeight};
    Argument arg {{&paint}};

    action(arg, draw);
}

void MainWindow::on_bntFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);

    Argument arg {.file = {&file}};

    if (action(arg, load) != success) {
        QMessageBox::critical(this, "Ошибка", "Файл некорректный");
    }

    file.close();

    repaint();
}

void MainWindow::on_btnSave_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this);
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);

    Argument arg {.file = {&file}};

    if (action(arg, save) != success) {
        QMessageBox::critical(this, "Ошибка", "Файл не удалось сохранить");
    }

    file.close();
}

void MainWindow::on_btnOffset_clicked()
{
    bool key1 = 0, key2 = 0, key3 = 0;
    int x = ui->lineOffsetX->text().toInt(&key1);
    int y = ui->lineOffsetY->text().toInt(&key2);
    int z = ui->lineOffsetZ->text().toInt(&key3);

    if (!(key1 && key2 && key3)) {
        QMessageBox::critical(this, "Ошибка", "Некорректный воод");
        return;
    }

    Argument arg {.change = {x, y, z}};
    action(arg, offset);

    repaint();
}

void MainWindow::on_btnRotate_clicked()
{
    bool key1 = 0, key2 = 0, key3 = 0;
    int ax = ui->lineRotateX->text().toInt(&key1);
    int ay = ui->lineRotateY->text().toInt(&key2);
    int az = ui->lineRotateZ->text().toInt(&key3);

    if (!(key1 && key2 && key3)) {
        QMessageBox::critical(this, "Ошибка", "Некорректный воод");
        return;
    }

    Argument arg {.change = {ax, ay, az}};
    action(arg, rotate);

    repaint();
}

void MainWindow::on_btnScale_clicked()
{
    bool key= 0;
    double k = ui->lineScale->text().toDouble(&key);

    if (!key) {
        QMessageBox::critical(this, "Ошибка", "Некорректный воод");
        return;
    }

    Argument arg {.scale = {k}};
    action(arg, scale);

    repaint();
}
