#ifndef CIRCUITELEMENT_H
#define CIRCUITELEMENT_H

#include <QGraphicsObject>
#include <QPainter>
#include <QApplication>
#include "gridscene.h"

class CircuitElement : public QGraphicsObject
{
	Q_OBJECT
public:
	explicit CircuitElement(QGraphicsItem *parent = 0);
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
	virtual QRectF boundingRect() const;
private:
	QVariant itemChange(GraphicsItemChange change,
							const QVariant &value);
};

#endif // CIRCUITELEMENT_H
