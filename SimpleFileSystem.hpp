#include "FileSystem.hpp"
#include "Info.h"

class SimpleFileSystem : public FileSystem
{
private:
    SuperBlock sb_;  
    BlockGroupDesc bgd_;

    u32 sb_size_;
    u32 block_group_size_;

    u32 cur_dir;

    void init();
    bool writeSuperBlockToDisk(u32 block_no, ptr_void p_disk);
    bool writeBlockGroupDescToDisk(u32 block_no, ptr_void p_disk);
    bool writeBitmapToDisk(u32 block_no, ptr_void p_disk);
    bool writeInodeTableToDisk(u32 block_no, ptr_void p_disk);

    bool readSuperBlockFromDisk(u32 block_no, ptr_void p_disk);
    bool readBlockGroupDescFromDisk(u32 block_no, ptr_void p_disk);

public:
    SimpleFileSystem(/* args */);
    ~SimpleFileSystem();

    // virtual bool initDisk(Disk * disk);
    // virtual bool open(const std::string filename);
    // virtual bool del(const std::string filename);

    bool initDisk(Disk * disk) override;


    bool open(const std::string filename) override { return true; };
    bool del(const std::string filename) override {return true; };
    bool close(const std::string filename) override { return true; };
    bool mkdir(const std::string filename) override { return true;};
    bool rmdir(const std::string filename) override { return true; };

};

void SimpleFileSystem::init(){
    sb_.block_size = 1024;
    sb_.blocks_per_group = 8192;
    sb_.inodes_per_group = 8192;

    sb_size_ = sizeof(sb_);
    block_group_size_ = sb_.block_size * sb_.blocks_per_group;
};

bool SimpleFileSystem::writeSuperBlockToDisk(u32 block_no, ptr_void p_disk){

    ptr_u32 p_space = (ptr_u32) p_disk;
    p_space = p_space + (block_no * sb_.block_size) / 4;

    *(p_space++) = sb_.blocks_count;
    *(p_space++) = sb_.inode_count;
    *(p_space++) = sb_.free_blocks_count;
    *(p_space++) = sb_.block_size;
    *(p_space++) = sb_.inodes_per_group;
    *(p_space++) = sb_.blocks_per_group;
    return true;
};

bool SimpleFileSystem::writeBlockGroupDescToDisk(u32 block_no, ptr_void p_disk){
    ptr_u32 p_space = (ptr_u32) p_disk;
    p_space = p_space + (block_no * sb_.block_size) / 4;

    *(p_space++) = bgd_.block_bitmap_head;
    *(p_space++) = bgd_.inode_bitmap_head;
    *(p_space++) = bgd_.inode_table_head;
    *(p_space++) = bgd_.free_blocks_count;
    *(p_space++) = bgd_.use_dirs_count;
    return true;

}
bool SimpleFileSystem::writeBitmapToDisk(u32 block_no, ptr_void p_disk){
    ptr_u32 p_space = (ptr_u32) p_disk;
    p_space = p_space + (block_no * sb_.block_size) / 4;
    
    memset((ptr_void) p_space, 0, 2 * sb_.block_size);
    return true;
}
bool SimpleFileSystem::writeInodeTableToDisk(u32 block_no, ptr_void p_disk){
    ptr_u32 p_space = (ptr_u32) p_disk;
    p_space = p_space + (block_no * sb_.block_size) / 4;
    
    memset((ptr_void) p_space, 0, 640 * sb_.block_size);
    return true;
}

bool SimpleFileSystem::initDisk(Disk * disk){
    u32 disk_size = disk->get_size_byte();
    u32 block_group_count = (disk_size - sb_size_) / block_group_size_;
    
    sb_.blocks_count = block_group_count * sb_.blocks_per_group;
    sb_.inode_count = block_group_count * sb_.inodes_per_group;

    u32 block_no = 0;
    ptr_void p_disk = disk->get_ptr_to_space();
    
    if(!writeSuperBlockToDisk(block_no, p_disk)){
        std::cout<<"Can't write SuperBlock to disk !"<<std::endl;
        return false;
    }
    
    block_no += 1;

    for(size_t i = 0; i<block_group_count; ++i){
        if(!writeBlockGroupDescToDisk(block_no + sb_.blocks_per_group * i, p_disk)){
            std::cout<<"Can't write BlockGroupDesc to disk !"<<std::endl;
            return false;
        }
        if(!writeBitmapToDisk(block_no + sb_.blocks_per_group * i + 1, p_disk)){
            std::cout<<"Can't write Bitmap to disk !"<<std::endl;
            return false;
        }
        if(!writeInodeTableToDisk(block_no + sb_.blocks_per_group * i + 2, p_disk)){
            std::cout<<"Can't write InodeTable to disk !"<<std::endl;
            return false;
        }
    }
    return true;
}

SimpleFileSystem::SimpleFileSystem(/* args */)
{
    init();
}

SimpleFileSystem::~SimpleFileSystem()
{
}
