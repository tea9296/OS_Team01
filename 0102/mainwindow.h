#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString app="why?";

    int Tk();
    void LIGHTM();
    void LIGHTT();
    void LIGHTP();
    void OFF_LIGHTM();
    void OFF_LIGHTT();
    void OFF_LIGHTP();
    void setMmonoOFF();
    void setBmonoOFF();
    void setPmonoOFF();
    void setAnn(QString t);
    void setMmonoON();
    void setBmonoON();
    void setPmonoON();
    void setMonoOFF();

    void setMatchOFF();
    void setTabaccoOFF();
    void setPaperOFF();
    void setMatchON();
    void setTabaccoON();
    void setPaperON();

    Ui::MainWindow *ui;

private slots:
   void stop();
   void restart();
};

#endif // MAINWINDOW_H
