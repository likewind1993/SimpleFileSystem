#include <iostream>

using u32 = unsigned int;
using ptr_u32 = unsigned int * ;
using ptr_void = void * ;

const int EXECUTE = 1;
const int WRITE = 2;
const int READ = 4;
const u32 INODE_N_BLOCKS = 15;

struct SuperBlock{
    u32 blocks_count;
    u32 inode_count;

    u32 free_blocks_count;
    u32 block_size;

    u32 inodes_per_group;
    u32 blocks_per_group;

};
struct InodeTable{
    u32 mode;
    u32 size;

    u32 last_access_time;
    u32 last_modify_time;
    
    u32 blocks_count;

    u32 block [INODE_N_BLOCKS];
};

struct BlockGroupDesc{
    u32 block_bitmap_head;
    u32 inode_bitmap_head;
    u32 inode_table_head;

    u32 free_blocks_count;
    u32 free_inodes_count;
    
    u32 use_dirs_count;
};

