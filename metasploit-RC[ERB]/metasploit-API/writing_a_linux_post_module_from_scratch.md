



## INTRO
                                 'writting a linux post module from scratch'
                Metasploit modules are writting in ruby. Even if you don’t know alot about ruby,
             you should still be able to write a metasploit linux post module based on this tutorial!

<br /><br />  

## MODULE OBJECTIVES
                Module name: linux_hostrecon.rb
                Affected systems: Linux (Unix)
                Arch: x84 bits | x64 bits

                Module objectives: Gather system information after succcessfully exploitation.
                Adicionally we are going to use a special MSF API call 'exec_com()' to be able to
                execute bash commands remotelly in target sys, display outputs and store to logfile.


<br /><br />  

## MODULE DEVELOP METHODOLOGIE

               1 - Research: For bash commands that can be used to dump target system information
               2 - Write skelleton: Basic explaination of 'include' 'require' 'class name' and module description
               3 - Write funtion logic: Basic explaination of ruby syntax + metasploit API calls
               4 - Port module to msf database: Copy module to the rigth location and reload msfdb


<br /><br /><br />

## WRITTING A MSF POST MODULE (step by step)


### 1 - research:


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


### 2 - build metasploit skelleton

<br />

Module dependencies/requires
![msf-auxiliarys](http://i.cubeupload.com/qOUGPr.png)
we are going to include all the functionalitys from the core library. MSF has a modular structure and is broken down into several pieces: the framework core, base, and ui. the framework’s core library is the low-level interface that provides the required functionality for interacting with exploit modules, sessions, plugins, etc. This line alone gives us access to some 6,000+ different functions.

<br />

Module class name and rank
![msf-auxiliarys](http://i.cubeupload.com/ETlv6v.png)
we begin defining the class and inherit from Msf::Post. Metasploit post modules are special in that they aren’t necessarily exploits that feature a payload. Instead, they can be considered as reconnaissance tools. This includes tools like port scanners, fuzzers, service fingerprinters, enumeration, information gathering, etc.

<br />

Module includes (mixins)
![msf-auxiliarys](http://i.cubeupload.com/cqF7gH.png)
Metasploit mixin: http://rapid7.github.io/metasploit-framework/api/Msf/Post/Linux/System.html

<br />

Module description (info)
![msf-auxiliarys](http://i.cubeupload.com/eHlLPT.png)

<br />

![msf-auxiliarys](http://i.cubeupload.com/qEoaAE.png)

<br />

![msf-auxiliarys](http://i.cubeupload.com/TSfW5w.png)

<br /><br /><br />

### 3 - write metasploit post-module funtion logic

<br /><br /><br />

### 4 - port module to metasploit database




<br /><br /><br />



## LINUX_HOSTRECON POST-MODULE
https://github.com/r00t-3xp10it/msf-auxiliarys/blob/master/linux/linux_hostrecon.rb
