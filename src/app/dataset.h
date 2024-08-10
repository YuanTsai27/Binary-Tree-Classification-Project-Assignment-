#ifndef DATASET_H
#define DATASET_H

#include <math.h>

#include <cmath>
#include <iostream>
#include <vector>

#include "data.h"
#include "node.h"

class Node;  // forward declaration of Node class

using namespace std;

class DataSet {
 private:
  vector<Data> data_set_;

  int total_num_;
  int num_label_1_;
  int num_label_neg_1_;

  static int train_dataset_iteration_;  // for debugging

 public:
  DataSet();

  // Task 1 stuff
  void AddData(float feature1, float feature2, int label);
  vector<Data> GetDataSet() const;
  void ClearDataSet();
  int GetSize() const;
  int GetNumLabel1() const;
  int GetNumLabelNeg1() const;

  // Task 2 Stuff

  int GetMajorityLabel();
  float GetEntropyImpurity();
  float SplitDataSet(int feature_num, int observation_num);
  bool TrainDataSet(Node* respective_node);

  ~DataSet();
};

#endif /* DATASET_H */
