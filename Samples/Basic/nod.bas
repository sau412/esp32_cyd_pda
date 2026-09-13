print "Greatest Common Factor"
input "enter a:" a
input "enter b:" b
loop:
if a > b then let a = a-b
if a < b then let b = b-a
if a <> b then goto loop
print "GCF = " a
stop