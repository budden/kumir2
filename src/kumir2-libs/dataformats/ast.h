#ifndef AST_H
#define AST_H

#include "ast_module.h"
#include "astext.h"

#include <QList>
#include <QDateTime>

#undef ABSTRACTSYNTAXTREE_EXPORT
#ifdef DATAFORMATS_LIBRARY
#define ABSTRACTSYNTAXTREE_EXPORT Q_DECL_EXPORT
#else
#define ABSTRACTSYNTAXTREE_EXPORT Q_DECL_IMPORT
#endif

namespace AST {


struct ABSTRACTSYNTAXTREE_EXPORT Data
{
	QList<ModulePtr> modules;
	QDateTime lastModified;

	explicit Data();
	explicit Data(DataPtr src);

	AST::ModulePtr findModuleByType(ModuleType moduleType) const;
};


}

#endif // AST_H
