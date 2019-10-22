#include <iostream>
#include "Bash.hpp"
using namespace std;

int main() {

    Disk disk;
    disk.set_size_byte(512 * 1024 * 1024);
    disk.alloc_disk_space();
    
    SimpleFileSystem fs;
    
    Bash bash;
    bash.setDiskAndFileSystem( &disk, &fs);
    
    bash.show();

    return 0;
}