#ifndef __EDITORCONFIG_H__
#define __EDITORCONFIG_H__

#include <QObject>
#include <QSettings>
#include <QWidget>
#include <memory>

#include <QtGlobal>
#if QT_VERSION == 0x050600
#include <QObject>
#include <wobjectdefs.h>
#endif

class EditorConfig : public QWidget {
#if QT_VERSION == 0x050600
	W_OBJECT(EditorConfig)
#else
	Q_OBJECT
#endif

	public:
	EditorConfig(std::shared_ptr<QSettings> topic_editor_config_, QWidget *parent = 0);
	~EditorConfig();

	// Настройка стандартного шрифта
	QString get_default_font(void);
	void set_default_font(QString fontName);

	int get_default_font_size(void);
	void set_default_font_size(int size);

	// Настройка моноширинного шрифта
	QString get_monospace_font(void);
	void set_monospace_font(QString fontName);

	int get_monospace_font_size(void);
	void set_monospace_font_size(int size);
	bool get_monospace_font_size_apply(void);
	void set_monospace_font_size_apply(bool i);

	// Настройка шрифта форматирования кода
	QString get_code_font(void);
	void set_code_font(QString fontName);

	int get_code_font_size(void);
	void set_code_font_size(int size);
	bool get_code_font_size_apply(void);
	void set_code_font_size_apply(bool i);
	QString get_code_font_color(void);
	void set_code_font_color(QString color);

	int get_code_indent_size(void);
	void set_code_indent_size(int size);
	bool get_code_indent_size_apply(void);
	void set_code_indent_size_apply(bool i);

	// Шаг изменения отступа
	int get_indent_step(void);
	void set_indent_step(int i);

	QString get_finddialog_geometry(void);
	void set_finddialog_geometry(QString geometry);

	// Настройка первой линии с кнопками инструментов
	QString tools_line_0(void);
	void tools_line_0(QString geometry);

	// Настройка второй линии с кнопками инструментов
	QString tools_line_1(void);
	void tools_line_1(QString geometry);

	// аскрыты или сомкнуты панели инструментов
	bool get_expand_tools_lines(void);
	void set_expand_tools_lines(bool i);

	private:
	std::shared_ptr<QSettings> _editor_conf;

	QString get_parameter(QString name);

	int get_config_version(void);
	void set_config_version(int i);

	void update_version_process(void);

	QStringList get_parameter_table_1(bool withEndSignature = true);
	QStringList get_parameter_table_2(bool withEndSignature = true);
	QStringList get_parameter_table_3(bool withEndSignature = true);
	QStringList get_parameter_table_4(bool withEndSignature = true);
	QStringList get_parameter_table_5(bool withEndSignature = true);
	QStringList get_parameter_table_6(bool withEndSignature = true);
	QStringList get_parameter_table_7(bool withEndSignature = true);
	QStringList get_parameter_table_8(bool withEndSignature = true);

	QStringList remove_option(QStringList table, QString optionName);

	QString update_version_allowcollision(int versionFrom, int versionTo, QString name, QString fromType, QString fromValue, QString toType, QString toValue);

	QString update_version_change_value(int versionFrom, int versionTo, QString name, QString fromValue, QString toValue);

	void update_version(int versionFrom, int versionTo, QStringList baseTable, QStringList finalTable);
};

#endif  // __EDITORCONFIG_H__
