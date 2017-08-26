#ifndef CAPACITOR_H
#define CAPACITOR_H
#include "circuitelement.h"

class Capacitor : public CircuitElement
{
public:
	Capacitor(QGraphicsItem *parent = 0);
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
};

#endif // CAPACITOR_H
