#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionSalvar,SIGNAL(triggered()), this, SLOT(salvar()));
    connect(ui->actionCarregar,SIGNAL(triggered()), this, SLOT(carregar()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::atualizarTabela(Incidencia x, int linhas)
{
    QTableWidgetItem *rec;
    ui->tableWidget->setItem(linhas, 0, new QTableWidgetItem(x.getZona()));
    ui->tableWidget->setItem(linhas, 1, new QTableWidgetItem(x.getBairro()));
    ui->tableWidget->setItem(linhas, 2, new QTableWidgetItem(QString::number(x.getDengue())));
    ui->tableWidget->setItem(linhas, 3, new QTableWidgetItem(QString::number(x.getZika())));
    ui->tableWidget->setItem(linhas, 4, new QTableWidgetItem(QString::number(x.getChik())));

    ui->tableWidget->setItem(linhas, 5, new QTableWidgetItem(QString :: number(x.getIncid())));
    if(x.getRisco() == 0){
        rec = new QTableWidgetItem("Baixo");
        rec->setTextColor("green");
        ui->tableWidget->setItem(linhas,6, rec);
    }else if(x.getRisco() == 1){
        rec = new QTableWidgetItem("Médio");
        rec->setTextColor("yellow");
        ui->tableWidget->setItem(linhas,6, rec);
    }else if (x.getRisco() == 2) {
        rec = new QTableWidgetItem("Alto");
        rec->setTextColor("red");
        ui->tableWidget->setItem(linhas,6, rec);
    }

}

void MainWindow::salvar()
{

    QString nome = QFileDialog::getSaveFileName(this,"Controle de Epidemie","","Texto Puro(*.txt);;Arquivos Separado por Vírgulas(*.csv)");
    if( salvarControle(nome, controle) ){
        QMessageBox::information(this, "Salvar Controle","Salvo com sucesso!");
    }else{
        QMessageBox::information(this, "Salvar Controle","Infelizmente, não foi possível salvar os dados!");
    }

}

bool MainWindow::salvarControle(QString name, Controle controle)
{
    QFile file(name);
    new_incid = new Incidencia;
    if(!file.open(QIODevice::WriteOnly)){
        return false;
    }

    QTextStream out (&file);

    for(int i=0;i<controle.size()-1;i++){
        new_incid = controle.retornoIncid(i);
        out << new_incid->getZona()<<","<<new_incid->getBairro()<<",";
        out << new_incid->getZika()<<","<<new_incid->getChik()<<",";
        out << new_incid->getDengue()<<","<< new_incid->getIncid()<<"\n";
    }

    file.close();
    delete new_incid;
    return true;

}

bool MainWindow::carregarControle(QString name, Controle &controle)
{
    QFile file(name);
    if(!file.open(QIODevice::ReadOnly)){
        return false;
    }else{
        QTextStream in(&file);
        QString linha;
        new_incid = new Incidencia;
        while(!in.atEnd()){
            linha = in.readLine();
            QStringList dados = linha.split(",");
            setarIncid(dados, new_incid);
            controle.pushBackIncidencia(*new_incid);
        }
    }
    file.close();
    delete new_incid;
    return true;
}

void MainWindow::carregar(){
    new_incid = new Incidencia;
    QString nome = QFileDialog::getOpenFileName(this,"Controle de Epidemia", "","Arquivos Separados por Vírgulas(*.csv)");
    if(carregarControle(nome, controle)){
        ui->tableWidget->clearContents();
        for(int i=0; i<controle.size(); i++ ){
            if(i>=ui->tableWidget->rowCount()){
                ui->tableWidget->insertRow(i);
            }
            new_incid = controle.retornoIncid(i);
            atualizarTabela(*new_incid, i);
        }
    }else{
        QMessageBox::information(this, "Controle de Epidemia","Infelizmente, não foi possível carregar os dados!");
    }
    atualizarEstatiscas();
}

void MainWindow::setarIncid(QStringList dados, Incidencia *x)
{
    x->setZona(dados[0]);
    x->setBairro(dados[1]);
    x->setZika(dados[2].toInt());
    x->setChik(dados[3].toInt());
    x->setDengue(dados[4].toInt());
    x->setIncid(dados[5].toInt());
}

void MainWindow::atualizarEstatiscas()
{
    int nzica = 0;
    int nchick = 0;
    int ndengue = 0;
    int incidzo = 0;
    int zn = 0;
    int zs = 0;
    int zo = 0;
    int zl = 0;
    for(int i = 0; i<controle.size(); i++){
        new_incid = controle.retornoIncid(i);
        nzica += new_incid->getZika();
        nchick += new_incid->getChik();
        ndengue += new_incid->getDengue();
        if(new_incid->getZona() == "Norte"){
           zn =+ new_incid->getIncid();
        }else if (new_incid->getZona() == "Sul"){
            zs =+ new_incid->getIncid();
        }else if (new_incid->getZona() == "Leste"){
            zl =+ new_incid->getIncid();
        }else if (new_incid->getZona() == "Oeste"){
            zo =+ new_incid->getIncid();
        }
    }

    if(zn>=zs and zn>=zo and zn>=zl){
        ui->zmr->setText( "Norte");
    }else if (zs>=zn and zs>=zo and zs>=zl) {
        ui->zmr->setText( "Sul");
    }else if (zl>=zn and zl>=zo and zl>=zs) {
        ui->zmr->setText( "Leste");
    }else{
        ui->zmr->setText( "Oeste");
    }

    if(nzica >= nchick and nzica >= ndengue){
        ui->dmi->setText("Zika");
    }else if(nchick >= nzica and nchick >= ndengue){
        ui->dmi->setText("Chikungunya");
    }else if (ndengue >= nchick and ndengue >= nzica) {
        ui->dmi->setText("Dengue");
    }

    if(nzica <= nchick and nzica <= ndengue){
        ui->dmie->setText("Zika");
    }else if(nchick <= nzica and nchick <= ndengue){
        ui->dmie->setText("Chikungunya");
    }else if (ndengue <= nchick and ndengue <= nzica) {
        ui->dmie->setText("Dengue");
    }


}

void MainWindow::on_Inserir_clicked()
{
    if(ui->nzika->text() !=0 and ui->cb_zona->currentText() != 0 and ui->nchick->text()!=0
            and ui->bairro_2->text()!=0 and ui->ndengue->text()!=0){
        if(controle.compararBairro(ui->bairro_2->text())){
            QString zonaTemp = ui->cb_zona->currentText();
            QString bairroTemp = ui->bairro_2->text();
            int zikaTemp = ui->nzika->text().toInt();
            int dengueTemp = ui->ndengue->text().toInt();
            int chikTemp = ui->nchick->text().toInt();


            Incidencia temp(bairroTemp, zonaTemp, dengueTemp, chikTemp, zikaTemp);
            controle.pushBackIncidencia(temp);

            int linhas = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(linhas);
            atualizarTabela(temp, linhas);
            atualizarEstatiscas();
            limparLabels();
        }else{
            QMessageBox::information(this, "Comando Inválido", "Esse bairro já foi informado!");
        }
    }
}

void MainWindow::limparLabels()
{
    ui->cb_zona->setCurrentIndex(0);
    ui->nzika->clear();
    ui->bairro_2->clear();
    ui->ndengue->clear();
    ui->nchick->clear();
}

void MainWindow::on_Limpar_clicked()
{
    for(int i = ui->tableWidget->rowCount(); i>=0; i--){
        ui->tableWidget->removeRow(i);
    }
}

void MainWindow::on_orbairro_clicked()
{
    controle.odernarBairro();
    ui->tableWidget->clearContents();
    for(int i = 0; i<controle.size(); i++){
        new_incid = controle.retornoIncid(i);
        atualizarTabela(*new_incid, i);
    }
}


void MainWindow::on_orrisco_clicked()
{
    controle.odernarRisco();
    ui->tableWidget->clearContents();
    for(int i = 0; i<controle.size(); i++){
        new_incid = controle.retornoIncid(i);
        atualizarTabela(*new_incid, i);
    }
}




void MainWindow::on_tableWidget_cellDoubleClicked(int row, int column)
{
    QString nome;
    if(column == 0){
        nome = QInputDialog::getText(this, "Editar", "Qual é o nome da zona?", QLineEdit::Normal);
    }else if(column == 1){
        nome = QInputDialog::getText(this, "Editar", "Qual é o nome do bairro?", QLineEdit::Normal);
    }else if(column == 2){
        nome = QInputDialog::getText(this, "Editar", "Qual é o número de casos de dengue?", QLineEdit::Normal);
    }else if(column == 3){
        nome = QInputDialog::getText(this, "Editar", "Qual é o número de casos de zika?", QLineEdit::Normal);
    }else if(column == 4){
        nome = QInputDialog::getText(this, "Editar", "Qual é o número de casos de chikungunya?", QLineEdit::Normal);
    }else if(column == 5){
        QMessageBox::information(this, "Editar", "Você não tem permissão para alterar o número de incidências!");
    }else{
        QMessageBox::information(this, "Editar", "Você não tem permissão para alterar o risco!");
    }
    controle.alterarControle(row, column, nome);
    for(int i=0; i<controle.size(); i++){
        atualizarTabela(*controle.retornoIncid(i), i);
    }
}


