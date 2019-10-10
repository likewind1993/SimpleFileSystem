#include <iostream>
#include <string>
#include <vector>

#include "Ls.hpp"
#include "Vim.hpp"
#include "Mkdir.hpp"
#include "SimpleFileSystem.hpp"

struct Commands{
    Ls * p_ls = NULL;
    Vim * p_vim  = NULL;
    Mkdir * p_mkdir = NULL;
};

class Bash
{
private:
    std::string cmd_;
    std::string cur_dir_;
    std::string format_output_;

    FileSystem * p_fs_;
    Disk * p_disk_;

    Commands commands;

    bool mount();
    void parseCmd(std::string cmd, vector<std::string> & args);

public:
    Bash(/* args */);
    ~Bash();

    void setDiskAndFileSystem(Disk * p_disk, FileSystem * p_fs);
    void show();
    bool execveCmd(std::string & cmd);
};

bool Bash::mount(){
    if(!p_fs_->initDisk(p_disk_)){
        std::cout<<"Can't mount FileSystem!"<<std::endl;
        return false;
    }
    return true;
}

void Bash::setDiskAndFileSystem(Disk * p_disk, FileSystem * p_fs){
    p_fs_ = p_fs;
    p_disk_ = p_disk;
    mount();
};

void Bash::parseCmd(std::string cmd, vector<std::string> & args){
    std::string arg = "";
    for(size_t i = 0; i<cmd.size(); ++i){
        if(cmd[i] == ' '){
            if(arg != ""){
                args.push_back(arg);
                arg = "";
            }
        }else 
            arg += cmd[i];
    }
    if(arg != "")
        args.push_back(arg);
};

bool Bash::execveCmd(std::string & cmd){
    vector<std::string> args;
    parseCmd(cmd, args);
    if(args[0] == "mkdir"){
        
    }


    return false;
}

void Bash::show(){
    while(true){
        std::cout<<format_output_<<": "<<cur_dir_<<" ";
        std::cin>>cmd_;
        if(cmd_ == "exit")
            break;
        if(!execveCmd(cmd_)){
            std::cout<<"-bash: "<<cmd_ <<" command not found"<<std::endl;
        }
    }
}

Bash::Bash(/* args */)
{
    cur_dir_ = "/";
    format_output_ = "likewinddeMacBook";
    
    commands.p_ls = new Ls();
    commands.p_mkdir  = new Mkdir();
    commands.p_vim = new Vim();
}

Bash::~Bash()
{
}
