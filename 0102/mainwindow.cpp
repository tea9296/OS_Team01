#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QMainWindow>
#include <QString>

int k=0;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_4->setText("Match");
    ui->label->setText("I'm Smoker1,I can't smoke");
    ui->label_2->setText("I'm Smoker2,I can't smoke");
    ui->label_3->setText("I'm Smoker3,I can't smoke");
    ui->label_5->setText("Tobacco");
    ui->label_6->setText("Paper");
    ui->label->setStyleSheet("background-color: rgba(0,0,0,0.6)");
    ui->label_2->setStyleSheet("background-color: rgba(0,0,0,0.6)");
    ui->label_3->setStyleSheet("background-color: rgba(0,0,0,0.6)");
    ui->label_4->setStyleSheet("background-color: rgba(0,0,0,0.6)");
    ui->label_5->setStyleSheet("background-color: rgba(0,0,0,0.6)");
    ui->label_6->setStyleSheet("background-color: rgba(0,0,0,0.6)");
    ui->textBrowser->setText("Ready to start!!");


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setAnn(QString t)
{
    ui->textBrowser->setText(t);
}

void MainWindow::setMmonoON()
{
ui->label_4->setStyleSheet("background-color: rgba(255,0,0,0.6)");
}


void MainWindow::setBmonoON()
{
ui->label_5->setStyleSheet("background-color: rgba(255,0,0,0.6)");
}

void MainWindow::setPmonoON()
{
ui->label_6->setStyleSheet("background-color: rgba(255,0,0,0.6)");
}

void MainWindow::setMonoOFF()
{
  ui->label_4->setStyleSheet("background-color: rgba(0,0,0,0.6)");
  ui->label_5->setStyleSheet("background-color: rgba(0,0,0,0.6)");
  ui->label_6->setStyleSheet("background-color: rgba(0,0,0,0.6)");
}

void MainWindow::setMmonoOFF()
{
    ui->label_4->setStyleSheet("background-color: rgba(0,0,0,0.6)");
}


void MainWindow::setBmonoOFF()
{
    ui->label_5->setStyleSheet("background-color: rgba(0,0,0,0.6)");
}

void MainWindow::setPmonoOFF()
{
    ui->label_6->setStyleSheet("background-color: rgba(0,0,0,0.6)");
}
void MainWindow::setMatchOFF()
{

    ui->label->setText("I'm Smoker1,I can't smoke");
    ui->label->setStyleSheet("background-color: rgba(0,0,0,0.6)");
}
void MainWindow::setTabaccoOFF()
{
    ui->label_2->setText("I'm Smoker2,I can't smoke");
    ui->label_2->setStyleSheet("background-color: rgba(0,0,0,0.6)");
}
void MainWindow::setPaperOFF()
{
    ui->label_3->setText("I'm Smoker3,I can't smoke");
    ui->label_3->setStyleSheet("background-color: rgba(0,0,0,0.6)");
}
void MainWindow::setMatchON()
{
    ui->label->setText("I got Tobacco and Paper and I can smoke!!");
    ui->label->setStyleSheet("background-color: rgba(255,0,0,0.6)");

}
void MainWindow::setTabaccoON()
{
    ui->label_2->setText("I got Match and Paper and I can smoke!!");
    ui->label_2->setStyleSheet("background-color: rgba(255,0,0,0.6)");

}
void MainWindow::setPaperON()
{
    ui->label_3->setText("I got Tobacco and Match and I can smoke");
    ui->label_3->setStyleSheet("background-color: rgba(255,0,0,0.6)");
}




void MainWindow::stop()
{
    k=1;

}
void MainWindow::restart()
{
    k=0;

}

int MainWindow::Tk()
{
    return k;
}
