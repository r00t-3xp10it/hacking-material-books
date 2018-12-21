
# parsing data in bash



      Parsing, syntax analysis, or syntactic analysis is the process of analysing a string of symbols, either in natural language,
      computer languages or data structures, conforming to the rules of a formal grammar. The term has slightly different meanings in
      different branches of linguistics and computer science. Traditional sentence parsing is often performed as a method of understanding
      the exact meaning of a sentence or word, sometimes with the aid of devices such as sentence diagrams. It usually emphasizes the
      importance of grammatical divisions such as subject and predicate.

      Within computational linguistics the term is used to refer to the formal analysis by a computer of a sentence or other string of words
      into its constituents, resulting in a parse tree showing their syntactic relation to each other, which may also contain semantic and
      other information.


      Within computer science, the term is used in the analysis of computer languages, referring to the syntactic analysis of the input code
      into its component parts in order to facilitate the writing of compilers and interpreters. The term may also be used to describe a
      split or separation. 


<br /><br />

![pic](http://i64.tinypic.com/205qy50.png)

<br />


### Article Glossario
[1] [grep](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md#grep)<br />
[2] [awk](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md#awk)<br />
[3] [cut](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md#cut)<br />
[4] [head](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md#head)<br />
[5] [tail](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md#tail)<br />

---


### GREP

      grep searches the input files for lines containing a match to a given pattern list.
      When it finds a match in a line, it copies the line to standard output (by default),
      or whatever other sort of output you have requested with options.

<br />

- grab all instances of inet pattern<br />

      ifconfig wlan0 | grep "inet"

![pic](http://i67.tinypic.com/2dt3t3n.png)

- colorize matching pattern<br />

      ifconfig wlan0 | grep "inet" --color=auto

![pic](http://i67.tinypic.com/vht43l.png)

- output only the matching pattern of each line<br />

      ifconfig wlan0 | grep -o "inet6"

![pic](http://i68.tinypic.com/2vijvhx.png)

- invert the sence of matching (sellect non-matching lines)<br />

      cat test.c | grep -v "="

![pic](http://i65.tinypic.com/2zpt4ix.png)

- grab only the 1º instance of inet pattern<br />

      ifconfig wlan0 | egrep -m 1 "inet"

![pic](http://i64.tinypic.com/4vo5g0.png)


[0] [article glossario](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md#article-glossario)<br />
---

### AWK

- grab 1º inet | print 2º string<br />

      ifconfig wlan0 | egrep -m 1 "inet" | awk {'print $2'}

![pic](http://i68.tinypic.com/193st2.png)

- grab 1º inet | print 2º string + 4º string<br />

      ifconfig wlan0 | egrep -m 1 "inet" | awk {'print $2,$4'}

![pic](http://i68.tinypic.com/4t0x2g.png)


[0] [article glossario](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md#article-glossario)<br />
---

### CUT


- grab 1º inet | print 2º string | grab the 1º [.] and cut until the next [.]<br />

      ifconfig wlan0 | egrep -m 1 "inet" | awk {'print $2'} | cut -d '.' -f1

![pic](http://i64.tinypic.com/dmpic4.png)


- grab the 1º inet | print 2º string | grab the 2º [.] and cut until the next [.]<br />

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

### HEAD


- head -3 (print 3 lines from start) tail -1 (print last line from end)<br />

      locate .ogg | grep "sounds/gnome"
      locate .ogg | grep "sounds/gnome" | head -3 | tail -1

![pic](http://i66.tinypic.com/2qmqn9z.png)

[0] [article glossario](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md#article-glossario)<br />
---

### TAIL


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

<br />

[0] [article glossario](https://github.com/r00t-3xp10it/hacking-material-books/blob/master/bash/parsing_data_in_bash.md#article-glossario)<br />

_EOF
