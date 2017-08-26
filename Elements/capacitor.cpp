#include "capacitor.h"

Capacitor::Capacitor(QGraphicsItem *parent):
	CircuitElement(parent)
{

}

void Capacitor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	painter->setPen(QPen(Qt::black, 2));

	QRectF rect = boundingRect();
	qreal midHeight = (rect.height() - rect.top()) / 2;
	int step = rect.height()/10;

	QPoint source(rect.left(), midHeight);
	QPoint dest((source.x()+rect.width())/2 - step, midHeight);
	painter->drawLine(source, dest);//pin 1

	source.setX( dest.x() );
	source.setY( rect.top()+step );
	dest.setY( rect.bottom()-step );

	painter->drawLine(source, dest);//plate 1

	source.setX( source.x() + 2*step-1 );
	dest.setX( source.x() );

	painter->drawLine(source, dest);//plate 2

	source.setY(midHeight);
	dest.setY(midHeight);
	dest.setX( rect.right());

	painter->drawLine(source, dest);//pin 2
	CircuitElement::paint(painter,option,widget);
}
