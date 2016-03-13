#include <math.h>
#include <errno.h>
extern int errno; 
double errcheck();

double Log(double x) {
    return errcheck(log(x), "log");
}

double Log10(double x) {
    return errcheck(log10(x), "log10");
}

double Exp(double x) {
    return errcheck(exp(x), "exp");
}

double Sqrt(double x) {
    return errcheck(sqrt(x), "sqrt");
}

double Pow(double x, double y) {
    return errcheck(pow(x, y), "exponenciation");
}

double integer(double x) {
    return (double)(long)x;
}

double errcheck(double d, char *s) {
    if( errno == EDOM ) {
        execerror(s, "result out of domain");
    }
    else if( errno == ERANGE) {
        execerror(s, "result out of range");
    }
    return d;
}
