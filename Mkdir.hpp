#include "FileSystem.hpp"

class Mkdir
{
private:
    FileSystem * fs_;
public:
    Mkdir();
    Mkdir(FileSystem * fs) : fs_(fs){};
    ~Mkdir();

    bool setFileSystem( FileSystem * fs){
        fs_ = fs;
    }

    bool mkdir(std::string filename){
        
    }

};

Mkdir::Mkdir(/* args */)
{
}

Mkdir::~Mkdir()
{
}
