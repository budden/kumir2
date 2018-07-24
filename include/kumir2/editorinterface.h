#ifndef EDITOR_INTERFACE
#define EDITOR_INTERFACE

class QString;
class QIODevice;
class QUrl;
#include <QFont>
#include <QtPlugin>

namespace Shared
{
namespace Editor { class InstanceInterface; }
namespace Analizer {
	class Data;
	class SourceFileInterface;
}

class EditorInterface
{
public:
	virtual QFont defaultEditorFont() const = 0;

	virtual Editor::InstanceInterface *loadDocument(
		QIODevice *device,
		const QString &fileNameSuffix,
		const QString &sourceEncoding,
		const QUrl &sourceUrl, QString *error
	) = 0;

	virtual Editor::InstanceInterface *loadDocument(
		const QString &fileName, QString *error
	) = 0;

	virtual Editor::InstanceInterface *loadDocument(
		const Analizer::Data &data, QString *error
	) = 0;

	virtual Editor::InstanceInterface *newDocument(
		const QString &canonicalLanguageName = "",
		const QString &documentDir = ""
	) = 0;
};

}

Q_DECLARE_INTERFACE(Shared::EditorInterface, "kumir2.editor")

#endif
