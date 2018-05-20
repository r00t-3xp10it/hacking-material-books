<br />

# parsing data in bash


- grab all instances of inet pattern
      ifconfig wlan0 | egrep "inet"


# grab only the 1º instance of inet pattern
ifconfig wlan0 | egrep -m 1 "inet"


# grab 1º inet | print 2º string
ifconfig wlan0 | egrep -m 1 "inet" | awk {'print $2'}


# grab 1º inet | print 2º string + 4º string
ifconfig wlan0 | egrep -m 1 "inet" | awk {'print $2,$4'}


# grab 1º inet | print 2º string | grab the 1º . and cut until the next .
ifconfig wlan0 | egrep -m 1 "inet" | awk {'print $2'} | cut -d '.' -f1


# grab 1º inet | print 2º string | grab the 2º . and cut until the next .
ifconfig wlan0 | egrep -m 1 "inet" | awk {'print $2'} | cut -d '.' -f2


# grab 1º inet | print 2º string | grab the 2º and 3º . and cut until the next .
ifconfig wlan0 | egrep -m 1 "inet" | awk {'print $2'} | cut -d '.' -f2,3


# parsing data (192.168.1.) [print first 10 chars]
parse=`echo $IP | grep "192" | cut -c1-10`


# delete last 3 chars from string
v1=`ifconfig | grep "broadcast" | awk {'print $6'}`
v2=`echo ${v1::-3}`


# remove everything after the final [ . ]
parse=`echo ${IP%.*}`


# head -3 (print 3 lines from start) tail -1 (print last line from end)
store=`locate .ogg | grep "sounds/gnome" | head -3 | tail -1`
paplay $store


