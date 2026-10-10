#include "client.h"
#include "ui_client.h"

Client::Client(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Client)
{
    ui->setupUi(this);
    // init socket
    clientSocket = new QTcpSocket(this);
    // asociando el dispositivo de entrada con el socket
    in.setDevice(clientSocket);
    // conexiones entre señales y slots
    // cerrar la ventana
    connect(ui->pb_close, &QAbstractButton::clicked, this, &QWidget::close);
    // conectar con el servidor
    connect(ui->pb_request, &QAbstractButton::clicked, this, &Client::requestMessage);
    // lectura del mensaje recibido
    connect(clientSocket, &QAbstractSocket::readyRead, this, &Client::readMessage);
}

Client::~Client()
{
    delete ui;
}

void Client::requestMessage()
{
    qDebug() << "requestMessage !!";
    //Datos del servidor
    QString ip = ui ->le_ip -> text();
    QString port = ui->le_port -> text();
    qDebug ()<< "ip :"<< ip << ",port"<< port;
    //conexion con el servidor
    clientSocket ->connectToHost (ip,port.toInt());

}

void Client::readMessage()
{

    //configuracion de la trasaccion
    in.startTransaction();
    QString msg ;
    // configuruacion del objeto
    in >> msg;
    //ejecutar la transaccion
    if(!in.commitTransaction()){
        qDebug ()<< "Error en el flujo de datos";
        return;
    }
    qDebug()<<"Mensaje recibido"<<msg;
    ui->lb_message->setText(msg);

}