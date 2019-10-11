#ifndef COURSESINTERFACE_H
#define COURSESINTERFACE_H


class QWidget;
class QAction;
class QMenu;
#include <QObject>
#include <QList>
#include <QStringList>

namespace Shared
{

class CoursesInterface
{
public:
	enum ProgramRunStatus {
		SuccessfullyFinished,
		UserTerminated,
		AbortedOnError
	};

	virtual QWidget* mainWindow() const = 0;
	virtual QAction* actionPerformCheck() const = 0;
	virtual QList<QMenu*> menus() const = 0;

	virtual QStringList getListOfCourses() const { return QStringList(); }
	virtual void activateCourseFromList(QString file) { Q_UNUSED(file); }

public slots:
	virtual void setEnabled(bool value) = 0;
	virtual void setTestingResult(ProgramRunStatus status, int value) = 0;
};

}

Q_DECLARE_INTERFACE(Shared::CoursesInterface, "kumir2.CourseManager")


#endif // COURSESINTERFACE_H
