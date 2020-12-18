#ifndef CLIENTCRAWLER_H
#define CLIENTCRAWLER_H

#include <QWidget>
#include <QGridLayout>
#include <QToolButton>
#include <QTcpSocket>
#define TAILLE 20

QT_BEGIN_NAMESPACE
namespace Ui { class ClientCrawler; }
QT_END_NAMESPACE

class ClientCrawler : public QWidget
{
    Q_OBJECT

public:
    ClientCrawler(QWidget *parent = nullptr);
    ~ClientCrawler();
    QPoint pos;

private:
    Ui::ClientCrawler *ui;
    QGridLayout *grille;
    QTcpSocket *socketClient;
    void EnvoyerCommande(QChar commande);


private slots:
    void onQTcpSocket_connected();
    void onQTcpSocket_disconnected();
    void onQTcpSocket_error(QAbstractSocket::SocketError socketError);
    void onQTcpSocket_readyRead();
    void on_pushButtonConnexion_clicked();
    void on_pushButtonUp_clicked();
    void on_pushButtonDown_clicked();
    void on_pushButtonLeft_clicked();
    void on_pushButtonRight_clicked();
};
#endif // CLIENTCRAWLER_H
