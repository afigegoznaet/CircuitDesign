#ifndef RESISTOR_H
#define RESISTOR_H

#include "circuitelement.h"

class Resistor : public CircuitElement
{
public:
	Resistor(QGraphicsItem *parent = 0);
	Resistor(const Resistor&) : CircuitElement((ElectricProps)V_I | R | Z){}
	void paint(	QPainter *painter, const QStyleOptionGraphicsItem *option,
				QWidget *widget = Q_NULLPTR) override;
	Resistor* clone() override;
};

#endif // RESISTOR_H
