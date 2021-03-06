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
	EndPoint(const EndPoint&) : CircuitElement(V_I){}
	void paint(	QPainter *painter, const QStyleOptionGraphicsItem *option,
				QWidget *widget = Q_NULLPTR) override;
	EndPoint* clone() override;
};


#endif // ENDPOINT_H
