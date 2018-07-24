#ifndef GUIINTERFACE_H
#define GUIINTERFACE_H

#include <kumir2/analizer_sourcefileinterface.h>

#include <QString>
#include <QDateTime>
#include <QUrl>
#include <QtPlugin>
class QWidget;

namespace Shared
{

struct ProgramSourceText {
	enum Language { Kumir, Pascal, Python, etc = 255 };

	Language language;
	QDateTime saved;
	QDateTime changed;
	Shared::Analizer::Data content;
	QString title;
	QUrl url;
};

class GuiInterface
{
public slots:
	virtual QObject* pluginObject() = 0;
	virtual QObject* mainWindowObject() = 0;
	virtual void setProgramSource(const ProgramSourceText& source) = 0;
	virtual ProgramSourceText programSource() const = 0;
	virtual int overridenEditorFontSize() const = 0;
	virtual void startTesting() = 0;
};

}

Q_DECLARE_METATYPE(Shared::ProgramSourceText)
Q_DECLARE_INTERFACE(Shared::GuiInterface, "kumir2.Gui")

#endif // GUIINTERFACE_H
