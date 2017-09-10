#ifndef RESISTOR_H
#define RESISTOR_H

#include "circuitelement.h"

class Resistor : public CircuitElement
{
public:
	Resistor(QGraphicsItem *parent = 0);
	Resistor(const Resistor&) : CircuitElement(){}
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
	Resistor* clone();
};

#endif // RESISTOR_H
