#ifndef SCENEEDITOR_H
#define SCENEEDITOR_H

#include <QObject>

class SceneEditor : public QObject
{
	Q_OBJECT
public:
	explicit SceneEditor(QObject *parent = nullptr);

signals:

public slots:
};

#endif // SCENEEDITOR_H