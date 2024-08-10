#include "node.h"

#include <math.h>

#include <iostream>

using namespace std;

Node::Node(DataSet *dataset, int split_dim, float split_value, float impurity,
           int majority_label) {
  this->data_set_ = dataset;
  this->split_dim_ = split_dim;
  this->split_value_ = split_value;
  this->impurity_ = impurity;
  this->majority_label_ = majority_label;
  this->left_node_ = nullptr;
  this->right_node_ = nullptr;
  this->is_leaf_ = false;
}

Node::Node(DataSet *dataset) {
  this->data_set_ = dataset;
  this->split_dim_ = 0;
  this->split_value_ = 0;
  this->impurity_ = 0;
  this->majority_label_ = 0;
  this->left_node_ = nullptr;
  this->right_node_ = nullptr;
}

void Node::SetLeft(Node *left_node) { this->left_node_ = left_node; }

void Node::SetRight(Node *right_node) { this->right_node_ = right_node; }

void Node::SetDataSet(DataSet *data_set) { this->data_set_ = data_set; }

void Node::SetSplitDim(int split_dim) { this->split_dim_ = split_dim; }

void Node::SetSplitValue(float split_value) {
  this->split_value_ = split_value;
}

void Node::SetImpurity(float impurity) { this->impurity_ = impurity; }

void Node::SetMajorityLabel(int majority_label) {
  this->majority_label_ = majority_label;
}

Node *Node::GetLeft() const { return this->left_node_; }

Node *Node::GetRight() const { return this->right_node_; }

float Node::GetSplitDim() const { return this->split_dim_; }

float Node::GetSplitValue() const { return this->split_value_; }

float Node::GetImpurity() const { return this->impurity_; }

int Node::GetMajorityLabel() const { return this->majority_label_; }

Node::~Node() {
  // cout << "I'm in Data's destructor. Value is " << this->getValue() << "." <<
  // endl; //debugging
}
