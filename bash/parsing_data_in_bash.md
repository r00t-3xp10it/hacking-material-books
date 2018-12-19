
# parsing data in bash


<br /><br />

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

- grab 1º inet | print 2º string<br />

      ifconfig wlan0 | egrep -m 1 "inet" | awk {'print $2'}

![pic](http://i68.tinypic.com/193st2.png)

- grab 1º inet | print 2º string + 4º string<br />

      ifconfig wlan0 | egrep -m 1 "inet" | awk {'print $2,$4'}

![pic](http://i68.tinypic.com/4t0x2g.png)


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


- head -3 (print 3 lines from start) tail -1 (print last line from end)<br />

      locate .ogg | grep "sounds/gnome"
      locate .ogg | grep "sounds/gnome" | head -3 | tail -1

![pic](http://i66.tinypic.com/2qmqn9z.png)


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
      echo "Looping ... number $i"
      done


- join variable with text

      var=sun
      echo $varshine     # $varshine is undefined (empty string)
      echo ${var}shine   # displays the word "sunshine"


- TODO: (csharp shellcode parsing)

      store=`cat shell.txt | grep -v '=' | tr -d ';' | tr -d '\"' | tr -d '\\' | tr -d 'x' | tr -d '\n'`

<br />

_EOF
