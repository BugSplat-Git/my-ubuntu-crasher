#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dlfcn.h>
#include "client/crashpad_client.h"
#include "client/crash_report_database.h"
#include "client/settings.h"

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

using namespace base;
using namespace crashpad;
using namespace std;

bool initializeCrashpad(string dbName, string appName, string appVersion);
string getExecutableDir(void);
void generateExampleCallstackAndCrash();

int main(int argc, char **argv)
{
	// Initialize crashpad first
	initializeCrashpad("fred", "myUbuntuCrasher", "1.0.0");

	// Generate an example callstack and crash
	generateExampleCallstackAndCrash();

	return 0;
}

bool initializeCrashpad(string dbName, string appName, string appVersion)
{
	// Get directory where the exe lives so we can pass a full path to handler, reportsDir and metricsDir
	string exeDir = getExecutableDir();

	// Ensure that crashpad_handler is shipped with your application
	FilePath handler(exeDir + "/../crashpad/bin/crashpad_handler");

	// Directory where reports will be saved. Important! Must be writable or crashpad_handler will crash.
	FilePath reportsDir(exeDir);

	// Directory where metrics will be saved. Important! Must be writable or crashpad_handler will crash.
	FilePath metricsDir(exeDir);

	// Configure url with your BugSplat database
	string url = "https://" + dbName + ".bugsplat.com/post/bp/crash/crashpad.php";

	// Metadata that will be posted to BugSplat
	map<string, string> annotations;
	annotations["format"] = "minidump";					// Required: Crashpad setting to save crash as a minidump
	annotations["database"] = dbName;					// Required: BugSplat database
	annotations["product"] = appName;					// Required: BugSplat appName
	annotations["version"] = appVersion;				// Required: BugSplat appVersion
	annotations["key"] = "Sample key";					// Optional: BugSplat key field
	annotations["user"] = "fred@bugsplat.com";			// Optional: BugSplat user email
	annotations["list_annotations"] = "Sample comment"; // Optional: BugSplat crash description

	// Disable crashpad rate limiting so that all crashes have dmp files
	vector<string> arguments;
	arguments.push_back("--no-rate-limit");

	// File paths of attachments to be uploaded with the minidump file at crash time - default bundle limit is 20MB
	vector<FilePath> attachments;
	FilePath attachment(exeDir + "/attachment.txt");
	attachments.push_back(attachment);

	// Initialize Crashpad database
	unique_ptr<CrashReportDatabase> database = CrashReportDatabase::Initialize(reportsDir);
	if (database == NULL)
		return false;

	// Enable automated crash uploads
	Settings *settings = database->GetSettings();
	if (settings == NULL)
		return false;
	settings->SetUploadsEnabled(true);

	// Start crash handler
	CrashpadClient *client = new CrashpadClient();
	bool status = client->StartHandler(handler, reportsDir, metricsDir, url, annotations, arguments, true, true, attachments);
	return status;
}

string getExecutableDir()
{
	char pBuf[FILENAME_MAX];
	int len = sizeof(pBuf);
	int bytes = MIN(readlink("/proc/self/exe", pBuf, len), len - 1);
	if (bytes >= 0)
	{
		pBuf[bytes] = '\0';
	}

	char *lastForwardSlash = strrchr(&pBuf[0], '/');
	if (lastForwardSlash == NULL)
		return NULL;
	*lastForwardSlash = '\0';

	return pBuf;
}

// Create some dummy frames for a more interesting call stack
void func2()
{
	printf("In func2, loading library and about to crash...\n");

	// Get the executable directory to find our .so
	string exeDir = getExecutableDir();
	string libPath = exeDir + "/libcrash.so.2";

	// Load the shared library
	void *handle = dlopen(libPath.c_str(), RTLD_LAZY);
	if (!handle)
	{
		fprintf(stderr, "Failed to load library: %s\n", dlerror());
		return;
	}

	// Get the crash function
	typedef void (*crash_func_t)(void);
	dlerror(); // Clear any existing error
	crash_func_t crash_func = (crash_func_t)dlsym(handle, "crash");
	const char *dlsym_error = dlerror();
	if (dlsym_error)
	{
		fprintf(stderr, "Failed to get crash function: %s\n", dlsym_error);
		dlclose(handle);
		return;
	}

	// Call the crash function
	crash_func();

	// We should never reach here
	dlclose(handle);
}

void func1()
{
	printf("In func1, calling func2...\n");
	func2();
}

void func0()
{
	printf("In func0, calling func1...\n");
	func1();
}

void generateExampleCallstackAndCrash()
{
	printf("Starting call chain...\n");
	func0();
}
