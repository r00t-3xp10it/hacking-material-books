



# INTRO
                                 'writing a linux post module from scratch'
                Metasploit modules are written in ruby. Even if you don’t know a lot about ruby,
             you should still be able to write a metasploit linux post module based on this tutorial!

<br /><br />  

# MODULE OBJECTIVES
                Module name: linux_hostrecon.rb
                Affected systems: Linux (Unix)
                Arch: x84 bits | x64 bits

                Module objectives: Gather system information after succcessfully exploitation.
                For that we are going to load the msf/core/post/common module to use the MSF
                API 'cmd_exec()' to execute bash commands on remote system, display outputs,
                and store outputs to logfile (store_loot).


<br /><br />  

# MODULE DEVELOP METHODOLOGIE

               1 - Research: For bash commands that can be used to dump target system information
               2 - Build template: Basic explaination of librarys, class name, mixins and description
               3 - Write funtion logic: Basic explaination of ruby syntax + metasploit APIs (def run)
               4 - Port module to msf database: Copy module to the rigth location and reload msfdb


<br /><br /><br /><br />

# WRITING A MSF POST MODULE (step by step)

# 1 - The research stage:

      At this stage (research) i have used online articles from diferent websites to store
      possible interesting bash commands that can be used in gathering target system information.  

![msf-auxiliarys](http://i.cubeupload.com/YK7B6f.png)


<br /><br /><br />


# 2 - Building the metasploit template

      The metasploit template its divided in to 3 main funtions.
      the librarys/class-name/mixins that contains module requires/imports, the 'def initialize()' funtion
      that contains module description/settings, and the 'def run()' funtion that contain the script logic.

      At this stage we are going to focous in the 'librarys/class-name/mixins' and 'def initialize()' funtions

<br /><br />

### The MSF librarys
![msf-auxiliarys](http://i.cubeupload.com/EZbnFy.png)<br />
**rex** the basic library for most tasks: Handles sockets, protocols, text transformations, SSL, SMB, HTTP, XOR, Base64, etc.

**msf/core** will include all the functionalitys from the core library. the framework’s core library is the low-level<br />
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

#### The def initialize(info)
![msf-auxiliarys](http://i.cubeupload.com/m77AgR.png)
**HINT**: Funtions in ruby start with **def** (definition) follow by the body of the method (funtion logic)<br />
and it closes the funtion using the **end** statement (It tells Ruby that we’re done defining the method)

     def hi
       puts "Hello World!"
     end

<br />
![msf-auxiliarys](http://i.cubeupload.com/eHlLPT.png)
**def initialize(info={})** Here we need to define some information about the post module, such as:<br />
Module name, description, module author, version, platform, target architecture, DefaultOptions, etc.<br />

Here we can adicionaly config module's default settings using the **DefaultOptions** method
![msf-auxiliarys](http://i.cubeupload.com/4H3A1x.png)


<br /><br />

#### The register_options method (show options)
![msf-auxiliarys](http://i.cubeupload.com/PF4Bdv.png)
![msf-auxiliarys](http://i.cubeupload.com/qEoaAE.png)
The **OptString.new()** API accepts string values (text-numbers-symbols)<br />
This method adds options that the user can specify before running the module.<br />

**HINT**: in **DefaultOptions** method we allready have defined the module to run agains session 1 by default.<br />
But users can still define (manually) a diferent session number to the run module againts (set SESSION 3).  

<br /><br />

#### The register_advanced_options method (show advanced options)
![msf-auxiliarys](http://i.cubeupload.com/xpmFB9.png)
![msf-auxiliarys](http://i.cubeupload.com/TSfW5w.png)
The **OptBool.new()** API accepts bollean values (1 or 0 - true or false)<br />
This method adds advanced options that the user can specify before running the module.<br />

**HINT**: The first value as **true** show us that is one **required** setting to run the module,<br />
The second value as **false** it activates or not the funtion to be run, If the second field its empty,<br />
it meens that module its waiting for user input settings to run the funtion. 

<br /><br />

#### Close the 'def initialize()' funtion
![msf-auxiliarys](http://i.cubeupload.com/ACpzcT.png)<br />
At this stage we have done writing the **def initialize()** funtion (module description/settings).<br/>
Now we need to close the funtion with the **end** statement, before start writing the **def run()** funtion.

<br />

**HINT**: The options set by a user are available via a predefined hash named datastore<br />
The settings of **'SESSION'** **'STORE_LOOT'** **'AGRESSIVE_DUMP'** and **'SINGLE_COMMAND'**<br />
will be stored into msfdb (metasploit database) and they can be called later to script logic.

      example: The next funtion will read the value inside the 'STORE_LOOT' option,
               and if its config as 'true' it will run the follow funtion (store_loot).
      
      if datastore['STORE_LOOT'] == true
        print_good("storing dump into loot folder ..")
        store_loot("hostrecon", "text/plain", session, data_dump, "hostrecon.txt", "linux_hostrecon")
      end

<br /><br /><br />

# 3 - Write metasploit post-module funtion logic (def run)

<br /><br /><br />

# 4 - Port module to metasploit database

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

