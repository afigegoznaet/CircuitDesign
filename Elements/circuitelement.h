#ifndef CIRCUITELEMENT_H
#define CIRCUITELEMENT_H

#include "pin.h"
#include <QMenu>
#include <QGraphicsItem>
#include <QDebug>

enum ElementType{DUMMY, CAPACITOR, INDUCTOR, RESISTOR, SPEAKER, ENDPOINT};
enum ElectricProp{V_I=1/*applicable to all*/,
				   C=2/*capacitance*/,
				   H=4/*inductance*/,
				   Z=8/*impedance*/,
				   R=16/*resistance*/};
Q_DECLARE_FLAGS(ElectricProps, ElectricProp)
class CircuitElement : public QGraphicsItem
{
	//Q_OBJECT
public:
	CircuitElement(ElectricProps props, QGraphicsItem *parent = 0, ElementType specialType=DUMMY);
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)=0;
	virtual QRectF boundingRect() const;
	int type() const { return CIRC_ELEMENT; }
	void setPos(const QPointF &pos);
	void rotateClockwise(bool clockwiseDirection=true);
	virtual CircuitElement* clone()=0;
	virtual void edit();
private:
	QVariant itemChange(GraphicsItemChange change,
							const QVariant &value);
protected:
	virtual Pin* addPort(bool inPin);
	static constexpr int width = 80;
	int height = 40;
//Electric params
	ElectricProps props;
	double voltage;
	double current;
	double capacitance;
	double inductance;
	double resistance;
	double impedance;//not needed for end-points, needed for pretty much everything else
};

#endif // CIRCUITELEMENT_H
