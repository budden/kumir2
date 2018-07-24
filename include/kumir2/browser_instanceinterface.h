#ifndef BROWSER_INSTANCEINTERFACE_H
#define BROWSER_INSTANCEINTERFACE_H

#include "startpage_widget_interface.h"
#include <QMap>
#include <QVariantList> // typedef
class QWidget;
class QUrl;

namespace Shared { namespace Browser {

class InstanceInterface : public StartpageWidgetInterface
{
public:
	typedef QMap<QString, QObject*> ObjectsMap;

	virtual QWidget* widget() = 0;
	virtual QWidget* startPageWidget() { return widget(); }

	virtual void go(const QUrl &url) = 0;
	virtual void setContent(const QString &data) = 0;
	virtual QUrl currentLocation() const = 0;

	virtual QString title() const = 0;
	virtual QString startPageTitle() const { return title(); }
	virtual void setTitleChangeHandler(
		const QObject *receiver,
		const char *method
	) = 0;
	virtual void setStartPageTitleChangeHandler(
		const QObject *receiver,
		const char *method
	) {
		setTitleChangeHandler(receiver, method);
	}

	virtual void evaluateCommand(const QString &method, const QVariantList &arguments) = 0;
	virtual ObjectsMap& manageableObjects() = 0;

	QObject* & operator[](const QString &objName)
	{
		ObjectsMap &mo = manageableObjects();
		if (!mo.contains(objName))
			mo.insert(objName, nullptr);
		return mo[objName];
	}
};

}}

Q_DECLARE_INTERFACE(Shared::Browser::InstanceInterface, "kumir2.browser.instance")

#endif // BROWSER_INSTANCEINTERFACE_H
