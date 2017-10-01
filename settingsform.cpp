#include "settingsform.h"
#include "ui_settingsform.h"
#include "Elements/circuitelement.h"

class CustomWidgetItem : public QWidget{
public:
	CustomWidgetItem(QWidget* parent = Q_NULLPTR) : QWidget(parent){

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
	auto itemWidget = new QListWidgetItem(ui->listWidget);

	auto listItem = new CustomWidgetItem(this);
	listItem->label = new QLabel(labelText, listItem);
	listItem->edit = new QLineEdit(value, listItem);
	auto layout = new QHBoxLayout(listItem);
	layout->addWidget(listItem->label);
	layout->addStretch();
	layout->addWidget(listItem->edit);
	layout->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);
	listItem->setLayout(layout);
	itemWidget->setSizeHint(listItem->sizeHint());
	ui->listWidget->addItem(itemWidget);
	ui->listWidget->setItemWidget(itemWidget, listItem);
	qDebug()<<"item widget: "<<itemWidget;
	qDebug()<<"List item: "<<listItem;
}

void SettingsForm::updateElement(){

	int i=1, j=0;
	auto lw = ui->listWidget;
	for(int i=0;i<lw->model()->rowCount(lw->rootIndex());i++){
		auto widgetItem = lw->itemWidget(lw->item(i));
		qDebug()<<lw->item(i);
		qDebug()<<widgetItem;
	}
	while (i!=R && j<lw->model()->rowCount(lw->rootIndex())) {
		CustomWidgetItem* listItem = (CustomWidgetItem* )lw->itemWidget(lw->item(j++));
		qDebug()<<"List item: "<<listItem;
		switch (elem->props & i) {
		case V_I:
			elem->voltage = listItem->edit->text().toDouble();
			listItem = (CustomWidgetItem* )lw->itemWidget(lw->item(j++));
			elem->current = listItem->edit->text().toDouble();
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
	//deleteLater();
}

void SettingsForm::on_cancelButton_clicked(){
	hide();
}
