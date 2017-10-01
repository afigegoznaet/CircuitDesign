#ifndef CAPACITOR_H
#define CAPACITOR_H
#include "circuitelement.h"

class Capacitor : public CircuitElement
{
public:
	Capacitor(QGraphicsItem *parent = 0);
	Capacitor(const Capacitor&) : CircuitElement((ElectricProps)V_I | C){}
	void paint(	QPainter *painter, const QStyleOptionGraphicsItem *option,
				QWidget *widget = Q_NULLPTR) override;
	Capacitor* clone() override;
};

#endif // CAPACITOR_H
