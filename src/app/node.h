#ifndef NODE_H
#define NODE_H

#include <math.h>

#include <cmath>
#include <iostream>
#include <vector>

#include "dataset.h"

using namespace std;

class DataSet;  // forward declaration of DataSet class

class Node {
 private:
  DataSet *data_set_;
  float split_dim_;
  float split_value_;
  float impurity_;
  int majority_label_;

  bool is_leaf_;

  Node *left_node_;
  Node *right_node_;

 public:
  Node(DataSet *data_set);
  Node(DataSet *data_set, int split_dim, float split_value, float impurity,
       int majority_label);
  void SetLeft(Node *left);
  void SetRight(Node *right);
  void SetDataSet(DataSet *data_set);
  void SetSplitDim(int split_dim);
  void SetSplitValue(float split_value);
  void SetImpurity(float impurity);
  void SetMajorityLabel(int majority_label);
  Node *GetLeft() const;
  Node *GetRight() const;
  float GetSplitDim() const;
  float GetSplitValue() const;
  float GetImpurity() const;
  int GetMajorityLabel() const;

  ~Node();
};

#endif /* NODE_H */
