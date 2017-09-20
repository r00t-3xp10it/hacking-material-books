



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
               2 - Write template: Basic explaination of 'include' 'require' 'class name' and module description
               3 - Write funtion logic: Basic explaination of ruby syntax + metasploit API calls
               4 - Port module to msf database: Copy module to the rigth location and reload msfdb


<br /><br /><br /><br />

# WRITING A MSF POST MODULE (step by step)


## 1 - research:


      'LIST OF BASH COMMANDS TO BE USED TO DUMP TARGET SYSTEM INFORMATION'

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


## 2 - build metasploit template

<br />

#### Module dependencies/requires
![msf-auxiliarys](http://i.cubeupload.com/qOUGPr.png)
Adding **require msf/core** will include all the functionalitys from the **core library**. the framework’s core library
is the low-level interface that provides the required functionality for interacting with exploit modules, sessions,
plugins, post modules, etc.<br /> This line alone gives us access to over **6,000+ different functions**. 

Adding **require msf/core/post/common** allow us to use the API **cmd_exec()** to execute bash commands on remote system.<br />
**cmd_exec()**: http://rapid7.github.io/metasploit-framework/api/Msf/Post/Common.html#cmd_exec-instance_method

<br />

#### Module class name and rank
![msf-auxiliarys](http://i.cubeupload.com/ETlv6v.png)
we begin defining the **class** and inherit from **Msf::Post**. Metasploit post modules are special in that they aren’t
necessarily exploits that feature a payload. Instead, they can be considered as **reconnaissance tools**. This includes
tools like port scanners, fuzzers, service fingerprinters, enumeration, information gathering, etc.

**Rank** = Every exploit module has been assigned a rank based on its potential impact to the target system.<br />
Metasploit ranking: https://github.com/rapid7/metasploit-framework/wiki/Exploit-Ranking

<br />

#### The Msf::Post Mixin
![msf-auxiliarys](http://i.cubeupload.com/cqF7gH.png)
One of the first things that is done is the implementaion of the **class** Msf::Post mixin.<br />
When you create a post module with this mixin, a lot of other mixins are also already included.<br />
Class Msf::Post http://rapid7.github.io/metasploit-framework/api/Msf/Post.html<br />

    mixins loaded by Msf::Post method class

    msf/core/post/common - Common methods post modules use, for example: cmd_exec.
    msf/core/post_mixin - Keeps track of the session state.
    msf/core/post/file - File system related methods.
    msf/core/post/webrtc - Uses WebRTC to interact with the target machine's webcam.
    msf/core/post/linux - There actually isn't a lot going on, just get_sysinfo and is_root? specifically for Linux.
    msf/core/post/osx - get_sysinfo, get_users, get_system_accounts, get_groups, and methods for operating the target machine's webcam.
    msf/core/post/solaris - Pretty much like the linux mixin. Same methods, but for Solaris.
    msf/core/post/unix - get_users, get_groups, enum_user_directories
    msf/core/post/windows - From Windows account management, event log, file info, Railgun, LDAP, netapi, powershell, registry, wmic, services, etc.

Msf::Post::Linux::System: http://rapid7.github.io/metasploit-framework/api/Msf/Post/Linux/System.html

<br />

#### Module description (info)
![msf-auxiliarys](http://i.cubeupload.com/eHlLPT.png)

<br />

#### The register_options method (show options)
![msf-auxiliarys](http://i.cubeupload.com/qEoaAE.png)
This method adds options that the user can specify before running the module.<br />
The **OptString.new()** method accepts string values (text)

<br />

#### The register_advanced_options method (show advanced options)
![msf-auxiliarys](http://i.cubeupload.com/TSfW5w.png)
This method adds advanced options that the user can specify before running the module.<br />
The **OptBool.new()** method accepts bollean values (1 or 0 - true or false)

<br /><br /><br />

## 3 - write metasploit post-module funtion logic

<br /><br /><br />

## 4 - port module to metasploit database




<br /><br /><br /><br />



# LINUX_HOSTRECON POST-MODULE
https://github.com/r00t-3xp10it/msf-auxiliarys/blob/master/linux/linux_hostrecon.rb



# REFERENCES
https://github.com/rapid7/metasploit-framework/wiki
https://en.wikibooks.org/wiki/Metasploit/DevelopingAuxiliaryModules
https://www.offensive-security.com/metasploit-unleashed/building-module/
https://www.offensive-security.com/metasploit-unleashed/creating-auxiliary-module/
https://github.com/rapid7/metasploit-framework/wiki/How-to-get-started-with-writing-an-exploit
https://github.com/rapid7/metasploit-framework/wiki/How-to-get-started-with-writing-a-post-module



First, I included Metasploit’s TCP library (include Msf::Exploit::Remote::Tcp), as I need to connect to a TCP server.

In initialize(), you need to define some information about the exploit module, such as name, description, payload encoding and target architecture. In this case, I will not use any payload encoding for the sake of simplicity, and the target architecture would be linux x86


The datastore

The options set by a user are available via a predefined hash named datastore. For example:
 print_status("the contents of the DATA variable are: " + datastore['DATA'])

