#include <iostream>
#include <string>
#include "../drive/User.hpp"
#include "../drive/Elements.hpp"
#include "../drive/Permission.hpp"
#define FILE "file"
#define ROOT "root"

std::string elements_html_maker(User* user, Elements* elem, std::vector<Elements *> elements){
  std::string str = "";
  if(elem->get_elem_path() != "/"+ user->get_username() && user->get_username() != ROOT){
    str += "<form style=\"display: inline;\" action=\"/fatherfolder\" method=\"post\">";
    str += "<button type=\"fatherfolder\" style=\" border: none; display: in-block; margin-right:5px; \"> Back </button>";
    str += "<input type=\"hidden\" name=\"path\" value=\"" + (elem->get_father_folder())->get_elem_path() + "\">";
    str += "</form>";
  }
  else if(user->get_username() == ROOT && elem->get_father_folder()){
    str += "<form style=\"display: inline;\" action=\"/fatherfolder\" method=\"post\">";
    str += "<button type=\"fatherfolder\" style=\" border: none; display: in-block; margin-right:5px; \"> Back </button>";
    str += "<input type=\"hidden\" name=\"path\" value=\"" + (elem->get_father_folder())->get_elem_path() + "\">";
    str += "</form>";
  }
  str += "<input type=\"hidden\" name=\"path\" placeholder=\"New folder\">";

  for (int i = 0; i < elements.size(); i++){
    str += "<div class=\"Folder\">";
    str += "<form action=\"/element\" method=\"post\">";
    str += "<input type=\"hidden\" name=\"path\" value=\"" + elements[i]->get_elem_path() + "\">";
    if(elements[i]->if_folder())
      str += "<img src=\"Folder.png\" style=\"width: 2%\">";
    else if(elements[i]->if_file())
      str += "<img src=\"file.png\" style=\"width: 3%\">";
    str += "<button type=\"submit\" style=\"background-color: transparent; border: none;\">" + elements[i]->get_elem_name() +"</button>";
    str += "</form>";
    str += "<form style=\"display: inline;\" action=\"/details\" method=\"post\">";
    str +=  "<button type=\"submit\" style=\"background-color: #d580ff; display: inline;\">Details</button>";
    str += "<input type=\"hidden\" name=\"path\" value=\"" + elements[i]->get_elem_path() + "\">";
    str += "</form>";

    str += "<form style=\"display: inline;\" action=\"/copy\" method=\"post\">";
    str +=  "<button type=\"submit\" style=\"background-color: #d580ff; display: inline;\">copy</button>";
    str += "<input type=\"hidden\" name=\"path\" value=\"" + elements[i]->get_elem_path() + "\">";
    str += "</form>";

    str += "<form style=\"display: inline;\" action=\"/remove\" method=\"post\">";
    str +=  "<button type=\"submit\" style=\"background-color: #d580ff; display: inline;\">remove</button>";
    str += "<input type=\"hidden\" name=\"path\" value=\"" + elements[i]->get_elem_path() + "\">";
    str += "</form>";

    str += "</div>";
  }
  return str;
}

void setVariable(std::string &body, std::string variable, std::string value){
  std::string word = "<var id=\"" + variable + "\">";
  int startOfVarTag = body.find(word);
  int endOfVarTag = body.find("</var>", startOfVarTag);
  body.erase(body.begin() + startOfVarTag + word.size(), body.begin() + endOfVarTag);
  body.insert(startOfVarTag + word.size(), value);
}

std::string add_style(){
  std::string str = "";
  str += "<style type=\"text/css\">";
  str += "body {";
  str += "background-color: #79589f;";
  str += "font-family: 'Open Sans', sans-serif;";
  str += "text-align: center ;";
  str += "display : flex ;";
  str += "justify-content: center;";
  str += "flex-direction: column ;";
  str += "align-items: center;";
  str += "border: 10 px;";
  str += "height: 100vh;}";

  str += ".card {";
  str += "display: flex;";
  str += "justify-content: center;";
  str += " flex-direction: column;";
  str += "background-color: white; ";
  str += "padding: 40px 50px;";
  str += "border-radius: 15px;}";
  str += "</style>";
  return str;
}

std::string html_file_content_maker(Elements* elem, std::string content){
  Folder* father_folder = elem->get_father_folder();
  std::string str = "";
  str += "<!DOCTYPE html>";
  str += "<html>";
  str += "<body background=\"background.jpg\">";
  str += "<div class=\"card\">";
  str += "<form style=\"display: inline;\" action=\"/fatherfolder\" method=\"post\">";
  str += "<button type=\"fatherfolder\" style=\" border: none; display: in-block; margin-right:5px; \"> Back </button>";
  if(father_folder == NULL){
    str += "<input type=\"hidden\" name=\"path\" value=\"\">";
  }
  else{
    std::cerr<<father_folder->get_elem_name()<<std::endl;
  }
  str += "</form>";
  str += "<p>"+ content +"</p>";
  str += "</div>";
  str += "</body>";
  str += "</html>";

  str += add_style();
  return str;
}

std::string users_html_maker(std::vector<User*> users){
  std::string str = "";
  for (int i = 0; i < users.size(); ++i)
  {
    str += "<div class = \"User\"";
    str += "<form action=\"/userlist\" method=\"post\">";
    
    str += "<img src=\"user.png\" style=\"width: 2%\">";
    str += "<button type=\"submit\" style=\"background-color: transparent; border: none; display: in-block; margin-right:5px; \">" + users[i]->get_username() + " </button>";
    str += "<button type=\"submit\" style=\"background-color: transparent; border: none; display: in-block; margin-right:5px; \">" + users[i]->get_authority() + " </button>";
    
    str += "<form style=\"display: inline;\" action=\"/promote\" method=\"post\">";
    str += "<button type=\"submit\" style=\" border: none; display: in-block; margin-right:5px; \"> Promote </button>";
    str += "<input type=\"hidden\" name=\"username\" value=\"" + users[i]->get_username() + "\">";
    str += "</form>";
    str += "<var id = \"p_Message\"></var>";

    str += " <form style=\"display: inline;\" action=\"/demote\" method=\"post\">";
    str += "<button type=\"submit\" style=\" border: none; display: in-block; margin-right:5px; \"> Demote </button>";
    str += "<input type=\"hidden\" name=\"username\" value=\"" + users[i]->get_username() + "\">";
    str += "</form>";
    str += "<var id = \"d_Message\"></var>";
    str += "<br />";

    str += "</form>";
    str += "</div>";
    str += "</br>";
  }
  return str;
}

std::string detail_html_maker(User* user, Elements* elem){
  std::string str = "";
  str += "<!DOCTYPE html>";
  str += "<html>";
  str += "<body background=\"background.jpg\">";
  str += "<div class=\"card\">";
  str += "<form style=\"display: inline;\" action=\"/elemslist\" method=\"post\">";
  str += "<button type=\"elemslist\" style=\" border: none; display: in-block; margin-right:5px; \"> Back </button>";
  str += "</form>";
  str += "<p style=\"display: inline;\">Owner user: " + user->get_username() + "</p>";
  str += "<p style=\"display: inline;\"> Owner user's permissions: " + elem->get_elem_permission()->get_user_permission() + "</p>";
  if(!elem->get_group_owner()){
    str += "<p style=\"display: inline;\"> Owner group: --</p>";
  }
  else{
    str += "<p style=\"display: inline;\"> Owner group:" + elem->get_group_owner()->get_group_name() + " </p>";
  }
  str += "<p style=\"display: inline;\"> Owner group's permissions: " + (elem->get_elem_permission())->get_group_permission() + "</p>";
  if(elem->get_elem_type() == FILE){
    auto size = std::to_string(dynamic_cast<File*>(elem)->get_file_content().size());
    str += "<p style=\"display: inline;\"> File size: " + size + " kb </p>";
  }
  str += "</div>";
  str += "</body>";
  str += "</html>";
  str += add_style();
  return str;
}