#ifndef SPEAKER_H
#define SPEAKER_H
#include "circuitelement.h"


class Speaker : public CircuitElement
{
public:
	Speaker(QGraphicsItem *parent = 0);
	Speaker(const Speaker&) : CircuitElement((ElectricProps)V_I | R){}
	void paint(	QPainter *painter, const QStyleOptionGraphicsItem *option,
				QWidget *widget = Q_NULLPTR) override;
protected:
	Pin* addPort(bool inPin) override;
	Speaker* clone() override;
};
#endif // SPEAKER_H
