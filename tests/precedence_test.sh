./bin/rshell <<EOF
(ls -l && ls -a) || echo "OR"
echo "this " && (echo "is " && echo "a ") && echo "sentence.";
echo "this" || ls; mkdir test;
rmdir test && ls -a;
(cal && gfh) || date
(echo "do nothing" && donothing) || echo do something
(echo "Goodbye " && logname) || echo goodbye
exit
exit
EOF
echo
