#ifndef PIN_H
#define PIN_H

//#include "circuitelement.h"
#include "wire.h"

class CircuitElement;
class SceneEditor;

class Pin : public QGraphicsPathItem
{
public:
	Pin(bool inPin, QGraphicsItem *parent = 0);
	~Pin();

	QVector<Wire*>& connections(){return m_connections;}
	bool isConnected(Pin*);
	int type() const { return PIN; }

protected:
	QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
	CircuitElement *parent_;
	static constexpr int length = 10;
	QVector<Wire*> m_connections;

friend class SceneEditor;
};

#endif // PIN_H
