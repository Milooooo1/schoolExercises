#include "shell.hh"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cerrno>
#pragma GCC diagnostic ignored "-Wwrite-strings"
int main() {
    std::string input;
    std::string prompt = "Insert function name: \n \t -";

    while(true) {
        std::cout << std::endl;
        std::cout << prompt;
        std::getline(std::cin, input);
        if (input == "new_file") new_file();
        else if (input == "ls") list();
        else if (input == "src") src();  
        else if (input == "find") find();
        else if (input == "seek") seek();
        else if (input == "exit") return 0;
        else if (input == "quit") return 0;
        else if (input == "error") return 1;
        if (std::cin.eof()) return 0; 
    } 
}

void new_file() { 
    int n,fd;
	char buff[100000];
    std::string filename = "";
    std::cout << "Input file name: ";
    std::cin >> filename;
	printf("Enter text to write in the file:\n");
	n = read(0, buff, 100);
	fd = syscall(SYS_open, filename.c_str(), O_CREAT | O_RDWR, 0777); 
	syscall(SYS_write, fd, buff, n);
	syscall(SYS_write, buff, n);
	syscall(SYS_close, fd);
}

void list() { 
    int status;
    const char* exec = "/bin/ls";
    const char* args[] = {"/bin/ls", "-la", NULL};

    if(syscall(SYS_fork) == 0) {
        syscall(SYS_execve, exec, args, NULL);
    } else {
        syscall(SYS_wait4, &status );
    }
}

void find() { 

    std::string arg;
    std::cout << "\tInput string to find: ";
    std::getline(std::cin, arg);

    int descriptors[2];
    syscall(SYS_pipe, descriptors);
    syscall(SYS_close, descriptors[1]);

    if(syscall(SYS_fork)  == 0 ){

        std::cout << "find error: " << errno << std::endl;
        syscall(SYS_close, descriptors[0]);
        syscall(SYS_dup2, descriptors[1], 1);

        const char* exec2 = "/usr/bin/find";
        const char* args2[] = {"/usr/bin/find", ".", NULL};

        syscall(SYS_execve, exec2, args2, NULL);
        syscall(SYS_close, descriptors[1]);


    } else {
        
        std::cout << "grep error: " << errno << std::endl;
        syscall(SYS_wait4, NULL, NULL, NULL);
        syscall(SYS_close, descriptors[1]);
        syscall(SYS_dup2, descriptors[0], 0);

        if (syscall(SYS_fork) == 0) {

            const char* exec = "/usr/bin/grep"; 
            const char* args[] = {"/usr/bin/grep", arg.c_str(), NULL};
            
            syscall(SYS_execve, exec, args, NULL);

        } else {

            syscall(SYS_wait4, NULL, NULL, NULL);
            syscall(SYS_close, descriptors[0]);
        }
    }
}

void seek() {
    char buff[100000];
    syscall(SYS_creat, "seek", 0777);
    syscall(SYS_creat, "loop", 0777);
    int fd = syscall(SYS_open, "seek", O_RDWR);
    syscall(SYS_lseek, fd, 5000000, SEEK_CUR);
    syscall(SYS_write, fd, "\0", 1);
    syscall(SYS_close, fd);
    int fd2 = syscall(SYS_open, "loop", O_RDWR);
    for(int i = 0; i < 5000000; i++){
        syscall(SYS_write, fd2, "\0", 1);
    }
    syscall(SYS_close, fd2);
    std::cout << "Seek function done." << std::endl;
}

void src() {                                                    // Voorbeeld: Gebruikt SYS_open en SYS_read om de source van de shell (shell.cc) te printen.
    int fd = syscall(SYS_open, "shell.cc", O_RDONLY, 0755);     // Gebruik de SYS_open call om een bestand te openen.
    char byte[1];                                               // 0755 zorgt dat het bestand de juiste rechten krijgt (leesbaar is).
    while(syscall(SYS_read, fd, byte, 1))                       // Blijf SYS_read herhalen tot het bestand geheel gelezen is,
        std::cout << byte;                                      // zet de gelezen byte in "byte" zodat deze geschreven kan worden.
}
