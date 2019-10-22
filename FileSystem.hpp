#include "Disk.hpp"

class FileSystem
{
private:
    virtual u32 alloc_inode() = 0;
    virtual bool delete_inode() = 0;

public:
    FileSystem(/* args */);

    ~FileSystem();

    


    virtual bool initDisk(Disk * disk) = 0;
    virtual bool open(const std::string filename) = 0 ;
    virtual bool close(const std::string filename) = 0;
    virtual bool mkdir(const std::string filename) = 0;
    virtual bool rmdir(const std::string filename) = 0;
    virtual bool del(const std::string filename) = 0;

};

FileSystem::FileSystem(/* args */)
{
}

FileSystem::~FileSystem()
{
}
