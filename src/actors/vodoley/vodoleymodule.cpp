/*
This file is generated, but you can safely change it
until you run "gen_actor_source.py" with "--project" flag.

Generated file is just a skeleton for module contents.
You should change it corresponding to functionality.
*/

// Self include
#include "vodoleymodule.h"
#include "vodoley.h"
#include "pult.h"
#include <kumir2-libs/widgets/pultlogger.h>

namespace ActorVodoley
{

VodoleyModule *VodoleyModule::self = 0;

VodoleyModule::VodoleyModule(ExtensionSystem::KPlugin *parent)
	: VodoleyModuleBase(parent)
{
	self = this;
	MainWindow = 0;
}

// Module constructor, called once on plugin load
void VodoleyModule::createGui()
{
	MainWindow = new Vodoley();

	QList<QAction *> actions;
	actions.append(m_actionVodoleyNewEnvironment);
	actions.append(m_actionVodoleyLoadEnvironment);
	actions.append(m_actionVodoleySaveEnvironment);
	MainWindow->createActions(actions);
	connect(m_actionVodoleyRevertEnvironment, SIGNAL(triggered()), MainWindow, SLOT(reset()));

	rescentMenu = new QMenu();
	createRescentMenu();
	m_actionVodoleyLoadRescent->setMenu(rescentMenu);
	connect(MainWindow, SIGNAL(FileLoaded(QString)), this, SLOT(updateLastFiles(QString)));

}

QString VodoleyModule::initialize(
	const QStringList &configurationParameters,
	const ExtensionSystem::CommandLine &
) {
	if (!configurationParameters.contains("tablesOnly")) {
		createGui();
		createRescentMenu();

		redrawTimer = new QTimer(this);
		connect(redrawTimer, SIGNAL(timeout()), MainWindow, SLOT(redraw()));
	}

	return "";
}

QList<ExtensionSystem::CommandLineParameter> VodoleyModule::acceptableCommandLineParameters()
{
	// See "src/shared/extensionsystem/commandlineparameter.h" for constructor details
	return QList<ExtensionSystem::CommandLineParameter>();
}

void VodoleyModule::changeGlobalState(
	ExtensionSystem::GlobalState old,
	ExtensionSystem::GlobalState current
) {
	// Called when changed kumir state. The states are defined as enum ExtensionSystem::GlobalState:
	/*
	namespace ExtensionSystem {
		enum GlobalState {
			GS_Unlocked, // Edit mode
			GS_Observe,  // Observe mode
			GS_Running,  // Running mode
			GS_Input,    // User input required
			GS_Pause     // Running paused
		};
	}
	*/
	// TODO implement me
	using namespace ExtensionSystem;  // not to write "ExtensionSystem::" each time in this method scope
	Q_UNUSED(old);  // Remove this line on implementation
	Q_UNUSED(current);  // Remove this line on implementation
	MainWindow->redraw();
#if 0
	if (current == GlobalState::GS_Running) {
		redrawTimer->start(100);
	} else {
		redrawTimer->stop();
	}
#endif
}

void VodoleyModule::loadActorData(QIODevice *source)
{
	// Set actor specific data (like environment)
	// The source should be ready-to-read QIODevice like QBuffer or QFile

	MainWindow->loadIoDevice(source);
	MainWindow->pult->pltLogger()->ClearLog();
	MainWindow->reset();
}

void VodoleyModule::tryToSleep()
{
	if ((rand() % 100 < 5)) {
		msleep(2);
	}
}

QWidget *VodoleyModule::mainWidget() const
{
	return  MainWindow;
}

class AAA : public QWidget
{
public:
	explicit AAA(QWidget *pult): QWidget(), pult_(pult)
	{
		setLayout(new QVBoxLayout);
		layout()->setContentsMargins(0, 0, 0, 0);
		layout()->addWidget(pult);
	}

	QSize minimumSizeHint() const
	{
		return pult_->minimumSizeHint();
	}

private:
	QWidget *pult_;
};

QWidget *VodoleyModule::pultWidget() const
{
	// Returns module control view widget, or nullptr if there is no control view
	// NOTE: the method is const and might be called at any time,
	//       so DO NOT create widget here, just return!
	// TODO implement me
	// qDebug() << "Pult" << MainWindow->pult->size();
	// qDebug() << "Pult visible " << MainWindow->pult->isVisible();


	static QWidget *dummy = new AAA(MainWindow->pult);
	return dummy;
//    return MainWindow->pult;
}

void VodoleyModule::reloadSettings(
	ExtensionSystem::SettingsPtr settings,
	const QStringList &keys
) {
	// Updates setting on module load, workspace change or appliyng settings dialog.
	// If @param keys is empty -- should reload all settings, otherwise load only setting specified by @param keys
	my_settings = settings;
	createRescentMenu();
	Q_UNUSED(settings);  // Remove this line on implementation
	Q_UNUSED(keys);  // Remove this line on implementation
}

void VodoleyModule::reset()
{
	// Resets module to initial state before program execution
	MainWindow->reset();
}

void VodoleyModule::setAnimationEnabled(bool enabled)
{
	// Sets GUI animation flag on run
	// NOTE this method just setups a flag and might be called anytime, even module not needed
	// TODO implement me
	Q_UNUSED(enabled);  // Remove this line on implementation
}

void VodoleyModule::runFillA()
{
	/* алг наполни A */

	mutex.lock();
	MainWindow->FillA();
	mutex.unlock();
	tryToSleep();
}

void VodoleyModule::runFillB()
{
	/* алг наполни B */

	mutex.lock();
	MainWindow->FillB();
	mutex.unlock();
	tryToSleep();
}

void VodoleyModule::runFillC()
{
	/* алг наполни C */
	// TODO implement me
	mutex.lock();
	MainWindow->FillC();
	mutex.unlock();
	tryToSleep();
}

void VodoleyModule::runEmptyA()
{
	/* алг вылей A */

	mutex.lock();
	MainWindow->MoveFromTo(0, 3); //Move water from A to ....
	mutex.unlock();
	tryToSleep();
}

void VodoleyModule::runEmptyB()
{
	/* алг вылей B */

	mutex.lock();
	MainWindow->MoveFromTo(1, 3);
	mutex.unlock();
	tryToSleep();
}

/* public slot */ void VodoleyModule::runEmptyC()
{
	/* алг вылей C */

	mutex.lock();
	MainWindow->MoveFromTo(2, 3);
	mutex.unlock();
	tryToSleep();
}

void VodoleyModule::runFromAToB()
{
	/* алг перелей из A в B */

	mutex.lock();
	MainWindow->MoveFromTo(0, 1);
	mutex.unlock();
	tryToSleep();
}

void VodoleyModule::runFromAToC()
{
	/* алг перелей из A в C */

	mutex.lock();
	MainWindow->MoveFromTo(0, 2);
	mutex.unlock();
	tryToSleep();
}

void VodoleyModule::runFromBToA()
{
	/* алг перелей из B в A */

	mutex.lock();
	MainWindow->MoveFromTo(1, 0);
	mutex.unlock();
	tryToSleep();
}

void VodoleyModule::runFromBToC()
{
	/* алг перелей из B в C */

	mutex.lock();
	MainWindow->MoveFromTo(1, 2);
	mutex.unlock();
	tryToSleep();
}

void VodoleyModule::runFromCToB()
{
	/* алг перелей из C в B */

	mutex.lock();
	MainWindow->MoveFromTo(2, 1);
	mutex.unlock();
	tryToSleep();
}

void VodoleyModule::runFromCToA()
{
	/* алг перелей из C в A */

	mutex.lock();
	MainWindow->MoveFromTo(2, 0);
	mutex.unlock();
	tryToSleep();
}

bool VodoleyModule::runTaskComplited()
{
	/* алг лог @@задание выполнено */
	return MainWindow->isReady();
}

int VodoleyModule::runSizeA()
{
	return MainWindow->Asize();
}

int VodoleyModule::runSizeB()
{
	return MainWindow->Bsize();
}

int VodoleyModule::runSizeC()
{
	return MainWindow->Csize();
}

int VodoleyModule::runInA()
{
	return MainWindow->CurA();
}

int VodoleyModule::runInB()
{
	return MainWindow->CurB();
}

int VodoleyModule::runInC()
{
	return MainWindow->CurC();
}


void VodoleyModule::openRecent()
{
	QAction *s = qobject_cast<QAction *>(sender());
	QString txt = s->text();

	QString VodFile = txt;

	if (!MainWindow->loadFile(VodFile)) {
		QMessageBox::information(mainWidget(), "", QString::fromUtf8("Ошибка открытия файла! ") + VodFile, 0, 0, 0);
	}

}

void VodoleyModule::updateLastFiles(QString newFile)
{
	QStringList lastFiles = VodoleyModule::self->mySettings()->value("Vodoley/LastFiles").toString().split(";");
	if (lastFiles.indexOf(newFile) < 0) {
		lastFiles.prepend(newFile);
	}
	int max_fid = std::min(lastFiles.count(), 11);
	QString sett = "";
	for (int i = 0; i < max_fid; i++) {
		sett += lastFiles.at(i) + ";";
	}
	VodoleyModule::self->mySettings()->setValue("Vodoley/LastFiles", sett);
	createRescentMenu();
}

void VodoleyModule::createRescentMenu()
{
	rescentMenu->clear();
	QStringList lastFiles = VodoleyModule::self->mySettings()->value("Vodoley/LastFiles").toString().split(";");
	qDebug() << lastFiles;
	if (lastFiles.count() == 0 || (lastFiles.count() == 1 && lastFiles[0] == "")) {
		rescentMenu->setEnabled(false);
	} else {
		rescentMenu->setEnabled(true);
	}


	for (int i = 0; i < lastFiles.count(); i++) {
		if (lastFiles[i] == "") {
			continue;
		}
		QAction *action = rescentMenu->addAction(lastFiles[i], this, SLOT(openRecent()));
		Q_UNUSED(action);
	}
}


} // namespace ActorVodoley
