#include "robotmodulebase.h"
#include "robotplugin.h"

#include <QMenu>

namespace ActorRobot {

RobotModuleBase::RobotModuleBase(ExtensionSystem::KPlugin* p) :
	QObject(p)
{
	plugin = qobject_cast<RobotPlugin*>(parent());
	bool hasGui = true;
#ifdef Q_OS_LINUX
	hasGui = getenv("DISPLAY") != 0;
#endif
	if (!hasGui)
		return;

	QString currentLocaleName = QLocale().name();

	m_menuRobot = new QMenu("Robot");
	m_actionRobotLoadEnvironment = m_menuRobot->addAction("");
	m_actionRobotLoadRescent = m_menuRobot->addAction("");
	m_actionRobotRevertEnvironment = m_menuRobot->addAction("");
	m_actionRobotSaveEnvironment = m_menuRobot->addAction("");
	m_actionRobotSave2Png = m_menuRobot->addAction("");
	m_actionRobotEditEnvironment = m_menuRobot->addAction("");
	m_actionRobotAutoWindowSize = m_menuRobot->addAction("");
	m_actionRobotNewEnvironment = m_menuRobot->addAction("");

	if (currentLocaleName=="ru_RU") {
		m_menuRobot->setTitle(QString::fromUtf8("Робот"));
		m_actionRobotLoadEnvironment->setText(QString::fromUtf8("Загрузить обстановку..."));
		m_actionRobotLoadRescent->setText(QString::fromUtf8("Недавние обстановки"));
		m_actionRobotRevertEnvironment->setText(QString::fromUtf8("Вернуть исходную обстановку"));
		m_actionRobotSaveEnvironment->setText(QString::fromUtf8("Сохранить обстановку..."));
		m_actionRobotSave2Png->setText(QString::fromUtf8("Сохранить как изображение…"));
		m_actionRobotEditEnvironment->setText(QString::fromUtf8("Редактировать обстановку..."));
		m_actionRobotAutoWindowSize->setText(QString::fromUtf8("Авто размер окна"));
		m_actionRobotNewEnvironment->setText(QString::fromUtf8("Новая обстановка..."));
	} else {
//		m_menuRobot->setTitle(QString::fromLatin1("Robot"));
		m_actionRobotLoadEnvironment->setText(QString::fromLatin1("Load Environment..."));
		m_actionRobotLoadRescent->setText(QString::fromLatin1("Load Rescent..."));
		m_actionRobotRevertEnvironment->setText(QString::fromLatin1("Revert Environment"));
		m_actionRobotSaveEnvironment->setText(QString::fromLatin1("Save Environment..."));
		m_actionRobotSave2Png->setText(QString::fromLatin1("Save2Png."));
		m_actionRobotEditEnvironment->setText(QString::fromLatin1("Edit Environment..."));
		m_actionRobotAutoWindowSize->setText(QString::fromLatin1("Auto window size."));
		m_actionRobotNewEnvironment->setText(QString::fromLatin1("New Environment..."));
	}

}

const ExtensionSystem::CommandLine& RobotModuleBase::commandLineParameters() const
{
	return plugin->commandLineParameters();
}

void RobotModuleBase::handleGuiReady()
{
}

QString RobotModuleBase::initialize(
	const QStringList &configurationParameters,
	const ExtensionSystem::CommandLine &runtimeParameters
)
{
	Q_UNUSED(configurationParameters);
	Q_UNUSED(runtimeParameters);

	return QString();
}

bool RobotModuleBase::isSafeToQuit()
{
	return true;
}

void RobotModuleBase::loadActorData(QIODevice * source)
{
	Q_UNUSED(source);  // By default do nothing
}



QList<QMenu*> RobotModuleBase::moduleMenus() const
{
	bool hasGui = true;
#ifdef Q_OS_LINUX
	hasGui = getenv("DISPLAY") != 0;
#endif
	QList<QMenu*> result;
	if (hasGui) {
		result.push_back(m_menuRobot);
	}
	return result;
}

QDir RobotModuleBase::myResourcesDir() const
{
	return plugin->myResourcesDir();
}

ExtensionSystem::SettingsPtr RobotModuleBase::mySettings() const
{
	return plugin->mySettings();
}

void RobotModuleBase::setError(const QString &errorText)
{
	plugin->setError(errorText);
}

QVariantList RobotModuleBase::templateParameters() const
{
	return plugin->defaultTemplateParameters();
}

void RobotModuleBase::sleep(unsigned long secs)
{
	plugin->sleep(secs);
}

void RobotModuleBase::msleep(unsigned long msecs)
{
	plugin->msleep(msecs);
}

void RobotModuleBase::usleep(unsigned long usecs)
{
	plugin->usleep(usecs);
}

} // namespace ActorRobot
