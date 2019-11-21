



#include <QIcon>
#include <QMessageBox>
#include <QSizePolicy>
#include <QTextDocumentFragment>
#include <QTextEdit>
#include <QWidget>
#include <QtDebug>

#include "info_field_enter.h"
#include "main.h"
#include "record_info_fields_editor.h"

#if QT_VERSION == 0x050600
#include <wobjectimpl.h>
#endif

// Окно редактирования информационных полей записи (не текста записи!)
// Оно появляется при двойном клике на записи или при клике на кнопку
// редактирования полей записи

#if QT_VERSION == 0x050600
W_OBJECT_IMPL(InfoFieldsEditor)
#endif

#if QT_VERSION < 0x050000

RecordInfoFieldsEditor::RecordInfoFieldsEditor(QWidget *parent, Qt::WFlags f)
    : QDialog(parent, f)
#else

InfoFieldsEditor::InfoFieldsEditor(QWidget *parent, Qt::WindowFlags f)
    : QDialog(parent, f)
#endif
{
	setupUI();
	setupSignals();
	assembly();
}

InfoFieldsEditor::~InfoFieldsEditor() {
}

void InfoFieldsEditor::setupUI(void) {
	// Ввод инфополей записи
	infoField = new InfoFieldEnter();

	// Кнопки OK и Cancel
	buttonBox = new QDialogButtonBox();
	buttonBox->setOrientation(Qt::Horizontal);
	buttonBox->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::NoButton | QDialogButtonBox::Cancel);

	// На кнопку OK назначается комбинация клавиш Ctrl+Enter
	QPushButton *OkButton = buttonBox->button(
	    QDialogButtonBox::Ok);  // Выясняется указатель на кнопку OK
	OkButton->setShortcut(
	    QKeySequence(Qt::CTRL + Qt::Key_Return));  // Устанавливается шорткат
	OkButton->setToolTip(tr("Ctrl+Enter"));
}

void InfoFieldsEditor::setupSignals(void) {
	connect(buttonBox, &QDialogButtonBox::accepted, this, &InfoFieldsEditor::okClick);
	connect(buttonBox, &QDialogButtonBox::rejected, this, &InfoFieldsEditor::reject);
}

void InfoFieldsEditor::assembly(void) {
	// азмещалка элементов
	QVBoxLayout *layout = new QVBoxLayout();
	layout->setMargin(8);
	layout->setSpacing(10);

	// Добавление элементов в размещалку
	layout->addWidget(infoField);
	layout->addWidget(buttonBox, 0, Qt::AlignRight);

	layout->setSizeConstraint(QLayout::SetFixedSize);

	setLayout(layout);

	// setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));

	// Фокус устанавливается на поле ввода названия записи
	infoField->setFocusToStart();
}

void InfoFieldsEditor::okClick(void) {
	QString message = "";
	// Проверка наличия названия записи
	if (infoField->getField("name").length() == 0)
		message = message + tr("Please enter the note's <b>title</b>.");
	// Если что-то не заполнено, выдается предупреждение
	if (message.length() > 0) {
		QMessageBox::warning(this, tr("The note's fields cannot be modified"), message, QMessageBox::Close);

		return;
	} else
		emit(accept());
}

QString InfoFieldsEditor::getField(QString name) {
	if (infoField->checkFieldName(name) == true)
		return infoField->getField(name);
	else
		critical_error("Can not get field " + name + " in editrecord method get_field");
	return QString();
}

void InfoFieldsEditor::setField(QString name, QString value) {
	if (infoField->checkFieldName(name) == true)
		infoField->setField(name, value);
	else
		critical_error("Can not set field " + name + " in editrecord method set_field");
}
