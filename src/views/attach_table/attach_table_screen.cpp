
#if QT_VERSION == 0x050600
#include <wobjectimpl.h>
#endif

#include "attach_table_screen.h"
#include "attach_table_view.h"
#include "controllers/attach_table/attach_table_controller.h"
#include "libraries/global_parameters.h"
#include "libraries/qtm/blogger.h"
#include "main.h"
#include "utility/add_action.h"
#include "views/record/editor_wrap.h"

#include <QToolButton>

extern std::shared_ptr<gl_para> gl_paras;

#if QT_VERSION == 0x050600
W_OBJECT_IMPL(AttachTableScreen)
#endif

AttachTableScreen::AttachTableScreen(Blogger* blogger_, QWidget* parent)
    : QWidget(parent)
    , _tools_line([&]() -> QToolBar* {
	    _tools_line = new QToolBar(this);
	    setupActions();
	    return _tools_line;
    }())
    , _attach_table_crtl(new AttachTableController(blogger_, this))
    , _attach_table_view(_attach_table_crtl->view())
{
	// По факту этот класс - синглтон. Синглтон сам задает себе имя
	this->setObjectName("attachTableScreen");

	//// Создаются действия. Они используются как в данном классе (на кнопках),
	///так и в контекстном меню в AttachTableView
	// setupActions();

	// Инициализируется контроллер списка файлов
	// attachTableController = new AttachTableController(this);
	_attach_table_crtl->setObjectName("attachTableController");

	//	gl_paras->attachtable_controller(attachTableController);

	setupUI();
	setupSignals();
	assembly();
}

AttachTableScreen::~AttachTableScreen()
{
}

// Настройка возможных действий
void AttachTableScreen::setupActions(void)
{
	// Добавление файла
	actionAddAttach =
	    add_action<QToolBar, QAction, AttachTableScreen, AttachTableController>(
		_tools_line, this, tr("Attach file"), tr("Attach file"),
		tr("Attach file"), QIcon(":/resource/pic/attach_add.svg"), [&](bool) {
			_attach_table_crtl->on_add_attach();
		}); // new QAction(tr("Attach file"), this);
	// actionAddAttach->setStatusTip(tr("Attach file"));
	// actionAddAttach->setIcon(QIcon(":/resource/pic/attach_add.svg"));

	// Добавление линка
	actionAddLink =
	    add_action<QToolBar, QAction, AttachTableScreen, AttachTableController>(
		_tools_line, this, tr("Add link"), tr("Add link without file copying"),
		tr("Add link without file copying"),
		QIcon(":/resource/pic/attach_add_link.svg"), [&](bool) {
			_attach_table_crtl->on_add_link();
		}); // new QAction(tr("Attach file"), this);// new QAction(tr("Add
		    // link"), this);
	// actionAddLink->setStatusTip(tr("Add link without file copying"));
	// actionAddLink->setIcon(QIcon(":/resource/pic/attach_add_link.svg"));

	// едактирование информации о файле (имени файла)
	actionEditFileName =
	    add_action<QToolBar, QAction, AttachTableScreen, AttachTableController>(
		_tools_line, this, tr("Edit file name"), tr("Edit file name"),
		tr("Edit file name"), QIcon(":/resource/pic/attach_edit.svg"),
		[&](bool) {
			_attach_table_crtl->on_edit_file_name();
		}); // new QAction(tr("Edit file name"), this);
	// actionEditFileName->setStatusTip(tr("Edit file name"));
	// actionEditFileName->setIcon(QIcon(":/resource/pic/attach_edit.svg"));

	// Удаление файла
	actionDeleteAttach =
	    add_action<QToolBar, QAction, AttachTableScreen, AttachTableController>(
		_tools_line, this, tr("Delete file"), tr("Delete file"),
		tr("Delete file"), QIcon(":/resource/pic/attach_delete.svg"),
		[&](bool) {
			_attach_table_crtl->on_delete_attach();
		}); // new QAction(tr("Delete file"), this);
	// actionDeleteAttach->setStatusTip(tr("Delete file"));
	// actionDeleteAttach->setIcon(QIcon(":/resource/pic/attach_delete.svg"));

	// Просмотр файла
	actionOpenAttach =
	    add_action<QToolBar, QAction, AttachTableScreen, AttachTableController>(
		_tools_line, this, tr("Preview file"), tr("Preview file"),
		tr("Preview file"), QIcon(":/resource/pic/attach_preview.svg"),
		[&](bool) {
			_attach_table_crtl->on_open_attach();
		}); // new QAction(tr("Preview file"), this);
	// actionOpenAttach->setStatusTip(tr("Preview file"));
	// actionOpenAttach->setIcon(QIcon(":/resource/pic/attach_preview.svg"));

	// Сохранить как... файл
	actionSaveAsAttach =
	    add_action<QToolBar, QAction, AttachTableScreen, AttachTableController>(
		_tools_line, this, tr("Save as..."), tr("Save as..."), tr("Save as..."),
		QIcon(":/resource/pic/attach_save_as.svg"), [&](bool) {
			_attach_table_crtl->on_save_as_attach();
		}); // new QAction(tr("Save as..."), this);
	// actionSaveAsAttach->setStatusTip(tr("Save as..."));
	// actionSaveAsAttach->setIcon(QIcon(":/resource/pic/attach_save_as.svg"));

	// Информация об аттаче
	actionShowAttachInfo =
	    add_action<QToolBar, QAction, AttachTableScreen, AttachTableController>(
		_tools_line, this, tr("Attach info"), tr("Attach info"),
		tr("Attach info"), QIcon(":/resource/pic/attach_info.svg"),
		[&](bool) {
			_attach_table_crtl->on_show_attach_info();
		}); // new QAction(tr("Attach info"), this);
	// actionShowAttachInfo->setStatusTip(tr("Attach info"));
	// actionShowAttachInfo->setIcon(QIcon(":/resource/pic/attach_info.svg"));

	_tools_line->addSeparator();

	// Переключение на редактор
	_action_switch_to_editor =
	    add_action<QToolBar, QAction, AttachTableScreen, AttachTableController>(
		_tools_line, this, tr("Return to editor"), tr("Return to editor"),
		tr("Return to editor"),
		QIcon(":/resource/pic/attach_switch_to_editor.svg"), [&](bool) {
			_attach_table_crtl->on_switch_to_editor();
		}); // new QAction(tr("Return to editor"), this);
		    // actionSwitchToEditor->setStatusTip(tr("Return to editor"));
		    // actionSwitchToEditor->setIcon(QIcon(":/resource/pic/attach_switch_to_editor.svg"));
}

void AttachTableScreen::setupUI(void)
{
	// Создание тулбара
	// toolsLine = new QToolBar(this);

	//// Создание кнопок на тулбаре
	// add_action<QToolButton>(toolsLine, actionAddAttach);
	// add_action<QToolButton>(toolsLine, actionAddLink);
	// add_action<QToolButton>(toolsLine, actionEditFileName);
	// add_action<QToolButton>(toolsLine, actionDeleteAttach);
	// add_action<QToolButton>(toolsLine, actionOpenAttach);
	// add_action<QToolButton>(toolsLine, actionSaveAsAttach);
	// add_action<QToolButton>(toolsLine, actionShowAttachInfo);

	// toolsLine->addSeparator();

	// add_action<QToolButton>(toolsLine, actionSwitchToEditor);
}

void AttachTableScreen::setupSignals(void)
{
	// Связывание действий
	// connect(actionAddAttach, &QAction::triggered, attachTableController,
	// &AttachTableController::on_add_attach);
	// connect(actionAddLink, &QAction::triggered, attachTableController,
	// &AttachTableController::on_add_link);
	// connect(actionEditFileName, &QAction::triggered, attachTableController,
	// &AttachTableController::on_edit_file_name);
	// connect(actionDeleteAttach, &QAction::triggered, attachTableController,
	// &AttachTableController::on_delete_attach);
	// connect(actionOpenAttach, &QAction::triggered, attachTableController,
	// &AttachTableController::on_open_attach);
	// connect(actionSaveAsAttach, &QAction::triggered, attachTableController,
	// &AttachTableController::on_save_as_attach);

	// connect(actionShowAttachInfo, &QAction::triggered, attachTableController,
	// &AttachTableController::on_show_attach_info);

	// connect(actionSwitchToEditor, &QAction::triggered, attachTableController,
	// &AttachTableController::on_switch_to_editor);
}

void AttachTableScreen::assembly(void)
{
	_screen_layout = new QVBoxLayout(); // todo: Добавить this?

	_screen_layout->addWidget(_tools_line);
	_screen_layout->addWidget(_attach_table_crtl->view());

	setLayout(_screen_layout);

	// Границы убираются, так как данный объект будет использоваться как виджет
	QLayout* lt;
	lt = layout();
	lt->setContentsMargins(0, 0, 0, 0);
}

// Очистка таблицы приаттаченных файлов
// Список на экране должен быть пустой
// Вызывается в моменты, когда ни одна запись не выбрана или содержимое записи
// недоступно
void AttachTableScreen::clear()
{
	_attach_table_crtl->attach_table_data(nullptr);
}

AttachTableController* AttachTableScreen::attach_table_ctrl() { return _attach_table_crtl; }
