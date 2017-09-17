



##                                                 DESCRIPTION

                Metasploit modules are writting in ruby. Even if you don’t know a lot about ruby,
             you should still be able to write a metasploit linux post module based on this tutorial

  

                                       Metasploit exploit module structure
                    A typical metasploit post module consists of the following components :

                                       1 - header and some dependencies
                                           Some comments about the exploit module
                                           require ‘msf/core’
                                       2 - class definition
                                       3 - includes
                                       4 - “def” definitions :
                                            initialize
                                            def_run





## WRITING A POST MODULE (auxiliary)



1 - research



2 - build metasploit skelleton

![msf-auxiliarys](http://i.cubeupload.com/qOUGPr.png)
we are going to include all the functionality from the core library. MSF has a modular structure and is broken down into several pieces: the framework core, base, and ui. A full discussion of the MSF architecture is outside the scope of this tutorial but for now, know that the framework’s core library is the low-level interface that provides the required functionality for interacting with exploit modules, sessions, plugins, etc. This line alone gives us access to some 6,000+ different functions.

![msf-auxiliarys](http://i.cubeupload.com/ETlv6v.png)
we begin defining the class and inherit from Msf::Auxiliary. Metasploit auxiliary modules are special in that they aren’t necessarily exploits that feature a payload. Instead, they can be considered as reconnaissance tools. This includes tools like port scanners, fuzzers, service fingerprinters, enumeration, information gathering, etc.




3 - write metasploit post-module funtion logic



4 - port module to metasploit database


5 - debug post-module






## LINUX HOST_RECON MODULE
https://github.com/r00t-3xp10it/msf-auxiliarys/blob/master/linux/linux_hostrecon.rb
