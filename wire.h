#ifndef WIRE_H
#define WIRE_H

#include <QGraphicsObject>
#include <QGraphicsPathItem>
#include <QGraphicsItem>
#include <QPainter>
#include <QApplication>
#include "gridscene.h"
//#include "pin.h"

enum { CIRC_ELEMENT = QGraphicsItem::UserType, PIN, WIRE };

class Pin;
class SceneEditor;

class Wire : public QGraphicsPathItem
{
public:
	Wire(QGraphicsItem *parent = 0);
	~Wire();

	void setPos1(const QPointF &p);
	void setPos2(const QPointF &p);
	void setPort1(Pin *p);
	void setPort2(Pin *p);
	void updatePosFromPorts();
	void updatePath();

	//void save(QDataStream&);
	//void load(QDataStream&, const QMap<quint64, QNEPort*> &portMap);

	int type() const { return WIRE; }

private:
	QPointF pos1;
	QPointF pos2;
	Pin *pin1;
	Pin *pin2;
friend class Pin;
friend class SceneEditor;
};

#endif // WIRE_H
