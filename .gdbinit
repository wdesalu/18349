set architecture armv5te
target remote localhost:1234
add-symbol-file ~/18349/laura/kernel/kernel 0xa3000000
add-symbol-file ~/18349/laura/tasks/hello/hello 0xa0000000
