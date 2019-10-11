#ifndef COURSEMANAGER_COURSEMANAGER_PLUGIN_H
#define COURSEMANAGER_COURSEMANAGER_PLUGIN_H

#include <QObject>
#include <kumir2-libs/extensionsystem/kplugin.h>
#include <kumir2/coursesinterface.h>

class MainWindowTask;
class KumZadanie;
class courseModel;

namespace Widgets {
	class DeclarativeSettingsPage;
}

namespace Shared {
	class ActorInterface;
}

namespace CourseManager
{

class Plugin :
	public ExtensionSystem::KPlugin,
	public Shared::CoursesInterface
{
	Q_OBJECT
#if QT_VERSION >= 0x050000
	Q_PLUGIN_METADATA(IID "kumir2.CourseManager")
#endif
	Q_INTERFACES(Shared::CoursesInterface)

public:
	explicit Plugin();
	QWidget *mainWindow() const;
	QAction *actionPerformCheck() const;
	QWidget *settingsEditorPage();
	QList<QMenu *> menus() const;
	QString getText();
	QList<ExtensionSystem::CommandLineParameter> acceptableCommandLineParameters() const
	{
		QList<ExtensionSystem::CommandLineParameter> params;
		params.append(ExtensionSystem::CommandLineParameter(true, 'w', "work", tr("Work book file"), QVariant::String, false));
		params.append(ExtensionSystem::CommandLineParameter(true, 'c', "classbook", tr("Classbook file"), QVariant::String, false));
		params.append(ExtensionSystem::CommandLineParameter(true, 'o', "output", tr("Output file"), QVariant::String, false));
		return params;
	}

	void setParam(QString paramname, QString param)
	{
		Q_UNUSED(paramname);
		Q_UNUSED(param);
	}
	bool startNewTask(QStringList isps, KumZadanie *task);
	void setPreProgram(QVariant param);
	void startProgram(QVariant param, KumZadanie *task);
	void checkNext(KumZadanie *task);
	void showMW();

	void activateCourseFromList(QString file)
	{
		loadCource(file);
	}
	QStringList getListOfCourses() const;
	void rebuildRescentMenu();
	bool isSafeToQuit();
	void start();

public slots:
	void setEnabled(bool value);
	void setTestingResult(ProgramRunStatus status, int value);
	void nextField();
	void prevField();
	void lockContrls();

private /*methods*/:
	void createPluginSpec();
	void saveSession() const;
	void restoreSession();
	void changeCurrentDirectory(const QString &path);
	void changeGlobalState(
		ExtensionSystem::GlobalState old,
		ExtensionSystem::GlobalState current
	);
	QString initialize(
		const QStringList &configurationArguments,
		const ExtensionSystem::CommandLine &runtimeArguments
	);
	void updateSettings(const QStringList &keys);

private /*fields*/:
	void loadCource(QString file);
	int loadCourseFromConsole(QString wbname, QString cbname);
	int checkTaskFromConsole(int taskID);
	int loadWorkBook(QString wbfilename, QString cbname);
	Shared::ActorInterface *getActor(QString name);
	QWidget *mainWindow_;
	QAction *actionPerformCheck_;
	QAction *nextFld;
	QAction *prevFld;
	Widgets::DeclarativeSettingsPage *settingsEditorPage_;
	QMenu *courseMenu;
	QList<QMenu *> MenuList;
	QMenu *rescentMenu;
	MainWindowTask *MW;
	bool setTextFromFile(QString fname);
	void fixOldKumTeacherMark(QDataStream *ds);//Inserts into start program, techer part marker.
	int isp_no, field_no;
	void selectNext(KumZadanie *task);
	KumZadanie *cur_task;
	bool DISPLAY;
	courseModel *course;
	void showError(QString err);
	QFileInfo cur_courseFileInfo;
	QTextStream  resultStream;
	QFile outFile;
};

} // namespace CourseManager

#endif // COURSEMANAGER_COURSEMANAGER_PLUGIN_H
