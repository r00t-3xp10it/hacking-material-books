



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
               2 - Build template: Basic explaination of libraries, classname, mixins and module description
               3 - Write funtion logic: Basic explaination of ruby syntax + metasploit API calls logic
               4 - Port module to msf database: Copy module to the rigth location and reload msfdb


<br /><br /><br /><br />

# WRITING A MSF POST MODULE (step by step)

# 1 - The research stage:
In this stage (research) i have used online articles from diferent websites<br />
to store interesting bash commands that can be used in gathering target sys info.  

      # system information
      id
      df -h
      uname -a
      hostname
      cat /etc/*-release
 
      # Show the current date and time
      date
 
      # Show possible locations of app
      whereis firefox 
 
      # Display your currently active processes
      ps
 
      # lists available shells
      grep '^[^#]' /etc/shells
 
      # How to check which shell you are using?
      echo $0
 
      # How to check which is the default shell for you?
      echo "$SHELL"
 
      # dump credentials
      cat /etc/passwd | cut -d ":" -f 1,2,3,4
      cat /etc/shadow | cut -d ":" -f 1,2,3,4
 
      # Storage info
      cat /proc/partitions
 
      # distro release
      lsb_release -a | grep "Description"

      # hardware system info
      lscpu | grep "Architecture"; lscpu | grep "CPU op-mode"; lscpu | grep "Vendor ID"
 
      # list all root accounts (uid 0)
      grep -v -E "^#" /etc/passwd | awk -F: '$3 == 0 { print $1}'

      # lists all id's and respective group(s)
      for i in $(cat /etc/passwd | cut -d ":" -f1);do id $i;done
 
      # is root permitted to login via ssh ?
      grep "PermitRootLogin" /etc/ssh/sshd_config | grep -v "#" | awk '{print  $2}'
 
      # search for logfiles
      find /var/log -type f -perm -4
 
      # packages installed
      /usr/bin/dpkg -l
 
      # are there any cron jobs configured ?
      ls -la /etc/cron*
 
      # store gateway (192.168.1.254)
      cat /etc/resolv.conf | grep "nameserver" | awk {'print $2'}
 
      # store interface in use
      route | grep default | awk {'print $8'}
 
      # what account is apache running under
      cat /etc/apache2/envvars | grep -i 'user\|group' | awk '{sub(/.*\export /,"")}1'
 
      # can we read roots *_history files - could be passwords stored etc.
      ls -la /root/.*_history
 
      # memory info
      cat /proc/meminfo | grep "MemTotal"; cat /proc/meminfo | grep "MemFree"; cat /proc/meminfo | grep "MemAvailable"; cat /proc/meminfo | grep "Dirty"; cat /proc/meminfo | grep "SwapTotal"; cat /proc/meminfo | grep "SwapFree"


<br /><br /><br />


# 2 - Building the metasploit template

### MSF libraries
![msf-auxiliarys](http://i.cubeupload.com/EZbnFy.png)
**rex** the basic library for most tasks: Handles sockets, protocols, text transformations, SSL, SMB, HTTP, XOR, Base64, etc.

**msf/core** will include all the functionalitys from the core library. the framework’s core library is the low-level<br />
interface that provides the required functionality for interacting with exploit modules, sessions, plugins, etc.<br />
This line alone gives us access to over 6,000+ different functions.<br />

**msf/core/post/common** allow us to use the API cmd_exec() to execute bash commands on remote system.<br />
cmd_exec(): http://rapid7.github.io/metasploit-framework/api/Msf/Post/Common.html#cmd_exec-instance_method

<br /><br />

#### Module class name and rank
![msf-auxiliarys](http://i.cubeupload.com/ETlv6v.png)
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

#### Module description (info)
![msf-auxiliarys](http://i.cubeupload.com/eHlLPT.png)
**def initialize(info={})** here we need to define some information about the post module, such as:<br />
Module name, description, module author, version, platform, target architecture, etc. And close the<br/>
funtion with the **end** statement before start writing the def run() funtion ..

Here we can adicionaly config module's default settings using the **DefaultOptions** funtion
![msf-auxiliarys](http://i.cubeupload.com/4H3A1x.png)


<br /><br />

#### The register_options method (show options)
![msf-auxiliarys](http://i.cubeupload.com/qEoaAE.png)
The **OptString.new()** method accepts string values (text-numbers-symbols)<br />
This method adds options that the user can specify before running the module.<br />
HINT: in **DefaultOptions** funtion we allready have defined the module to run agains session 1 by default

<br /><br />

#### The register_advanced_options method (show advanced options)
![msf-auxiliarys](http://i.cubeupload.com/TSfW5w.png)
The **OptBool.new()** method accepts bollean values (1 or 0 - true or false)<br />
This method adds advanced options that the user can specify before running the module.<br />


<br />

**HINT**: Funtions in ruby start with **def** (definition) follow by the body of the method (funtion logic)<br />
and it closes the funtion using the **end** statement (It tells Ruby that we’re done defining the method)

     def hi
       puts "Hello World!"
     end

<br /><br /><br />

# 3 - Write metasploit post-module funtion logic

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





The datastore

The options set by a user are available via a predefined hash named datastore. For example:
 print_status("the contents of the DATA variable are: " + datastore['DATA'])

