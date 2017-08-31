#ifndef INDUCTOR_H
#define INDUCTOR_H
#include "circuitelement.h"

class Inductor : public CircuitElement
{
public:
	Inductor(QGraphicsItem *parent = 0);
	Inductor(const Inductor&){};
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
	Inductor* clone();
};

#endif // INDUCTOR_H
