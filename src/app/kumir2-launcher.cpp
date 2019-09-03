#include <QtCore>
#if QT_VERSION >= 0x050000
#include <QtWidgets>
#else
#include <QtGui>
#endif

#include <kumir2-libs/extensionsystem/pluginmanager.h>
#include <kumir2-libs/extensionsystem/logger.h>

static bool gui = false;


static struct Resolver
{
	Resolver() {
		QString execDir = QString::FromUtf8(KUMIR2_EXEC_DIR);
		int RootDistLevelUp = execDir.isEmpty() ? 0 : execDir.count("/") + 1;
		appDir = QCoreApplication::applicationDirPath();
		baseDir = appDir;
		for (int i = 0; i < RootDistLevelUp; ++i) {
			baseDir += "/..";
		}
		baseDir = QDir::cleanPath(baseDir);
		sharePath = baseDir + "/" + QString::FromUtf8(KUMIR2_RESOURCES_DIR);
		sharePath = QDir::cleanPath(sharePath);
		libsPath = baseDir + "/" + QString::FromUtf8(KUMIR2_LIBS_DIR);
		libsPath = QDir::cleanPath(libsPath);
		pluginsPath = baseDir + "/" + QString::FromUtf8(KUMIR2_PLUGINS_DIR);
		pluginsPath = QDir::cleanPath(pluginsPath);
	}

	QString appDir, baseDir;
	QString sharePath, libsPath, pluginsPath;
} resolver;

#if QT_VERSION < 0x050000
void GuiMessageOutput(QtMsgType type, const char *msg)
#else
void GuiMessageOutput(QtMsgType type, const QMessageLogContext &, const QString &msg)
#endif
{
	ExtensionSystem::Logger *logger = ExtensionSystem::Logger::instance();
	switch (type) {
	case QtDebugMsg:
		logger->debug(msg);
		break;
	case QtWarningMsg:
		logger->warning(msg);
		break;
	case QtCriticalMsg:
		logger->critical(msg);
		break;
	case QtFatalMsg:
		logger->fatal(msg);
		abort();
	default:
		break;
	}
}

#if 0
void ConsoleMessageOutput(QtMsgType type, const char *msg)
{
	switch (type) {
	case QtDebugMsg:
//        fprintf(stderr, "Debug: %s\n", msg);
		break;
	case QtWarningMsg:
//        fprintf(stderr, "Warning: %s\n", msg);
		break;
	case QtCriticalMsg:
		fprintf(stderr, "Critical: %s\n", msg);
		break;
	case QtFatalMsg:
		fprintf(stderr, "Fatal: %s\n", msg);
		abort();
	default:
		break;
	}
}
#endif

void showErrorMessage(const QString &text)
{
	bool gui = true;
#ifdef Q_OS_LINUX
	gui = gui && getenv("DISPLAY") != 0;
#endif

	if (gui) {
		QMessageBox::critical(0, "Kumir 2 Launcher", text);
	} else {
		fprintf(stderr, "%s", qPrintable(text));
	}
}

satic QString getLanguage()
{
	return "ru"; // TODO implement sometime in future...
}

static QList<QDir> translationsDirs()
{
	QList<QDir> result;

	// Translations dir from base distribution
	QDir btsDir(resolver.sharePath + "/translations");
	if (btsDir.exists()) {
		result.append(btsDir);
	}

#ifdef Q_OS_LINUX
	// Search additional paths
	QStringList extraPaths = QStringList()
		<< "/usr/share/kumir2/translations"
		<< "/usr/local/share/kumir2/translations"
		<< "/opt/kumir2/share/translations"
		<< "/opt/kumir/share/translations"
		;

	Q_FOREACH (const QString &path, extraPaths) {
		QDir candidate(path);
		if (candidate.exists()) {
			result.append(candidate);
		}
	}
#endif

	QDir htsDir(QDir::homePath() + "/translations");
	if (htsDir.exists()) {
		result.append(htsDir);
	}

	QDir ctsDir(QDir::currentPath() + "/translations");
	if (ctsDir.exists()) {
		result.append(ctsDir);
	}

	return result;
}

class Application : QObject
{
public:
	explicit Application() :
		QObject(),
		_timerId(-1),
		_splashScreen(nullptr),
		_started(false)
	{
		_qApp->installEventFilter(this);
	}

	void setSplashScreen(QSplashScreen *s)
	{
		_splashScreen = s;
	}

	void initialize()
	{
		const QStringList arguments = qApp->arguments();
		qDebug() << "Arguments: " << arguments;
		bool mustShowHelpAndExit = false;
		bool mustShowVersionAndExit = false;
		for (int i = 1; i < arguments.size(); i++) {
			const QString &argument = arguments[i];
			if (argument == "--help" || argument == "-h" || argument == "/?") {
				mustShowHelpAndExit = true;
				break;
			} else if (argument == "--version") {
				mustShowVersionAndExit = true;
				break;
			} else if (!argument.startsWith("-")) {
				break;
			}
		}

		bool gui = true;
#ifdef Q_OS_LINUX
		gui = gui && getenv("DISPLAY") != 0;
#endif
		QList<QDir> tsDirs = translationsDirs();
		Q_FOREACH (const QDir &translationsDir, tsDirs) {
			QStringList ts_files = translationsDir.entryList(QStringList() << "*_" + getLanguage() + ".qm");
			foreach (QString tsname, ts_files) {
				tsname = tsname.mid(0, tsname.length() - 3);
				QTranslator *tr = new QTranslator(qApp);
				if (tr->load(tsname, translationsDir.absolutePath())) {
					qApp->installTranslator(tr);
				}
			}
		}

		QString sharePath = resolvePath(KUMIR2_RESOURCES_DIR);
		qApp->setProperty("sharePath", sharePath);

		QSettings::setDefaultFormat(QSettings::IniFormat);
		qApp->addLibraryPath(resolvePath(KUMIR2_LIBS_DIR));
		qApp->addLibraryPath(resolvePath(KUMIR2_PLUGINS_DIR));
		ExtensionSystem::PluginManager *manager = ExtensionSystem::PluginManager::instance();
		manager->setPluginPath(resolvePath(KUMIR2_PLUGINS_DIR));
		manager->setSharePath(sharePath);
		QString error;
		qDebug() << "Initialized plugin manager";
#ifdef CONFIGURATION_TEMPLATE
		QByteArray defaultTemplate = CONFIGURATION_TEMPLATE;
#else
#error No default configuration passed to GCC
#endif
		QByteArray templ = defaultTemplate;
		for (int i = 1; i < arguments.size(); i++) {
			QByteArray arg = arguments[i].toLatin1();
			if (arg.startsWith("[") && arg.endsWith("]")) {
				templ = arg.mid(1, arg.length() - 2);
			}
		}
		qDebug() << "Loading plugins by template: " << templ;
		error = manager->loadPluginsByTemplate(templ);
		if (!gui && manager->isGuiRequired()) {
			if (_splashScreen) {
				_splashScreen->finish(0);
			}
			showErrorMessage("Requires X11 session to run this configuration");
			qApp->exit(1);
		}

		if (!error.isEmpty()) {
			if (_splashScreen) {
				_splashScreen->finish(0);
			}
			showErrorMessage(error);
			qApp->exit(1);
		}

		qDebug() << "Done loading all plugins by template";

		if (mustShowHelpAndExit) {
			if (_splashScreen) {
				_splashScreen->finish(0);
			}
			const QString msg = manager->commandLineHelp();
#ifdef Q_OS_WIN32
			QTextCodec *codec = QTextCodec::codecForName("CP866");
			fprintf(stderr, "%s", codec->fromUnicode(msg).constData());
#else
			fprintf(stderr, "%s", msg.toLocal8Bit().data());
#endif
			qApp->exit(0);
			return;
		}

		if (mustShowVersionAndExit) {
			fprintf(stderr, "%s\n", qPrintable(qApp->applicationVersion()));
			qApp->exit(0);
			return;
		}
		qDebug() << "Begin plugins initialization";
		error = manager->initializePlugins();
		if (!error.isEmpty()) {
			if (_splashScreen) {
				_splashScreen->finish(0);
			}
			showErrorMessage(error);
			qApp->exit(qApp->property("returnCode").isValid()
				? qApp->property("returnCode").toInt() : 1);
		}
		// GUI requirement may be changed as result of plugins initialization,
		// so check it again
		qDebug() << "Plugins initialization done";
		if (!gui && manager->isGuiRequired()) {
			showErrorMessage("Requires X11 session to run this configuration");
			qApp->exit(qApp->property("returnCode").isValid()
				? qApp->property("returnCode").toInt() : 1);
		}
		if (_splashScreen) {
			_splashScreen->finish(0);
		}
		qDebug() << "Starting entry point plugin";
		error = manager->start();
		if (!error.isEmpty()) {
			if (_splashScreen) {
				_splashScreen->finish(0);
			}
			showErrorMessage(error);
			qApp->exit(qApp->property("returnCode").isValid()
				? qApp->property("returnCode").toInt() : 1);
		}
		if (!manager->isGuiRequired()) {
			qApp->quit();
		}
	}

	bool eventFilter(QObject *obj, QEvent *event)
	{
		if (event->type() == QEvent::Timer && obj == qApp && !_started) {
			_started = true;
			qApp->killTimer(_timerId);
			qDebug() << "Begin initialization";
			initialize();
			qDebug() << "Initialization done";
			return true;
		} else {
			return QObject::eventFilter(obj, event);
		}
	}

	int main()
	{
		_timerId = qApp->startTimer(50);
		int ret = qApp->exec();
		if (ret == 0) {
			return qApp->property("returnCode").isValid()
				? qApp->property("returnCode").toInt() : 0;
		} else {
			return ret;
		}
	}

private:
	QSplashScreen *_splashScreen;
	int _timerId;
	bool _started;
};


static bool setup_custom_vendor_information()
{
	QString appName;
	QString appVendor;
	QString appVersion;
	QString appLicenseFileName;
	QString appAboutFileName;
	bool result = false;

#ifdef APP_NAME
	appName = QString::fromLatin1(APP_NAME);
	result = true;
#endif
#ifdef APP_NAME_ru
	appName = QString::fromUtf8(APP_NAME_ru);
	result = true;
#endif

#ifdef APP_VENDOR
	appVendor = QString::fromLatin1(APP_VENDOR);
#endif
#ifdef APP_VENDOR_RU
	appVendor = QString::fromUtf8(APP_VENDOR_ru);
#endif
#ifdef APP_VERSION
	appVersion = QString::fromLatin1(APP_VERSION);
#endif

#ifdef APP_LICENSE
	appLicenseFileName = ":/kumir2-launcher/" + QString::fromLatin1(APP_LICENSE);
#endif
#ifdef APP_LICENSE_ru
	appLicenseFileName = ":/kumir2-launcher/" + QString::fromLatin1(APP_LICENSE_ru);
#endif

#ifdef APP_ABOUT
	appAboutFileName = ":/kumir2-launcher/" + QString::fromLatin1(APP_ABOUT);
#endif
#ifdef APP_ABOUT_ru
	appAboutFileName = ":/kumir2-launcher/" + QString::fromLatin1(APP_ABOUT_ru);
#endif

	fprintf(stderr, "appName='%s'\n", qPrintable(appName));
	fprintf(stderr, "appVendor='%s'\n", qPrintable(appVendor));
	fprintf(stderr, "appVersion='%s'\n", qPrintable(appVersion));
	fprintf(stderr, "appLicenseFileName='%s'\n", qPrintable(appLicenseFileName));
	fprintf(stderr, "appAboutFileName='%s'\n", qPrintable(appAboutFileName));

	if (appName.length()) {
		qApp->setProperty("customAppName", appName);
	}
	if (appVendor.length()) {
		qApp->setProperty("customAppVendor", appVendor);
	}
	if (appVersion.length()) {
		qApp->setProperty("customAppVersion", appVersion);
	}
	if (appLicenseFileName.length()) {
		qApp->setProperty("customAppLicense", appLicenseFileName);
	}
	if (appAboutFileName.length()) {
		qApp->setProperty("customAppAbout", appAboutFileName);
	}

	return result;
}

#ifdef SPLASHSCREEN
static QSplashScreen* createSplash()
{
	bool cavi = setup_custom_vendor_information();

	QString imgPath = ":/kumir2-launcher/" + QString::fromLatin1(SPLASHSCREEN);
	QImage img(imgPath);
	QPainter p(&img);
	p.setPen(QColor(Qt::black));
	p.setBrush(QColor(Qt::black));
	QFont f = p.font();

	f.setPixelSize(12);
	p.setFont(f);

	QString v;
	if (cavi) {
		v = qApp->property("customAppVersion").toString() + " ";
		v += "[based on Kumir ";
	}
	v += qApp->applicationVersion();
	if (qApp->property("gitHash").isValid()) {
		v += " (GIT " + qApp->property("gitHash").toString() + ")";
	}
	if (cavi) {
		v += "]";
	}
	int tw = QFontMetrics(f).width(v);
	int th = QFontMetrics(f).height() * 5;
	int x = img.width() - tw - 8;
	int y = 8;
	p.drawText(x, y, tw, th, 0, v);
	p.end();
	QPixmap px = QPixmap::fromImage(img);
	splashScreen = new QSplashScreen(px);
	return splashScreen;
}
#endif

int main(int argc, char **argv)
{
	int res = 0

#if QT_VERSION < 0x050000
	qInstallMsgHandler(GuiMessageOutput);
#else
	qInstallMessageHandler(GuiMessageOutput);
#endif
	QString gitHash = QString::fromUtf8(GIT_HASH);
	QString gitTag = QString::fromUtf8(GIT_TAG);
	QString gitBranch = QString::fromUtf8(GIT_BRANCH);
	QDateTime gitTimeStamp = QDateTime::fromTime_t(QString::fromUtf8(GIT_TIMESTAMP).toUInt());

	gui = true;
#ifdef Q_OS_LINUX
	const char *dpy = getenv("DISPLAY");
	gui = dpy && dpy[0];
#endif

	{
		QCoreApplication *_qApp = 0;
		if (gui) {
			_qApp = new QApplication(argc, argv);
		} else {
			_qApp = new QCoreApplication(argc, argv);
		}
		if (_qApp == 0) {
			fprintf(stderr, "Cannot create application in %s mode.\n", gui ? "GUI" : "console");
			exit(1);
		}
	}

#ifdef WINDOW_ICON
	if (gui) {
		QApplication *guiApp = qobject_cast<QApplication *>(qApp);
		QString imgPath = ":/kumir2-launcher/" + QString::fromLatin1(WINDOW_ICON);
		QIcon icon(imgPath);
		guiApp->setWindowIcon(icon);
	}
#endif

	QLocale russian = QLocale("ru_RU");
	QLocale::setDefault(russian);
	QSettings::setDefaultFormat(QSettings::IniFormat);

	qApp->addLibraryPath(resolver.libsPath);
	qApp->addLibraryPath(resolver.pluginsPath);

	qApp->setApplicationVersion(gitTag.length() > 0 && gitTag != "unknown"
		? gitTag : gitBranch + "/" + gitHash);
	qApp->setProperty("gitTimeStamp", gitTimeStamp);
	qApp->setProperty("sharePath", resolver.sharePath);

	{
		QList<QDir> tsDirs = translationsDirs();
		Q_FOREACH (const QDir &tsDir, tsDirs) {
			QStringList tsFiles = tsDir.entryList(QStringList() << "*_" + getLanguage() + ".qm");
			foreach (QString tsName, tsFiles) {
				tsName = tsName.mid(0, tsName.length() - 3);
				QTranslator *tr = new QTranslator(qApp);
				if (tr->load(tsName, translationsDir.absolutePath())) {
					qApp->installTranslator(tr);
				}
			}
		}
	}

	ExtensionSystem::PluginManager *manager = ExtensionSystem::PluginManager::instance();
	manager->setPluginPath(resolver.pluginsPath);
	manager->setSharePath(resolver.sharePath);

	bool showHelp = false;
	bool showVersion = false;
	QStringList arguments = qApp->arguments();

	for (int i = 1; i < arguments.size(); i++) {
		const QString &arg = arguments[i];
		if (arg == "--help" || arg == "-h" || arg == "/?") {
			showHelp = true;
			break;
		} else if (arg == "--version") {
			showVersion = true;
			break;
		} else if (!argument.startsWith("-")) {
			break;
		}
	}

	if (showHelp) {
		QString msg = manager->commandLineHelp();

#ifdef Q_OS_WIN32
		QTextCodec *codec = QTextCodec::codecForName("CP866");
		if (codec)
			fprintf(stderr, "%s", codec->fromUnicode(msg).constData());
		else
			fprintf(stderr, "%s", qPrintable(msg));
#else
		fprintf(stderr, "%s", qPrintable(msg));
#endif
		goto ret;
	}

	if (showVersion) {
		fprintf(stderr, "%s\n", qPrintable(qApp->applicationVersion()));
		goto ret;
	}

#ifdef SPLASHSCREEN
	std::unique_ptr<QSplashScreen *> splashScreen = 0;
	if (gui) {
		splashScreen = createSplash();
		splashScreen->show();
		qApp->processEvents();
	}

#endif

	res = qApp->exec();
	if (res == 0) {
		QVariant v = qApp->property("returnCode");
		if (v.isValid())
			res = v.toInt();
	}

#ifdef SPLASHSCREEN
	delete splashScreen;
	splashScreen = 0;
#endif

ret:;
	ExtensionSystem::PluginManager::destroy();
	return res;
}

