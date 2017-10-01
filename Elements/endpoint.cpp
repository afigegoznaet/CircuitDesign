#include "endpoint.h"

bool EndPoint::start = true;

EndPoint::EndPoint(QGraphicsItem *parent):
	CircuitElement(V_I, parent, ENDPOINT), startPoint(start){
	//end=true;//static, innitializes only once
	if(start)
		start=false;
}

EndPoint* EndPoint::clone(){
	return new EndPoint(*this);
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
	//QRectF labelRect(4,10,20,20);
	QRectF labelRect(rect.width()/20,rect.width()/8,rect.height()/2,rect.height()/2);
	auto font = painter->font();
	font.setPixelSize(rect.width()/5);
	painter->setFont(font);
	if(startPoint)
		painter->drawText(labelRect, "*");
	else
		painter->drawText(labelRect, "0");

	CircuitElement::paint(painter,option,widget);

}
