#include "settingsform.h"
#include "ui_settingsform.h"
#include "Elements/circuitelement.h"

class CustomWidgetItem : public QListWidgetItem{
public:
	CustomWidgetItem(QListWidget* parent = Q_NULLPTR) : QListWidgetItem(parent){

	}

	QLabel* label;
	QLineEdit* edit;
};

SettingsForm::SettingsForm(CircuitElement *elem, QWidget *parent) :
	QWidget(parent),
	elem(elem),
	ui(new Ui::SettingsForm){
	ui->setupUi(this);
	ui->listWidget->setSelectionMode(QAbstractItemView::NoSelection);


	int i=1;
	while (i!=R) {
		switch (elem->props & i) {
		case V_I:
			addItem("Voltage: V", QString::number(elem->voltage));
			addItem("Current: A", QString::number(elem->current));
			break;
		case C:
			addItem("Capacitance: F", QString::number(elem->capacitance));
			break;
		case L:
			addItem("Inductance, H", QString::number(elem->inductance));
			break;
		case Z:
			addItem("Impedance, Z", QString::number(elem->impedance));
			break;
		case R:
			addItem("Resistance", QString::number(elem->resistance));
			break;
		}
		i<<=1;
	}
}

SettingsForm::~SettingsForm(){
	delete ui;
}

void SettingsForm::addItem(QString labelText, QString value){
	auto item = new CustomWidgetItem(ui->listWidget);
	auto listItem = new QWidget(this);
	item->label = new QLabel(labelText, listItem);
	item->edit = new QLineEdit(value, listItem);
	auto layout = new QHBoxLayout(listItem);
	layout->addWidget(item->label);
	layout->addStretch();
	layout->addWidget(item->edit);
	layout->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);
	listItem->setLayout(layout);
	item->setSizeHint(listItem->sizeHint());
	ui->listWidget->addItem(item);
	ui->listWidget->setItemWidget(item, listItem);
}

void SettingsForm::updateElement(){
	int i=1, j=0;
	auto lw = ui->listWidget;
	while (i!=R) {
		CustomWidgetItem* widgetItem = (CustomWidgetItem*)lw->itemWidget(lw->item(j++));
		switch (elem->props & i) {
		case V_I:
			elem->voltage = widgetItem->edit->text().toDouble();
			widgetItem = (CustomWidgetItem*)lw->itemWidget(lw->item(j++));
			elem->current = widgetItem->edit->text().toDouble();
			break;
		case C:
			break;
		case L:
			break;
		case Z:
			break;
		case R:
			break;
		}
		i<<=1;
	}
}


void SettingsForm::on_okButton_clicked(){
	updateElement();
	hide();
	deleteLater();
}

void SettingsForm::on_cancelButton_clicked(){
	hide();
}
