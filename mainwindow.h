#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "incidencia.h"
#include "controle.h"
#include <QVector>
#include <QInputDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
       Controle controle;
       Incidencia *new_incid;
       void limparLabels();
       void atualizarTabela(Incidencia x, int linhas);
       void atualizarEstatiscas();
       bool salvarControle(QString name, Controle controle);
       bool carregarControle(QString name, Controle &controle);
       void setarIncid(QStringList dados, Incidencia *x);

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Inserir_clicked();

    void on_Limpar_clicked();

    void on_orbairro_clicked();

    void on_orrisco_clicked();

    void on_tableWidget_cellDoubleClicked(int row, int column);

    void salvar();

    void carregar();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
