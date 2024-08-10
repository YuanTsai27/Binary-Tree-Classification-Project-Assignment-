
#include "message.h"

#include <iostream>

using namespace std;

const Message Message::ERROR_NO_DATA(
    "Cannot perform that operation without at least one observation from each "
    "category in training data set.");
const Message Message::ERROR_NO_CLASSIFIER(
    "Cannot perform that operation without first training a classifier.");
const Message Message::OUTCOME_CLASSIFY("Observation classified as: %s");
const Message Message::ERROR_UNKNOWN_LABEL("Label must be either -1 or 1.");
const Message Message::MESSAGE_NO_DATA("No observations in training data set.");
const Message Message::MESSAGE_LEAF_COUNT(
    "Binary classification tree is comprised of %s leaf node(s).");
const Message Message::COMMAND_NOT_FOUND(
    "Command '%s' not found. Run 'help' for the list of available commands.");
const Message Message::WRONG_ARGUMENT_COUNT(
    "Incorrect number of arguments for %s.");
const Message Message::END("Program ended.");

Message::Message(const std::string &msg) { this->msg_ = msg; }

std::string Message::GetMessage() const { return GetMessage({}); }

std::string Message::GetMessage(std::initializer_list<std::string> args) const {
  std::string result = msg_;
  for (const string &arg : args) {
    size_t pos = result.find("%s");
    if (pos != std::string::npos) {
      result.replace(pos, 2, arg);
    }
  }
  return result;
}

void Message::PrintMessage() const { PrintMessage({}); }

void Message::PrintMessage(std::initializer_list<std::string> args) const {
  cout << GetMessage(args) << endl;
}
