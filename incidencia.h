#ifndef INCIDENCIA_H
#define INCIDENCIA_H

#include <QMainWindow>


class Incidencia{

private:

    QString zona;
    QString bairro;
    int dengue;
    int zika;
    int chik;
    float incid;
    int risco;

public:


   Incidencia();
   Incidencia(QString n, QString zo, int d,int c, int z);


   int getDengue() const;
   void setDengue(int value);
   int getZika() const;
   void setZika(int value);
   int getChik() const;
   void setChik(int value);
   QString getZona() const;
   void setZona(const QString &value);
   QString getBairro() const;
   void setBairro(const QString &value);
   void atualizarIncid();
   float getIncid() const;
   int getRisco() const;
   void setIncid(float value);
};


#endif
