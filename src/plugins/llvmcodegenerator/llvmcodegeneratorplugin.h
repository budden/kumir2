#ifndef LLVMCODEGENERATORPLUGIN_H
#define LLVMCODEGENERATORPLUGIN_H

#include "extensionsystem/kplugin.h"
#include "interfaces/generatorinterface.h"

#include <QObject>

namespace LLVMCodeGenerator {

class LLVMCodeGeneratorPlugin
        : public ExtensionSystem::KPlugin
        , public Shared::GeneratorInterface
{
    Q_OBJECT
    Q_INTERFACES(Shared::GeneratorInterface)

public:
    LLVMCodeGeneratorPlugin();
    ~LLVMCodeGeneratorPlugin();

    QList<ExtensionSystem::CommandLineParameter> acceptableCommandLineParameters() const;

    void setDebugLevel(DebugLevel debugLevel);
    void generateExecuable(
                const AST::DataPtr tree,
                QByteArray & out,
                QString & mimeType,
                QString & fileSuffix
                );

    void setOutputToText(bool flag);
    inline void setVerbose(bool) {}
    inline void setTemporaryDir(const QString &, bool ) {}
    inline void updateSettings(const QStringList &) {}

protected:
    QString initialize(const QStringList &configurationArguments,
                       const ExtensionSystem::CommandLine &runtimeArguments);
    void start();
    void stop();
private:
    class LLVMGenerator * d;

};

} // end namespace

#endif // LLVMCODEGENERATORPLUGIN_H
