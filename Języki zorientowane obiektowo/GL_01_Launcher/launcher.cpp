#include <cstdio>
#include <Windows.h>
#include <cstdlib>
#include <cstring>

// _______________________________________________________________________________________

// Switching between applications using 16-bit WinExec() function.
void WindowsApplicationExecute(const char * _argv2);

// Checking for the file execution done by WinExec() function.
void OpenCheck1(const UINT _code);

// Switching between applications using WinAPI CreateProcess() function.
void ExecuteNewProcess(const char * _argv3);

// Checking for the file execution done by CreateProcess() windows macro.
void OpenCheck2(const BOOL _code);

// _______________________________________________________________________________________
// _______________________________________________________________________________________

int main(int argc, const char *argv[])
{
const short int P = 12;
char param[P];

memset(param,0,sizeof(param));
sprintf(param,"%s",argv[1]);
//WindowsApplicationExecute(param);
ExecuteNewProcess(param);
printf("GL_01_Launcher.exe closed.\n");

return (0);
};

// _______________________________________________________________________________________
// _______________________________________________________________________________________

void WindowsApplicationExecute(const char * _argv2)
{
UINT code;

if (!(strcmp(_argv2,"--console"))) 
	{
	printf("Starting GL_02_Console.exe...\n");
	code = WinExec("..\\Debug\\GL_02_Console.exe", SW_SHOWNORMAL);
	OpenCheck1(code);
	}
else if (!(strcmp(_argv2,"--winapi")))
	{
	printf("Starting GL_03_WinAPI.exe...\n");
	code = WinExec("..\\Debug\\GL_03_WinAPI.exe",SW_SHOWNORMAL);
	OpenCheck1(code);
	}
else 
	{
	printf("No valid parameter was used.\n");
	};
};

// _______________________________________________________________________________________

void OpenCheck1(const UINT _code)
{
switch (_code)
	{

	// -----------------------------------------------------------------------------------

	case 0 : 
		{
		fputs("The system is out of memory or resources.\n",stderr);
		abort();
		}
		break;

	// -----------------------------------------------------------------------------------
		
	case ERROR_BAD_FORMAT :
		{
		fputs("The .exe file is invalid.\n",stderr);
		abort();
		}
		break;

	// -----------------------------------------------------------------------------------

	case ERROR_FILE_NOT_FOUND :
		{
		fputs("The specified file was not found.\n",stderr);
		abort();
		}
		break;

	// -----------------------------------------------------------------------------------

	case ERROR_PATH_NOT_FOUND :
		{
		fputs("The specified path was not found.\n",stderr);
		abort();
		}
		break;

	// -----------------------------------------------------------------------------------

	};
};

// _______________________________________________________________________________________

void ExecuteNewProcess(const char * _argv3)
{
BOOL code;
STARTUPINFO si;
PROCESS_INFORMATION pi;

ZeroMemory(&si,sizeof(si));
ZeroMemory(&pi,sizeof(pi));
si.cb = sizeof(si);

if (!(strcmp(_argv3,"--console"))) 
	{
	printf("Starting GL_02_Console.exe...\n");
	code = CreateProcess("..\\Debug\\GL_02_Console.exe",nullptr,nullptr,nullptr,FALSE,NULL,nullptr,nullptr,&si,&pi);
	OpenCheck2(code);
	}
else if (!(strcmp(_argv3,"--winapi")))
	{
	printf("Starting GL_03_WinAPI.exe...\n");
	code = CreateProcess("..\\Debug\\GL_03_WinAPI.exe",nullptr,nullptr,nullptr,FALSE,NULL,nullptr,nullptr,&si,&pi);
	OpenCheck2(code);
	}
else 
	{
	printf("No valid parameter was used.\n");
	};
};

// _______________________________________________________________________________________

void OpenCheck2(const BOOL _code)
{
switch (_code)
	{
	
	// -----------------------------------------------------------------------------------

	case 0 :
		{
		fprintf(stderr,"Could not create a process (%ld).\n",GetLastError());
		abort();
		}
		break;

	// -----------------------------------------------------------------------------------

	default :
		{
		fprintf(stdout,"Process returned a value %ld.\n",_code);
		}
		break;

	// -----------------------------------------------------------------------------------

	};
};

// _______________________________________________________________________________________
