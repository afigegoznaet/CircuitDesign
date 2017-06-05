#include "wire.h"
#include "pin.h"
/*
#include <QBrush>
#include <QPen>
#include <QGraphicsScene>
 */

#include <QDebug>

Wire::Wire(QGraphicsItem *parent) : QGraphicsPathItem(parent)
{
	setPen(QPen(Qt::black, 2));
	setBrush(Qt::NoBrush);
	setZValue(-1);
	pin1 = 0;
	pin2 = 0;

}

Wire::~Wire()
{
	if (pin1)
		pin1->connections().remove(pin1->connections().indexOf(this));
	if (pin2)
		pin2->connections().remove(pin2->connections().indexOf(this));
}

void Wire::setPos1(const QPointF &p)
{
	pos1 = p;
}

void Wire::setPos2(const QPointF &p)
{
	pos2 = p;
}

void Wire::setPort1(Pin *p)
{
	pin1 = p;

	pin1->connections().append(this);
}

void Wire::setPort2(Pin *p)
{
	pin2 = p;

	pin2->connections().append(this);
}

void Wire::updatePosFromPorts()
{
	pos1 = pin1->scenePos();
	pos2 = pin2->scenePos();
}

void Wire::updatePath(){
	QPainterPath p;

	//QPointF pos1(m_port1->scenePos());
	//QPointF pos2(m_port2->scenePos());

	p.moveTo(pos1);

	qreal dx = pos2.x() - pos1.x();
	qreal dy = pos2.y() - pos1.y();

	QPointF ctr1(pos1.x() + dx * 0.25, pos1.y() + dy * 0.1);
	QPointF ctr2(pos1.x() + dx * 0.75, pos1.y() + dy * 0.9);

	//p.cubicTo(ctr1, ctr2, pos2);

	p.lineTo(pos1.x()+dx/2, pos1.y());//pos1.y()+dy/2
	p.lineTo(pos1.x()+dx/2, pos2.y());
	p.lineTo(pos2.x(), pos2.y());

	qDebug()<<pos1;
	qDebug()<<pos2;

	setPath(p);
}

