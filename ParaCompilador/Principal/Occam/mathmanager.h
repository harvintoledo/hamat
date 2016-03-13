#ifndef MATHMANAGER_H
#define MATHMANAGER_H
#include <math.h>
#include <errno.h>
extern int errno;
double errcheck();
#include <QObject>

class MathManager : public QObject
{
    Q_OBJECT
public:
    explicit MathManager(QObject *parent = 0);

private:
    double Log(double x);
    double Log10(double x);
    double Exp(double x);
    double Sqrt(double x);
    double Pow(double x, double y);
    double integer(double x);
    double errcheck(double d, char *s);
signals:
public slots:
};

#endif // MATHMANAGER_H
