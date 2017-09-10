#ifndef SPEAKER_H
#define SPEAKER_H
#include "circuitelement.h"


class Speaker : public CircuitElement
{
public:
	Speaker(QGraphicsItem *parent = 0);
	Speaker(const Speaker&) : CircuitElement(){}
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
protected:
	virtual Pin* addPort(bool inPin);
	Speaker* clone();
};
#endif // SPEAKER_H
