#ifndef SCENEEDITOR_H
#define SCENEEDITOR_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QMessageBox>
#include "clipboard.h"
#include "Elements/endpoint.h"
#include "Elements/capacitor.h"
#include "Elements/inductor.h"
#include "Elements/resistor.h"
#include "Elements/speaker.h"

class SceneEditor : public QObject
{
	Q_OBJECT
public:
	explicit SceneEditor(QObject *parent = nullptr);
	void install(QGraphicsScene *scene);
	bool eventFilter(QObject *, QEvent *);
	~SceneEditor(){ClipBoard::getRidOfInstance();}
private slots:
	void contextMenuRequested(const QPoint &pos);
signals:
	void clipboardContentsEnabled(bool);

private:
	QGraphicsItem *itemAt(const QPointF&);
	void showMenu(CircuitElement*elem);
	void createMenus();
	void insertElement(ElementType type);
	void disposeSelectedItems();

private:
	QGraphicsScene *scene;
	Wire *conn;
	QMenu* sceneContextMenu;
	QMenu* itemContextMenu;
	ClipBoard* clipboard;
};

#endif // SCENEEDITOR_H
