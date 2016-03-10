#ifndef CLASEMIEMBROPROYECTO_H
#define CLASEMIEMBROPROYECTO_H

#include <QString>
class ClaseMiembroProyecto {
public:
    ClaseMiembroProyecto();
    QString getNombre() {
        return smNombre;
    }
    void setNombre(QString spNombre) {
        smNombre = spNombre;
    }

    QString getNumeroCarnet() {
        return smNumeroCarnet;
    }
    void setNumeroCarnet(QString spNumeroCarnet) {
        smNumeroCarnet = spNumeroCarnet;
    }
private:
    QString smNombre,
    smNumeroCarnet;

};

#endif // CLASEMIEMBROPROYECTO_H
