#ifndef ANALIZER_HELPERINTERFACE_H
#define ANALIZER_HELPERINTERFACE_H

#include <kumir2-libs/dataformats/lexem.h>
#include <kumir2-libs/dataformats/ast.h>

#include <QString>
#include <QList>

namespace Shared { namespace Analizer {

typedef QPair<QString, quint32> TextAppend;

struct Suggestion
{
	enum Kind {
		LocalVariable,
		GlobalVariable,
		Function,
		Module,
		BuiltinModule,
		Statement,
		PrimaryKeyword,
		SecondaryKeyword,
		Other
	};
	Suggestion() {
		kind = Other;
		showOnlyInFullList = false;
	}

	QString value;
	QString description;
	bool showOnlyInFullList;
	Kind kind;
};

struct ApiHelpItem
{
	enum Kind { Empty, Keyword, Module, Function, GlobalVariable };

	QString packageName;
	QString itemName;
	Kind kind;

	ApiHelpItem() : kind(Empty) {}
};

class HelperInterface
{
public:
	virtual QList<Suggestion> suggestAutoComplete(int lineNo, const QString &before, const QString &after) const = 0;
	virtual TextAppend closingBracketSuggestion(int lineNo) const = 0;
	virtual QStringList importModuleSuggestion(int lineNo) const = 0;
	virtual ApiHelpItem itemUnderCursor(const QString &text, int lineNo, int colNo, bool includeRightBound) const = 0;
	virtual QStringList imports() const = 0;
	virtual QString createImportStatementLine(const QString &importName) const = 0;
	virtual QString suggestFileName() const = 0;
	virtual QRegExp lineCommentStartLexemPattern() const = 0;
	virtual void connectSignalImportsChanged(
		QObject *receiver,
		const char *slot
	) {
		Q_UNUSED(receiver);
		Q_UNUSED(slot);
	}
/** Corrects lexem capitalization for case-insensetive grammatics (optional) */
	virtual QString correctCapitalization(
		const QString &name,
		LexemType lxType
	) const {
		Q_UNUSED(lxType);
		return name;
	}

	virtual bool isKnownLexem(
		const QString &lexem,
		int lineNo,
		int colNo,
		const QString &context
	) const {
		Q_UNUSED(lexem);
		Q_UNUSED(lineNo);
		Q_UNUSED(colNo);
		Q_UNUSED(context);
		return false;
	}
};


} }


Q_DECLARE_INTERFACE(Shared::Analizer::HelperInterface,
                    "kumir2.Analizer.HelperInterface")

#endif // ANALIZER_HELPERINTERFACE_H
