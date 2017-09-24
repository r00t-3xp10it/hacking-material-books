



# INTRO
                                 'writing a linux post module from scratch'
                Metasploit modules are written in ruby. Even if you don’t know a lot about ruby,
             you should still be able to write a metasploit linux post module based on this tutorial!

![msf-auxiliarys](http://i.cubeupload.com/m77AgR.png)

<br /><br />  

# MODULE OBJECTIVES
                Gather system information after succcessfully exploitation (post-exploitation).
                For that we are going to load the msf/core/post/common module to use the MSF
                API 'cmd_exec()' to execute bash commands on remote system, display outputs,
                and store outputs to logfile (store_loot).

<br /><br />  

# MODULE DEVELOP METHODOLOGY

               1 - The Research stage: bash commands that can be used to dump target system information
               2 - The metasploit template: Basic explaination of librarys, class name, mixins, description
               3 - The exploit code logic: Basic explaination of ruby syntax + metasploit APIs (def run)
               4 - Port module to msf database: Copy module to the rigth location and reload msfdb


<br /><br /><br /><br />

# WRITING A MSF POST MODULE (step by step)

# 1 - The research stage:

      At this stage (research) i have used online articles from different websites to store
      possible interesting bash commands that can be used in gathering target system information.  

![msf-auxiliarys](http://i.cubeupload.com/YK7B6f.png)


<br /><br /><br />


# 2 - The metasploit template

      The metasploit template its divided in to 3 main funtions.
      1 - the librarys, class name, mixins that contains module requires/imports.
      2 - the 'def initialize()' funtion that contains module description/settings.
      3 - and the 'def run()' funtion that contain the script logic (exploit code).

      At this stage we are going to focous in the 'librarys' and 'def initialize()' funtions

<br /><br />

### The MSF librarys
![msf-auxiliarys](http://i.cubeupload.com/EZbnFy.png)<br />
**rex** the basic library for most tasks: Handles sockets, protocols, text transformations, SSL, SMB, HTTP, XOR, Base64, etc.

**msf/core** will include all the functionalities from the core library. the framework’s core library is the low-level<br />
interface that provides the required functionality for interacting with exploit modules, sessions, plugins, etc.<br />
This line alone gives us access to over 6,000+ different functions.<br />

**msf/core/post/common** allow us to use the API cmd_exec() to execute bash commands on remote system (linux).<br />
cmd_exec(): http://rapid7.github.io/metasploit-framework/api/Msf/Post/Common.html#cmd_exec-instance_method

<br /><br />

#### The Module class name and rank
![msf-auxiliarys](http://i.cubeupload.com/ZcWceG.png)
we begin defining the **class** as MetasploitModule and inherit from **Msf::Post** mixin. Metasploit post modules are special<br />
in that they aren’t necessarily exploits that feature a payload. Instead, they can be considered as **reconnaissance tools**.<br />
This includes port scanners, fuzzers, service fingerprinters, enumeration, information gathering, post-exploitation, etc.

**Rank** = Every module has been assigned a rank based on its potential impact to the target system.<br />
Metasploit ranking system: https://github.com/rapid7/metasploit-framework/wiki/Exploit-Ranking

<br /><br />

#### The Msf::Post Mixin
![msf-auxiliarys](http://i.cubeupload.com/gvgw2G.png)
One of the first things that is done is the implementaion of the **class** Msf::Post mixin.<br />
When you create a post module with this mixin, a lot of other mixins are also already included.<br />
Msf::Post::File http://rapid7.github.io/metasploit-framework/api/Msf/Post/File.html<br />
Msf::Post::Linux::Priv http://rapid7.github.io/metasploit-framework/api/Msf/Post/Linux/Priv.html<br />
Msf::Post::Linux::System: http://rapid7.github.io/metasploit-framework/api/Msf/Post/Linux/System.html<br />

<br /><br />

#### The 'def initialize()' function
Here we need to define some information about the post module, such as:<br />
Module name, description, module author, version, platform, target architecture, DefaultOptions, etc.<br />
![msf-auxiliarys](http://i.cubeupload.com/eHlLPT.png)

Here we can adicionaly config module's default settings using the **DefaultOptions** method
![msf-auxiliarys](http://i.cubeupload.com/4H3A1x.png)


<br /><br />

#### The register_options method (show options)
![msf-auxiliarys](http://i.cubeupload.com/qEoaAE.png)
This method adds options that the user can specify before running the module.<br />
The **OptString.new()** API accepts string values (text-numbers-symbols) to be inputed manually by user<br />

**HINT**: in **DefaultOptions** method we allready have defined the module to run agains session 1 by default.<br />
But users can still define (manually) a different session number to run module againts, example: set SESSION 3  

<br /><br />

#### The register_advanced_options method (show advanced options)
![msf-auxiliarys](http://i.cubeupload.com/TSfW5w.png)
This method adds advanced options that the user can specify before running the module.<br />
The **OptBool.new()** API accepts bollean values (1 or 0 - true or false) to be inputed manually by user<br />
The **OptString.new()** API accepts string values (text-numbers-symbols) to be inputed manually by user<br />

<br />

#### Close the 'def initialize()' funtion
![msf-auxiliarys](http://i.cubeupload.com/ACpzcT.png)<br />
**HINT**: Funtions in ruby start with **def** (definition) follow by the body of the method (funtion logic)<br />
and it closes the funtion using the **end** statement (It tells Ruby that we’re done defining the method)


<br /><br /><br />

# 3 - The 'exploit' code (def run)

      The 'def run()' funtion will contain all the 'exploit' code to be executed againt target session.
      It contains the module 'banner' the target 'compatibility checks' and the actual 'exploit' code.

<br />

#### writing the module 'banner'
![msf-auxiliarys](http://i.cubeupload.com/mveW2q.png)<br />
The **session = client** API tells msf that **session** variable holds the **client** meterpreter communications.<br />
The **print_line()** API allow us to write on screen (terminal)

<br />

#### writing the module 'compatibility checks'
![msf-auxiliarys](http://i.cubeupload.com/Y2G72X.png)<br />
The line 12 uses meterpreter **sysinfo['OS']** module to check if target system its a **linux distro**<br />



<br /><br /><br /><br />



      example: The next funtion will read the value inside the 'STORE_LOOT' option,
               and if its config as 'true' it will run the follow funtion (store_loot).
      
      if datastore['STORE_LOOT'] == true
        print_good("storing dump into loot folder ..")
        store_loot("hostrecon", "text/plain", session, data_dump, "hostrecon.txt", "linux_hostrecon")
      end

<br /><br /><br />

# 4 - Port module to metasploit database

      At this stage we need to port our post-module to the rigth location inside metasploit
      directory structure, reload the database with the new module and load/run the module.

      HINT: reloading our module to msfdb will reveal us if any syntax error was commited.
      loading/executing the module will also reveal us if any sintax errors was commited.

#### port module to msf database
`cp linux_hostrecon.rb /usr/share/metasploit-framework/modules/post/linux/gather/linux_hostrecon.rb`
#### start postgresql database
`service postgresql start`
#### rebuild msfdb database (database.yml)
`msfdb reinit`
#### reload msfdb database
`msfconsole -q -x 'db_status; reload_all'`

#### search module
`msf > search linux_hostrecon`
#### load module
`msf > use post/linux/gather/linux_hostrecon`

#### show all module options
`msf post(linux_hostrecon) > show advanced options`
#### set module options
`msf post(linux_hostrecon) > set SINGLE_COMMAND netstat -ano`
#### execute module (run)
`msf post(linux_hostrecon) > exploit`


<br /><br /><br /><br />

### Download/read linux_hostrecon.rb post-module from here:
https://github.com/r00t-3xp10it/msf-auxiliarys/blob/master/linux/linux_hostrecon.rb

<br /><br /><br />

## REFERENCES
https://github.com/rapid7/metasploit-framework/wiki
https://en.wikibooks.org/wiki/Metasploit/DevelopingAuxiliaryModules
https://www.offensive-security.com/metasploit-unleashed/building-module/
https://www.offensive-security.com/metasploit-unleashed/creating-auxiliary-module/
https://github.com/rapid7/metasploit-framework/wiki/How-to-get-started-with-writing-an-exploit
https://github.com/rapid7/metasploit-framework/wiki/How-to-get-started-with-writing-a-post-module

# SSA Red_Team

