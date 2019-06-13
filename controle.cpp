#include "controle.h"

Controle::Controle()
{

}

void Controle::pushBackIncidencia(Incidencia a)
{
    controle.push_back(a);
}

void Controle::odernarBairro()
{
    std::sort(controle.begin(), controle.end(), [](Incidencia a, Incidencia b){return a.getBairro()<b.getBairro();});
}

void Controle::odernarRisco()
{
    std::sort(controle.begin(), controle.end(), [](Incidencia a, Incidencia b){return a.getRisco()<b.getRisco();});
}

int Controle::size()
{
    return controle.size();
}

Incidencia *Controle::retornoIncid(int x)
{
    return &controle[x];
}

void Controle::alterarControle(int row, int column, QString nome)
{
    if(column==0){
        controle[row].setZona(nome);
    }else if(column==1){
        controle[row].setBairro(nome);
    }else if(column==2){
        controle[row].setDengue(nome.toInt());
        controle[row].atualizarIncid();
    }else if(column==3){
        controle[row].setZika(nome.toInt());
        controle[row].atualizarIncid();
    }else if(column==4){
        controle[row].setChik(nome.toInt());
        controle[row].atualizarIncid();
    }else if(column==5){
        controle[row].setIncid(nome.toInt());
    }
}

bool Controle::compararBairro(QString nome)
{
    for(int i=0; i< controle.size(); i++){
        if(controle[i].getBairro() == nome){
            return false;
        }
    }
    return true;
}
