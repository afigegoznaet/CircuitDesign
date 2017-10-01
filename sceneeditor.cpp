#include "sceneeditor.h"

SceneEditor::SceneEditor(QObject *parent) : QObject(parent){
	conn = 0;
	createMenus();
	clipboard = ClipBoard::getInstance();
}

void SceneEditor::install(QGraphicsScene *s, QGraphicsView *view){
	this->view=view;
	s->installEventFilter(this);
	scene = s;
}

QGraphicsItem* SceneEditor::itemAt(const QPointF &pos){
	QList<QGraphicsItem*> items = scene->items(QRectF(pos - QPointF(1,1), QSize(3,3)));

	foreach(QGraphicsItem *item, items)
		if (item->type() >= QGraphicsItem::UserType)
			return item;
	return 0;
}

bool SceneEditor::eventFilter(QObject *o, QEvent *e){

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
						conn = new Wire();
						scene->addItem(conn);
						conn->setPort1((Pin*) item);
						conn->setPos1(item->scenePos());
						conn->setPos2(me->scenePos());
						conn->updatePath();
						return true;
					}else if(item){
						disposeSelectedItems();
						item->setSelected(true);
					}else
						disposeSelectedItems();
					break;
				}
				case Qt::RightButton:{
					QGraphicsItem *item = itemAt(me->scenePos());
					if (item && item->type() == CIRC_ELEMENT)
						showMenu((CircuitElement*)item);
					else
						contextMenuRequested(me->scenePos().toPoint());
					break;
				}
			}
		}
		case QEvent::GraphicsSceneMouseMove:{
			if (conn){
				//qDebug()<<conn;
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
					return false;
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
				}else
					((CircuitElement*)item)->setPos(item->scenePos());

				delete conn;
				conn = 0;
				return true;
			}
			break;
		}
	}
	qDebug()<<e->AcceptDropsChange;
	qDebug()<<e->type();
	return QObject::eventFilter(o, e);
}

void SceneEditor::createMenus(){
	sceneContextMenu = new QMenu((QWidget*)this->parent());//parent is main windwo. Ugly hack
	actions.push_back(sceneContextMenu->addAction("Add &capacitor",
						[&](){insertElement(CAPACITOR);} , QString("C")));
	actions.push_back(sceneContextMenu->addAction("Add &inductor",
						[&](){insertElement(INDUCTOR);}, QString("I")));
	actions.push_back(sceneContextMenu->addAction("Add &resistor",
						[&](){insertElement(RESISTOR);}, QString("R")));
	sceneContextMenu->addSeparator();
	actions.push_back(sceneContextMenu->addAction("Add &speaker",
						[&](){insertElement(SPEAKER);}, QString("S")));
	actions.push_back(sceneContextMenu->addAction("Add &endpoint",
						[&](){insertElement(ENDPOINT);}, QString("E")));
	sceneContextMenu->addSeparator();
	sceneContextMenu->addAction("Add active filter (N/A yet)");
	sceneContextMenu->addAction("Add digital filter (N/A yet)");
	sceneContextMenu->addAction("Add buffer/amplifier (N/A yet)");
	sceneContextMenu->addSeparator();
	sceneContextMenu->addAction("Place text (N/A yet)");
	sceneContextMenu->addSeparator();
	actions.push_back(sceneContextMenu->addAction("Cut",
					[&](){cutToClipboard();},QKeySequence(tr("Ctrl+X"))));
	actions.push_back(sceneContextMenu->addAction("Copy",
					[&](){copyToClipboard();},QKeySequence(tr("Ctrl+C"))));
	actions.push_back(sceneContextMenu->addAction("Paste",this,
					&SceneEditor::pasteFromClipboard, QKeySequence(tr("Ctrl+V"))));
	actions.push_back(sceneContextMenu->addAction("Delete selected",
					[&](){elementDeleter();}, QKeySequence(tr("Del"))));
	sceneContextMenu->addSeparator();
	sceneContextMenu->addAction("Properties (N/A yet)");
	((QWidget*)parent())->addActions(actions);
}

void SceneEditor::showMenu(CircuitElement* elem){
	QMenu* itemContextMenu = new QMenu((QWidget*)this->parent());
	itemContextMenu->addAction("Rotate element", [&](){elem->rotateClockwise();});
	itemContextMenu->addSeparator();

	itemContextMenu->addAction("Cut",[&](){cutToClipboard(elem);});
	itemContextMenu->addAction("Copy",  [&](){ copyToClipboard(elem);});
	itemContextMenu->addAction("Paste", this, &SceneEditor::pasteFromClipboard);
	itemContextMenu->addAction("&Delete", [&](){ elementDeleter(elem);});
	itemContextMenu->addSeparator();
	itemContextMenu->addAction("&Edit proprties", [&](){ elem->edit();});
	itemContextMenu->exec(QCursor::pos());
}

void SceneEditor::contextMenuRequested(const QPoint &){
	sceneContextMenu->exec(QCursor::pos());
	//qDebug()<<pos<<" "<<QCursor::pos();
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
	disposeSelectedItems();
	scene->addItem(elem);
	scene->selectedItems().append(elem);
	QPoint viewPoint = view->mapFromGlobal(QCursor::pos());
	QPointF scenePoint = view->mapToScene(viewPoint);
	elem->setPos(scenePoint);
	elem->setPos(scenePoint);
}

void SceneEditor::disposeSelectedItems(){
	qDebug()<<"Dispose";
	auto selections = scene->selectedItems();
	foreach (auto &item, selections) {
		item->setSelected(false);
	}
}

void SceneEditor::copyToClipboard(CircuitElement *elem){
	if(elem){
		clipboard->copy(elem);
		return;
	}
	if(scene->selectedItems().size())
		clipboard->copy((CircuitElement*)scene->selectedItems().first());
}
void SceneEditor::cutToClipboard(CircuitElement *elem){
	copyToClipboard(elem);
	if(elem)
		delete elem;
	else if(scene->selectedItems().size())
		delete scene->selectedItems().first();
	disposeSelectedItems();
}

void SceneEditor::pasteFromClipboard(){
	auto elem = clipboard->paste();
	if(elem == nullptr)
		return;
	scene->addItem(elem);
	QPoint viewPoint = view->mapFromGlobal(QCursor::pos());
	QPointF scenePoint = view->mapToScene(viewPoint);
	elem->setPos(scenePoint);
	elem->setPos(scenePoint);
}

//too many "if"s here, gotta do something about it
void SceneEditor::elementDeleter(CircuitElement *elem){
	if(elem == nullptr){
		if(scene->selectedItems().size())
			elem = (CircuitElement*)scene->selectedItems().first();
		else
			return;
	}
	if(EndPoint* endP = dynamic_cast<EndPoint*> (elem))
		if(endP->isStartingPoint()){
			(QMessageBox(QMessageBox::Information,
						 "Error", "Can't delete starting endpoint")).exec();
			return;
		}

	scene->removeItem(elem);
	delete elem;
}
