#ifndef CLASEPROYECTO_H
#define CLASEPROYECTO_H
#include <QString>
#include <QByteArray>
#include <QDateTime>
#include "clasemiembroproyecto.h"
#define NUMERO_MAXIMO_ESTUDIANTES 6
class ClaseProyecto {
public:
    enum eTipoArquitectura {
        TA_TRES_DIRECCIONES,
        TA_DOS_DIRECCIONES,
        TA_PILA,
        TA_NINGUNA_ARQUITECTURA
    };
    enum ePlataforma {
        TP_JAVA_NETBEANS_O_ECLIPSE,
        TP_CSHARP_VISUAL_STUDIO,
        TP_NINGUNA_PLATAFORMA
    };
    ClaseProyecto();
    void setNombreProyecto(QString spNombreProyecto) {
        smNombreProyecto = spNombreProyecto;
    }
    QString getNombreProyecto() {
        return smNombreProyecto;
    }
    void setUbicacionDirectorio(QString spUbicacionDirectorio) {
        smUbicacionDirectorio = spUbicacionDirectorio;
    }
    QString getUbicacionDirectorio() {
        return smUbicacionDirectorio;
    }
    void setTipoArquitectura(eTipoArquitectura epTipoArquitectura) {
        emTipoArquitectura = epTipoArquitectura;
    }
    eTipoArquitectura getTipoArquitectura() {
        return emTipoArquitectura;
    }
    void setPlataforma(ePlataforma epPlataforma) {
        emPlataforma = epPlataforma;
    }
    ePlataforma getPlataforma() {
        return emPlataforma;
    }
    void setFechaDeGeneradoProyecto(QString spFechaDeGeneradoProyecto) {
        smFechaDeGeneradoProyecto = spFechaDeGeneradoProyecto;
    }
    QString getFechaDeGeneradoProyecto() {
        return smFechaDeGeneradoProyecto;
    }
    void setMiembroProyecto(ClaseMiembroProyecto spMiembroProyecto) {
        omDocenteMiembroProyecto = spMiembroProyecto;
    }
    ClaseMiembroProyecto getMiembroProyecto() {
        return omDocenteMiembroProyecto;
    }
    void setIntegrante1(ClaseMiembroProyecto spIntegrante1) {
        omIntegrante1 = spIntegrante1;
    }
    ClaseMiembroProyecto getIntegrante1() {
        return omIntegrante1;
    }
protected:
    QString smNombreProyecto,
    smFechaDeGeneradoProyecto,
    smUbicacionDirectorio;
    eTipoArquitectura emTipoArquitectura;
    ePlataforma emPlataforma;
    ClaseMiembroProyecto omDocenteMiembroProyecto;
    ClaseMiembroProyecto omIntegrante1;
};
#endif // CLASEPROYECTO_H
