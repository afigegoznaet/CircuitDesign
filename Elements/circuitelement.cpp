#include "circuitelement.h"
#include <QDebug>

CircuitElement::CircuitElement(QGraphicsItem *parent, ElementType specialType):
	QGraphicsItem(parent){

	setFlags(QGraphicsItem::ItemIsSelectable |
			QGraphicsItem::ItemIsMovable
			 | QGraphicsItem::ItemSendsGeometryChanges
			 );

	if(specialType == SPEAKER)
		height=80;
	else{
		addPort(true);
		if(specialType != ENDPOINT)
			addPort(false);
	}
	setTransformOriginPoint(width/2, height/2);
}

void CircuitElement::setPos(const QPointF &pos){

	QPointF newPos((pos));
	qDebug()<<"origPos: "<<pos;
	qDebug()<<"mapto Scene: "<<mapToScene(pos);
	qDebug()<<"mapto Parent: "<<mapToParent(pos);
	qDebug()<<"mapto Item: "<<mapToItem(this, pos);
	qDebug()<<"mapfrom Scene: "<<mapFromScene(pos);
	qDebug()<<"mapfrom Parent: "<<mapFromParent(pos);
	qDebug()<<"mapfrom Item: "<<mapFromItem(this, pos);
	//qDebug()<<"mapto Scene: "<<mapToScene(pos);
	QGraphicsItem::setPos(newPos);
	//QGraphicsItem::setPos(pos);
}

QRectF CircuitElement::boundingRect() const{
	QRectF rect(0,0,width,height);
	return rect;
}

void CircuitElement::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
	painter->setPen(QPen(Qt::green, 1, Qt::DashLine));
	if(isSelected())
		painter->drawRect(boundingRect());

}

QVariant CircuitElement::itemChange(GraphicsItemChange change,
const QVariant &value){
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



void CircuitElement::rotateClockwise(bool clockwiseDirection){

	qreal angle;
	if(clockwiseDirection)
		angle = rotation()+90;
	else
		angle = rotation()-90;

	setRotation(angle);
}
