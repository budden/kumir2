#ifndef RUN_INTERFACE
#define RUN_INTERFACE

#include <QString>
#include <QDateTime>
#include <QPair>
#include <QVariant>
#include <QByteArray>
#include <QtPlugin>

class QAbstractItemModel;
class QTextStream;

namespace Shared {

namespace Analizer {
class HelperInterface;
}

struct RunnableProgram {
	QString sourceFileName;
	QString executableFileName;
	QByteArray executableData;
	QString sourceData;
};

enum StopReason { SR_Done, SR_UserInteraction, SR_InputRequest, SR_Error, SR_UserTerminated };
enum RunMode { RM_StepOver, RM_ToEnd, RM_StepOut, RM_StepIn, RM_Idle, RM_Regular, RM_Blind };

class RunInterface {
public:
	virtual bool hasBreakpointsSupport() const { return false; }
	virtual void setBreakpoint(
		const QString &fileName,
		const quint16 lineNo,
		const QString &condition,
		const quint32 ignoreCount
	) {
		Q_UNUSED(fileName);
		Q_UNUSED(lineNo);
		Q_UNUSED(condition);
		Q_UNUSED(ignoreCount);
	}

	virtual bool loadProgram(const RunnableProgram &sourceInfo) = 0;
	virtual QDateTime loadedProgramVersion() const = 0;

	virtual RunMode currentRunMode() const = 0;
	virtual bool canStepOut() const = 0;
	virtual void runBlind() = 0;
	virtual void runContinuous() = 0;
	virtual void runStepOver() = 0;
	virtual void runStepInto() = 0;
	virtual void runToEnd() = 0;
	virtual void runTesting() = 0;

	virtual void runProgramInCurrentThread(bool useTestingEntryPoint = false) = 0;

	virtual bool isTestingRun() const = 0;
	virtual void terminate() = 0;
	virtual bool hasMoreInstructions() const = 0;
	virtual bool hasTestingEntryPoint() const = 0;
	virtual void terminateAndWaitForStopped() = 0;
	virtual int currentLineNo() const = 0;
	virtual QPair<quint32,quint32> currentColumn() const = 0;
	virtual QString error() const = 0;
	virtual QVariant valueStackTopItem() const = 0;
	virtual unsigned long int stepsCounted() const = 0;
	virtual QAbstractItemModel * debuggerVariablesViewModel() const = 0;

	virtual void setStdInTextStream(QTextStream *) = 0;
	virtual void setStdOutTextStream(QTextStream *) = 0;

	virtual void setSourceHelper(Analizer::HelperInterface *) {}

	virtual void removeAllBreakpoints() {}

	virtual void insertOrChangeBreakpoint(
		bool enabled, const QString &fileName,
		quint32 lineNo, quint32 ignoreCount,
		const QString &condition
	) {
		Q_UNUSED(enabled);
		Q_UNUSED(fileName);
		Q_UNUSED(lineNo);
		Q_UNUSED(ignoreCount);
		Q_UNUSED(condition);
	}

	virtual void insertSingleHitBreakpoint(
		const QString &fileName, quint32 lineNo
	) {
		Q_UNUSED(fileName);
		Q_UNUSED(lineNo);
	}

	virtual void removeBreakpoint(
		const QString &fileName, quint32 lineNo
	) {
		Q_UNUSED(fileName);
		Q_UNUSED(lineNo);
	}

};


}
Q_DECLARE_METATYPE(Shared::StopReason)
Q_DECLARE_INTERFACE(Shared::RunInterface, "kumir2.run")

#endif
