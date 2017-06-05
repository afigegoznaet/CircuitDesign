#include "pin.h"
#include "circuitelement.h"

Pin::Pin(bool inPin, QGraphicsItem *parent):
	QGraphicsPathItem(parent),
	parent_(static_cast<CircuitElement*>(parent)){

	QPainterPath p;

	if(inPin)
		p.lineTo(-length,0);
	else
		p.lineTo(length,0);
	setPath(p);

	setPen(QPen(Qt::darkRed, 2));
	//setBrush(Qt::red);

	setFlag(QGraphicsItem::ItemSendsScenePositionChanges);

}

Pin::~Pin(){
	foreach(Wire *conn, m_connections)
		delete conn;
}

bool Pin::isConnected(Pin *other){
	foreach(Wire *conn, m_connections)
		if (conn->pin1 == other || conn->pin2 == other)
			return true;

	return false;
}

QVariant Pin::itemChange(GraphicsItemChange change, const QVariant &value){
	if (change == ItemScenePositionHasChanged){
		foreach(Wire *conn, m_connections){
			conn->updatePosFromPorts();
			conn->updatePath();
		}
	}
	return value;
}

