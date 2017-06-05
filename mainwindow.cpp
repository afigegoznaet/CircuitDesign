#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow){
	ui->setupUi(this);
	QGraphicsView* scrollArea = ui->graphicsView;

	scrollArea->setContextMenuPolicy(Qt::CustomContextMenu);

	connect(scrollArea, SIGNAL(customContextMenuRequested(const QPoint &)),
			this, SLOT(contextMenuRequested(const QPoint &)));

	//connect(ui->scrollArea,SIGNAL(mousePressEvent(QMouseEvent*)),
		//	this, SLOT(mousePressEvent(QMouseEvent*)));

	auto scene = new GridScene(this);

	ui->graphicsView->setScene(scene);
	editor = new SceneEditor(this);
	editor->install(scene);
}

MainWindow::~MainWindow(){
	delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event){
	if(event->button() != Qt::RightButton)
		return;
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

void MainWindow::contextMenuRequested(const QPoint &pos){
	auto contextMenu = new QMenu(this);
	contextMenu->addAction("Insert capacitor", this, &MainWindow::insertCapacitor);
	contextMenu->addAction("Insert resistor", this, &MainWindow::insertResistor);
	contextMenu->exec(QCursor::pos());
}
