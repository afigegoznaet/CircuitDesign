#include "circuitelement.h"
#include <QDebug>

CircuitElement::CircuitElement(QGraphicsItem *parent, SpecialDrawings specialType):
	height(40),
	QGraphicsItem(parent){

	setFlags(QGraphicsItem::ItemIsSelectable |
			QGraphicsItem::ItemIsMovable
			 | QGraphicsItem::ItemSendsGeometryChanges
			 );

	if(specialType == SPEAKER){
		height=80;
		return;
	}

	addPort(true);
	if(specialType == ENDPOINT)
		return;
	addPort(false);
}

void CircuitElement::setPos(const QPointF &pos){

	QPointF newPos(itemChange(ItemPositionChange, pos).toPointF());
	//int grid = qobject_cast<GridScene*> (scene())->gridSize;
	QGraphicsItem::setPos(newPos);
}

QRectF CircuitElement::boundingRect() const{
	QRectF rect(0,0,width,height);
	return rect;
}

void CircuitElement::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	painter->setPen(QPen(Qt::green, 1, Qt::DashLine));
	if(isSelected())
		painter->drawRect(boundingRect());

}

QVariant CircuitElement::itemChange(GraphicsItemChange change,
const QVariant &value)
{
	if (change == ItemPositionChange && scene()) {
		QPointF newPos = value.toPointF();
		GridScene* customScene = qobject_cast<GridScene*> (scene());
		int gridSize = customScene->getGridSize();

		auto collisions = collidingItems();
		if( QApplication::mouseButtons() != Qt::LeftButton && !collisions.isEmpty()){
			qreal newX;
			qreal newY;

			QRectF otherBoundingRect = collisions.first()->boundingRect();
			otherBoundingRect.moveTo(collisions.first()->pos());
			QPointF otherMidPoint = otherBoundingRect.center();

			QRectF ownBoundingRect = boundingRect();
			ownBoundingRect.moveTo(pos());
			QPointF ownMidPoint = ownBoundingRect.center();

			if(ownMidPoint.x() - otherMidPoint.x() > 0)
				newX = otherBoundingRect.left()-gridSize;
			else
				newX = otherBoundingRect.right()+gridSize;

			if(ownMidPoint.y() - otherMidPoint.y() > 0)
				newY = otherBoundingRect.top()-gridSize;
			else
				newY = otherBoundingRect.bottom()+gridSize;

			return QPointF(newX, newY);
		}

		qreal xV = round(newPos.x()/gridSize)*gridSize;
		qreal yV = round(newPos.y()/gridSize)*gridSize;
		return QPointF(xV, yV);
	}
	else
		return QGraphicsItem::itemChange(change, value);
}


Pin *CircuitElement::addPort(bool inPin){
	Pin *port = new Pin(inPin,this);
	int y = height / 2 + boundingRect().y();

	if (inPin)
		port->setPos(boundingRect().x()+width+port->boundingRect().width(), y);
	else
		port->setPos(boundingRect().x()-port->boundingRect().width(), y);


	return port;
}

void CircuitElement::showMenu(){
	QMenu contextMenu;
	contextMenu.addAction("Rotate element clockwise", [=](){rotateClockwise();});
	contextMenu.addAction("Rotate element counterclockwise", [=](){rotateClockwise();});
	contextMenu.addAction("Edit proprties");
	contextMenu.exec(QCursor::pos());
}

void CircuitElement::setConnection(CircuitElement *other){
	connections.insert(other);
}

void CircuitElement::removeConnection(CircuitElement *other){
	connections.erase(other);
}

void CircuitElement::rotateClockwise(bool clockwiseDirection){
	qreal angle;
	if(clockwiseDirection)
		angle = rotation()+90;
	else
		angle = rotation()-90;

	setRotation(angle);
}
