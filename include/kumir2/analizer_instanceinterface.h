#ifndef ANALIZER_COMMONINTERFACE_H
#define ANALIZER_COMMONINTERFACE_H


#include "analizer_compilerinterface.h"
#include "analizer_helperinterface.h"

#include "kumir2/lexemtype.h"

class QObject;
#include <QString>
#include <QList>
#include <QVector>
#include <QtPlugin>

#include <string>

namespace Shared {

class AnalizerInterface;

namespace Analizer {

class ASTCompilerInterface;
class ExternalExecutableCompilerInterface;
class HelperInterface;

struct Error
{
	int line; // line number from 0
	int start; // position in line from 0
	int len; // error markup length
	QString message; // error message
	QByteArray msgid;  // internal message id
	QByteArray origin;  // message origin name (PyLint, PyFlakes etc.)
};

typedef QVector<LexemType> LineProp;


class InstanceInterface {
public:
	virtual void setSourceDirName(const QString &path) = 0;
	virtual void setSourceText(const QString &plainText) = 0;
	virtual std::string rawSourceData() const = 0;
	virtual QList<Error> errors() const = 0;
	virtual QList<LineProp> lineProperties() const = 0;
	virtual QList<QPoint> lineRanks() const = 0;
	virtual LineProp lineProp(int lineNo, const QString &text) const = 0;

	virtual bool multipleStatementsInLine(int lineNo) const {
		Q_UNUSED(lineNo);
		return false;
	}

	virtual ASTCompilerInterface* compiler() {
		QObject *me = dynamic_cast<QObject*>(this);
		return me ? qobject_cast<ASTCompilerInterface*>(me) : 0;
	}

	virtual HelperInterface* helper() {
		QObject *me = dynamic_cast<QObject*>(this);
		return me ? qobject_cast<HelperInterface*>(me) : 0;
	}

	virtual ExternalExecutableCompilerInterface* externalToolchain() {
		QObject *me = dynamic_cast<QObject*>(this);
		return me ? qobject_cast<ExternalExecutableCompilerInterface*>(me) : 0;
	}

	virtual void connectUpdateRequest(QObject *receiver, const char *method) {
		Q_UNUSED(receiver); Q_UNUSED(method);
	}

	virtual AnalizerInterface* plugin() = 0;
};


}}

Q_DECLARE_INTERFACE(
	Shared::Analizer::InstanceInterface,
	"kumir2.Analizer.InstanceInterface"
)


#endif // ANALIZER_COMMONINTERFACE_H
