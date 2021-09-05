#ifndef __FOLDER_H__
#define __FOLDER_H__

#include <string>
#include <iostream>
#include <vector>
#include "Elements.hpp"
#include "exception.hpp"
#define FOLDER "folder"

class File;


class Folder :public Elements
{
public:
	Folder(std::string elem_name, std:: string _path, User* owner_user, Group* owner_group);
	Folder(Folder* folder);
	~Folder();

private:
	
	
};

#endif