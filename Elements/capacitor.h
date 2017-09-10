#ifndef CAPACITOR_H
#define CAPACITOR_H
#include "circuitelement.h"

class Capacitor : public CircuitElement
{
public:
	Capacitor(QGraphicsItem *parent = 0);
	Capacitor(const Capacitor&) : CircuitElement(){}
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
	Capacitor* clone();
};

#endif // CAPACITOR_H
