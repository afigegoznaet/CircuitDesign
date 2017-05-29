#include "circuitelement.h"

CircuitElement::CircuitElement(QGraphicsItem *parent):
	QGraphicsObject(parent){

	setFlags(QGraphicsItem::ItemIsSelectable |
			QGraphicsItem::ItemIsMovable |
			QGraphicsItem::ItemSendsGeometryChanges);
}


QRectF CircuitElement::boundingRect() const{
	QRectF rect(0,0,100,50);
	return rect;
}

void CircuitElement::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	painter->setBrush(Qt::green);
	painter->drawRect(boundingRect());
}

QVariant CircuitElement::itemChange(GraphicsItemChange change,
const QVariant &value)
{
	if (change == ItemPositionChange && scene()) {
		QPointF newPos = value.toPointF();
		if(QApplication::mouseButtons() == Qt::LeftButton &&
				qobject_cast<GridScene*> (scene())){
			GridScene* customScene = qobject_cast<GridScene*> (scene());
			int gridSize = customScene->getGridSize();
			qreal xV = round(newPos.x()/gridSize)*gridSize;
			qreal yV = round(newPos.y()/gridSize)*gridSize;
			return QPointF(xV, yV);
		}
		else
			return newPos;
	}
	else
		return QGraphicsItem::itemChange(change, value);
}
