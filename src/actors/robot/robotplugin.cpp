#include "robotplugin.h"
#include "robotmodule.h"
#include <kumir2-libs/widgets/declarativesettingspage.h>

namespace ActorRobot {

RobotPlugin::RobotPlugin() :
	ExtensionSystem::KPlugin(),
	module_(nullptr),
	asyncRunThread_(nullptr),
	settingsPage_(nullptr)
{
#ifdef Q_OS_LINUX_NO
	bool hasGuiThread = true;
	hasGuiThread = getenv("DISPLAY") != 0;
#endif
	QObject::connect(
		this, SIGNAL(asyncRun(quint32, QVariantList)),
		this, SLOT(asyncEvaluate(quint32, QVariantList)),
		Qt::DirectConnection
	);
}

QList<ExtensionSystem::CommandLineParameter> RobotPlugin::acceptableCommandLineParameters() const
{
	return RobotModule::acceptableCommandLineParameters();
}

QVariantList RobotPlugin::algOptResults() const
{
	return optResults_;
}

QByteArray RobotPlugin::asciiModuleName() const
{
	return QByteArray("Robot");
}

void RobotPlugin::asyncEvaluate(quint32 index, const QVariantList &args)
{
	Q_UNUSED(args);
	using namespace Shared;
	errorText_.clear();
	result_ = QVariant::Invalid;
	optResults_.clear();
	switch (index) {
		default : {
			errorText_ = "Unknown method index for async evaluation";
		}
	}
	Q_EMIT sync();
}

void RobotPlugin::changeGlobalState(ExtensionSystem::GlobalState old, ExtensionSystem::GlobalState current)
{
	module_->changeGlobalState(old, current);
}

void RobotPlugin::connectSync(QObject* receiver, const char* method)
{
	QObject::connect(this, SIGNAL(sync()), receiver, method, Qt::DirectConnection);
}

void RobotPlugin::createPluginSpec()
{
	_pluginSpec.name = "ActorRobot";
	_pluginSpec.gui = isGuiRequired();
}

QVariant RobotPlugin::customValueFromString(const QByteArray & , const QString & ) const
{
	QVariant result;

	return result;
}

QString RobotPlugin::customValueToString(const QByteArray & , const QVariant & ) const
{
	QString result;

	return result;
}

QVariantList RobotPlugin::defaultTemplateParameters() const
{
	QVariantList result;
	return result;
}

QString RobotPlugin::errorText() const
{
	return errorText_;
}

void RobotPlugin::setError(QString err)
{
	errorText_ = err;
}

const ExtensionSystem::CommandLine& RobotPlugin::commandLineParameters() const
{
	return commandLineParameters_;
}

Shared::EvaluationStatus RobotPlugin::evaluate(quint32 index, const QVariantList & args)
{
	using namespace Shared;
	errorText_.clear();
	result_ = QVariant::Invalid;
	optResults_.clear();
	switch (index) {
		case 0x0000: {
			/* go up */
			module_->runGoUp();
			if (errorText_.length() > 0) {
				return ES_Error;
			}
			return ES_NoResult;
			break;
		}
		case 0x0001: {
			/* go down */
			module_->runGoDown();
			if (errorText_.length() > 0) {
				return ES_Error;
			}
			return ES_NoResult;
			break;
		}
		case 0x0002: {
			/* go left */
			module_->runGoLeft();
			if (errorText_.length() > 0) {
				return ES_Error;
			}
			return ES_NoResult;
			break;
		}
		case 0x0003: {
			/* go right */
			module_->runGoRight();
			if (errorText_.length() > 0) {
				return ES_Error;
			}
			return ES_NoResult;
			break;
		}
		case 0x0004: {
			/* do paint */
			module_->runDoPaint();
			if (errorText_.length() > 0) {
				return ES_Error;
			}
			return ES_NoResult;
			break;
		}
		case 0x0005: {
			/* is wall at top */
			result_ = QVariant::fromValue(module_->runIsWallAtTop());
			if (errorText_.length() > 0) {
				return ES_Error;
			}
			return ES_StackResult;
			break;
		}
		case 0x0006: {
			/* is wall at bottom */
			result_ = QVariant::fromValue(module_->runIsWallAtBottom());
			if (errorText_.length() > 0) {
				return ES_Error;
			}
			return ES_StackResult;
			break;
		}
		case 0x0007: {
			/* is wall at left */
			result_ = QVariant::fromValue(module_->runIsWallAtLeft());
			if (errorText_.length() > 0) {
				return ES_Error;
			}
			return ES_StackResult;
			break;
		}
		case 0x0008: {
			/* is wall at right */
			result_ = QVariant::fromValue(module_->runIsWallAtRight());
			if (errorText_.length() > 0) {
				return ES_Error;
			}
			return ES_StackResult;
			break;
		}
		case 0x0009: {
			/* is free at top */
			result_ = QVariant::fromValue(module_->runIsFreeAtTop());
			if (errorText_.length() > 0) {
				return ES_Error;
			}
			return ES_StackResult;
			break;
		}
		case 0x000a: {
			/* is free at bottom */
			result_ = QVariant::fromValue(module_->runIsFreeAtBottom());
			if (errorText_.length() > 0) {
				return ES_Error;
			}
			return ES_StackResult;
			break;
		}
		case 0x000b: {
			/* is free at left */
			result_ = QVariant::fromValue(module_->runIsFreeAtLeft());
			if (errorText_.length() > 0) {
				return ES_Error;
			}
			return ES_StackResult;
			break;
		}
		case 0x000c: {
			/* is free at right */
			result_ = QVariant::fromValue(module_->runIsFreeAtRight());
			if (errorText_.length() > 0) {
				return ES_Error;
			}
			return ES_StackResult;
			break;
		}
		case 0x000d: {
			/* is Color */
			result_ = QVariant::fromValue(module_->runIsColor());
			if (errorText_.length() > 0) {
				return ES_Error;
			}
			return ES_StackResult;
			break;
		}
		case 0x000e: {
			/* is Clear */
			result_ = QVariant::fromValue(module_->runIsClear());
			if (errorText_.length() > 0) {
				return ES_Error;
			}
			return ES_StackResult;
			break;
		}
		case 0x000f: {
			/* radiation */
			result_ = QVariant::fromValue(module_->runRadiation());
			if (errorText_.length() > 0) {
				return ES_Error;
			}
			return ES_StackResult;
			break;
		}
		case 0x0010: {
			/* temperature */
			result_ = QVariant::fromValue(module_->runTemperature());
			if (errorText_.length() > 0) {
				return ES_Error;
			}
			return ES_StackResult;
			break;
		}
		case 0x0011: {
			/* field size */
			int rows = qvariant_cast<int>(args[0]);
			int cols = qvariant_cast<int>(args[1]);
			module_->runFieldSize(rows, cols);
			optResults_ << QVariant::fromValue(rows);
			optResults_ << QVariant::fromValue(cols);
			if (errorText_.length() > 0) {
				return ES_Error;
			}
			return ES_RezResult;
			break;
		}
		case 0x0012: {
			/* mark */
			int row = qvariant_cast<int>(args[0]);
			int col = qvariant_cast<int>(args[1]);
			result_ = QVariant::fromValue(module_->runMark(row, col));
			optResults_ << QVariant::Invalid;
			optResults_ << QVariant::Invalid;
			if (errorText_.length() > 0) {
				return ES_Error;
			}
			return ES_StackResult;
			break;
		}
		case 0x0013: {
			/* colored */
			int row = qvariant_cast<int>(args[0]);
			int col = qvariant_cast<int>(args[1]);
			result_ = QVariant::fromValue(module_->runColored(row, col));
			optResults_ << QVariant::Invalid;
			optResults_ << QVariant::Invalid;
			if (errorText_.length() > 0) {
				return ES_Error;
			}
			return ES_StackResult;
			break;
		}
		case 0x0014: {
			/* robot pos */
			int row = qvariant_cast<int>(args[0]);
			int col = qvariant_cast<int>(args[1]);
			module_->runRobotPos(row, col);
			optResults_ << QVariant::fromValue(row);
			optResults_ << QVariant::fromValue(col);
			if (errorText_.length() > 0) {
				return ES_Error;
			}
			return ES_RezResult;
			break;
		}
		case 0x0015: {
			/* upChar */
			int row = qvariant_cast<int>(args[0]);
			int col = qvariant_cast<int>(args[1]);
			result_ = QVariant::fromValue(module_->runUpChar(row, col));
			optResults_ << QVariant::Invalid;
			optResults_ << QVariant::Invalid;
			if (errorText_.length() > 0) {
				return ES_Error;
			}
			return ES_StackResult;
			break;
		}
		case 0x0016: {
			/* cellTemp */
			int row = qvariant_cast<int>(args[0]);
			int col = qvariant_cast<int>(args[1]);
			result_ = QVariant::fromValue(module_->runCellTemp(row, col));
			optResults_ << QVariant::Invalid;
			optResults_ << QVariant::Invalid;
			if (errorText_.length() > 0) {
				return ES_Error;
			}
			return ES_StackResult;
			break;
		}
		case 0x0017: {
			/* cellRad */
			int row = qvariant_cast<int>(args[0]);
			int col = qvariant_cast<int>(args[1]);
			result_ = QVariant::fromValue(module_->runCellRad(row, col));
			optResults_ << QVariant::Invalid;
			optResults_ << QVariant::Invalid;
			if (errorText_.length() > 0) {
				return ES_Error;
			}
			return ES_StackResult;
			break;
		}
		case 0x0018: {
			/* downChar */
			int row = qvariant_cast<int>(args[0]);
			int col = qvariant_cast<int>(args[1]);
			result_ = QVariant::fromValue(module_->runDownChar(row, col));
			optResults_ << QVariant::Invalid;
			optResults_ << QVariant::Invalid;
			if (errorText_.length() > 0) {
				return ES_Error;
			}
			return ES_StackResult;
			break;
		}

		default : {
			errorText_ = "Unknown method index";
			return ES_Error;
		}
	}
}

Shared::ActorInterface::FunctionList RobotPlugin::functionList() const
{
	Shared::ActorInterface::FunctionList result;

	/* алг вверх */
	result.push_back(Shared::ActorInterface::Function());
	result.last().id = result.size() - 1;
	result.last().accessType = Shared::ActorInterface::PublicFunction;
	result.last().asciiName = QByteArray("go up");
	result.last().localizedNames[QLocale::Russian] = QString::fromUtf8("вверх");
	result.last().returnType = Shared::ActorInterface::Void;

	/* алг вниз */
	result.push_back(Shared::ActorInterface::Function());
	result.last().id = result.size() - 1;
	result.last().accessType = Shared::ActorInterface::PublicFunction;
	result.last().asciiName = QByteArray("go down");
	result.last().localizedNames[QLocale::Russian] = QString::fromUtf8("вниз");
	result.last().returnType = Shared::ActorInterface::Void;

	/* алг влево */
	result.push_back(Shared::ActorInterface::Function());
	result.last().id = result.size() - 1;
	result.last().accessType = Shared::ActorInterface::PublicFunction;
	result.last().asciiName = QByteArray("go left");
	result.last().localizedNames[QLocale::Russian] = QString::fromUtf8("влево");
	result.last().returnType = Shared::ActorInterface::Void;

	/* алг вправо */
	result.push_back(Shared::ActorInterface::Function());
	result.last().id = result.size() - 1;
	result.last().accessType = Shared::ActorInterface::PublicFunction;
	result.last().asciiName = QByteArray("go right");
	result.last().localizedNames[QLocale::Russian] = QString::fromUtf8("вправо");
	result.last().returnType = Shared::ActorInterface::Void;

	/* алг закрасить */
	result.push_back(Shared::ActorInterface::Function());
	result.last().id = result.size() - 1;
	result.last().accessType = Shared::ActorInterface::PublicFunction;
	result.last().asciiName = QByteArray("do paint");
	result.last().localizedNames[QLocale::Russian] = QString::fromUtf8("закрасить");
	result.last().returnType = Shared::ActorInterface::Void;

	/* алг лог сверху стена */
	result.push_back(Shared::ActorInterface::Function());
	result.last().id = result.size() - 1;
	result.last().accessType = Shared::ActorInterface::PublicFunction;
	result.last().asciiName = QByteArray("is wall at top");
	result.last().localizedNames[QLocale::Russian] = QString::fromUtf8("сверху стена");
	result.last().returnType = Shared::ActorInterface::Bool;

	/* алг лог снизу стена */
	result.push_back(Shared::ActorInterface::Function());
	result.last().id = result.size() - 1;
	result.last().accessType = Shared::ActorInterface::PublicFunction;
	result.last().asciiName = QByteArray("is wall at bottom");
	result.last().localizedNames[QLocale::Russian] = QString::fromUtf8("снизу стена");
	result.last().returnType = Shared::ActorInterface::Bool;

	/* алг лог слева стена */
	result.push_back(Shared::ActorInterface::Function());
	result.last().id = result.size() - 1;
	result.last().accessType = Shared::ActorInterface::PublicFunction;
	result.last().asciiName = QByteArray("is wall at left");
	result.last().localizedNames[QLocale::Russian] = QString::fromUtf8("слева стена");
	result.last().returnType = Shared::ActorInterface::Bool;

	/* алг лог справа стена */
	result.push_back(Shared::ActorInterface::Function());
	result.last().id = result.size() - 1;
	result.last().accessType = Shared::ActorInterface::PublicFunction;
	result.last().asciiName = QByteArray("is wall at right");
	result.last().localizedNames[QLocale::Russian] = QString::fromUtf8("справа стена");
	result.last().returnType = Shared::ActorInterface::Bool;

	/* алг лог сверху свободно */
	result.push_back(Shared::ActorInterface::Function());
	result.last().id = result.size() - 1;
	result.last().accessType = Shared::ActorInterface::PublicFunction;
	result.last().asciiName = QByteArray("is free at top");
	result.last().localizedNames[QLocale::Russian] = QString::fromUtf8("сверху свободно");
	result.last().returnType = Shared::ActorInterface::Bool;

	/* алг лог снизу свободно */
	result.push_back(Shared::ActorInterface::Function());
	result.last().id = result.size() - 1;
	result.last().accessType = Shared::ActorInterface::PublicFunction;
	result.last().asciiName = QByteArray("is free at bottom");
	result.last().localizedNames[QLocale::Russian] = QString::fromUtf8("снизу свободно");
	result.last().returnType = Shared::ActorInterface::Bool;

	/* алг лог слева свободно */
	result.push_back(Shared::ActorInterface::Function());
	result.last().id = result.size() - 1;
	result.last().accessType = Shared::ActorInterface::PublicFunction;
	result.last().asciiName = QByteArray("is free at left");
	result.last().localizedNames[QLocale::Russian] = QString::fromUtf8("слева свободно");
	result.last().returnType = Shared::ActorInterface::Bool;

	/* алг лог справа свободно */
	result.push_back(Shared::ActorInterface::Function());
	result.last().id = result.size() - 1;
	result.last().accessType = Shared::ActorInterface::PublicFunction;
	result.last().asciiName = QByteArray("is free at right");
	result.last().localizedNames[QLocale::Russian] = QString::fromUtf8("справа свободно");
	result.last().returnType = Shared::ActorInterface::Bool;

	/* алг лог клетка закрашена */
	result.push_back(Shared::ActorInterface::Function());
	result.last().id = result.size() - 1;
	result.last().accessType = Shared::ActorInterface::PublicFunction;
	result.last().asciiName = QByteArray("is Color");
	result.last().localizedNames[QLocale::Russian] = QString::fromUtf8("клетка закрашена");
	result.last().returnType = Shared::ActorInterface::Bool;

	/* алг лог клетка чистая */
	result.push_back(Shared::ActorInterface::Function());
	result.last().id = result.size() - 1;
	result.last().accessType = Shared::ActorInterface::PublicFunction;
	result.last().asciiName = QByteArray("is Clear");
	result.last().localizedNames[QLocale::Russian] = QString::fromUtf8("клетка чистая");
	result.last().returnType = Shared::ActorInterface::Bool;

	/* алг вещ радиация */
	result.push_back(Shared::ActorInterface::Function());
	result.last().id = result.size() - 1;
	result.last().accessType = Shared::ActorInterface::PublicFunction;
	result.last().asciiName = QByteArray("radiation");
	result.last().localizedNames[QLocale::Russian] = QString::fromUtf8("радиация");
	result.last().returnType = Shared::ActorInterface::Real;

	/* алг цел температура */
	result.push_back(Shared::ActorInterface::Function());
	result.last().id = result.size() - 1;
	result.last().accessType = Shared::ActorInterface::PublicFunction;
	result.last().asciiName = QByteArray("temperature");
	result.last().localizedNames[QLocale::Russian] = QString::fromUtf8("температура");
	result.last().returnType = Shared::ActorInterface::Int;

	/* алг @@размер поля(рез цел rows, рез цел cols) */
	result.push_back(Shared::ActorInterface::Function());
	result.last().id = result.size() - 1;
	result.last().accessType = Shared::ActorInterface::TeacherModeFunction;
	result.last().asciiName = QByteArray("field size");
	result.last().localizedNames[QLocale::Russian] = QString::fromUtf8("@@размер поля");
	result.last().returnType = Shared::ActorInterface::Void;
	result.last().arguments.push_back(Shared::ActorInterface::Argument());
	result.last().arguments.last().accessType = Shared::ActorInterface::OutArgument;
	result.last().arguments.last().type = Shared::ActorInterface::Int;
	result.last().arguments.last().dimension = 0u;
	result.last().arguments.push_back(Shared::ActorInterface::Argument());
	result.last().arguments.last().accessType = Shared::ActorInterface::OutArgument;
	result.last().arguments.last().type = Shared::ActorInterface::Int;
	result.last().arguments.last().dimension = 0u;

	/* алг лог @@метка(цел row, цел col) */
	result.push_back(Shared::ActorInterface::Function());
	result.last().id = result.size() - 1;
	result.last().accessType = Shared::ActorInterface::TeacherModeFunction;
	result.last().asciiName = QByteArray("mark");
	result.last().localizedNames[QLocale::Russian] = QString::fromUtf8("@@метка");
	result.last().returnType = Shared::ActorInterface::Bool;
	result.last().arguments.push_back(Shared::ActorInterface::Argument());
	result.last().arguments.last().accessType = Shared::ActorInterface::InArgument;
	result.last().arguments.last().type = Shared::ActorInterface::Int;
	result.last().arguments.last().dimension = 0u;
	result.last().arguments.push_back(Shared::ActorInterface::Argument());
	result.last().arguments.last().accessType = Shared::ActorInterface::InArgument;
	result.last().arguments.last().type = Shared::ActorInterface::Int;
	result.last().arguments.last().dimension = 0u;

	/* алг лог @@закрашена(цел row, цел col) */
	result.push_back(Shared::ActorInterface::Function());
	result.last().id = result.size() - 1;
	result.last().accessType = Shared::ActorInterface::TeacherModeFunction;
	result.last().asciiName = QByteArray("colored");
	result.last().localizedNames[QLocale::Russian] = QString::fromUtf8("@@закрашена");
	result.last().returnType = Shared::ActorInterface::Bool;
	result.last().arguments.push_back(Shared::ActorInterface::Argument());
	result.last().arguments.last().accessType = Shared::ActorInterface::InArgument;
	result.last().arguments.last().type = Shared::ActorInterface::Int;
	result.last().arguments.last().dimension = 0u;
	result.last().arguments.push_back(Shared::ActorInterface::Argument());
	result.last().arguments.last().accessType = Shared::ActorInterface::InArgument;
	result.last().arguments.last().type = Shared::ActorInterface::Int;
	result.last().arguments.last().dimension = 0u;

	/* алг @@робот(рез цел row, рез цел col) */
	result.push_back(Shared::ActorInterface::Function());
	result.last().id = result.size() - 1;
	result.last().accessType = Shared::ActorInterface::TeacherModeFunction;
	result.last().asciiName = QByteArray("robot pos");
	result.last().localizedNames[QLocale::Russian] = QString::fromUtf8("@@робот");
	result.last().returnType = Shared::ActorInterface::Void;
	result.last().arguments.push_back(Shared::ActorInterface::Argument());
	result.last().arguments.last().accessType = Shared::ActorInterface::OutArgument;
	result.last().arguments.last().type = Shared::ActorInterface::Int;
	result.last().arguments.last().dimension = 0u;
	result.last().arguments.push_back(Shared::ActorInterface::Argument());
	result.last().arguments.last().accessType = Shared::ActorInterface::OutArgument;
	result.last().arguments.last().type = Shared::ActorInterface::Int;
	result.last().arguments.last().dimension = 0u;

	/* алг сим @@верхняя буква(цел row, цел col) */
	result.push_back(Shared::ActorInterface::Function());
	result.last().id = result.size() - 1;
	result.last().accessType = Shared::ActorInterface::TeacherModeFunction;
	result.last().asciiName = QByteArray("upChar");
	result.last().localizedNames[QLocale::Russian] = QString::fromUtf8("@@верхняя буква");
	result.last().returnType = Shared::ActorInterface::Char;
	result.last().arguments.push_back(Shared::ActorInterface::Argument());
	result.last().arguments.last().accessType = Shared::ActorInterface::InArgument;
	result.last().arguments.last().type = Shared::ActorInterface::Int;
	result.last().arguments.last().dimension = 0u;
	result.last().arguments.push_back(Shared::ActorInterface::Argument());
	result.last().arguments.last().accessType = Shared::ActorInterface::InArgument;
	result.last().arguments.last().type = Shared::ActorInterface::Int;
	result.last().arguments.last().dimension = 0u;

	/* алг цел @@температура(цел row, цел col) */
	result.push_back(Shared::ActorInterface::Function());
	result.last().id = result.size() - 1;
	result.last().accessType = Shared::ActorInterface::TeacherModeFunction;
	result.last().asciiName = QByteArray("cellTemp");
	result.last().localizedNames[QLocale::Russian] = QString::fromUtf8("@@температура");
	result.last().returnType = Shared::ActorInterface::Int;
	result.last().arguments.push_back(Shared::ActorInterface::Argument());
	result.last().arguments.last().accessType = Shared::ActorInterface::InArgument;
	result.last().arguments.last().type = Shared::ActorInterface::Int;
	result.last().arguments.last().dimension = 0u;
	result.last().arguments.push_back(Shared::ActorInterface::Argument());
	result.last().arguments.last().accessType = Shared::ActorInterface::InArgument;
	result.last().arguments.last().type = Shared::ActorInterface::Int;
	result.last().arguments.last().dimension = 0u;

	/* алг вещ @@радиация(цел row, цел col) */
	result.push_back(Shared::ActorInterface::Function());
	result.last().id = result.size() - 1;
	result.last().accessType = Shared::ActorInterface::TeacherModeFunction;
	result.last().asciiName = QByteArray("cellRad");
	result.last().localizedNames[QLocale::Russian] = QString::fromUtf8("@@радиация");
	result.last().returnType = Shared::ActorInterface::Real;
	result.last().arguments.push_back(Shared::ActorInterface::Argument());
	result.last().arguments.last().accessType = Shared::ActorInterface::InArgument;
	result.last().arguments.last().type = Shared::ActorInterface::Int;
	result.last().arguments.last().dimension = 0u;
	result.last().arguments.push_back(Shared::ActorInterface::Argument());
	result.last().arguments.last().accessType = Shared::ActorInterface::InArgument;
	result.last().arguments.last().type = Shared::ActorInterface::Int;
	result.last().arguments.last().dimension = 0u;

	/* алг сим @@нижняя буква(цел row, цел col) */
	result.push_back(Shared::ActorInterface::Function());
	result.last().id = result.size() - 1;
	result.last().accessType = Shared::ActorInterface::TeacherModeFunction;
	result.last().asciiName = QByteArray("downChar");
	result.last().localizedNames[QLocale::Russian] = QString::fromUtf8("@@нижняя буква");
	result.last().returnType = Shared::ActorInterface::Char;
	result.last().arguments.push_back(Shared::ActorInterface::Argument());
	result.last().arguments.last().accessType = Shared::ActorInterface::InArgument;
	result.last().arguments.last().type = Shared::ActorInterface::Int;
	result.last().arguments.last().dimension = 0u;
	result.last().arguments.push_back(Shared::ActorInterface::Argument());
	result.last().arguments.last().accessType = Shared::ActorInterface::InArgument;
	result.last().arguments.last().type = Shared::ActorInterface::Int;
	result.last().arguments.last().dimension = 0u;
	;
	return result;
}

void RobotPlugin::handleSettingsChangedCppImplementation(const QStringList & keys)
{
	if (module_) {
		module_->reloadSettings(mySettings(), keys);
	}
}

QString RobotPlugin::initialize(const QStringList &a, const ExtensionSystem::CommandLine &b)
{
	module_ = new RobotModule(this);
	QMap<QString,Widgets::DeclarativeSettingsPage::Entry> entries;

	{
		Widgets::DeclarativeSettingsPage::Entry entry;
		entry.title = QString::fromUtf8("Толщина борта");  // TODO non-Russian language support
		entry.type = Widgets::DeclarativeSettingsPage::Integer;
		entry.defaultValue = 6;
		entry.minimumValue = QVariant::Invalid;
		entry.maximumValue = QVariant::Invalid;
		entry.items = QStringList();
		entry.displayOrder = 12;
		entries["BortW"] = entry;
	}

	{
		Widgets::DeclarativeSettingsPage::Entry entry;
		entry.title = QString::fromUtf8("Цвет поля (редактирование)");  // TODO non-Russian language support
		entry.type = Widgets::DeclarativeSettingsPage::Color;
		entry.defaultValue = QString::fromUtf8("#6496ff");
		entry.minimumValue = QVariant::Invalid;
		entry.maximumValue = QVariant::Invalid;
		entry.items = QStringList();
		entry.displayOrder = 6;
		entries["EditColor"] = entry;
	}

	{
		Widgets::DeclarativeSettingsPage::Entry entry;
		entry.title = QString::fromUtf8("Цвет закрашивания");  // TODO non-Russian language support
		entry.type = Widgets::DeclarativeSettingsPage::Color;
		entry.defaultValue = QString::fromUtf8("#9370db");
		entry.minimumValue = QVariant::Invalid;
		entry.maximumValue = QVariant::Invalid;
		entry.items = QStringList();
		entry.displayOrder = 7;
		entries["FillColor"] = entry;
	}

	{
		Widgets::DeclarativeSettingsPage::Entry entry;
		entry.title = QString::fromUtf8("Пикселей/клетку при сохранении картинки");	// TODO non-Russian language support
		entry.type = Widgets::DeclarativeSettingsPage::Double;
		entry.defaultValue = 100;
		entry.minimumValue = QVariant::Invalid;
		entry.maximumValue = 5000;
		entry.items = QStringList();
		entry.displayOrder = 11;
		entries["ImageSize"] = entry;
	}

	{
		Widgets::DeclarativeSettingsPage::Entry entry;
		entry.title = QString::fromUtf8("Сдвиг символов вверх/вниз");	 // TODO non-Russian language support
		entry.type = Widgets::DeclarativeSettingsPage::Integer;
		entry.defaultValue = 2;
		entry.minimumValue = QVariant::Invalid;
		entry.maximumValue = QVariant::Invalid;
		entry.items = QStringList();
		entry.displayOrder = 8;
		entries["LettShift"] = entry;
	}

	{
		Widgets::DeclarativeSettingsPage::Entry entry;
		entry.title = QString::fromUtf8("Цвет сетки");	 // TODO non-Russian language support
		entry.type = Widgets::DeclarativeSettingsPage::Color;
		entry.defaultValue = QString::fromUtf8("#C8C800");
		entry.minimumValue = QVariant::Invalid;
		entry.maximumValue = QVariant::Invalid;
		entry.items = QStringList();
		entry.displayOrder = 2;
		entries["LineColor"] = entry;
	}

	{
		Widgets::DeclarativeSettingsPage::Entry entry;
		entry.title = QString::fromUtf8("Цвет сетки (редактирование)");	// TODO non-Russian language support
		entry.type = Widgets::DeclarativeSettingsPage::Color;
		entry.defaultValue = QString::fromUtf8("#C8C800");
		entry.minimumValue = QVariant::Invalid;
		entry.maximumValue = QVariant::Invalid;
		entry.items = QStringList();
		entry.displayOrder = 3;
		entries["LineColorEdit"] = entry;
	}

	{
		Widgets::DeclarativeSettingsPage::Entry entry;
		entry.title = QString::fromUtf8("Сдвиг точки вверх/вниз");  // TODO non-Russian language support
		entry.type = Widgets::DeclarativeSettingsPage::Integer;
		entry.defaultValue = 3;
		entry.minimumValue = QVariant::Invalid;
		entry.maximumValue = QVariant::Invalid;
		entry.items = QStringList();
		entry.displayOrder = 9;
		entries["MarkShift"] = entry;
	}

	{
		Widgets::DeclarativeSettingsPage::Entry entry;
		entry.title = QString::fromUtf8("Сдвиг точки право/лево");  // TODO non-Russian language support
		entry.type = Widgets::DeclarativeSettingsPage::Integer;
		entry.defaultValue = 6;
		entry.minimumValue = QVariant::Invalid;
		entry.maximumValue = QVariant::Invalid;
		entry.items = QStringList();
		entry.displayOrder = 10;
		entries["MarkShiftLeft"] = entry;
	}

	{
		Widgets::DeclarativeSettingsPage::Entry entry;
		entry.title = QString::fromUtf8("Цвет поля");  // TODO non-Russian language support
		entry.type = Widgets::DeclarativeSettingsPage::Color;
		entry.defaultValue = QString::fromUtf8("#289628");
		entry.minimumValue = QVariant::Invalid;
		entry.maximumValue = QVariant::Invalid;
		entry.items = QStringList();
		entry.displayOrder = 5;
		entries["NormalColor"] = entry;
	}

	{
		Widgets::DeclarativeSettingsPage::Entry entry;
		entry.title = QString::fromUtf8("Толщина линий");  // TODO non-Russian language support
		entry.type = Widgets::DeclarativeSettingsPage::Integer;
		entry.defaultValue = 1;
		entry.minimumValue = QVariant::Invalid;
		entry.maximumValue = QVariant::Invalid;
		entry.items = QStringList();
		entry.displayOrder = 13;
		entries["StW"] = entry;
	}

	{
		Widgets::DeclarativeSettingsPage::Entry entry;
		entry.title = QString::fromUtf8("Цвет символов");  // TODO non-Russian language support
		entry.type = Widgets::DeclarativeSettingsPage::Color;
		entry.defaultValue = QString::fromUtf8("#FFFFFF");
		entry.minimumValue = QVariant::Invalid;
		entry.maximumValue = QVariant::Invalid;
		entry.items = QStringList();
		entry.displayOrder = 1;
		entries["TextColor"] = entry;
	}

	{
		Widgets::DeclarativeSettingsPage::Entry entry;
		entry.title = QString::fromUtf8("Цвет стен");  // TODO non-Russian language support
		entry.type = Widgets::DeclarativeSettingsPage::Color;
		entry.defaultValue = QString::fromUtf8("#C8C810");
		entry.minimumValue = QVariant::Invalid;
		entry.maximumValue = QVariant::Invalid;
		entry.items = QStringList();
		entry.displayOrder = 4;
		entries["WallColor"] = entry;
	}

	{
		Widgets::DeclarativeSettingsPage::Entry entry;
		entry.title = QString::fromUtf8("Толщина стен");	 // TODO non-Russian language support
		entry.type = Widgets::DeclarativeSettingsPage::Integer;
		entry.defaultValue = 4;
		entry.minimumValue = QVariant::Invalid;
		entry.maximumValue = QVariant::Invalid;
		entry.items = QStringList();
		entry.displayOrder = 14;
		entries["WallW"] = entry;
	}

	bool guiAvailable = true;
	#ifdef Q_OS_LINUX
	guiAvailable = 0 != getenv("DISPLAY");
	#endif
	if (guiAvailable) {
		settingsPage_ = new Widgets::DeclarativeSettingsPage(
			Shared::actorCanonicalName(localizedModuleName(QLocale::Russian)),
			mySettings(),
			entries
		);
		connect(settingsPage_, SIGNAL(settingsChanged(QStringList)), this, SLOT(handleSettingsChangedCppImplementation(QStringList)));
	}

	return module_->initialize(a, b);
}

bool RobotPlugin::isGuiRequired() const
{
	return false;
}

bool RobotPlugin::isSafeToQuit()
{
	return module_->isSafeToQuit();
}

void RobotPlugin::loadActorData(QIODevice * source)
{
	if (module_) {
		module_->loadActorData(source);
	}
}

QString RobotPlugin::localizedModuleName(const QLocale::Language ) const
{
	return QString::fromUtf8("Робот");
}

QString RobotPlugin::mainIconName() const
{
	return QString::fromLatin1("robot");
}

QWidget* RobotPlugin::mainWidget()
{
	return module_->mainWidget();
}

QList<QMenu*> RobotPlugin::moduleMenus() const
{
	return module_->moduleMenus();
}

/* public */ void RobotPlugin::notifyGuiReady()
{
	module_->handleGuiReady();
}

QString RobotPlugin::pultIconName() const
{
	return QString::fromLatin1("robot-pult");
}

QWidget* RobotPlugin::pultWidget()
{
	return module_->pultWidget();
}

void RobotPlugin::reset()
{
	module_->reset();
}

QVariant RobotPlugin::result() const
{
	return result_;
}

void RobotPlugin::setAnimationEnabled(bool enabled)
{
	// The module might be not created at a time of call,
	// so check it propertly
	if (module_) {
		module_->setAnimationEnabled(enabled);
	}
}

QWidget* RobotPlugin::settingsEditorPage()
{
	return settingsPage_;
}

void RobotPlugin::sleep(unsigned long secs)
{
	if (QThread::currentThread()==asyncRunThread_) {
		asyncRunThread_->asleep(secs);
	}
}

void RobotPlugin::msleep(unsigned long msecs)
{
	//if (QThread::currentThread()==asyncRunThread_) {
		asyncRunThread_->amsleep(msecs);
	//}
}

void RobotPlugin::usleep(unsigned long usecs)
{
	if (QThread::currentThread()==asyncRunThread_) {
		asyncRunThread_->ausleep(usecs);
	}
}


QVariantList RobotPlugin::templateParameters() const
{
	if (module_) {
		return module_->templateParameters();
	}
	else {
		return defaultTemplateParameters();
	}
}

void RobotPlugin::terminateEvaluation()
{
	module_->terminateEvaluation();
}

Shared::ActorInterface::TypeList RobotPlugin::typeList() const
{
	Shared::ActorInterface::TypeList result;
	return result;
}

void RobotPlugin::updateSettings(const QStringList & keys)
{
	if (settingsPage_) {
		settingsPage_->setSettingsObject(mySettings());
	}
	if (module_) {
		module_->reloadSettings(mySettings(), keys);
	}
}

QList<Shared::ActorInterface*> RobotPlugin::usesList() const
{
	static const QList<Shared::ActorInterface*> empty = QList<Shared::ActorInterface*>();
	return empty;
}


RobotAsyncRunThread::RobotAsyncRunThread(
	class RobotPlugin* plugin,
	class RobotModuleBase* module
) :
	QThread(plugin),
	index_(0),
	args_(QVariantList()),
	plugin_(plugin),
	module_(module)
{
}

void RobotAsyncRunThread::asleep(unsigned long secs)
{
	sleep(secs);
}

void RobotAsyncRunThread::amsleep(unsigned long msecs)
{
	msleep(msecs);
}

void RobotAsyncRunThread::ausleep(unsigned long usecs)
{
	usleep(usecs);
}

void RobotAsyncRunThread::init(quint32 index, const QVariantList & args)
{
	index_ = index;
	args_ = args;
}

void RobotAsyncRunThread::run()
{
	switch (index_) {

		default: {
			plugin_->setError("Unknown method index");
		}
	}
}


} // namespace ActorRobot
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN(ActorRobot::RobotPlugin)
#endif
