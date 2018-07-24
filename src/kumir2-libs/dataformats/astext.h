#ifndef ASTEXT_H
#define ASTEXT_H

#include <QSharedPointer>

namespace AST {
struct Data;
typedef QSharedPointer<Data> DataPtr;
typedef QSharedPointer<const Data> DataCPtr;
}

#endif // ASTEXT_H
