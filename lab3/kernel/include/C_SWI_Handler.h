void C_SWI_Handler(unsigned swi_num, unsigned *regs);
void exit(int status);
ssize_t read(int fd, void* buf, size_t count);
ssize_t write(int fd, void* buf, size_t count);
ssize_t time();
ssize_t sleep(int fd);
