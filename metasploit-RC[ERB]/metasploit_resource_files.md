## METASPLOIT RESOURCE FILES

<blockquote>Resource scripts provide an easy way for you to automate repetitive tasks in Metasploit. Conceptually, they're just like batch scripts. They contain a set of commands that are automatically and sequentially executed when you load the script in Metasploit. You can create a resource script by chaining together a series of Metasploit console commands and by directly embedding Ruby to do things like call APIs, interact with objects in the database, and iterate actions.</blockquote>

![pic](http://i68.tinypic.com/21ovkfm.jpg)


<blockquote>The console (msfconsole or msf pro) supports basic automation using resource scripts. These scripts contain a set of console commands that are executed when the script loads. In addition to the basic console (core) commands, these scripts are also treated as ERB models. ERB is a way to embed Ruby code directly into a document. This allows you to call APIs that are not exposed through console commands and until you programmatically generate and return a list of commands based on your own logic. Resource scripts can be specified with the -r option for the Metasploit Console and runs automatically on startup if it exists. Resource scripts can also be run from the console prompt through the resource command (msf> resource file-to-run.rc)</blockquote>

| article chapters | jump links | API examples |
|-------|---|---|
| metasploit skeleton | [requires-includes-info](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/metasploit-RC%5BERB%5D/metasploit-API/my-API-Cheat-sheet.md#metasploit-skeleton) | include Msf::Post::Linux::System |

<br />

## EXTERNAL LINKS

- [Rapid7 resource files](https://metasploit.help.rapid7.com/docs/resource-scripts)

