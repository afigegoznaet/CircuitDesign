#include "resistor.h"

Resistor::Resistor(QGraphicsItem *parent):
	CircuitElement((ElectricProps)V_I | R | Z, parent){}

Resistor* Resistor::clone(){
	return new Resistor(*this);
}

void Resistor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	painter->setPen(QPen(Qt::black, 2));
	QRectF rect = boundingRect();
	qreal midHeight = (rect.height() - rect.top()) / 2;
	QPoint source(rect.left(), midHeight);
	QPoint dest(rect.left()+rect.width()/4, midHeight);
	painter->drawLine(source, dest);//pin 1

	source.setX( dest.x() );
	source.setY( rect.top()+9 );
	dest.setX(rect.right() - rect.width()/4);
	dest.setY( rect.bottom()-9 );

	painter->drawRect(QRectF(source, dest)); //draw resistor

	source.setY(midHeight);
	dest.setY(midHeight);
	source.setX(dest.x() );
	dest.setX( rect.right());

	painter->drawLine(source, dest);//pin 2
	CircuitElement::paint(painter,option,widget);
}
