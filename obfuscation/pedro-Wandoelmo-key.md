<br />

# SIMPLE STRING OBFUSCATION TECHNICS [2]<br />

- using one batch local variable to serve as our **master key** (varObj)<br />
`varObj=abcdefghijlmnopqrstuvxzkyW0123456789ABCDEFGHIJLMNOPQRSTUVXZKYW`<br />

- Then we just need to call the letter possition inside the **varObj** local variable to build our command<br />
**examples:** `%varObj:~3,1% (letter c)` **+** `%varObj:~12,1% (letter m)` **+** `%varObj:~4,1% (letter d)` **=** `cmd`<br />

---

**Letter/Number - Position inside varObj var**

a - 1<br />
b - 2<br />
c - 3<br />
d - 4<br />
e - 5<br />
f - 6<br />
g - 7<br />
h - 8<br />
i - 9<br />
j - 10<br />
l - 11<br />
m - 12<br />
n - 13<br />
o - 14<br />
p - 15<br />
q - 16<br />
r - 17<br />
s - 18<br />
t - 19<br />
u - 20<br />
v - 21<br />
x - 22<br />
z - 23<br />
k - 24<br />
y - 25<br />
w - 26<br />
<br />
0 - 27<br />
1 - 28<br />
2 - 29<br />
3 - 30<br />
4 - 31<br />
5 - 32<br />
6 - 33<br />
7 - 34<br />
8 - 35<br />
9 - 36<br />
<br />
A - 37<br />
B - 38<br />
C - 39<br />
D - 40<br />
E - 41<br />
F - 42<br />
G - 43<br />
H - 44<br />
I - 45<br />
J - 46<br />
L - 47<br />
M - 48<br />
N - 49<br />
O - 50<br />
P - 51<br />
Q - 52<br />
R - 53<br />
S - 54<br />
T - 55<br />
U - 56<br />
V - 57<br />
X - 58<br />
Z - 59<br />
K - 60<br />
Y - 61<br />
W - 62<br />
<br />

---

This document belongs to this article:<br />
https://github.com/r00t-3xp10it/hacking-material-books/blob/master/obfuscation/simple_obfuscation.md<br />
### Special thanks to: @Wandoelmo Silva

<br />

