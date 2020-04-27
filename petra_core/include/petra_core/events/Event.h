#pragma once

#include <string>

class Event
{
public:
  std::string type;
  std::string message;

  Event(const std::string &type, const std::string &message) : id_(++max_id_), type(type), message(message) {}
  Event(const std::string &type) : Event(type, "") {}

  int id() { return id_; }
  
private:
  static int max_id_;

  int id_;
};