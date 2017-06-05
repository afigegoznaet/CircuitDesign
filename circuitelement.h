#ifndef CIRCUITELEMENT_H
#define CIRCUITELEMENT_H

#include "pin.h"
#include <QGraphicsItem>

class CircuitElement : public QGraphicsItem
{
	//Q_OBJECT
public:
	explicit CircuitElement(QGraphicsItem *parent = 0);
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR)=0;
	virtual QRectF boundingRect() const;
	int type() const { return CIRC_ELEMENT; }
	void setPos(const QPointF &pos);

private:
	QVariant itemChange(GraphicsItemChange change,
							const QVariant &value);
	Pin* addPort(bool inPin);
	static constexpr int width=80;
	static constexpr int height=40;
	static constexpr int horzMargin = 20;
	static constexpr int vertMargin = 5;
};

#endif // CIRCUITELEMENT_H
