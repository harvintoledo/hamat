#include "hoc.h"
#include "y.tab.h"
#include <math.h>

extern double Log(), Log10(), Exp(), Sqrt(), integer();

static struct {
	char *name;
	double cval;
} consts [] = {
	"PI", 3.14159265358979323846
	"E", 2.71828182845904523536,
}