#include <stdio.h>
#include <unistd.h>
#include "client/crashpad_client.h"
#include "client/crash_report_database.h"
#include "client/settings.h"

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#if defined(OS_POSIX)
typedef std::string StringType;
#elif defined(OS_WIN)
typedef std::wstring StringType;
#endif

using namespace base;
using namespace crashpad;
using namespace std;

bool initializeCrashpad(void);
StringType getExecutableDir(void);
void crash(void);

int main(int argc, char **argv) {
	initializeCrashpad();
	crash();
}

void crash() {
	*(volatile int *)0 = 0;
}

bool initializeCrashpad() {
	// Get directory where the exe lives so we can pass a full path to handler, reportsDir and metricsDir
	StringType exeDir = getExecutableDir();

	// Ensure that handler is shipped with your application
	FilePath handler(exeDir + "/../crashpad/bin/crashpad_handler");

	// Directory where reports will be saved. Important! Must be writable or crashpad_handler will crash.
	FilePath reportsDir(exeDir);

	// Directory where metrics will be saved. Important! Must be writable or crashpad_handler will crash.
	FilePath metricsDir(exeDir);

	// Configure url with BugSplat’s public fred database. Replace 'fred' with the name of your BugSplat database.
	StringType url = "http://fred.bugsplat.com/post/bp/crash/crashpad.php";

	// Metadata that will be posted to the server with the crash report map
	map<StringType, StringType> annotations;
	annotations["format"] = "minidump";           // Required: Crashpad setting to save crash as a minidump
	annotations["database"] = "fred";             // Required: BugSplat database
	annotations["product"] = "myUbuntuCrasher";   // Required: BugSplat appName
	annotations["version"] = "1.0.0";             // Required: BugSplat appVersion
	annotations["key"] = "Sample key";            // Optional: BugSplat key field
	annotations["user"] = "fred@bugsplat.com";    // Optional: BugSplat user email
	annotations["list_annotations"] = "Sample comment"; // Optional: BugSplat crash description

	// Disable crashpad rate limiting so that all crashes have dmp files
	vector<StringType> arguments; 
	arguments.push_back("--no-rate-limit");

	// File paths of attachments to be embedded in polyglot minidump file at crash time
	vector<FilePath> attachments;
	FilePath attachment(exeDir + "/attachment.txt");
	attachments.push_back(attachment);

	// Initialize Crashpad database
	unique_ptr<CrashReportDatabase> database = CrashReportDatabase::Initialize(reportsDir);
	if (database == NULL) return false;

	// Enable automated crash uploads
	Settings *settings = database->GetSettings();
	if (settings == NULL) return false;
	settings->SetUploadsEnabled(true);

	// Start crash handler
	CrashpadClient *client = new CrashpadClient();
	bool status = client->StartHandler(handler, reportsDir, metricsDir, url, annotations, arguments, true, false, attachments);
	return status;
}

StringType getExecutableDir() {
	char pBuf[FILENAME_MAX];
	int len = sizeof(pBuf);
	int bytes = MIN(readlink("/proc/self/exe", pBuf, len), len - 1);
	if (bytes >= 0) {
		pBuf[bytes] = '\0';
	}

	char* lastForwardSlash = strrchr(&pBuf[0], '/');
	if (lastForwardSlash == NULL) return NULL;
	*lastForwardSlash = '\0';

	return pBuf;
}