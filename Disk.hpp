#include <stdlib.h>
#include <iostream>

using u32 = unsigned int;
using ptr_void = void *;

class Disk{
private:
    u32 size_byte_;
    ptr_void ptr_head_;

public:
    Disk() {
        size_byte_ = 0;
        ptr_head_ = NULL;
    }
    
    ~Disk() {
        if(ptr_head_ != NULL)
            free(ptr_head_);
    }

    void set_size_byte(u32 size);
    void alloc_disk_space();
    u32 get_size_byte();
    ptr_void get_ptr_to_space();

};

void Disk::alloc_disk_space(){
    if(size_byte_ == 0){
        std::cout<<"Disk's space is Zero!"<<std::endl;
        exit(-1);
    }
    ptr_head_  = (ptr_void) malloc(sizeof(u32) * size_byte_);

    if(ptr_head_ == NULL){
        std::cout<<"Alloc memory space Failed!"<<std::endl;
        exit(-1);
    }
}


void Disk::set_size_byte(u32 size){
    size_byte_ = size;
}
u32 Disk::get_size_byte(){
    return size_byte_;
}

ptr_void Disk::get_ptr_to_space(){
    return ptr_head_;
}