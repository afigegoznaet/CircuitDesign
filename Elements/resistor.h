#ifndef RESISTOR_H
#define RESISTOR_H

#include "circuitelement.h"

class Resistor : public CircuitElement
{
public:
	Resistor(QGraphicsItem *parent = 0);
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
};

#endif // RESISTOR_H
