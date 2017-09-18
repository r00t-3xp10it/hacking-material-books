



## DESCRIPTION

                Metasploit modules are writting in ruby. Even if you don’t know a lot about ruby,
             you should still be able to write a metasploit linux post module based on this tutorial


<br /><br />  

## MODULE OBJECTIVES
                module objectives are: gather system information after succcessfully exploitation
                we are going to use a special msf API call (exec_com) to be able to execute bash
                commands remotelly in target system


<br /><br />  

##    MODULE DEVELOP METHODOLOGIE

               1 - research: for bash commands that can be used to dump target system information
               2 - write skelleton: basic explaination of 'include' 'require' 'class name' and module description
               3 - write funtion logic: basic explaination of ruby syntax + metasploit API calls
               4 - port module to msf database: copy module to the rigth location and reload msfdb



<br /><br />

## WRITING A POST MODULE (step by step)


1 - research: for bash command that can be used to dump target system information




2 - build metasploit skelleton

![msf-auxiliarys](http://i.cubeupload.com/qOUGPr.png)
we are going to include all the functionality from the core library. MSF has a modular structure and is broken down into several pieces: the framework core, base, and ui. know that the framework’s core library is the low-level interface that provides the required functionality for interacting with exploit modules, sessions, plugins, etc. This line alone gives us access to some 6,000+ different functions.

![msf-auxiliarys](http://i.cubeupload.com/ETlv6v.png)
we begin defining the class and inherit from Msf::Post. Metasploit post modules are special in that they aren’t necessarily exploits that feature a payload. Instead, they can be considered as reconnaissance tools. This includes tools like port scanners, fuzzers, service fingerprinters, enumeration, information gathering, etc.




3 - write metasploit post-module funtion logic



4 - port module to metasploit database




<br /><br />



## LINUX HOST_RECON MODULE
https://github.com/r00t-3xp10it/msf-auxiliarys/blob/master/linux/linux_hostrecon.rb
