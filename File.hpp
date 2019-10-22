#include "Info.h"

class File
{
private:
    /* data */
    std::string path_;
    u64         pos_;

public:
    File(/* args */);
    ~File();


    size_t write();
    size_t read();


    int open();
    void set_dir(std::string dir);    
};

File::File(/* args */)
{
}

File::~File()
{
}
void File::set_dir(std::string dir ){
    path_ = dir;
}