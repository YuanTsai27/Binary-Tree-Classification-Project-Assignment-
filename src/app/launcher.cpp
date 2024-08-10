
#include "launcher.h"

#include <iostream>
#include <vector>

#include "message.h"
#include "utils.h"

using namespace std;

string Launcher::COMMAND_PREFIX = "binary_classifier> ";

Launcher::Launcher() {}

bool Launcher::ProcessCommand(const std::string &cmd_input) {
  // Check it is a valid command name
  string cmd_input_name = Utils::GetFirstWord(cmd_input);
  Command command = Command::Find(cmd_input_name);
  if (command == Command::INVALID) {
    Message::COMMAND_NOT_FOUND.PrintMessage({cmd_input_name});
    return true;
  }

  // Check the number of arguments provided match as the command expects
  vector<string> args = Utils::SplitString(cmd_input);
  int num_args_provided = args.size() - 1;
  int num_args_expected = command.GetNumArgs();
  if (num_args_provided != num_args_expected) {
    string provided = to_string(num_args_provided) + " argument" +
                      (num_args_provided == 1 ? "" : "s");
    string expected = to_string(num_args_expected) + " argument" +
                      (num_args_expected == 1 ? "" : "s");
    cout << Message::WRONG_ARGUMENT_COUNT.GetMessage({command.GetName()}) +
                " Expected " + expected + ", but " + provided + " provided."
         << endl;
    return true;
  }

  if (command == Command::ADD_DATA) {
    app_.AddData(args[1], args[2], args[3]);
  } else if (command == Command::CLEAR_DATA) {
    app_.ClearData();
  } else if (command == Command::SHOW_DATA) {
    app_.ShowData();
  } else if (command == Command::TRAIN_CLASSIFIER) {
    app_.TrainClassifier();
  } else if (command == Command::CLASSIFY) {
    app_.Classify(args[1], args[2]);
  } else if (command == Command::SHOW_CLASSIFIER) {
    app_.ShowClassifier();
  } else if (command == Command::HELP) {
    cout << Command::GetHelp() << endl;
  } else if (command == Command::EXIT) {
    Message::END.PrintMessage();
    return false;
  } else {
    Message::COMMAND_NOT_FOUND.PrintMessage({cmd_input});
  }
  return true;
}

void Launcher::Start() {
  PrintBanner();
  cout << Command::GetHelp() << endl;

  // Keep reading commands until the user exits
  string cmd_input;
  do {
    cout << COMMAND_PREFIX;
    std::getline(std::cin, cmd_input);
    cmd_input = Utils::TrimString(cmd_input);
  } while (ProcessCommand(cmd_input));
}

void Launcher::PrintBanner() const {
  // https://emojicombos.com/dot-art-generator
  // https://www.freeformatter.com/java-dotnet-escape.html#before-output

  std::string banner = "Welcome to Binary Classifier!";
  cout << endl << banner << endl << endl;
}

std::string Launcher::GetCommandPrefix() const { return COMMAND_PREFIX; }
