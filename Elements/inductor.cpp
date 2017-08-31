#include "inductor.h"

Inductor::Inductor(QGraphicsItem *parent):
	CircuitElement(parent)
{

}

Inductor* Inductor::clone(){
	return new Inductor(*this);
}

void Inductor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	painter->setPen(QPen(Qt::black, 2));

	QRectF rect = boundingRect();
	qreal midHeight = (rect.height() - rect.top()) / 2;
	QPoint source(rect.left(), midHeight);
	QPoint dest(rect.left()+rect.width()/8, midHeight);
	painter->drawLine(source, dest);//pin 1

	QRectF rectangle(dest.x(),midHeight/2,midHeight,midHeight);
	int startAngle = 180 * 16;
	int spanAngle = -180 * 16;
	painter->drawArc(rectangle, startAngle, spanAngle);
	rectangle.moveRight(rectangle.right()+midHeight);
	painter->drawArc(rectangle, startAngle, spanAngle);
	rectangle.moveRight(rectangle.right()+midHeight);
	painter->drawArc(rectangle, startAngle, spanAngle);

	source.setX(rectangle.right());
	source.setY(midHeight);
	dest.setY(midHeight);
	dest.setX(rect.right());

	painter->drawLine(source, dest);//pin 2
	CircuitElement::paint(painter,option,widget);
}
