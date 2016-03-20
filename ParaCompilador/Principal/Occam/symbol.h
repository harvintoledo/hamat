#ifndef SYMBOL_H
#define SYMBOL_H
#include <QObject>

class Symbol : public QObject
{
    Q_OBJECT
public:
    explicit Symbol(QObject *parent = 0);
    Symbol *lookup(char *s);

signals:

public slots:
};
#endif // SYMBOL_H

