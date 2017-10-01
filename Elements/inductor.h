#ifndef INDUCTOR_H
#define INDUCTOR_H
#include "circuitelement.h"

class Inductor : public CircuitElement
{
public:
	Inductor(QGraphicsItem *parent = 0);
	Inductor(const Inductor&) : CircuitElement((ElectricProps)V_I | L){}
	void paint(	QPainter *painter, const QStyleOptionGraphicsItem *option,
				QWidget *widget = Q_NULLPTR) override;
	Inductor* clone() override;
};

#endif // INDUCTOR_H
