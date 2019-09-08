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
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Ui::MainWindow *ui;
signals:
   void signalMean(int);
   void signalVar(int);
   void signalStatus();
public slots:
    void setText(const QString &string);
private slots:
    void on_meanSlider_sliderMoved(int position);

    void on_varSlider_sliderMoved(int position);

    void on_startButton_clicked();

private:


};

#endif // MAINWINDOW_H
