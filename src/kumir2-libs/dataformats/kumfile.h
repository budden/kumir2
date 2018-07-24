#ifndef KUMFILE_KUMFILE_H
#define KUMFILE_KUMFILE_H

#include <QtCore>
#include <kumir2/analizer_sourcefileinterface.h>

#ifdef DATAFORMATS_LIBRARY
#define KUMFILE_EXPORT Q_DECL_EXPORT
#else
#define KUMFILE_EXPORT Q_DECL_IMPORT
#endif

namespace KumFile {

enum VerifyResult {
	SignatureMatch,
	SignatureMismatch,
	NoSignature,
	CryptographyNotSupported
};


KUMFILE_EXPORT void insertTeacherMark(
	Shared::Analizer::Data &data
);

KUMFILE_EXPORT bool hasCryptographicRoutines();
KUMFILE_EXPORT void generateKeyPair(
	const QString &passPhrase,
	QString &privateKey,
	QString &publicKey
);

KUMFILE_EXPORT void signHiddenText(
	Shared::Analizer::Data &data,
	const QString &privateKey,
	const QString &passPhrase
);

KUMFILE_EXPORT VerifyResult verifyHiddenText(
	const Shared::Analizer::Data &data,
	const QString &publicKey
);

} // namespace KumFile


#endif // KUMFILE_KUMFILE_H
