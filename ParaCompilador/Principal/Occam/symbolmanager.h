#ifndef SYMBOLMANAGER_H
#define SYMBOLMANAGER_H
#include "hoc.h"
#include "ytab.h"
#include "string.h" /* Declaracion para strcpy y strcmp */
#include "stdlib.h" /* Declaracion para malloc */
#include <QObject>

class SymbolManager : public QObject
{
public:
    explicit SymbolManager(QObject *parent = 0);
    Symbol *lookup(char *s); /* find s in symbol table */
    Symbol *install(char *s, int t, double d); /* install s in symbol table */
    char *emalloc(unsigned n);
};

#endif // SYMBOLMANAGER_H
