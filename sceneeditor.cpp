#include "sceneeditor.h"
#include <QDebug>

SceneEditor::SceneEditor(QObject *parent) : QObject(parent){
	conn = 0;
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
					}
					break;
				}
				case Qt::RightButton:{
					QGraphicsItem *item = itemAt(me->scenePos());
					if (item && item->type() == CIRC_ELEMENT)
						((CircuitElement*)item)->showMenu();
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
