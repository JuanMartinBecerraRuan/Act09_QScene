#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qfiledialog.h>
#include <fstream>

list<Neurona> lista;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow(){
    delete ui;
}

bool MainWindow::id_repetido(int id){
    bool bandera = true;
    list<Neurona>::iterator aux = lista.begin();
    while(aux!=lista.end()){
        if(id==aux->getId()){
            bandera=false;
        }
        aux++;
    }
    return bandera;
}

void MainWindow::on_pushButton_clicked(){
    //INSERTAR AL INICIO
    int id, posicion_x,posicion_y,red,green,blue;
    double voltaje;
    id=ui->id_spinBox->value();
    bool bandera;
    bandera=id_repetido(id);
    voltaje=ui->voltaje_doubleSpinBox->value();
    posicion_x=ui->Pos_x_spinBox_2->value();
    posicion_y=ui->Pos_y_spinBox_2->value();
    red=ui->red_spinBox_4->value();
    green=ui->green_spinBox_5->value();
    blue=ui->spinBox_6->value();
    if(!bandera){
        QMessageBox::warning(this,"Mensaje","Id repetido.");
    }else{
        if((id == 0 or voltaje == 0 or id == NULL or voltaje == NULL)){
            QMessageBox::warning(this,"Mensaje","Tiene que existir un voltaje y un id.");
        }else{
            Neurona *nuevo = new Neurona(id,voltaje,posicion_x,posicion_y,red,green,blue);
            lista.push_front(*nuevo);
            ui->id_spinBox->clear();
            ui->voltaje_doubleSpinBox->clear();
            ui->Pos_x_spinBox_2->clear();
            ui->Pos_y_spinBox_2->clear();
            ui->red_spinBox_4->clear();
            ui->green_spinBox_5->clear();
            ui->spinBox_6->clear();
        }
    }
}

void MainWindow::on_pushButton_2_clicked(){
    //INSERTAR AL FINAL
    int id, posicion_x,posicion_y,red,green,blue;
    double voltaje;
    id=ui->id_spinBox->value();
    bool bandera;
    bandera=id_repetido(id);
    voltaje=ui->voltaje_doubleSpinBox->value();
    posicion_x=ui->Pos_x_spinBox_2->value();
    posicion_y=ui->Pos_y_spinBox_2->value();
    red=ui->red_spinBox_4->value();
    green=ui->green_spinBox_5->value();
    blue=ui->spinBox_6->value();
    if(!bandera){
        QMessageBox::warning(this,"Mensaje","Id repetido.");
    }else{
        if((id == 0 or voltaje == 0 or id == NULL or voltaje == NULL)){
            QMessageBox::warning(this,"Mensaje","Tiene que existir un voltaje y un id.");
        }else{
            Neurona *nuevo = new Neurona(id,voltaje,posicion_x,posicion_y,red,green,blue);
            lista.push_back(*nuevo);
            ui->id_spinBox->clear();
            ui->voltaje_doubleSpinBox->clear();
            ui->Pos_x_spinBox_2->clear();
            ui->Pos_y_spinBox_2->clear();
            ui->red_spinBox_4->clear();
            ui->green_spinBox_5->clear();
            ui->spinBox_6->clear();
        }
    }
}

void MainWindow::on_pushButton_3_clicked(){
    //MOSTRAR EN EL QPLAINTEXTEDID
    if(!lista.empty()){
        ui->plainTextEdit->clear();
        list<Neurona>::iterator aux = lista.begin();
        while(aux!=lista.end()){
            ui->plainTextEdit->insertPlainText("ID: "+QString::number(aux->getId())+"\n");
            ui->plainTextEdit->insertPlainText("VOLTAJE: "+QString::number(aux->getVoltaje())+"\n");
            ui->plainTextEdit->insertPlainText("POS_X: "+QString::number(aux->getPosX())+"\n");
            ui->plainTextEdit->insertPlainText("POS_Y: "+QString::number(aux->getPosY())+"\n");
            ui->plainTextEdit->insertPlainText("RED: "+QString::number(aux->getRed())+"\n");
            ui->plainTextEdit->insertPlainText("GREEN: "+QString::number(aux->getGreen())+"\n");
            ui->plainTextEdit->insertPlainText("RED: "+QString::number(aux->getRed())+"\n\n");
            aux++;
        }
    }else{
        ui->plainTextEdit->clear();
        ui->plainTextEdit->insertPlainText("La lista esta vacia...");
    }
}


void MainWindow::on_pushButton_4_clicked(){
    //RESPALDO DE UN ARCHIVO
    string delimitador = "|";
    if(!lista.empty()){
        QString filename = QFileDialog::getSaveFileName(this, "Save file","respaldo.txt");
        ofstream archivo(filename.toStdString(),ios::out);
        list<Neurona>::iterator aux = lista.begin();
        while(aux!=lista.end()){
            archivo<<aux->getId()<<delimitador;
            archivo<<aux->getVoltaje()<<delimitador;
            archivo<<aux->getPosX()<<delimitador;
            archivo<<aux->getPosY()<<delimitador;
            archivo<<aux->getRed()<<delimitador;
            archivo<<aux->getGreen()<<delimitador;
            archivo<<aux->getBlue()<<delimitador;
            aux++;
        }
        QMessageBox::information(this,"Guardado","Guardado exitosamente...");
    }else{
        ui->plainTextEdit->clear();
        ui->plainTextEdit->insertPlainText("La lista esta vacia...");
    }
}


void MainWindow::on_pushButton_5_clicked(){
    //RECUPERAR DE UN ARCHIVO
    int id, posicion_x,posicion_y,red,green,blue;
    double voltaje;
    string registro;
    QString filename = QFileDialog::getOpenFileName(this, "Open file","C://");
    ifstream archivo(filename.toStdString(),ios::in);
    if(!archivo.fail()){
        while(!archivo.eof()){
            getline(archivo,registro,'|');
            id=atoi(registro.c_str());
            if(id != NULL){
                getline(archivo,registro,'|');
                voltaje=strtof(registro.c_str(), nullptr);
                getline(archivo,registro,'|');
                posicion_x=atoi(registro.c_str());
                getline(archivo,registro,'|');
                posicion_y=atoi(registro.c_str());
                getline(archivo,registro,'|');
                red=atoi(registro.c_str());
                getline(archivo,registro,'|');
                green=atoi(registro.c_str());
                getline(archivo,registro,'|');
                blue=atoi(registro.c_str());
                Neurona *nuevo = new Neurona(id,voltaje,posicion_x,posicion_y,red,green,blue);
                lista.push_back(*nuevo);
            }
        }
        QMessageBox::information(this,"Recuperado","Se recuperaron los archivos correctamente...");
    }else{
        QMessageBox::critical(this,"Error","El archivo no se abrio correctamente...");
    }
}

void MainWindow::on_tabWidget_tabBarClicked(int index){
    //MOSTRAR ELEMENTOS EN TABLA AL PRESIONAR EL BAR "BUSCAR"
    ui->tableWidget->clear();
    int tamano = lista.size();
    int i=0;
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setRowCount(tamano);
    QStringList nom_colum={"ID","VOLTAJE","POS_X","POS_Y"};
    ui->tableWidget->setHorizontalHeaderLabels(nom_colum);
    if(index == 1){
        if(!lista.empty()){
            list<Neurona>::iterator aux = lista.begin();
            while(aux!=lista.end()){
                QString a = QString::number(aux->getId());
                QTableWidgetItem *c= new QTableWidgetItem(a);
                ui->tableWidget->setItem(i,0,c);
                a = QString::number(aux->getVoltaje());
                c= new QTableWidgetItem(a);
                ui->tableWidget->setItem(i,1,c);
                a = QString::number(aux->getPosX());
                c= new QTableWidgetItem(a);
                ui->tableWidget->setItem(i,2,c);
                a = QString::number(aux->getPosY());
                c= new QTableWidgetItem(a);
                ui->tableWidget->setItem(i,3,c);
                aux++;
                i++;
            }
        }
    }
}

void MainWindow::on_pushButton_6_clicked(){
    //BUSCAR
    bool bandera = false;
    QString line_text=ui->lineEdit->text();
    list<Neurona>::iterator aux = lista.begin();
    while(aux!=lista.end()){
        if(line_text==QString::number(aux->getId())){
            ui->tableWidget->clear();
            ui->tableWidget->setColumnCount(4);
            ui->tableWidget->setRowCount(1);
            QStringList nom_colum={"ID","VOLTAJE","POS_X","POS_Y"};
            QString a = QString::number(aux->getId());
            QTableWidgetItem *c= new QTableWidgetItem(a);
            ui->tableWidget->setItem(0,0,c);
            a = QString::number(aux->getVoltaje());
            c= new QTableWidgetItem(a);
            ui->tableWidget->setItem(0,1,c);
            a = QString::number(aux->getPosX());
            c= new QTableWidgetItem(a);
            ui->tableWidget->setItem(0,2,c);
            a = QString::number(aux->getPosY());
            c= new QTableWidgetItem(a);
            ui->tableWidget->setItem(0,3,c);
            bandera=true;
        }
        aux++;
    }
    if(!bandera){
        QMessageBox::information(this,"Buscar","Id no encontrado...");
    }
}

void MainWindow::on_pushButton_7_clicked(){
    //MOSTRAR EN TABLA
    ui->tableWidget->clear();
    int tamano = lista.size();
    int i=0;
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setRowCount(tamano);
    QStringList nom_colum={"ID","VOLTAJE","POS_X","POS_Y"};
    ui->tableWidget->setHorizontalHeaderLabels(nom_colum);
    if(!lista.empty()){
        list<Neurona>::iterator aux = lista.begin();
        while(aux!=lista.end()){
            QString a = QString::number(aux->getId());
            QTableWidgetItem *c= new QTableWidgetItem(a);
            ui->tableWidget->setItem(i,0,c);
            a = QString::number(aux->getVoltaje());
            c= new QTableWidgetItem(a);
            ui->tableWidget->setItem(i,1,c);
            a = QString::number(aux->getPosX());
            c= new QTableWidgetItem(a);
            ui->tableWidget->setItem(i,2,c);
            a = QString::number(aux->getPosY());
            c= new QTableWidgetItem(a);
            ui->tableWidget->setItem(i,3,c);
            aux++;
            i++;
        }
    }
}

void MainWindow::on_pushButton_8_clicked(){
    //GRAFICAR
    if(!lista.empty()){
        list<Neurona>::iterator aux = lista.begin();
        while(aux!=lista.end()){
            QPen pen;
            pen.setWidth(2);
            QColor color(aux->getRed(),aux->getGreen(),aux->getBlue());
            pen.setColor(color);
            grafica.addEllipse(aux->getPosX(),aux->getPosY(),aux->getVoltaje(),aux->getVoltaje(),pen);
            ui->graphicsView->setScene(&grafica);
            aux++;
        }
    }
}

void MainWindow::on_pushButton_9_clicked(){
    //LIMPIAR GRÁFICA
    grafica.clear();
}
