#ifndef MESSAGE_H
#define MESSAGE_H

#include <initializer_list>
#include <string>

class Message {
 private:
  std::string msg_;

 public:
  static const Message ERROR_NO_DATA;
  static const Message ERROR_NO_CLASSIFIER;
  static const Message OUTCOME_CLASSIFY;
  static const Message ERROR_UNKNOWN_LABEL;
  static const Message MESSAGE_NO_DATA;
  static const Message MESSAGE_LEAF_COUNT;

  static const Message COMMAND_NOT_FOUND;
  static const Message WRONG_ARGUMENT_COUNT;
  static const Message END;

  Message(const std::string &msg);
  std::string GetMessage() const;
  std::string GetMessage(std::initializer_list<std::string> args) const;
  void PrintMessage() const;
  void PrintMessage(std::initializer_list<std::string> args) const;
};

#endif  // MESSAGE_H
