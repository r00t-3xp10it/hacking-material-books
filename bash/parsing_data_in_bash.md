
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
[1] [Parsing data with GREP](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md#grep)<br />
[2] [Parsing data with HEAD](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md#head)<br />
[3] [Parsing data with TAIL](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md#tail)<br />
[4] [Parsing data with CAT](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md#cat)<br />
[5] [Parsing data with AWK](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md#awk)<br />
[6] [Parsing data with CUT](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md#cut)<br />
[7] [Parsing data with TR](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md#tr)<br />


---

<br /><br />

### GREP

      grep searches the input files or commands for lines containing a match to a given pattern list.
      When it finds a match in a line, it copies the line to standard output (by default), or whatever
      other sort of output you have requested with grep command options (switch's).

<br />

- Print **All** the lines that contains the **'inet'** expression<br />

      ifconfig wlan0 | grep "inet"

![pic](http://i66.tinypic.com/2uoi0sz.png)

- Colorize the **matching** expression<br />

      ifconfig wlan0 | grep "inet" --color=auto

![pic](http://i67.tinypic.com/vht43l.png)


- Print only the lines with **'inet'** in them (only perfect matches)<br />

      ifconfig wlan0 | grep -w "inet"

![pic](http://i66.tinypic.com/25kraxc.png)

- Print only the **1º line** containing the **'inet'** expression<br />

      ifconfig wlan0 | grep -m 1 "inet"

![pic](http://i67.tinypic.com/95sy91.png)

- print only the matching expression (**not the line**)<br />

      ifconfig wlan0 | grep -o "inet6"

![pic](http://i68.tinypic.com/2vijvhx.png)
**HINT:** grep -o switch can be used to **check** if the suplied expression exists (in scripting)<br /><br />


- **Invert** the sence of matching (**delete all matching lines** that contains the expression)<br />

      ifconfig wlan0 | grep -v "inet"

![pic](http://i67.tinypic.com/2upeloz.png)


<br /><br />

                                               * EXERCISES *

**EXERCISE1:** Print only the line that contains **'RX packets'** expression<br />
With everything we have learn until now, how do you print only the line that contains the RX packets expression?<br />

**EXERCISE2:** Print only the line that contains your **'mac address'**<br />
With everything we have learn until now, how do you print only the line that contains your mac address?<br />

[?] [exercise1 soluction](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md#exercise1)<br />
[?] [exercise2 soluction](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md#exercise2)<br />
[0] [article glossario](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md#article-glossario)<br />

---

<br /><br />

### HEAD

      By default, ‘head’ command reads the first 10 lines of the file. If you want to read more or less
      than 10 lines from the beginning of the file then you have to use ‘-n’ option with ‘head’ command.
      In the next example we are using 'grep' command to displays all lines that contains the 'X' expression.

![pic](http://i68.tinypic.com/nfr43c.png)

<br />

- Print the **'first line'** that contains the expression **'X'** using **head -n** switch<br />

      ifconfig wlan0 | grep "X" | head -n 1

![pic](http://i66.tinypic.com/2wbz22b.png)

- Print the first **'two lines'** that contains the expression **'X'** using **head -n** switch<br />

      ifconfig wlan0 | grep "X" | head -n 2

![pic](http://i66.tinypic.com/15hna6h.png)

<br /><br />

                                               * EXERCISES *

**EXERCISE3:** Print the **4 lines** that contains the **'X'** expression using **head -n** switch<br />

[?] [exercise3 soluction](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md#exercise3)<br />
[0] [article glossario](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md#article-glossario)<br />

---

<br /><br />

### TAIL

      By default, ‘tail’ command reads the last 10 lines of the file. If you want to read more or less
      than 10 lines from the ending of the file then you have to use ‘-n’ option with ‘tail’ command.
      In the next example we are using 'grep' command to displays all lines that contains the 'X' expression.

![pic](http://i68.tinypic.com/nfr43c.png)

<br />

- Grab the first **'two lines'** (head -n 2) that contains the expression **'X'** and print the **last line** (tail -n 1)<br />

      ifconfig wlan0 | grep "X" | head -n 2 | tail -n 1

![pic](http://i65.tinypic.com/2nc14t5.png)

- Grab the first **'3 lines'** (head -n 3) that contains the expression **'X'** and print the **last line** (tail -n 1)<br />

      ifconfig wlan0 | grep "X" | head -n 3 | tail -n 1

![pic](http://i63.tinypic.com/2j29mab.png)

- Grab the first **'3 lines'** (head -n 3) that contains the expression **'X'** and print the **last two lines** (tail -n 2)<br />

      ifconfig wlan0 | grep "X" | head -n 3 | tail -n 2

![pic](http://i68.tinypic.com/2w4l0g8.png)
**HINT:** we are displaying the **last two lines** (tail -n 2) that **'head -n 3'** command have filter previously.<br /> 

<br /><br />

                                               * EXERCISES *

**EXERCISE4:** Print **only the line** that contains the **'TX errors'** expression with the help of **'tail -n'** switch<br />

[?] [exercise4 soluction](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md#exercise4)<br />
[0] [article glossario](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md#article-glossario)<br />

---

<br /><br />

### CAT

      cat is a standard Unix utility that reads files sequentially, writing them to standard output.
      The name is derived from its function to concatenate files. In this section we will use 'article'
      file to demonstrate parsing technincs. The demonstration file can be downloaded from the link above.

![pic](http://i65.tinypic.com/73mr1w.png)
[+] [demonstration file of 'parsing data in bash' (article demo file)](https://gist.github.com/r00t-3xp10it/c3f7cbf1ca73f8d7ce24d17af39738a8)

<br /><br />

- Read **article** file and print a line **[ only if ]:** the whole line matches your suppied regex<br />

      cat article | grep -x "This line will be displayed .."

![pic](http://i68.tinypic.com/34zzn08.png)

- Print **all lines** that contains the **ERROR** expression<br />

      cat article | grep "ERROR"

![pic](http://i68.tinypic.com/znwor9.png)

- Store all **ERROR** lines from article file into another logfile<br />

      cat article | grep "ERROR" >> new_logfile.log

![pic](http://i66.tinypic.com/2a0nuhk.png)

<br /><br />

                                               * EXERCISES *

**EXERCISE5:** Write only the line that contains **192.168.1.69** expression into a new logfile<br />
With everything we have learn until now, how do you write only the line that contains the **192.168.1.69** expression?<br />

[?] [exercise5 soluction](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md#exercise5)<br />
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

### TR

      tr is an UNIX utility for translating, or deleting, or squeezing repeated characters.
      It will read from STDIN and write to STDOUT. In the next example we are using 'ifconfig'
      command and 'tr' to delete numbers, leters, expressions, empty spaces and tab spaces.

![pic](http://i64.tinypic.com/205qy50.png)

<br />


- **Delete** from STDOUT characters ('5' and '.') using **'tr -d'** switch<br />

      ifconfig wlan0 | tr -d '5' | tr -d '.'

![pic](http://i64.tinypic.com/rktvmd.png)

- **'tr'** can also be used to remove **'new line paragraphs'** using \n (paragraph)<br />

      ifconfig wlan0 | tr -d '\n'

![pic](http://i63.tinypic.com/rc7z49.png)

- Delete **empty spaces** between lines (tr -d ' ')<br />

      ifconfig wlan0 | tr -d ' '

![pic](http://i65.tinypic.com/8y6hph.png)

- Replace (tr -s) **'empty spaces'** between lines by a **'tab space'**<br />

      ifconfig wlan0 | tr -s ' ' '\t'

![pic](http://i63.tinypic.com/2isxzjc.png)

- Delete **'new line paragraphs'** (tr -d '\n') and replace (tr -s '\t' ' ') **'tab spaces'** by nothing<br />

      ifconfig wlan0 | tr -d '\n' | tr -s '\t' ' '

![pic](http://i63.tinypic.com/24enepv.png)

- Csharp shellcode parsing (build oneliner droper)<br />

      store=`cat shell.txt | grep -v '=' | tr -d ';' | tr -d '\"' | tr -d '\\' | tr -d 'x' | tr -d '\n'`

<br /><br />

                                               * EXERCISES *

**EXERCISE7:** blablabla ...<br />


[?] [exercise7 soluction](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md#exercise7)<br />
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

---

<br /><br />

### EXERCISE1:

![pic](http://i66.tinypic.com/28hziac.png)

### EXERCISE2:

![pic](http://i65.tinypic.com/2vcc12o.png)

### EXERCISE3:

![pic](http://i66.tinypic.com/jqhmoo.png)

### EXERCISE4:

![pic](http://i67.tinypic.com/2hwd2ls.png)

### EXERCISE5:

![pic](http://i63.tinypic.com/e64xs3.png)
![pic](http://i63.tinypic.com/24v0787.png)

---

<br /><br />

[0] [article glossario](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md#article-glossario)<br />
[1] [Parsing data with GREP](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md#grep)<br />
[2] [Parsing data with HEAD](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md#head)<br />
[3] [Parsing data with TAIL](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md#tail)<br />
[4] [Parsing data with CAT](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md#cat)<br />
[5] [Parsing data with AWK](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md#awk)<br />
[6] [Parsing data with CUT](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md#cut)<br />
[7] [Parsing data with TR](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md#tr)<br />

_EOF
