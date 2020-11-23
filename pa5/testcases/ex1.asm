print 5
print 6
jmp 5
read bx
jmp 18
read ax
jle 3 ax 0
sub 5 ax
mul 10 ax
read bx

jle 18 bx 0
add ax bx
add bx ax
print ax

print bx