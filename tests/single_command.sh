./bin/rshell<<EOF
echo "hello"
ls
ls -l
ls -a
mkdir test
ls -a
mv test newName
ls -a
rmdir newName
ls -a
logname
cal
exit
exit
EOF
echo
