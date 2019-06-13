#ifndef CONTROLE_H
#define CONTROLE_H

#include <QMainWindow>
#include "incidencia.h"
#include <QVector>
#include <algorithm>

class Controle
{
public:
    Controle();
    QVector <Incidencia> controle;

    void pushBackIncidencia(Incidencia a);
    void odernarBairro();
    void odernarRisco();
    int size();
    Incidencia* retornoIncid(int x);
    void alterarControle(int row, int column, QString nome);
    bool compararBairro(QString nome);
};

#endif // CONTROLE_H
