#include "File.hpp"
File::File(std::string elem_name, std:: string _path, User* owner_user, Group* owner_group)
		:Elements(elem_name, _path, owner_user, owner_group){ element_type = FILE; }

File::File(File* file)
		:File(file->get_elem_name(), "", file->get_user_owner(), file->get_group_owner()){set_file_content(file->get_file_content());}

double File::get_file_size()
{
	return file_size;
}

void File::set_file_content(std::string content)
{
	file_content = content;
}

std::string File::get_file_content()
{
	return file_content;
}

void File::set_file_size(double size)
{
	file_size = size;
}