#ifndef __FILE_H__
#define __FILE_H__

#include <string>
#include <iostream>
#include <vector>
#include "Elements.hpp"
#include "exception.hpp"
#include "Folder.hpp"
#define FILE "file"

class File : public Elements
{
public:
	File(std::string elem_name, std:: string _path, User* owner_user, Group* owner_group);
	File(File* file);
	double get_file_size();
	void set_file_content(std::string content);
	std::string get_file_content();
	void set_file_size(double size);
	
private:
	double file_size = file_content.size();
	std::string file_content;
};

#endif