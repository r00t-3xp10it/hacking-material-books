
                                           * PARSING DATA IN BASH *

      Parsing, syntax analysis, or syntactic analysis is the process of analysing a string of symbols,
      either in natural language, computer languages or data structures, conforming to the rules of a
      formal grammar. In the follow examples we will use the UNIX 'ifconfig' command as example.

![pic](http://i64.tinypic.com/205qy50.png)

      The 'ifconfig wlan0' presents many information about the current interface in use, but lets say
      we only need to 'extract' the ip address from ifconfig command and store that info into one bash
      variable (for scripting) or into a logfile for later review, its when 'parsing' its helpfull ..
      This article will show easy examples using bash commands like: GREP, CAT, AWK, CUT, HEAD, TAIL, etc.


<br /><br />

### Article Glossario
[1] [Parsing with grep](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md#grep)<br />
[2] [Parsing with cat](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md#cat)<br />
[3] [Parsing with awk](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md#awk)<br />
[4] [Parsing with cut](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md#cut)<br />
[5] [Parsing with head](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md#head)<br />
[6] [Parsing with tail](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md#tail)<br />

---

<br /><br />

### GREP

      grep searches the input files or commands for lines containing a match to a given pattern list.
      When it finds a match in a line, it copies the line to standard output (by default), or whatever
      other sort of output you have requested with grep command options.

<br />

- Print **'All'** lines that contains the **'inet'** expression<br />

      ifconfig wlan0 | grep "inet"

![pic](http://i66.tinypic.com/2uoi0sz.png)

- Colorize the matching expression<br />

      ifconfig wlan0 | grep "inet" --color=auto

![pic](http://i67.tinypic.com/vht43l.png)


- Outputs only the lines with **'inet'** in them (perfect match - not inet6)<br />

      ifconfig wlan0 | grep -w "inet"

![pic](http://i66.tinypic.com/25kraxc.png)

- Print only the **1º line** containing the **'inet'** expression<br />

      ifconfig wlan0 | egrep -m 1 "inet"

![pic](http://i64.tinypic.com/4vo5g0.png)

- Outputs only the matching expression (not the line)<br />

      ifconfig wlan0 | grep -o "inet6"

![pic](http://i68.tinypic.com/2vijvhx.png)
**HINT:** grep -o switch can be used to **'check'** if the suplied expression exists (scripting)<br />

- **Invert** the sence of matching (**delete matching lines** that contains the expression)<br />

      ifconfig wlan0 | grep -v "inet"

![pic](http://i67.tinypic.com/2upeloz.png)


<br />

**EXERCISE1:** Print only the line that contains **RX packets** expression<br />
With everything we have learn until now, how do you print only the line that contains the RX packets expression?<br />

**EXERCISE2:** Print only the line that contains your mac address<br />
With everything we have learn until now, how do you print only the line that contains your mac address?<br />

[?] [exercise1 soluction](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md#exercise1-ifconfig-wlan0--grep-rx-packets)<br />
[?] [exercise1 soluction](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md#exercise2-ifconfig-wlan0--grep-ether)<br />
[0] [article glossario](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md#article-glossario)<br />

---

<br /><br />

### CAT

      cat is a standard Unix utility that reads files sequentially, writing them to standard output.
      The name is derived from its function to concatenate files. 

<br />

- Read **article** file and print a line **only if:** the whole line matches your suppied regex<br />

      cat article | grep -x "This line will be displayed .."

![pic](http://i67.tinypic.com/14ne8b4.png)

- Print **all lines** that contains the **ERROR** expression<br />

      cat article | grep "ERROR"

![pic](http://i63.tinypic.com/rarr6e.png)

[0] [article glossario](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md#article-glossario)<br />

---

<br /><br />

### AWK

      Awk breaks each line of input passed to it into fields. By default, a field is a string of consecutive
      characters delimited by whitespace, though there are options for changing this. Awk parses and operates
      on each separate field. This makes it ideal for handling large text files, logfiles or databases.

<br />

- Grab **1º line** that contains the **'inet'** expression AND print the **2º field**<br />

      ifconfig wlan0 | egrep -m 1 "inet" | awk {'print $2'}

![pic](http://i68.tinypic.com/193st2.png)

- Grab **1º line** that contains the **'inet'** expression AND print **1º field + 2º field**<br />

      ifconfig wlan0 | egrep -m 1 "inet" | awk {'print $1,$2'}

![pic](http://i64.tinypic.com/2wcgpcz.png)

- Grab **1º line** that contains the **'inet'** expression AND print **3º field + 4º field**<br />

      ifconfig wlan0 | egrep -m 1 "inet" | awk {'print $3,$4'}

![pic](http://i66.tinypic.com/2urq9vn.png)

- **HINT:** Store IP address into one bash **variable** for later use (scripting)<br />

      parse_data=`ifconfig wlan0 | egrep -m 1 "inet" | awk {'print $2'}`
      echo my ip: $parse_data

![pic](http://i63.tinypic.com/vws7z7.png)


[0] [article glossario](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md#article-glossario)<br />

---

<br /><br />

### CUT

      The cut command in UNIX is a command for cutting out the sections from each line of files and writing
      the result to standard output. It can be used to cut parts of a line by byte position, character and field.
      Basically the cut command slices a line and extracts the text.

<br />

- grab 1º line that contains the 'inet' expression AND print 2º string | grab the 1º [.] and cut until the next [.]<br />

      ifconfig wlan0 | egrep -m 1 "inet" | awk {'print $2'} | cut -d '.' -f1

![pic](http://i64.tinypic.com/dmpic4.png)


- grab the 1º inet | print 2º string | grab the 2º [.] and cut (delete) everything to the rigth position<br />

      ifconfig wlan0 | egrep -m 1 "inet" | awk {'print $2'} | cut -d '.' -f2

![pic](http://i68.tinypic.com/72c1h0.png)


- grab the 1º inet | print 2º string | grab the 2º and 3º [.] and cut until the next [.]<br />

      ifconfig wlan0 | egrep -m 1 "inet" | awk {'print $2'} | cut -d '.' -f2,3

![pic](http://i64.tinypic.com/qwy4gz.png)


- parsing data (192.168.1.) [print first 10 chars]<br />

      var=`echo 192.168.1.71 | grep "192" | cut -c1-10`; echo $var

![pic](http://i66.tinypic.com/207q58y.png)


[0] [article glossario](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md#article-glossario)<br />

---

<br /><br />

### REGEX


- delete last 3 chars from string<br />

      v1=`ifconfig | grep "broadcast" | awk {'print $6'}`
      v2=`echo ${v1::-3}`
      echo $v2

![pic](http://i67.tinypic.com/2ypajyf.png)


- remove everything after the final [.]<br />

      IP="192.168.1.71"
      parse=`echo ${IP%.*}`
      echo $parse

![pic](http://i64.tinypic.com/2i1fuyw.png)

[0] [article glossario](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md#article-glossario)<br />

---

<br /><br />

### HEAD


- head -3 (print 3 lines from start) tail -1 (print last line from end)<br />

      locate .ogg | grep "sounds/gnome"
      locate .ogg | grep "sounds/gnome" | head -3 | tail -1

![pic](http://i66.tinypic.com/2qmqn9z.png)

[0] [article glossario](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md#article-glossario)<br />

---

<br /><br />

### TAIL


- grab only the 2º 'inet' expression with the help of 'tail' command

      ifconfig wlan0 | egrep -m 2 "inet" | tail -1

![pic](http://i66.tinypic.com/119yzwn.png)

---

<br /><br />

- check for empty variable declarations<br />

      var=""
      if [ -z "$var" ]; then
        echo "The variable declaration its empty .."
      else
        echo "Data: $var"
      fi


- check for NOT empty variable declarations<br />

      var="hello"
      if ! [ -z "$var" ]; then
        echo "The variable declaration its NOT empty .."
      else
        echo "The variable declaration its empty .."
      fi


- FOR loops<br />

      for i in 1 2 3 4 5
      do
      echo "Looping ... number $i" && sleep 1
      done

![pic](http://i64.tinypic.com/2a6qki8.png)


- join variable with text

      var=sun
      echo $varshine     # $varshine is undefined (empty string)
      echo ${var}shine   # displays the word "sunshine"
      echo ${var}spot    # displays the word "sunspot"

![pic](http://i64.tinypic.com/34njqc2.png)


- TODO: (csharp shellcode parsing)

      store=`cat shell.txt | grep -v '=' | tr -d ';' | tr -d '\"' | tr -d '\\' | tr -d 'x' | tr -d '\n'`

<br /><br />

### EXERCISE1: ifconfig wlan0 | grep "RX packets"
### EXERCISE2: ifconfig wlan0 | grep "ether"


[0] [article glossario](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md#article-glossario)<br />

_EOF
