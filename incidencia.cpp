#include "incidencia.h"



float Incidencia::getIncid() const
{
    return incid;
}

int Incidencia::getRisco() const
{
    return risco;
}

void Incidencia::setIncid(float value)
{
    incid = value;
    if(incid < 50){
        risco = 0;
    }else if (incid > 50 and incid < 100 ) {
        risco = 1;
    }else {
        risco = 2;
    }
}

Incidencia::Incidencia()
{
}

Incidencia::Incidencia(QString n, QString zo, int d, int c, int z)
{
    setBairro(n);
    setZona(zo);
    setDengue(d);
    setChik(c);
    setZika(z);
    incid = z+c+d;
    if(incid < 10){
        risco = 0;
    }else if (incid > 10 and incid < 20 ) {
        risco = 1;
    }else {
        risco = 2;
    }
}

int Incidencia::getDengue() const
{
    return dengue;
}

void Incidencia::setDengue(int value)
{
    dengue = value;
}

int Incidencia::getZika() const
{
    return zika;
}

void Incidencia::setZika(int value)
{
    zika = value;
}

int Incidencia::getChik() const
{
    return chik;
}

void Incidencia::setChik(int value)
{
    chik = value;
}

QString Incidencia::getZona() const
{
    return zona;
}

void Incidencia::setZona(const QString &value)
{
    zona = value;
}

QString Incidencia::getBairro() const
{
    return bairro;
}

void Incidencia::setBairro(const QString &value)
{
    bairro = value;
}

void Incidencia::atualizarIncid()
{
    incid = getChik()+getZika()+getDengue();
}


