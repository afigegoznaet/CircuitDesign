#include "speaker.h"

Speaker::Speaker(QGraphicsItem *parent):
	CircuitElement(parent, SPEAKER)
{
	addPort(false);
	addPort(true);
}

Speaker* Speaker::clone(){
	return new Speaker(*this);
}

void Speaker::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	painter->setPen(QPen(Qt::black, 2));
	QRectF rect = boundingRect();

	QPoint source(rect.left(), rect.top()+30);
	QPoint dest(rect.left()+20, rect.top()+30);
	painter->drawLine(source, dest);//pin 1

	source.setY(rect.top()+50);
	dest.setY(rect.top()+50);
	painter->drawLine(source, dest);//pin 2

	source.setX(dest.x());
	source.setY(rect.top()+20);

	dest.setX(dest.x()+20);
	dest.setY(rect.top()+60);

	painter->drawRect(QRectF(source, dest)); //draw speaker magnet

	source.setX(dest.x());
	dest.setX(dest.x()+20);
	dest.setY(rect.top());
	painter->drawLine(source, dest);//start drawing speaker cone

	source.setX(dest.x());
	source.setY(dest.y());
	dest.setY(rect.bottom());
	painter->drawLine(source, dest);

	source.setX(rect.left()+40);
	source.setY(rect.top()+60);
	painter->drawLine(source, dest);//finish drawing speaker cone

	CircuitElement::paint(painter,option,widget);
}

Pin *Speaker::addPort(bool inPin){
	Pin *port;
	int y = 30 + boundingRect().y();

	if (inPin){
		port = new Pin(!inPin,this);
		port->setPos(boundingRect().x()-port->boundingRect().width(), y);
	}else{
		port = new Pin(inPin,this);
		port->setPos(boundingRect().x()-port->boundingRect().width(), y+20);
	}


	return port;
}
