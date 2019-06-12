## C Shellcode Linux

<br />

### EXERCISE OBJECTIVES
Take control of a linux system remotely ( metasploit )

<br />

### STEPS REQUIRED TO ACHIEVE THIS
[1º - Use Metasploit Framework to Build Shellcode in C For Linux Systems](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/shellcoding/C_Shellcode_Linux.md#Use-Metasploit-Framework-to-Build-Shellcode-in-C-For-Linux-Systems)
[2º - Embedding (shellcode in C) into a C program](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/shellcoding/C_Shellcode_Linux.md#Embedding-(shellcode-in-C)-into-a-C-program)
[3º - Use GCC to compile the program (make it executable)](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/shellcoding/C_Shellcode_Linux.md#Use GCC to compile the program (make it executable))

<br />

### SOCIAL ENGENEERING
**Take a desktop screenshot using a C program.**<br />
<blockquote>The C program not only runs the shellcode (RAM) that allows us to control the target PC remotely,
but also contains a system command that takes a screenshot to the desktop of the target PC using the package [xwd](https://mmm)</blockquote>

<br />

| DEPENDENCIE | FUNCTION | REQUIRED |
|---|---|---|
| Metasploit | Build shellcode ; recive connection | yes |
| GCC | Compile C Program ( make it executable ) | yes |
| xwd | Take Screenshots ( social engeneering ) | optional |


### SHELLCODING DESCRIPTION


---

<br /><br /><br />

### Use Metasploit Framework to Build Shellcode in C For Linux Systems


