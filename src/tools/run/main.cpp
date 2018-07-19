#include <assert.h>
#include <iostream>
#include <kumir2-libs/stdlib/kumirstdlib.hpp>
#include <kumir2-libs/vm/vm_abstract_handlers.h>
#include <kumir2-libs/vm/vm_console_handlers.hpp>
#include <kumir2-libs/vm/vm.hpp>

#if defined(WIN32) || defined(_WIN32)
#include <Windows.h>
#else
#include <unistd.h>
#endif

using namespace Kumir;

static Encoding LOCALE;

static int usage(const char *pName)
{
	bool russianLanguage = false;
	Char _n = Char('\n');

#if defined(WIN32) || defined(_WIN32)
	russianLanguage = true;
#else
	char *env = getenv("LANG");
	if (env) {
		std::string LANG(env);
		russianLanguage = (LANG.find("ru") != std::string::npos);
	}
#endif
	String message;
	if (russianLanguage) {
		message  = Core::fromUtf8("Вызов:");
		message.push_back(_n);
		message += Core::fromUtf8("\t")+Core::fromUtf8(std::string(pName));
		message += Core::fromUtf8(" [-ansi] ИМЯФАЙЛА.kod [ПАРАМ1 [ПАРАМ2 ... [ПАРАМn]]]");
		message.push_back(_n);
		message.push_back(_n);
		message += Core::fromUtf8("\t-ansi\t\tИспользовать кодировку 1251 вместо 866 в терминале (только для Windows)");
		message.push_back(_n);
		message += Core::fromUtf8("\tИМЯФАЙЛА.kod\tИмя выполнеяемой программы");
		message.push_back(_n);
		message += Core::fromUtf8("\tПАРАМ1...ПАРАМn\tАргументы главного алгоритма Кумир-программы");
		message.push_back(_n);
	} else {
		message  = Core::fromUtf8("Usage:");
		message.push_back(_n);
		message += Core::fromUtf8("\t")+Core::fromUtf8(std::string(pName));
		message += Core::fromUtf8(" [-ansi] FILENAME.kod [ARG1 [ARG2 ... [ARGn]]]");
		message.push_back(_n);
		message.push_back(_n);
		message += Core::fromUtf8("\t-ansi\t\tUse codepage 1251 instead of 866 in console (Windows only)");
		message.push_back(_n);
		message += Core::fromUtf8("\tFILENAME.kod\tKumir runtime file name");
		message.push_back(_n);
		message += Core::fromUtf8("\tARG1...ARGn\tKumir program main algorithm arguments");
		message.push_back(_n);
	}
	Kumir::EncodingError encodingError;
	std::cerr << Coder::encode(LOCALE, message, encodingError);
	return 127;
}

static int showErrorMessage(const String &message, int code)
{
	Kumir::EncodingError encodingError;
	bool toHttp = false;
#if !defined(WIN32) && !defined(_WIN32)
	char *REQUEST_METHOD = getenv("REQUEST_METHOD");
	char *QUERY_STRING = getenv("QUERY_STRING");
	toHttp = (REQUEST_METHOD != 0 && QUERY_STRING != 0);
#endif
	if (!toHttp) {
		std::string localMessage = Coder::encode(LOCALE, message, encodingError);
		std::cerr << localMessage << std::endl;
	} else {
		std::string localMessage = Coder::encode(UTF8, message, encodingError);
		std::cout << "Content-type: text/plain;charset=utf-8\n\n";
		std::cout << localMessage << std::endl;
		code = 0;
	}
	return code;
}

int runKumirXRun(int argc, char* argv[])
{
#if defined(WIN32) || defined(_WIN32) // Win32 implementation
	char buf[MAX_PATH];
	GetModuleFileNameA(NULL, buf, MAX_PATH);
	std::string kumir2run(buf);
	size_t lastSlash = kumir2run.find_last_of('\\');
	std::string basePath = kumir2run.substr(0, lastSlash + 1);
	std::string kumir2xrun = basePath + std::string("kumir2-xrun.exe");
	std::string commandLine = kumir2xrun;
	for (int i = 1; i < argc; i++) {
		std::string arg(argv[i]);
		commandLine.push_back(' ');
		commandLine.append(arg);
	}
	STARTUPINFOA startupInfo;
	ZeroMemory(&startupInfo, sizeof(startupInfo));
	startupInfo.cb = sizeof(startupInfo);
	PROCESS_INFORMATION processInformation;
	ZeroMemory(&processInformation, sizeof(processInformation) );
	LPSTR lpCommandLine = const_cast<LPSTR> (commandLine.c_str());
	BOOL success = CreateProcessA(
		NULL, // lpApplicationName
		lpCommandLine, // lpCommandLine
		NULL, // lpProcessAttributes
		NULL, // lpThreadAttributes
		TRUE, // bInheritHandles
		0, // dwCreationFlags
		NULL, // lpEnvironment
		NULL, // lpCurrentDirectory
		&startupInfo, // lpStartupInfo
		&processInformation // lpProcessInformation
	);
	if (success) {
		return WaitForSingleObject(processInformation.hProcess, INFINITE);
	}
#else // Posix implementation
	(void) argc;
	assert (0 < argc);
	std::string kumir2run = std::string(argv[0]);
	if (kumir2run.at(0) != '/') {
		char buf[2048];
		getcwd(buf, 2048);
		std::string cwd(buf);
		cwd.push_back('/');
		kumir2run = cwd + kumir2run;
	}
	size_t lastSlash = kumir2run.find_last_of('/');
	std::string basePath = kumir2run.substr(0, lastSlash + 1);
	std::string kumir2xrun = basePath + std::string("kumir2-xrun");
	return execv(kumir2xrun.c_str(), argv);
#endif
	return 127;
}

static bool IsPluginExtern(const Bytecode::TableElem &e)
{
	bool isExtern = (e.type == Bytecode::EL_EXTERN);
	size_t l = e.fileName.length();
	bool isKumirModule = (l > 4) &&
		e.fileName.substr(l - 4) == Kumir::Core::fromAscii(".kod");
	return isExtern && !isKumirModule;
}

int main(int argc, char *argv[])
{
#if defined(WIN32) || defined(_WIN32)
	IO::LOCALE_ENCODING = LOCALE = CP866;
#else
	IO::LOCALE_ENCODING = LOCALE = UTF8;
#endif
	Kumir::EncodingError encodingError;
	bool testingMode = false;
	bool quietMode = false;

	std::deque<std::string> args;
	std::string pName;
	for (int i = 1; i < argc; i++) {
		if (argv[i][0] == 0)
			continue;
		std::string arg(argv[i]);

		if (pName.empty()) {
			if (arg == "-t" || arg == "--test") {
				testingMode = true;
			} else if (arg == "-p" || arg == "--pipe") {
				quietMode = true;
			} else if (arg == "--ansi") {
				IO::LOCALE_ENCODING = LOCALE = CP1251;
			} else {
				pName = arg;
			}
		} else {
			args.push_back(arg);
		}
	}

	if (pName.empty())
		return usage(argv[0]);

	// Load a program
	std::ifstream pFile(pName.c_str(), std::ios::in | std::ios::binary);
	if (!pFile.is_open()) {
		std::cerr << "Can't open program file: " << pName << std::endl;
		return 1;
	}
	Bytecode::Data pData;
	Bytecode::bytecodeFromDataStream(pFile, pData);
	pFile.close();

	// Check if it's possible to run using regular runtime
	bool hasPluginDependency =
		0 != std::count_if(pData.d.begin(), pData.d.end(), IsPluginExtern);

	if (hasPluginDependency) {
		return runKumirXRun(argc, argv);
	}

	// Prepare runner
	VM::KumirVM vm;

	VM::Console::InputFunctor inputFunctor;
	VM::Console::OutputFunctor outputFunctor;
	VM::Console::GetMainArgumentFunctor getMainArgumentFunctor;
	VM::Console::ReturnMainValueFunctor returnMainValueFunctor;
	getMainArgumentFunctor.setQuietMode(quietMode);
	returnMainValueFunctor.setQuietMode(quietMode);

	inputFunctor.setLocale(LOCALE);
	outputFunctor.setLocale(LOCALE);
	getMainArgumentFunctor.setLocale(LOCALE);
	returnMainValueFunctor.setLocale(LOCALE);

	getMainArgumentFunctor.init(argc, argv);

	vm.setFunctor(&inputFunctor);
	vm.setFunctor(&outputFunctor);
	vm.setFunctor(&getMainArgumentFunctor);
	vm.setFunctor(&returnMainValueFunctor);
	vm.setConsoleInputBuffer(&inputFunctor);
	vm.setConsoleOutputBuffer(&outputFunctor);

	String pPath = Files::getAbsolutePath(Coder::decode(LOCALE, pName, encodingError));
	size_t slashPos = pPath.find_last_of(Char('/'));
	String pDir;
	if (slashPos != String::npos) {
		pDir = pPath.substr(0, slashPos);
	}

	vm.setProgramDirectory(pDir);

	static String LOAD_ERROR = Core::fromUtf8("ОШИБКА ЗАГРУЗКИ ПРОГРАММЫ: ");
	static String NO_TESTING = Core::fromUtf8("В ПРОГРАММЕ НЕТ ТЕСТОВОГО АЛГОРИТМА");
	static String RUNTIME_ERROR = Core::fromUtf8("ОШИБКА ВЫПОЛНЕНИЯ: ");
	static String RUNTIME_ERROR_AT = Core::fromUtf8("ОШИБКА ВЫПОЛНЕНИЯ В СТРОКЕ ");
	static String COLON = Core::fromAscii(": ");

	String setProgramError;
	vm.setProgram(pData, true, Coder::decode(LOCALE, pName, encodingError), &setProgramError);

	if (setProgramError.length() > 0) {
		String message = LOAD_ERROR + setProgramError;
		return showErrorMessage(message, 126);
	}

	if (testingMode) {
		if (!vm.hasTestingAlgorithm()) {
			return showErrorMessage(NO_TESTING, 125);
		}
		vm.setEntryPoint(VM::KumirVM::EP_Testing);
	}

	vm.reset();
	vm.setDebugOff(true);

	// Main loop
	while (vm.hasMoreInstructions()) {
		vm.evaluateNextInstruction();
		if (vm.error().length() > 0) {
			String message = RUNTIME_ERROR;
			int line = vm.effectiveLineNo();
			if (line >= 0) {
				message = RUNTIME_ERROR_AT +
					Converter::sprintfInt(line + 1, 10, 0, 0) +
					COLON;
			}
			return showErrorMessage(message + vm.error(), 120);
		}
	}

	return testingMode ? vm.returnCode() : 0;
}
