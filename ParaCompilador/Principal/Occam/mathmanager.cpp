#include "mathmanager.h"

MathManager::MathManager(QObject *parent) : QObject(parent)
{

}


double MathManager::Log(double x) {
    return errcheck(log(x), "log");
}

double MathManager::Log10(double x) {
    return errcheck(log10(x), "log10");
}

double MathManager::Exp(double x) {
    return errcheck(exp(x), "exp");
}

double MathManager::Sqrt(double x) {
    return errcheck(sqrt(x), "sqrt");
}

double MathManager::Pow(double x, double y) {
    return errcheck(pow(x, y), "exponenciation");
}

double MathManager::integer(double x) {
    return (double)(long)x;
}

double MathManager::errcheck(double d, char *s) {
//    if( errno == EDOM ) {
//        execerror(s, "result out of domain");
//    }
//    else if( errno == ERANGE) {
//        execerror(s, "result out of range");
//    }
    return d;
}
