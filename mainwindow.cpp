#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <iostream>
#include <stdlib.h>
#include "grafo.h"

Grafo g = Grafo();

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void addStartPoint(Ui::MainWindow *ui, string nodoEntrada){
    g.marcarNodoEntrada(nodoEntrada);
    ui->checkIsStart->setCheckable(false);
    ui->checkIsStart->setDisabled(true);
}

void addItemComboBox(Ui::MainWindow *ui, QString nameItem){
    ui->comboBoxVertexOrigin->addItem(nameItem);
    ui->comboBoxVertexCominIn->addItem(nameItem);
}

void setChecked(Ui::MainWindow *ui, bool checked){
    ui->checkIsAcceptation->setChecked(checked);
    ui->checkIsStart->setChecked(checked);
}

void MainWindow::on_btnAddVertex_clicked()
{
    QPalette palette;
    if(!ui->lineVertex->text().isEmpty()){
        if(g.agregarVertice(new Vertice(ui->lineVertex->text().toStdString(), ui->checkIsAcceptation->isChecked()))){
            QString esAceptado;
            if(ui->checkIsAcceptation->isChecked()){
                esAceptado = "Estado de aceptación";
            }else{
                esAceptado = "No es estado de aceptación";
            }
            ui->listWidget->addItem("Nodo  " + ui->lineVertex->text() + "\t " + esAceptado);
            if(ui->checkIsStart->isChecked()){
                addStartPoint(ui, ui->lineVertex->text().toStdString());
            }
            addItemComboBox(ui, ui->lineVertex->text());
            setChecked(ui, false);
            ui->lineVertex->clear();

            palette.setColor(QPalette::Base,Qt::white);
            ui->lineVertex->setPalette(palette);
        }else{
            palette.setColor(QPalette::Base,Qt::red);
            ui->lineVertex->setPalette(palette);
        }
    }else{
        palette.setColor(QPalette::Base,Qt::red);
        ui->lineVertex->setPalette(palette);
        setChecked(ui, false);
    }

}

void MainWindow::on_buttonAddRules_clicked()
{
    char characterRead, characterExtract;
    string textPutInHead;

    if(ui->lineRead->text().isEmpty()){
        characterRead = 156;
    }else{
        characterRead = ui->lineRead->text().toStdString()[0];
    }
    if(ui->lineExtract->text().isEmpty()){
        characterExtract = 157;
    }else{
        characterExtract = ui->lineExtract->text().toStdString()[0];
    }
    if(ui->linePutInHeap->text().isEmpty()){
        textPutInHead = "λ";
    }else{
        textPutInHead = ui->linePutInHeap->text().toStdString();
    }
    g.relacionar(ui->comboBoxVertexOrigin->currentText().toStdString(),
                     ui->comboBoxVertexCominIn->currentText().toStdString());


    g.agregarReglas(ui->comboBoxVertexOrigin->currentText().toStdString(),
                    ui->comboBoxVertexCominIn->currentText().toStdString(),
                            characterRead, characterExtract, textPutInHead);
    ui->lineRead->clear();
    ui->lineExtract->clear();
    ui->linePutInHeap->clear();
}

void setLabelText(Ui::MainWindow *ui, int aceptation){
    switch (aceptation) {
        case 1:{
            ui->labelMessage->setStyleSheet("color: green");
            ui->labelMessage->setText("Aceptado");
            break;
        }
        case 2:{
            ui->labelMessage->setStyleSheet("color: red");
            ui->labelMessage->setText("No Aceptado");
            break;
        }
        case 3:{
            ui->labelMessage->setStyleSheet("color: gray");
            ui->labelMessage->setText("Revisa la entrada");
            break;
        }
    }
}

void MainWindow::on_buttonValidate_clicked()
{
    Pila pila = Pila();

    if(!ui->lineWords->text().isEmpty() && g.getNodoEntrada() != ""){
        if(g.verificarAceptacion(g.getNodoEntrada(), ui->lineWords->text().toStdString(), pila, true)){
            setLabelText(ui, 1);
        }else{
            setLabelText(ui, 2);
        }        
    }else{
        setLabelText(ui, 3);
    }
    ui->lineWords->clear();
}

void MainWindow::on_action_Acerca_de_triggered()
{
    QMessageBox::information(this, "Automata Basado en Pila",
                             "Código basado en C++. \nEmpleando en G++ y Qt Creator. \nDiseñado y programado por Ricardo Alzamora Valle.");
}
