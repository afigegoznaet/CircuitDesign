#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow){
	ui->setupUi(this);
	QGraphicsView* scrollArea = ui->graphicsView;

	scrollArea->setContextMenuPolicy(Qt::CustomContextMenu);

	auto scene = new GridScene(this);

	scrollArea->setAlignment(Qt::AlignTop|Qt::AlignLeft);
	scrollArea->setScene(scene);
	qDebug()<<scene->sceneRect();
	scrollArea->setMaximumSize(scene->sceneRect().width()+4,
							   scene->sceneRect().height()+4);
	//ui->graphicsView->setSceneRect(scene->sceneRect());
	editor = new SceneEditor(this);
	editor->install(scene);

	connect(scrollArea, SIGNAL(customContextMenuRequested(const QPoint &)),
			editor, SLOT(contextMenuRequested(const QPoint &)));
	scrollArea->setTransformationAnchor(QGraphicsView::NoAnchor);

	qDebug()<<"inductor";
	auto object1 = new EndPoint();
	auto object2 = new EndPoint();
	scrollArea->scene()->addItem(object1);

	((QGraphicsItem*)object1)->setPos(QPointF(0,0));

	scrollArea->scene()->addItem(object2);
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

