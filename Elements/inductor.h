#ifndef INDUCTOR_H
#define INDUCTOR_H
#include "circuitelement.h"

class Inductor : public CircuitElement
{
public:
	Inductor(QGraphicsItem *parent = 0);
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
};

#endif // INDUCTOR_H
