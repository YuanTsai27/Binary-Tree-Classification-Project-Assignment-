#include "app.h"

#include <iostream>

#include "message.h"
#include "utils.h"

using namespace std;

App::App() {
  training_data_set_ = new DataSet();
  binary_classification_tree_ = new BinaryClassificationTree();
  is_trained_ = false;
}

App::~App() {}

void App::AddData(std::string x_in_, std::string y_in_, std::string label_in_) {
  if (stoi(label_in_) != -1 && stoi(label_in_) != 1) {
    Message::ERROR_UNKNOWN_LABEL.PrintMessage();
    return;
  }

  // no need to test for under 1000 observations condition

  // add data to training_data_set_
  training_data_set_->AddData(stof(x_in_), stof(y_in_), stoi(label_in_));
  return;
}

void App::ClearData() { training_data_set_->ClearDataSet(); }

void App::ShowData() {
  // check if dataset has data points
  if (training_data_set_->GetSize() == 0) {
    Message::MESSAGE_NO_DATA.PrintMessage();
    return;
  }

  for (int i = 0; i < training_data_set_->GetSize(); i++) {
    cout << i << "\t"
         << roundf(training_data_set_->GetDataSet()[i].GetFeature1() * 1000) /
                1000
         << "\t"
         << roundf(training_data_set_->GetDataSet()[i].GetFeature2() * 1000) /
                1000
         << "\t" << training_data_set_->GetDataSet()[i].GetLabel() << endl;
  }

  // cout << "Entropy is " << training_data_set_->GetEntropyImpurity() << endl;

  return;
}

void App::TrainClassifier() {
  // check if dataset has the appropriate data points to train

  if (training_data_set_->GetSize() == 0) {
    Message::ERROR_NO_DATA.PrintMessage();
    return;
  }

  if (training_data_set_->GetNumLabel1() == 0 ||
      training_data_set_->GetNumLabelNeg1() == 0) {
    Message::ERROR_NO_DATA.PrintMessage();
    return;
  }

  // reset classifier if required
  if (is_trained_ == true) {
    delete binary_classification_tree_;
    binary_classification_tree_ = new BinaryClassificationTree();
  }

  bool not_the_end = true;

  Node* root_node = new Node(training_data_set_);
  binary_classification_tree_->SetRoot(root_node);
  not_the_end = training_data_set_->TrainDataSet(root_node);

  // cout << "*****************END OF TRAINCLASSIFIER*****************" << endl;

  is_trained_ = true;
}

void App::Classify(std::string x_in_, std::string y_in_) {
  if (is_trained_ == false) {
    Message::ERROR_NO_CLASSIFIER.PrintMessage();
    return;
  }

  float x = stof(x_in_);
  float y = stof(y_in_);

  int prediction = binary_classification_tree_->ClassifyPoint(
      binary_classification_tree_->GetRoot(), x, y);

  Message::OUTCOME_CLASSIFY.PrintMessage({to_string(prediction)});

  return;
}

void App::ShowClassifier() {
  if (is_trained_ == false) {
    Message::ERROR_NO_CLASSIFIER.PrintMessage();
    return;
  }

  // cout << "Now entering PrintTree" << endl;
  binary_classification_tree_->PrintTree(binary_classification_tree_->GetRoot(),
                                         0);

  // cout << "Now printing final message" << endl;
  Message::MESSAGE_LEAF_COUNT.PrintMessage(
      {to_string(binary_classification_tree_->GetLeafNodes(
          binary_classification_tree_->GetRoot()))});

  return;
}
