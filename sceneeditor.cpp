#include "sceneeditor.h"
#include <QDebug>

SceneEditor::SceneEditor(QObject *parent) : QObject(parent){
	conn = 0;
	createMenus();
	clipboard = ClipBoard::getInstance();
}

void SceneEditor::install(QGraphicsScene *s)
{
	s->installEventFilter(this);
	scene = s;
}

QGraphicsItem* SceneEditor::itemAt(const QPointF &pos)
{
	QList<QGraphicsItem*> items = scene->items(QRectF(pos - QPointF(1,1), QSize(3,3)));

	foreach(QGraphicsItem *item, items)
		if (item->type() >= QGraphicsItem::UserType)
			return item;
	return 0;
}

bool SceneEditor::eventFilter(QObject *o, QEvent *e)
{
	QGraphicsSceneMouseEvent *me = (QGraphicsSceneMouseEvent*) e;

	switch (e->type()){
		default:
			break;
		case QEvent::GraphicsSceneMousePress:{
			switch (me->button()){
				default:
					break;
				case Qt::LeftButton:{
					QGraphicsItem *item = itemAt(me->scenePos());
					if (item && item->type() == PIN){
						conn = new Wire(0);
						scene->addItem(conn);
						conn->setPort1((Pin*) item);
						conn->setPos1(item->scenePos());
						conn->setPos2(me->scenePos());
						conn->updatePath();
						return true;
					}else if(item){
						item->setSelected(true);
						item->setEnabled(true);
					}else
						foreach (auto &itemRef, scene->selectedItems()) {
							itemRef->setSelected(false);
							itemRef->setEnabled(false);
						}
					break;
				}
				case Qt::RightButton:{
					QGraphicsItem *item = itemAt(me->scenePos());
					if (item && item->type() == CIRC_ELEMENT)
						showMenu((CircuitElement*)item);
					break;
				}
			}
		}
		case QEvent::GraphicsSceneMouseMove:{
			if (conn){
				qDebug()<<conn;
				conn->setPos2(me->scenePos());
				conn->updatePath();
				return true;
			}
			break;
		}
		case QEvent::GraphicsSceneMouseRelease:{
			qDebug()<<"Mouse released";
			if (me->button() == Qt::LeftButton){
				QGraphicsItem *item = itemAt(me->scenePos());
				if(!item)
					break;
				if (conn && item->type() == PIN){
					Pin *pin1 = conn->pin1;
					Pin *pin2 = (Pin*) item;

					if (pin1->parent_ != pin2->parent_ && !pin1->isConnected(pin2)){
						conn->setPos2(pin2->scenePos());
						conn->setPort2(pin2);
						conn->updatePath();
						conn = 0;
						return true;
					}
				}else{
					((CircuitElement*)item)->setPos(item->scenePos());
					//item->setEnabled(false);
				}

				delete conn;
				conn = 0;
				return true;
			}
			break;
		}
	}
	return QObject::eventFilter(o, e);
}

void SceneEditor::createMenus(){
	sceneContextMenu = new QMenu((QWidget*)this->parent());//parent is main windwo. Ugly hack
	sceneContextMenu->addAction("Add &capacitor",[&](){insertElement(CAPACITOR);} , QString("C"));
	sceneContextMenu->addAction("Add &inductor", [&](){insertElement(INDUCTOR);}, QString("I"));
	sceneContextMenu->addAction("Add &resistor",[&](){insertElement(RESISTOR);}, QString("R"));
	sceneContextMenu->addSeparator();
	sceneContextMenu->addAction("Add &speaker", [&](){insertElement(SPEAKER);}, QString("S"));
	sceneContextMenu->addAction("Add &endpoint", [&](){insertElement(ENDPOINT);}, QString("E"));
	sceneContextMenu->addSeparator();
	sceneContextMenu->addAction("Add active filter (N/A yet)");
	sceneContextMenu->addAction("Add digital filter (N/A yet)");
	sceneContextMenu->addAction("Add buffer/amplifier (N/A yet)");
	sceneContextMenu->addSeparator();
	sceneContextMenu->addAction("Place text (N/A yet)");
	sceneContextMenu->addSeparator();
	auto act = sceneContextMenu->addAction("Cut");
	act->setEnabled(false);
	//connect(this, SIGNAL(clipboardContentsEnabled(bool)), act, SLOT(setEnabled(bool)));
	act = sceneContextMenu->addAction("Copy");
	act->setEnabled(false);
	//connect(this, SIGNAL(clipboardContentsEnabled(bool)), act, SLOT(setEnabled(bool)));
	act = sceneContextMenu->addAction("Paste", [&](){auto elem = clipboard->paste(); scene->addItem(elem); elem->setPos(QCursor::pos());});
	act->setEnabled(false);
	connect(this, SIGNAL(clipboardContentsEnabled(bool)), act, SLOT(setEnabled(bool)));
	sceneContextMenu->addSeparator();
	sceneContextMenu->addAction("Properties (N/A yet)");

}

void SceneEditor::showMenu(CircuitElement* elem){
	QMenu* itemContextMenu = new QMenu((QWidget*)this->parent());
	itemContextMenu->addAction("Rotate element", [&](){elem->rotateClockwise();});
	itemContextMenu->addSeparator();
	itemContextMenu->addAction("Cut", [&](){clipboard->cut(elem); scene->removeItem(elem); emit clipboardContentsEnabled(true);});
	itemContextMenu->addAction("Copy", [&](){clipboard->copy(elem);emit clipboardContentsEnabled(true);});
	auto act = itemContextMenu->addAction("Paste");
	act->setEnabled(false);
	auto deleter = [&](){
		if(EndPoint* endP = dynamic_cast<EndPoint*> (elem))
			if(endP->isStartingPoint()){
				(QMessageBox(QMessageBox::Information, "Error", "Can't delete starting endpoint")).exec();
				return;
			}

		scene->removeItem(elem);
		delete elem;
	};
	itemContextMenu->addAction("&Delete)", this, deleter, QString("D"));
	itemContextMenu->addSeparator();
	itemContextMenu->addAction("Edit proprties");
	itemContextMenu->exec(QCursor::pos());
}

void SceneEditor::contextMenuRequested(const QPoint &pos){
	sceneContextMenu->exec(QCursor::pos());
	qDebug()<<pos<<" "<<QCursor::pos();
}

void SceneEditor::insertElement(ElementType type){
	CircuitElement* elem;
	switch (type) {
	case CAPACITOR:
		elem = new Capacitor();
		break;
	case INDUCTOR:
		elem = new Inductor();
		break;
	case RESISTOR:
		elem = new Resistor();
		break;
	case SPEAKER:
		elem = new Speaker();
		break;
	case ENDPOINT:
		elem = new EndPoint();
		break;
	default:
		break;
	}
	scene->addItem(elem);
	elem->setPos(QCursor::pos());
}
