## METASPLOIT RESOURCE FILES

<blockquote>Resource scripts provide an easy way for you to automate repetitive tasks in Metasploit. Conceptually, they're just like batch scripts. They contain a set of commands that are automatically and sequentially executed when you load the script in Metasploit. You can create a resource script by chaining together a series of Metasploit console commands and by directly embedding Ruby to do things like call APIs, interact with objects in the database, and iterate actions.</blockquote>

![pic](http://i68.tinypic.com/21ovkfm.jpg)

| article chapters | jump links | API examples |
|-------|---|---|
| resource files | [resource files examples](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit_resource_files.md#resource-files-examples) |  run migrate -n wininit.exe |
| erb scripting| [ERB scripting](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit_resource_files.md#erb-scripting-ruby) | run_single("services #{framework.datastore['RHOSTS']}") |

<br />

### Description:
<blockquote>The console (msfconsole or msf pro) supports basic automation using resource scripts. These scripts contain a set of console commands that are executed when the script loads. In addition to the basic console (core) commands, these scripts are also treated as ERB models. ERB is a way to embed Ruby code directly into a document. This allows you to call APIs that are not exposed through console commands and until you programmatically generate and return a list of commands based on your own logic. Resource scripts can be specified with the -r option for the Metasploit Console and runs automatically on startup if it exists. Resource scripts can also be run from the console prompt through the resource command (msf> resource file-to-run.rc)</blockquote>


<br />

## EXTERNAL LINKS

- [Rapid7 resource files](https://metasploit.help.rapid7.com/docs/resource-scripts)

---

<br /><br /><br />

## RESOURCE FILES EXAMPLES

- **The following example creates a resource file to display the version number of metasploit.**

      touch version.rc
      echo 'version' >> version.rc

      run  :  msfconsole -r version.rc
      or    :  msfconsole -r /root/version.rc
      or    :  msf > resource /root/version.rc

<br />

#### [!] [Jump to article index](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit_resource_files.md#metasploit-resource-files)

---

<br /><br /><br />

## ERB SCRIPTING (ruby)




#### [!] [Jump to article index](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit_resource_files.md#metasploit-resource-files)

---

<br /><br /><br />


