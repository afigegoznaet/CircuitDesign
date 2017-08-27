#ifndef ENDPOINT_H
#define ENDPOINT_H
#include "circuitelement.h"

class EndPoint : public CircuitElement
{
	static bool start;
	bool startPoint;
public:
	bool isStartingPoint() const {return startPoint;}
	EndPoint(QGraphicsItem *parent = 0);
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
};


#endif // ENDPOINT_H
