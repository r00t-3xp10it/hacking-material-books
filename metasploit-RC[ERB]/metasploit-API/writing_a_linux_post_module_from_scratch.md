



# INTRO
                                 'writing a linux post module from scratch'
                Metasploit modules are written in ruby. Even if you don’t know a lot about ruby,
             you should still be able to write a metasploit linux post module based on this tutorial!

![msf-auxiliarys](http://i.cubeupload.com/m77AgR.png)

<br /><br />  

# MODULE OBJECTIVES
                Gather system information after succcessfully exploitation (post-exploitation).
                For that we are going to load the msf/core/post/common module to use the msf
                API 'cmd_exec()' to execute bash commands on remote system, display outputs,
                and store outputs to logfile (store_loot).

<br /><br />  

# MODULE DEVELOP METHODOLOGY

               1 - The Research stage: For bash commands that can be used to dump target system information
               2 - The metasploit template: Basic explaination of librarys, class name, mixins, description
               3 - The exploit code: Basic explaination of ruby syntax + metasploit APIs (def run)
               4 - Port module to msf database: Copy module to the rigth location and reload msfdb


<br /><br /><br /><br />

# WRITING A MSF POST MODULE (step by step)

# 1 - The research stage:

      At this stage (research) i have used online articles from different websites to store
      possible interesting bash commands that can be used in gathering target system information.

      The follow screenshot shows some of the bash commands that i have stored in a text file.

![msf-auxiliarys](http://i.cubeupload.com/YK7B6f.png)


<br /><br /><br /><br />


# 2 - The metasploit template

      The metasploit template its divided in to 3 main funtions.
      1 - the librarys, class name, mixins: that contains module requires/imports.
      2 - the 'def initialize()' funtion: that contains module description/settings.
      3 - and the 'def run()' funtion: that contain the script logic (exploit code).

      At this stage we are going to focous in the 'librarys' and 'def initialize()' funtions

<br /><br />

### The MSF librarys
![msf-auxiliarys](http://i.cubeupload.com/EZbnFy.png)<br />
**rex** the basic library for most tasks: Handles sockets, protocols, text transformations, SSL, SMB, HTTP, XOR, Base64, etc.

**msf/core** will include all the functionalities from the core library. the framework’s core library is the low-level<br />
interface that provides the required functionality for interacting with exploit modules, sessions, plugins, etc.<br />
`HINT: This line alone gives us access to over 6,000+ different functions (API calls).`<br />

**msf/core/post/common** allow us to use the API cmd_exec() to execute bash commands on remote system (linux).<br />
cmd_exec(): http://rapid7.github.io/metasploit-framework/api/Msf/Post/Common.html#cmd_exec-instance_method

<br /><br />

### The Module class name and rank
![msf-auxiliarys](http://i.cubeupload.com/ZcWceG.png)
we begin defining the **class** as MetasploitModule and inherit from **Msf::Post** mixin. Metasploit post modules are special<br />
in that they aren’t necessarily exploits that feature a payload. Instead, they can be considered as **reconnaissance tools**.<br />
This includes port scanners, fuzzers, service fingerprinters, enumeration, information gathering, post-exploitation, etc.

**Rank** = Every module has been assigned a rank based on its potential impact to the target system.<br />
Metasploit ranking system: https://github.com/rapid7/metasploit-framework/wiki/Exploit-Ranking

<br /><br />

### The Msf::Post Mixin
![msf-auxiliarys](http://i.cubeupload.com/gvgw2G.png)
One of the first things that is done is the implementaion of the **class** Msf::Post mixin.<br />
When you create a post module with this mixin, a lot of other mixins are also already included.<br />
Msf::Post::File http://rapid7.github.io/metasploit-framework/api/Msf/Post/File.html<br />
Msf::Post::Linux::Priv http://rapid7.github.io/metasploit-framework/api/Msf/Post/Linux/Priv.html<br />
Msf::Post::Linux::System: http://rapid7.github.io/metasploit-framework/api/Msf/Post/Linux/System.html<br />

<br /><br />

### The 'def initialize()' function
Here we need to define some information about the post module, such as:<br />
Module name, description, module author, version, platform, target architecture, DefaultOptions, etc.<br />
![msf-auxiliarys](http://i.cubeupload.com/eHlLPT.png)

Here we can adicionaly config module's default settings using the **DefaultOptions** method
![msf-auxiliarys](http://i.cubeupload.com/4H3A1x.png)


<br /><br />

### The register_options method (show options)
![msf-auxiliarys](http://i.cubeupload.com/qEoaAE.png)
This method adds options that the user can specify before running the module.<br />
The **OptString.new()** API accepts string values (text-numbers-symbols) to be inputed manually by user<br />

**HINT**: in **DefaultOptions** method we allready have defined the module to run againts session 1 by default.<br />
But users can still define (manually) a different session number to run module againts, example: set SESSION 3  

<br /><br />

### The register_advanced_options method (show advanced options)
![msf-auxiliarys](http://i.cubeupload.com/TSfW5w.png)
This method adds advanced options that the user can specify before running the module.<br />
The **OptBool.new()** API accepts bollean values (1 or 0 - true or false) to be inputed manually by user<br />
The **OptString.new()** API accepts string values (text-numbers-symbols) to be inputed manually by user<br />

<br /><br />

### Close the 'def initialize()' funtion
![msf-auxiliarys](http://i.cubeupload.com/ACpzcT.png)<br />
**HINT**: Funtions in ruby start with **def** (definition) follow by the body of the method (funtion logic)<br />
and it closes the funtion using the **end** statement (It tells Ruby that we’re done defining the method)


<br /><br /><br /><br />

# 3 - The 'exploit' code (def run)

      The 'def run()' funtion will contain all the 'exploit' code to be executed againt target session.
      It contains the module 'banner' the target 'compatibility checks' and the actual 'exploit' code.

      HINT: loading 'require msf/core/post/common' msf library in the beggining of the post-module,
      allows us to use most of the APIs used in post-exploitation develop (eg. client.sys.config.getuid).
<br /><br />

### writing the module 'banner'
![msf-auxiliarys](http://i.cubeupload.com/HjxmZp.png)<br />
The **session = client** API tells msf that **session** variable holds the **client** meterpreter communications chanel.<br />
The **print_line()** API allow us to write msgs on screen (terminal) and its used to build the module 'banner' in this case.<br />

<br /><br />

### writing the 'target compatibility checks' funtion
![msf-auxiliarys](http://i.cubeupload.com/7OHAEL.png)<br />
The line 12 uses meterpreter **sysinfo['OS']** API to check if target system its a **linux** distro<br />
The line 13 **print_error()** prints a error msg on screen, if none of the strings are returned: **Linux** or **linux**<br />
The line 14 **return nil** will exit module execution, if none of the above strings are returned<br />
The line 15 **end** will close the actual funtion, and resumes script execution.<br />

<br /><br />

![msf-auxiliarys](http://i.cubeupload.com/dDDnow.png)<br />
The line 19 will use **getuid** meterpreter API call, to check if we are running in an higth integrity context (root)<br />
`HINT: then it stores the returned string into a local variable named 'target_uid' for later use.`<br /><br />
The line 20 reads the **target_uid** local variable, and searchs for **uid=0** or **root** strings present<br />
`HINT: that reveal us that we are running under a privileged session (root privileges).`<br /><br />
The line 21 **print_error()** prints a error msg on screen, if none of the strings are returned: **uid=0** or **root**<br />
The line 22 **return nil** will exit module execution, if none of the above strings are returned<br />
The line 23 **end** will close the actual funtion, and resumes script execution.<br />

<br /><br />

![msf-auxiliarys](http://i.cubeupload.com/gZOBT6.png)<br />
The line 28 uses **sysinfo** meterpreter API call, to check if we are running in a meterpreter session<br />

      the sysinfo.nil? API checks if the sysinfo command returned, contains a empty string.
      the non-return of sysinfo command reveals that we are not on a meterpreter session!

The line 29 **print_status()** prints a msg on screen, if we are running in a meterpreter session.<br />
`HINT: If a meterpreter session its found, then script execution will jump to the end of this funtion`<br /><br />
The line 30 **else** will execute the 'non-meterpreter session' NOT found funtion<br />
The line 31 **print_error()** prints a error msg on screen, if we are NOT running in a meterpreter session.<br />
The line 32 **return nil** will exit module execution, if we are NOT running in a meterpreter session.<br />
The line 33 **end** will close the actual funtion, and resumes script execution.<br />

<br /><br />

### writing the 'exploit code'
![msf-auxiliarys](http://i.cubeupload.com/QRvSWa.png)<br />
The line 39 cleans the contents of **data_dump** local variable to be able to accept new data inputs.<br />
The line 40 **print_status()** prints a msg on screen for users to know that the module its working<br />
The line 41 **Rex::sleep(0.5)** makes a pause in script execution for half a second<br />

<br /><br />

![msf-auxiliarys](http://i.cubeupload.com/7cXJmO.png)<br />
From line 43 to 46 we are executing bash commands remotelly, and store the results inside local variables<br />
`HINT: The cmd_exec() API allow us to execute remotelly bash commands (in linux distros)`<br />

<br /><br />

This next funtion will store the contents of previous scans (stored inside local variables)<br />
into **data_dump** local variable to be able to write the logfile, and display outputs to user later.<br />
![msf-auxiliarys](http://i.cubeupload.com/Axodxo.png)<br />
The line 51 **data_dump << "\n\n"** will append 2 empty lines into **data_dump** local variable.<br />
The line 58 **data_dump << hardware_info** will append the contents of **hardware_info** inside **data_dump**<br />

<br /><br />

### writing the 'agressive_dump' advanced option funtion
`HINT: In ruby every IF funtion must be closed by the END statement.`<br />
![msf-auxiliarys](http://i.cubeupload.com/dnwV7r.png)<br />
The line 74 checks whats the settings of 'AGRESSIVE_DUMP' advanced option (if its **true** then it will run the funtion)<br />
The line 75 **print_status()** prints a msg on screen for users to know that the module its working<br />
The line 76 **Rex::sleep(0.5)** makes a pause in script execution for half a second<br />

<br /><br />

![msf-auxiliarys](http://i.cubeupload.com/ByQn9d.png)
From line 78 to 81 we are executing bash commands remotelly, and store the results inside local variables<br />
`HINT: The cmd_exec() API allow us to execute remotelly bash commands (in linux distros)`<br />

<br /><br />

This next funtion will store the contents of previous scans (stored inside local variables)<br />
into **data_dump** local variable to be able to write the logfile, and display outputs to user later.<br />
![msf-auxiliarys](http://i.cubeupload.com/BjByPP.png)
The line 102 **end** will close the actual funtion (agressive_dump), and resumes script execution.<br />
`HINT: In ruby every IF funtion must be closed by the END statement.`

<br /><br />

![msf-auxiliarys](http://i.cubeupload.com/bZzIoc.png)

<br /><br />

![msf-auxiliarys](http://i.cubeupload.com/D4kD0u.png)

<br /><br />

![msf-auxiliarys](http://i.cubeupload.com/OymZ84.png)

<br /><br /><br /><br />

# 4 - Port module to metasploit database

      At this stage we need to port our post-module to the rigth location inside metasploit
      directory structure, reload the database with the new module and load/run the module.

      HINT: reloading our module to msfdb will reveal us if any syntax error was commited.
      loading/executing the module will also reveal us if any sintax errors was commited.

#### Download linux_hostrecon V1.2 (latest review)
`wget https://github.com/r00t-3xp10it/msf-auxiliarys/blob/master/linux/linux_hostrecon.rb`
#### port the module to msf directory
`cp linux_hostrecon.rb /usr/share/metasploit-framework/modules/post/linux/gather/linux_hostrecon.rb`
#### start postgresql service
`service postgresql start`
#### rebuild msfdb database (database.yml)
`msfdb reinit`
#### reload all modules into database
`msfconsole -q -x 'db_status; reload_all'`
#### search for module
`msf > search linux_hostrecon`
#### load module
`msf > use post/linux/gather/linux_hostrecon`
#### show all module options
`msf post(linux_hostrecon) > show advanced options`
#### set module options
`msf post(linux_hostrecon) > set SINGLE_COMMAND netstat -ano`
#### execute module (run)
`msf post(linux_hostrecon) > exploit`
#### unset all module options
`msf post(linux_hostrecon) > unset_all`

<br /><br />

## Final Notes

      This module requires a session allready open to interact with it 
      This module requires a meterpreter session to run
      This module requires a linux distro as target
      This module requires root privileges to execute tasks
      This module stores dump logfiles into ~msf4/loot folder
      This module enables users to run options indevidually or all at once
      This module enables users to input a single bash command to be executed

      HINT: the single_command option accepts semi-collons to stack bash commands.
      EXAMPLE: cat /etc/passwd && cat /etc/shadow && find /var/log -type f -perm -4


![msf-auxiliarys](http://i.cubeupload.com/wO8vzX.png)


<br /><br />

#### linux_hostrecon.rb (v1.2) video tutorial:
https://youtube/blablabla

#### linux_hostrecon.rb (v1.2) sourcecode:
https://github.com/r00t-3xp10it/msf-auxiliarys/blob/master/linux/linux_hostrecon.rb

<br /><br />

## REFERENCES
http://rapid7.github.io/metasploit-framework/api/<br />
https://www.offensive-security.com/metasploit-unleashed/building-module/<br />
https://www.offensive-security.com/metasploit-unleashed/creating-auxiliary-module/<br />
https://github.com/rapid7/metasploit-framework/wiki/How-to-get-started-with-writing-a-post-module<br />
https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC[ERB]/metasploit-API/my-API-Cheat-sheet<br />

# @SSA Red_Team 2017

