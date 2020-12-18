#include "clientcrawler.h"
#include "ui_clientcrawler.h"
#include <QBuffer>

ClientCrawler::ClientCrawler(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ClientCrawler)
{
    ui->setupUi(this);

    grille = new QGridLayout(this);

    for(int ligne = 0; ligne<TAILLE; ligne++)
    {
        for(int colonne = 0; colonne<TAILLE; colonne++)
        {
            QToolButton *b = new QToolButton();
            grille->addWidget(b, ligne, colonne, 1, 1);
        }
    }

    grille->addWidget(ui->labelAdresseServeur,TAILLE,0,1,5);
    grille->addWidget(ui->labelNumeroPort,TAILLE,6,1,5);
    grille->addWidget(ui->labelDistance,TAILLE+3,0,1,5);
    grille->addWidget(ui->labelInformations,TAILLE+3,12,1,5);
    grille->addWidget(ui->lineEditAdresseServeur,TAILLE+1,0,1,5);
    grille->addWidget(ui->spinBoxPortServeur,TAILLE+1,6,1,5);
    grille->addWidget(ui->pushButtonConnexion,TAILLE+2,0,1,5);
    grille->addWidget(ui->pushButtonQuitter,TAILLE+2,6,1,5);
    grille->addWidget(ui->pushButtonUp,TAILLE,15,1,1);
    grille->addWidget(ui->pushButtonLeft,TAILLE+1,14,1,1);
    grille->addWidget(ui->pushButtonRight,TAILLE+1,16,1,1);
    grille->addWidget(ui->pushButtonDown,TAILLE+2,15,1,1);
    grille->addWidget(ui->lcdNumberDistance,TAILLE+3,6,1,5);
    this->setLayout(grille);

    socketClient = new QTcpSocket;

    connect(socketClient, &QTcpSocket::connected, this, &ClientCrawler::onQTcpSocket_connected);
    connect(socketClient, &QTcpSocket::disconnected, this, &ClientCrawler::onQTcpSocket_disconnected);
    connect(socketClient, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &ClientCrawler::onQTcpSocket_error);
    connect(socketClient, &QTcpSocket::readyRead, this, &ClientCrawler::onQTcpSocket_readyRead);

}

ClientCrawler::~ClientCrawler()
{
    delete ui;
}

void ClientCrawler::EnvoyerCommande(QChar commande)
{
    quint16 taille=0;
    QBuffer tampon;
    tampon.open(QIODevice::WriteOnly);
    QDataStream out(&tampon);
    out<<taille<<commande;
    taille=tampon.size()-sizeof (taille);
    tampon.seek(0);
    out<<taille;
    socketClient->write(tampon.buffer());
}

void ClientCrawler::onQTcpSocket_connected()
{
    qDebug()<<"Le client est connecté";
}

void ClientCrawler::onQTcpSocket_disconnected()
{
    qDebug()<<"Le client est déconnecté";
}

void ClientCrawler::onQTcpSocket_error(QAbstractSocket::SocketError socketError)
{
    qDebug()<<this;
}

void ClientCrawler::onQTcpSocket_readyRead()
{

    qDebug()<<"Données reçues";

    quint16 taille = 0;
    QString message;
    double distance;

    if(socketClient->bytesAvailable() > 0)
    {
        QDataStream in(socketClient);
        in>>taille>>pos>>message>>distance ;
    }

    if(message == "collision")
    {
        ui->labelInformations->setText(message);
        ui->labelInformations->setStyleSheet("QLabel{color : magenta}");

    }
    else if(message == "vide" || message == "start")
    {
        ui->labelInformations->setText(message);
        ui->labelInformations->setStyleSheet("QLabel{color : black}");
    }
    else
    {
        ui->labelInformations->setText(message);
        ui->labelInformations->setStyleSheet("QLabel{color : green}");
    }

    ui->lcdNumberDistance->display(distance);

    grille->itemAtPosition(pos.y(), pos.x())->widget()->setStyleSheet("background-color : black");
}


void ClientCrawler::on_pushButtonConnexion_clicked()
{
    QString IP = ui->lineEditAdresseServeur->text();
    quint16 port = ui->spinBoxPortServeur->text().toInt();

    socketClient->connectToHost(IP, port, QIODevice::ReadWrite, QAbstractSocket::AnyIPProtocol);
}

void ClientCrawler::on_pushButtonUp_clicked()
{
    EnvoyerCommande('U');
    grille->itemAtPosition(pos.y(), pos.x())->widget()->setStyleSheet("background-color : rgb(239, 239, 239)");
}

void ClientCrawler::on_pushButtonDown_clicked()
{
    EnvoyerCommande('D');
    grille->itemAtPosition(pos.y(), pos.x())->widget()->setStyleSheet("background-color : rgb(239, 239, 239)");
}

void ClientCrawler::on_pushButtonLeft_clicked()
{
    EnvoyerCommande('L');
    grille->itemAtPosition(pos.y(), pos.x())->widget()->setStyleSheet("background-color : rgb(239, 239, 239)");
}

void ClientCrawler::on_pushButtonRight_clicked()
{
    EnvoyerCommande('R');
    grille->itemAtPosition(pos.y(), pos.x())->widget()->setStyleSheet("background-color : rgb(239, 239, 239)");
}

