#
# Filename: Hello.ps1
# This file serves for remote download/execution demonstration effects ..
# and its stored in my remote apache2 webroot to be downloaded/executed remotely.
#
Write-Host ""
Write-Host "Hello.ps1 script executed remotelly .." -ForeGroundColor green -BackGroundColor black
Start-Sleep 2
Write-Host "Extracting juice Info from system .." -ForeGroundColor yellow -BackGroundColor black
Get-WmiObject -Class Win32_ComputerSystem
Get-CimInstance Win32_OperatingSystem | Select-Object OSArchitecture, Caption, SystemDirectory | FL *
Write-Host ""
