set architecture armv5te
target remote localhost:1234
add-symbol-file /home/ubuntu/18349/laura/kernel/kernel 0xa3000000
add-symbol-file /home/ubuntu/18349/laura/tasks/bin/hello 0xa0000000
