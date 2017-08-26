#ifndef PIN_H
#define PIN_H

//#include "circuitelement.h"
#include "wire.h"
#include <set>
#include <memory>

class CircuitElement;
class SceneEditor;

class Pin : public QGraphicsPathItem
{
public:
	Pin(bool inPin, QGraphicsItem *parent = 0);
	~Pin();

	QVector<Wire*>& connections(){return wireConnections;}
	bool isConnected(Pin*);
	int type() const { return PIN; }

protected:
	QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
	CircuitElement *parent_;
	static constexpr int length = 10;
	QVector<Wire*> wireConnections;
	void setConnection(Pin* other);
	//std::set<Pin*> pinConnections;
friend class SceneEditor;
};

#endif // PIN_H
