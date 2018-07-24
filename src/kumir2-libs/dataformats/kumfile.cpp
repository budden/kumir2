#include "kumfile.h"
#ifdef HAS_QCA
# include <QtCrypto/qca.h>
#endif

//Inserts |#%% if needed.
void KumFile::insertTeacherMark(
	Shared::Analizer::Data &data
) {
	static const QRegExp teacherMark("(^|\\n)\\|#%%");
	static const QRegExp speclAlg(QString::fromUtf8("^|\\s*алг\\s*(\\S\\S\\S)?\\s*@"));
	if (data.visibleText.indexOf(teacherMark) >= 0) {
		// qDebug() << " TM POS:" << data.visibleText.indexOf("\n|#%%");
		return;
	}
	if (data.hiddenText.indexOf(teacherMark) >= 0) {
		// qDebug() << " TM POS:" << data.hiddenText.indexOf("\n|#%%");
		return;
	}

	int pos = data.hiddenText.indexOf(speclAlg);
	qDebug() << data.hiddenText;
	if (pos >= 0) {
		data.hiddenText.insert(pos, "\n|#%%\n");
		return;
	}

	pos = data.visibleText.indexOf(speclAlg);
	if (pos > 1) {
		data.visibleText.insert(pos, "\n|#%%\n");
		QStringList strings = data.visibleText.split("\n", QString::KeepEmptyParts);
		for (int i = 0; i < strings.count(); i++) {
			if (strings.at(i).startsWith("|#%%")) {
				data.protectedLineNumbers.insert(i);
				break;
			}
		}
	}
}


bool KumFile::hasCryptographicRoutines()
{
#ifdef HAS_QCA
	return true;
#else
	return false;
#endif
}

void KumFile::generateKeyPair(
	const QString &passPhrase,
	QString &privateKey,
	QString &publicKey
) {
	privateKey.clear();
	publicKey.clear();
#ifdef HAS_QCA
	QCA::PrivateKey seckey = QCA::KeyGenerator().createRSA(1024);
	QCA::SecureArray phrase(passPhrase.toUtf8());
	privateKey = seckey.toPEM(phrase);
	QCA::PublicKey pubkey = seckey.toPublicKey();
	publicKey = pubkey.toPEM();
#else
	Q_UNUSED(passPhrase);
#endif
}

void KumFile::signHiddenText(
	Shared::Analizer::Data &data,
	const QString &privateKey,
	const QString &passPhrase
) {
#ifdef HAS_QCA
	QCA::SecureArray phrase(passPhrase.toUtf8());
	QCA::PrivateKey seckey = QCA::PrivateKey::fromPEM(privateKey, phrase);
	seckey.startSign(QCA::EMSA3_MD5);
	seckey.update(data.hiddenText.trimmed().toUtf8());
	data.hiddenTextSignature = seckey.signature();
#else
	Q_UNUSED(privateKey);
	Q_UNUSED(passPhrase);
	data.hiddenTextSignature.clear();
#endif
}

KumFile::VerifyResult KumFile::verifyHiddenText(
	const Shared::Analizer::Data &data,
	const QString &publicKey
) {
#ifdef HAS_QCA
	if (data.hiddenTextSignature.isEmpty())
		return NoSignature;
	QCA::PublicKey pubkey = QCA::PublicKey::fromPEM(publicKey);
	pubkey.startVerify(QCA::EMSA3_MD5);
	pubkey.update(data.hiddenText.trimmed().toUtf8());
	return pubkey.validSignature(data.hiddenTextSignature) ?
		SignatureMatch : SignatureMismatch;
#else
	Q_UNUSED(data);
	Q_UNUSED(publicKey);
	return CryptographyNotSupported;
#endif
}
