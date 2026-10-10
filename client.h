#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QTcpSocket>
#include <QDataStream>

QT_BEGIN_NAMESPACE
namespace Ui {
class Client;
}
QT_END_NAMESPACE

class Client : public QWidget
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = nullptr);
    ~Client() override;

private:
    Ui::Client *ui;
    // socket
    QTcpSocket *clientSocket = nullptr;
    // flujo de datos recibido
    QDataStream in;

private slots:
    // solicitar la conexión al Servidor
    void requestMessage();
    // leer el mensaje recibido
    void readMessage();
};
#endif // CLIENT_H