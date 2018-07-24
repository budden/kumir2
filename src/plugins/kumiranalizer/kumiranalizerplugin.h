#ifndef KUMIRANALIZERPLUGIN_H
#define KUMIRANALIZERPLUGIN_H

#include <kumir2-libs/extensionsystem/kplugin.h>
#include <kumir2/analizerinterface.h>
#include <kumir2-libs/extensionsystem/pluginspec.h>

#include <QtCore/QLocale>
#include <QtCore/QStringList>

namespace KumirAnalizer {

class Analizer;
class KumFileHandler;
class QuickReferenceWidget;

class KumirAnalizerPlugin :
	public ExtensionSystem::KPlugin,
	public Shared::AnalizerInterface
{
	Q_OBJECT
#if QT_VERSION >= 0x050000
	Q_PLUGIN_METADATA(IID "kumir2.KumirAnalizer")
#endif
	Q_INTERFACES(Shared::AnalizerInterface)
	friend class AnalizerPrivate;
public:
	Shared::Analizer::InstanceInterface* createInstance();
	Shared::Analizer::SourceFileInterface* sourceFileHandler();

	KumirAnalizerPlugin();
	~KumirAnalizerPlugin();

	QList<ExtensionSystem::CommandLineParameter> acceptableCommandLineParameters() const {
		return QList<ExtensionSystem::CommandLineParameter>();
	}

	bool primaryAlphabetIsLatin() const { return false; }
	bool caseInsensitiveGrammatic() const { return false; }
	bool supportPartialCompiling() const { return true; }
	Shared::IndentsBehaviour indentsBehaviour() const { return Shared::HardIndents; }
	Shared::SyntaxHighlightBehaviour syntaxHighlightBehaviour() const {
		return Shared::IndependentLinesHighlight;
	}

	QWidget* languageQuickReferenceWidget();

	QString defaultDocumentFileNameSuffix() const { return "kum"; }
	QString languageName() const { return QString::fromUtf8("Кумир"); }
	QByteArray asciiLanguageIdentifier() const { return "kumir"; }
	void updateSettings(const QStringList &) {}

protected:
	void createPluginSpec();
	QString initialize(
		const QStringList &configurationArguments,
		const ExtensionSystem::CommandLine &runtimeArguments
	);
	void start();
	void stop();

private:
	QVector<Analizer*> analizers_;
	bool teacherMode_;
	KumFileHandler* kumFileHandler_;
	QuickReferenceWidget* _quickReferenceWidget;

};

}

#endif
