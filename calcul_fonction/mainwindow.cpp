#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
#include <cmath>
#include <functional>
#include <QList>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_send_clicked()
{
    QString expr = ui->func->text();
    double x0 = ui->x0->text().toDouble();
    double racine = newton(expr, x0);
    ui->answer->setText("Racine : " + QString::number(racine));
}

double MainWindow::newton(const QString& expr, double x0)
{
    double h = 0.0001;
    double x = x0;

    for(int i = 0; i < 1000; i++)
    {
        double fx  = result_Function(expr, x);
        double dfx = (result_Function(expr, x + h) - result_Function(expr, x)) / h;

        if(fabs(dfx) < m_epsilon) break;

        double x_new = x - fx / dfx;

        if(fabs(x_new - x) < m_epsilon)
        {
            x = x_new;
            break;
        }
        x = x_new;
    }
    return x;
}

double MainWindow::result_Function(const QString& expr, double x)
{
    int pos = 0;
    QString expr_without_space = expr.simplified().remove(' ');
    return parseExpression(expr_without_space, x, pos);
}

//Caster les nombres et retourner leur valeur ou celle de x
double MainWindow::parsePrimary(const QString& expr, double x, int& pos)
{
    QString retour_string;

    if(pos < expr.size() && expr[pos] == '(')
    {
        pos++;
        double resultat = parseExpression(expr, x, pos);
        if(expr[pos] == ')')
            pos++;
        return resultat;
    }
    if(expr[pos] == 'x')
    {
        pos++;
        return x;
    }
    if(expr[pos].isLetter())
    {
        QString my_function;
        double valeur = 0;
        while(pos < expr.size() && expr[pos].isLetter())
        {
            my_function.append(expr[pos]);
            pos++;
        }

        if(pos < expr.size() && expr[pos] == '(')
            pos++;

        valeur = parseExpression(expr, x, pos);

        if(pos < expr.size() && expr[pos] == ')')
            pos++;

        if(my_function == "sin")
            return sin(valeur);
        if(my_function == "cos")
            return cos(valeur);
        if(my_function == "tan")
            return tan(valeur);
        if(my_function == "log")
            return log10(valeur);
        if(my_function == "ln")
            return log(valeur);

    }

    while(pos < expr.size() && (expr[pos].isDigit() || expr[pos] == '.'))
    {
        retour_string.append(expr[pos]);
        pos++;
    }
    return retour_string.toDouble();
}

//Gerer "^"
double MainWindow::parseFactor(const QString& expr, double x, int& pos)
{
    double gauche = parsePrimary(expr, x, pos);
    if(pos != expr.size() && expr[pos] == '^')
    {
        pos++;
        double droite = parsePrimary(expr, x, pos);
        return pow(gauche, droite);
    }
    return gauche;
}

//Gerer "*" et "/"
double MainWindow::parseTerm(const QString& expr, double x, int& pos)
{
    double resultat = parseFactor(expr, x, pos);
    while(pos < expr.size() && (expr[pos] == '*' || expr[pos] == '/'))
    {
        if(expr[pos] == '*')
        {
            pos++;
            resultat *= parseFactor(expr, x, pos);
        }
        else if(expr[pos] == '/')
        {
            pos++;
            double droite = parseFactor(expr, x, pos);
            if(droite == 0)
                return qQNaN(); // division par zéro !
            resultat /= droite;
        }
    }
    return resultat;
}

//Gerer "+" et "-"
double MainWindow::parseExpression(const QString& expr, double x, int& pos)
{
    double resultat = parseTerm(expr, x, pos);
    while(pos < expr.size() && (expr[pos] == '+' || expr[pos] == '-'))
    {
        if(expr[pos] == '+')
        {
            pos++;
            resultat += parseTerm(expr, x, pos);
        }
        else if(expr[pos] == '-')
        {
            pos++;
            double droite = parseTerm(expr, x, pos);
            resultat -= droite;
        }
    }
    return resultat;
}
