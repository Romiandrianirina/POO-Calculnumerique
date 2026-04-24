#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    // Parseur
    double parseExpression(const QString& expr, double x, int& pos);
    double parseTerm(const QString& expr, double x, int& pos);
    double parseFactor(const QString& expr, double x, int& pos);
    double parsePrimary(const QString& expr, double x, int& pos);

    // Evaluation
    double result_Function(const QString& expr, double x);

    // Newton
    double newton(const QString& expr, double x0);

public slots:
    void on_send_clicked();

private:
    Ui::MainWindow *ui;
    double m_epsilon = 0.00001;
};
#endif // MAINWINDOW_H
