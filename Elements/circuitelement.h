#ifndef CIRCUITELEMENT_H
#define CIRCUITELEMENT_H

#include "pin.h"
#include <QMenu>
#include <QGraphicsItem>

class CircuitElement : public QGraphicsItem
{
	//Q_OBJECT
public:
	enum SpecialDrawings{REGULAR, SPEAKER, ENDPOINT};
	explicit CircuitElement(QGraphicsItem *parent = 0, SpecialDrawings specialType=REGULAR);
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)=0;
	virtual QRectF boundingRect() const;
	int type() const { return CIRC_ELEMENT; }
	void setPos(const QPointF &pos);
	void rotateClockwise(bool clockwiseDirection=true);

private:
	QVariant itemChange(GraphicsItemChange change,
							const QVariant &value);
protected:
	virtual Pin* addPort(bool inPin);
	static constexpr int width = 80;
	int height = 40;
	//static constexpr int horzMargin = 20;
	//static constexpr int vertMargin = 5;
};

#endif // CIRCUITELEMENT_H
