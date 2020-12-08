## Alternate data streams (ADS)
<br />

**What are Alternate Data Streams?**
Alternate Data Streams (ADS) have been around since the introduction of windows NTFS. They were designed to provide
compatibility with the old Hierarchical File System (HFS) from Mac which uses something called resource forks.

Basically, ADS can be used to hide the presence of a secret or malicious file inside the file record of an innocent file. That is,
when windows shows you a file, say "readme.txt", the metadata that tells your system where to get "readme.txt" may also
contain information for "EvilSpyware.exe". Thus, malicious files may be on your system and you cannot see them using normal means.
<br /><br />
**How to see Alternate Data Streams records in CLI?**
```
dir /r
```
---
<br /><br />
## Proof-Of-Concept
<br />


- Create one **`text`** file to be embebbed with one **`jpg image`**
```
echo test if it works > SSAredTeam.txt
```
- Download kali-linux.jpg
![Kali-linux](https://user-images.githubusercontent.com/23490060/93417865-dded6580-f8a0-11ea-9b52-e0d16d32e189.jpg)

- Append the **`image`** file to the **`text`** file
```
type kali-linux.jpg > SSAredTeam.txt:kali-linux.jpg
```
- Delete kali-linux.jpg image
```
del kali-linux.jpg
```
- see ads
```
dir /r
```
- Execute kali-linux.jpg image
```
mspaint.exe C:\Users\pedro\Desktop\SSAredTeam.txt:kali-linux.jpg
```
![ads](https://user-images.githubusercontent.com/23490060/93419029-9c11ee80-f8a3-11ea-967b-98478b85f247.png)

<br /><br />

**hidde mp3 in text file**

- Create one **`text`** file to be embebbed with one **`mp3 file`**
```
echo test if it works > SSAredTeam.txt
```
- Append the **`mp3 file`**  to the **`text`** file
```
type mysong.mp3 > SSAredTeam.txt:mysong.mp3
```
- Delete mysong mp3
```
del mysong.mp3
```
- see ads
```
dir /r
```
- Execute mysong.mp3 (ads)
```
wmplayer.exe C:\Users\pedro\Desktop\SSAredTeam.txt:mysong.mp3

```

<br /><br />

**hidde exe in text file**

- Create one **`text`** file to be embebbed with one **`exe file`**
```
echo test if it works > SSAredTeam.txt
```
- Append the **`exe file`**  to the **`text`** file
```
type payload.exe > SSAredTeam.txt:payload.exe
```
- Delete payload exe
```
del payload.exe
```
- see ads
```
dir /r
```
- Execute payload.exe (ads)
```
wmic.exe process call create "C:\Users\pedro\Desktop\SSAredTeam.txt:payload.exe"

```
---
<br /><br />

- Execute payload.bat stored in an Alternate Data Stream (ADS). 
```
cmd.exe - < SSAredTeam.txt:payload.bat
```
![ADS](https://user-images.githubusercontent.com/23490060/93657285-90503480-fa29-11ea-822f-115dceeeca15.png)

<br /><br />

- Execute payload.ps1 stored in an Alternate Data Stream (ADS). 
```
powershell .\SSAredTeam.txt:payload.ps1
```
![ads2](https://user-images.githubusercontent.com/23490060/93659595-be8c3f00-fa3e-11ea-8f32-a68f59d8ce3b.png)
