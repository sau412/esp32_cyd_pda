let n = 3
loop:
let k = ceil(sqr(n))
ck:
if n%k = 0 goto next
let k = k-1
if k <= 2 print n
if k > 2 goto ck
next:
let n = n+2
goto loop