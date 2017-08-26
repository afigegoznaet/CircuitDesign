#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow){
	ui->setupUi(this);
	QGraphicsView* scrollArea = ui->graphicsView;

	createMenu();
	scrollArea->setContextMenuPolicy(Qt::CustomContextMenu);

	connect(scrollArea, SIGNAL(customContextMenuRequested(const QPoint &)),
			this, SLOT(contextMenuRequested(const QPoint &)));


	auto scene = new GridScene(this);

	ui->graphicsView->setScene(scene);
	editor = new SceneEditor(this);
	editor->install(scene);
	scrollArea->setTransformationAnchor(QGraphicsView::NoAnchor);

	qDebug()<<"inductor";
	auto object1 = new EndPoint();
	auto object2 = new EndPoint();
	ui->graphicsView->scene()->addItem(object1);

	((QGraphicsItem*)object1)->setPos(QPointF(0,0));

	ui->graphicsView->scene()->addItem(object2);
	auto point = QPointF(0,50);
	((QGraphicsItem*)object2)->setPos(point);
	((QGraphicsItem*)object2)->setPos(point);

}

MainWindow::~MainWindow(){
	delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event){
	if(event->button() != Qt::RightButton)
		return;
}

void MainWindow::createMenu(){
	contextMenu = new QMenu(this);
	contextMenu->addAction("Insert capacitor", this, &MainWindow::insertCapacitor);
	contextMenu->addAction("Insert inductor", this, &MainWindow::insertInductor);
	contextMenu->addAction("Insert resistor", this, &MainWindow::insertResistor);
	contextMenu->addSeparator();
	contextMenu->addAction("Insert speaker", this, &MainWindow::insertSpeaker);
	contextMenu->addAction("Insert endpoint", this, &MainWindow::insertEndPoint);
	contextMenu->addSeparator();
	contextMenu->addAction("Insert passive filter (N/A yet)");
	contextMenu->addAction("Insert active filter (N/A yet)");
	contextMenu->addAction("Insert digital filter (N/A yet)");
	contextMenu->addAction("Insert buffer/amplifier (N/A yet)");
	contextMenu->addSeparator();
	contextMenu->addAction("Place text (N/A yet)");
	contextMenu->addSeparator();
	contextMenu->addAction("Cut (N/A yet)");
	contextMenu->addAction("Copy (N/A yet)");
	contextMenu->addAction("Paste (N/A yet)");
	contextMenu->addSeparator();
	contextMenu->addAction("Properties (N/A yet)");
}

void MainWindow::insertCapacitor(){
	qDebug()<<"capacitor";
	auto object = new Capacitor();
	ui->graphicsView->scene()->addItem(object);
	object->setPos(QCursor::pos());
}

void MainWindow::insertResistor(){
	qDebug()<<"resistor";
	auto object = new Resistor();
	ui->graphicsView->scene()->addItem(object);
	object->setPos(QCursor::pos());
}

void MainWindow::insertInductor(){
	qDebug()<<"inductor";
	auto object = new Inductor();
	ui->graphicsView->scene()->addItem(object);
	object->setPos(QCursor::pos());
}

void MainWindow::insertSpeaker(){
	qDebug()<<"inductor";
	auto object = new Speaker();
	ui->graphicsView->scene()->addItem(object);
	object->setPos(QCursor::pos());
}

void MainWindow::insertEndPoint(){
	qDebug()<<"inductor";
	auto object = new EndPoint();
	ui->graphicsView->scene()->addItem(object);
	object->setPos(QCursor::pos());
}

void MainWindow::contextMenuRequested(const QPoint &pos){
	contextMenu->exec(QCursor::pos());
	qDebug()<<pos<<" "<<QCursor::pos();
}
