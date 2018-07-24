#ifndef BROWSER_INTERFACE
#define BROWSER_INTERFACE

#include <QString>
#include <QMap>
#include <QUrl>
#include <QtPlugin>

namespace Shared
{
namespace Browser {
	class InstanceInterface;
}

class BrowserInterface
{
public:
	typedef QMap<QString, QObject*> ObjectsMap;

	virtual Browser::InstanceInterface* createBrowser(
		const QUrl &url = QUrl(),
		const ObjectsMap manageableObjects = ObjectsMap(),
		bool enableKeyboardNavigation = false
	) = 0;
};

}

Q_DECLARE_INTERFACE(Shared::BrowserInterface, "kumir2.browser")

#endif
