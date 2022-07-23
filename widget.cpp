#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("BirdGame");
    setWindowIcon(QIcon(":/images/bird_blue_icon.png"));
    scene = new Scene(this);
    scene->setSceneRect(-250,-300,500,600);

    //scene->addLine(-400,0,400,0,QPen(Qt::blue));
    //scene->addLine(0,-400,0,400,QPen(Qt::blue));

    ui->graphicsView->setScene(scene);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_startGameB_clicked()
{
    qDebug() << "Starting the game..";
    scene->startGame();
}

