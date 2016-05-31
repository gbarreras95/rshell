.bin/rshell << EOF

echo Testing -e flag
mkdir test
test -e exit.sh && echo works
test -e nonexistentFile && echo doesn't work
test -e test || echo returns true so won't
echo Test -d flag

test -d test && echo works
test -d nonexistentDirectory
test -d exit.sh || echo not a directory

echo Test -f flag

test -f test || echo not a file
test -f exit.sh && echo is a file
test -f nonexistentFile

rmdir test
exit
exit
EOF
echo