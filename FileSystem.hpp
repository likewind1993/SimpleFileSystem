#include "Disk.hpp"

class FileSystem
{
private:
    

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
