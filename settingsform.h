#ifndef SETTINGSFORM_H
#define SETTINGSFORM_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QItemDelegate>
#include <QtConcurrent/QtConcurrent>
class CircuitElement;
namespace Ui {
class SettingsForm;
}

class SettingsForm : public QWidget
{
	Q_OBJECT

public:
	explicit SettingsForm(CircuitElement *elem, QWidget *parent = 0);
	~SettingsForm();
	void addItem(QString labelText, QString value);

private slots:
	void on_okButton_clicked();

	void on_cancelButton_clicked();

private:
	CircuitElement *elem;
	Ui::SettingsForm *ui;

	void updateElement();
};

#endif // SETTINGSFORM_H
