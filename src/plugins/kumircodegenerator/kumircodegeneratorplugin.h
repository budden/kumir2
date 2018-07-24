#ifndef KUMIRCODEGENERATORPLUGIN_H
#define KUMIRCODEGENERATORPLUGIN_H

#include <kumir2-libs/extensionsystem/kplugin.h>
#include <kumir2/generatorinterface.h>

namespace KumirCodeGenerator {

class KumirCodeGeneratorPlugin :
	public ExtensionSystem::KPlugin,
	public Shared::GeneratorInterface
{
	Q_OBJECT
#if QT_VERSION >= 0x050000
	Q_PLUGIN_METADATA(IID "kumir2.KumirCodeGenerator")
#endif
	Q_INTERFACES(Shared::GeneratorInterface)

public:
	KumirCodeGeneratorPlugin();

	QList<ExtensionSystem::CommandLineParameter> acceptableCommandLineParameters() const;

	void setDebugLevel(Shared::DebugLevel debugLevel);
	void generateExecutable(
		AST::DataPtr tree,
		QByteArray &out,
		QString &mimeType,
		QString &fileSuffix
	);

	void setOutputToText(bool flag);
	void setVerbose(bool) {}
	void setTemporaryDir(const QString &, bool ) {}
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
	class Generator *d;
	bool textMode_;
};

}

#endif // KUMIRCODEGENERATORPLUGIN_H
