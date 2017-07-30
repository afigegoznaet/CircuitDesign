#include "endpoint.h"

bool EndPoint::end = true;

EndPoint::EndPoint(QGraphicsItem *parent):
	CircuitElement(parent, ENDPOINT){
	//end=true;//static, innitializes only once
	if(end)
		end=false;
}

void EndPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	painter->setPen(QPen(Qt::black, 2));

	QRectF rect = boundingRect();
	qreal midHeight = (rect.height() - rect.top()) / 2;
	int step = rect.height()/4;

	QRectF ellipseRect(rect.left(), rect.top() + step, rect.left()+2*step, rect.top()+2*step);

	painter->drawEllipse(ellipseRect);

	QPoint source(ellipseRect.right(), midHeight);
	QPoint dest(rect.right(), midHeight);
	painter->drawLine(source, dest);//pin

	CircuitElement::paint(painter,option,widget);
}
