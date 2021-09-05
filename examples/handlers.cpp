#include "handlers.hpp"
#include "../utils/functions.cpp"

Response *LoginHandler::callback(Request *req) {
  std::string username = req->getBodyParam("username");
  std::string password = req->getBodyParam("password");
  Response *res;
  if (AP_drive->login(username, password)){
    res = Response::redirect("/loggedin");
    std::string sid = randomStrGnr();
    res->setSessionId(sid);
    AP_drive->setUserSID(sid, username);
  }
  else{
    res = new Response;
    res->setHeader("Content-Type", "text/html");
    std::string body = readFile("static/logincss.html");
    setVariable(body, "Message", "Invalid username or password.");
    res->setBody(body);
  }
  return res;
}

Response *UploadHandler::callback(Request *req) {
  std::string sid = req->getSessionId();
  User* user = AP_drive->findUserBySessionId(sid);
  if(!user)
    throw Server::Exception("You have to be logged in.");
  Elements* curr_element = user->get_current_elem();
  if(!curr_element)
    throw Server::Exception("Something went wrong.");
  std::string name = req->getBodyParam("file_name");
  std::string file = req->getBodyParam("file");
  File* new_file = new File(name, curr_element->get_elem_path(), user, NULL);
  new_file->set_file_content(file);
  new_file->set_file_size(file.size());
  new_file->set_father_folder(dynamic_cast<Folder*>(curr_element));
  AP_drive->upload_phase2(dynamic_cast<Folder*>(curr_element), new_file);
  Response *res = Response::redirect("/elemslist");
  return res;
}

Response *HomePageHandler::callback(Request *req){
  Response *res;
  std::string sid = req->getSessionId();
  User* user = AP_drive->findUserBySessionId(sid);
  if(user){
    if(user->if_superuser_or_admin()){
      res = Response::redirect("/systemManagement");
    }
    else
      res = Response::redirect("/elemslist");
  }
  return res;
}

Response *AddUserHandler::callback(Request *req){
  Response *res;
  std::string username = req->getBodyParam("username");
  std::string password = req->getBodyParam("password");
  res = new Response;
  res->setHeader("Content-Type", "text/html");
  std::string body = readFile("static/addusercss.html");
  bool addUserOk = AP_drive->add_user(username, password);
  if (addUserOk){
    setVariable(body, "Message", "User successfully added.");
  }
  else{
    setVariable(body, "Message", "This username already exists. Try another username.");
  }
  res->setBody(body);
  return res;
}

Response *LogoutHandler::callback(Request *req){
  Response* res;
  std::string sid = req->getSessionId();
  bool success = AP_drive->logout(sid);
  if(success){
    res = Response::redirect("/");
  }
  else
    throw Server::Exception("something went wrong.");
  return res;
}

Response * ShowFolderHandler::callback(Request * req){
  Response * res;
  std::string sid = req->getSessionId();
  User* user = AP_drive->get_user_by_sid(sid);
  Elements* curr_element;
  if(!user)
    throw Server::Exception("Something went wrong.");
  curr_element = user->get_current_elem();
  if (curr_element){
    res = new Response;
    res->setHeader("Content-Type", "text/html");
    std::string body = readFile("static/elemslist.html");
    insert(body, elements_html_maker(user, curr_element, curr_element->get_sub_elements()), "<!--new element-->");
    res->setBody(body);
  }
  else
    throw Server::Exception("Something went wrong.");
  return res;
}

Response * ShowElementHandler::callback(Request * req){
  std::string sid = req->getSessionId();
  User* user = AP_drive->get_user_by_sid(sid);
  if(!user)
    throw Server::Exception("Something went wrong.");
  Response *res = new Response;
  std::string path = req->getBodyParam("path");
  Elements* elem = AP_drive->find_element_by_absoloute_path(path);
  if(elem){
    if(elem->if_folder()){
      user->set_current_elem(elem);
      res = Response::redirect("/elemslist");
    }
    else if(elem->if_file()){
      res->setHeader("Content-Type", "text/html");
      File* file = dynamic_cast<File*>(elem);
      std::string body = html_file_content_maker(file, file->get_file_content());

      res->setBody(body);
    }
  }
  else
    throw Server::Exception("Something went wrong.");
  return res;
}

Response * UserlistHandler::callback(Request * req){
  Response *res = new Response;
  std::string sid = req->getSessionId();
  User* user = AP_drive->get_user_by_sid(sid);
  std::string body = "";
  if(user){
    if(user->if_superuser_or_admin()){
      std::vector<User*> users = AP_drive->get_all_users();
      body = readFile("static/userlistcss.html");
      res->setHeader("Content-Type", "text/html");
      insert(body, users_html_maker(users), "<!--user-->");
      res->setBody(body);
      return res;
    }
    else{
      body = readFile("static/super_admincss.html");
      setVariable(body, "userlist message", "Only admins and superusers can access this link.");
    }
  }
  else
    res = Response::redirect("/");
  return res;
}

Response * PromoteHandler::callback(Request * req){
  Response *res = new Response;
  std::string sid = req->getSessionId();
  std::string username = req->getBodyParam("username");
  User* promoter_user = AP_drive-> get_user_by_sid(sid);
  if(promoter_user){
    if(promoter_user->if_superuser_or_admin()){
      User* promoted = AP_drive->search_user(username);
      if(promoted){
        promoted->promote();
        res = Response::redirect("/userlist");
      }
      else
        throw Server::Exception("Something went wrong.");
    }
    else{
      res->setHeader("Content-Type", "text/html");
      std::string body = readFile("static/userlistcss.html");
      setVariable(body, "p_Message", "Sorry! Can't promote this user.");
      res->setBody(body);
    }
  }
  else
    throw Server::Exception("Something went wrong.");
  return res;
}

Response * DemoteHandler::callback(Request * req){
  Response *res = new Response;
  std::string sid = req->getSessionId();
  std::string username = req->getBodyParam("username");
  User* demoter_user = AP_drive-> get_user_by_sid(sid);
  if(demoter_user){
    if(demoter_user->if_superuser_or_admin()){
      User* demoted = AP_drive->search_user(username);
      if(demoted){
        demoted->demote();
        res = Response::redirect("/userlist");
      }
      else
        throw Server::Exception("Something went wrong.");
    }
    else{
      res->setHeader("Content-Type", "text/html");
      std::string body = readFile("static/userlistcss.html");
      setVariable(body, "d_Message", "Sorry! Can't promote this user.");
      res->setBody(body);
    }
  }
  else
    throw Server::Exception("Something went wrong.");
  return res;
}

Response * FatherFolderHandler::callback(Request * req){
  Response *res;
  std::string sid = req->getSessionId();
  User* user = AP_drive-> get_user_by_sid(sid);
  std::string path = req->getBodyParam("path");
  Elements* father_elem = AP_drive->find_element_by_absoloute_path(path);
  if(user){
    std::string path = req->getBodyParam("path");
    if(father_elem != AP_drive->get_root_folder() || user->get_username() == ROOT){
      user->set_current_elem(father_elem);
      res = Response::redirect("/elemslist");
    }
    else
      throw Server::Exception("Something went wrong.");
  }
  else
    throw Server::Exception("Something went wrong.");
  return res;
}

Response * NewFolderHandler::callback(Request * req){
  Response *res;
  std::string sid = req->getSessionId();
  std::string new_folder_name = req->getBodyParam("newfolder");
  User* user = AP_drive-> get_user_by_sid(sid);
  if(user){
    Elements* elem = user->get_current_elem();
    if(elem){
      AP_drive->new_folder(elem, new_folder_name);
      res = Response::redirect("/elemslist");
    }
    else
      throw Server::Exception("Something went wrong.");
  }
  else
    throw Server::Exception("Something went wrong.");
  return res;
}

Response * DetailsHandler::callback(Request * req){
  Response *res = new Response;
  std::string sid = req->getSessionId();
  User* user = AP_drive->get_user_by_sid(sid);
  if(!user)
    throw Server::Exception("You have to be logged in.");
  std::string path = req->getBodyParam("path");
  Elements* elem = AP_drive->find_element_by_absoloute_path(path);
  if(!elem)
    throw Server::Exception("Something went wrong.");
  res->setHeader("Content-Type", "text/html");
  std::string body = detail_html_maker(user, elem);
  res->setBody(body);
  return res;
}

Response * CopyHandler::callback(Request * req){
  Response *res;
  std::string sid = req->getSessionId();
  User* user = AP_drive->get_user_by_sid(sid);
  if(!user)
    throw Server::Exception("You have to be logged in.");
  std::string path = req->getBodyParam("path");
  Elements* elem = AP_drive->find_element_by_absoloute_path(path);
  if(!elem)
    throw Server::Exception("Something went wrong.");
  user->set_source_elem(elem);
  res = Response::redirect("/elemslist");
  return res;
}

Response * PasteHandler::callback(Request * req){
  Response *res = new Response;
  std::string sid = req->getSessionId();
  User* user = AP_drive->get_user_by_sid(sid);
  if(!user)
    throw Server::Exception("You have to be logged in.");
  Elements* dest_elem = user->get_current_elem();
  if(!dest_elem)
    throw Server::Exception("Something went wrong.");
  if(user->set_dest_elem(dest_elem)){
    if(user->get_source_elem() && user->get_dest_elem()){
      AP_drive->copy(user->get_source_elem(),dynamic_cast<Folder*>(user->get_dest_elem()));
      res = Response::redirect("/elemslist");
    }
  }
  else
    throw Server::Exception("Something went wrong.");
  return res;
}

Response * RemoveHandler::callback(Request * req){
  Response *res;
  std::string sid = req->getSessionId();
  User* user = AP_drive->get_user_by_sid(sid);
  if(!user)
    throw Server::Exception("You have to be logged in.");
  Elements* curr_element = user->get_current_elem();
  if(!curr_element)
    throw Server::Exception("Something went wrong.");
  std::string path = req->getBodyParam("path");
  Elements* to_be_removed = AP_drive->find_element_by_absoloute_path(path);
  if(!to_be_removed)
    throw Server::Exception("Something went wrong.");
  AP_drive->remove(dynamic_cast<Folder*>(curr_element), to_be_removed);
  res = Response::redirect("/elemslist");
  return res;
}