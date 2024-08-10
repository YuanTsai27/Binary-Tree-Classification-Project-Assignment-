#include "dataset.h"

#include <iostream>

using namespace std;

int DataSet::train_dataset_iteration_ = 1;  // debugging

DataSet::DataSet() {
  data_set_ = {};
  total_num_ = 0;
  num_label_1_ = 0;
  num_label_neg_1_ = 0;
}

void DataSet::AddData(float feature1, float feature2, int label) {
  Data new_data = Data(feature1, feature2, label);
  data_set_.push_back(new_data);

  total_num_++;
  if (label == 1) {
    num_label_1_++;
  } else {
    num_label_neg_1_++;
  }
}

vector<Data> DataSet::GetDataSet() const { return this->data_set_; }

void DataSet::ClearDataSet() {
  data_set_.clear();
  total_num_ = 0;
  num_label_1_ = 0;
  num_label_neg_1_ = 0;
}

int DataSet::GetSize() const { return total_num_; }

int DataSet::GetNumLabel1() const { return num_label_1_; }

int DataSet::GetNumLabelNeg1() const { return num_label_neg_1_; }

int DataSet::GetMajorityLabel() {
  if (num_label_1_ > num_label_neg_1_) {
    return 1;
  } else if (num_label_1_ < num_label_neg_1_) {
    return -1;
  } else {
    return 0;
  }
}

float DataSet::GetEntropyImpurity() {
  // n_1/n
  float prop_label_1 = (float)num_label_1_ / (float)total_num_;
  // n_-1/n
  float prop_label_neg_1 = (float)num_label_neg_1_ / (float)total_num_;

  // edge cases
  if (prop_label_1 == 0 || prop_label_neg_1 == 0 || total_num_ == 0) {
    return 0;
  }

  float entropy_impurity = -1 * (prop_label_1 * log2(prop_label_1)) -
                           (prop_label_neg_1 * log2(prop_label_neg_1));

  return entropy_impurity;
}

float DataSet::SplitDataSet(int feature_num, int observation_num) {
  // create sub datasets on the stack
  DataSet left_data_set;
  DataSet right_data_set;

  float impurity_drop = 0;

  // find value to compare to
  float value = data_set_[observation_num].GetFeature(feature_num);

  // splitting dataset

  for (int i = 0; i < data_set_.size(); i++) {
    if (data_set_[i].GetFeature(feature_num) < value) {
      left_data_set.AddData(data_set_[i].GetFeature1(),
                            data_set_[i].GetFeature2(),
                            data_set_[i].GetLabel());
    } else {
      right_data_set.AddData(data_set_[i].GetFeature1(),
                             data_set_[i].GetFeature2(),
                             data_set_[i].GetLabel());
    }
  }

  // calculate entropy impurity for the sub-datasets
  float left_entropy_impurity = left_data_set.GetEntropyImpurity();
  float right_entropy_impurity = right_data_set.GetEntropyImpurity();

  // DEBUGGING PURPOSES ----------------------------------------------
  // if (feature_num == 1 && observation_num == 6) {
  //   // show left dataset
  //   cout << "Left Dataset" << endl;
  //   for (int i = 0; i < left_data_set.GetSize(); i++) {
  //     cout << i << "\t" << left_data_set.GetDataSet()[i].GetFeature1() <<
  //     "\t"
  //          << left_data_set.GetDataSet()[i].GetFeature2() << "\t"
  //          << left_data_set.GetDataSet()[i].GetLabel() << endl;
  //   }

  //   // show right dataset
  //   cout << "Right Dataset" << endl;
  //   for (int i = 0; i < right_data_set.GetSize(); i++) {
  //     cout << i << "\t" << right_data_set.GetDataSet()[i].GetFeature1() <<
  //     "\t"
  //          << right_data_set.GetDataSet()[i].GetFeature2() << "\t"
  //          << right_data_set.GetDataSet()[i].GetLabel() << endl;
  //   }

  //   cout << "Left Entropy Impurity: " << left_entropy_impurity << endl;
  //   cout << "Right Entropy Impurity: " << right_entropy_impurity << endl;
  // }

  // calculate and return the impurity drop
  float left_impurity_drop =
      ((float)left_data_set.GetSize() / (float)total_num_) *
      left_entropy_impurity;
  float right_impurity_drop =
      (1 - (float)left_data_set.GetSize() / (float)total_num_) *
      right_entropy_impurity;

  impurity_drop =
      this->GetEntropyImpurity() - left_impurity_drop - right_impurity_drop;

  return impurity_drop;
}

bool DataSet::TrainDataSet(Node* respective_node) {
  int dataset_id = train_dataset_iteration_;
  train_dataset_iteration_++;

  if (this->GetEntropyImpurity() == 0) {
    respective_node->SetMajorityLabel(this->GetMajorityLabel());
    respective_node->SetImpurity(
        this->GetEntropyImpurity());  // should be 0 at all times

    // cout << "Node " << dataset_id << " is a leaf node with majority label "
    //      << respective_node->GetMajorityLabel() << "and impurity "
    //      << respective_node->GetImpurity()  // debugging purposes
    //      << endl;                           // debugging purposes
    return false;
  }

  int optimal_feature_num = 0;
  int optimal_observation_num = 0;
  float optimal_impurity_drop = 0;
  float impurity_drop = 0;

  // // DEBUGGING PURPOSES
  // impurity_drop = training_data_set_->SplitDataSet(1, 6);
  // cout << "Feature 1\t"
  //      << " Observation 6\t"
  //      << " Impurity Drop " << impurity_drop << endl;  // debugging purposes

  // cout << "----------------------------------" << endl;

  // i is feature number, j is observation number

  for (int i = 1; i <= 2; i++) {
    for (int j = 0; j < this->GetSize(); j++) {
      impurity_drop = this->SplitDataSet(i, j);
      // cout << "Feature " << i << "\t"
      //      << " Observation " << j << "\t"
      //      << " Impurity Drop " << impurity_drop << endl;  // debugging
      //      purposes

      if (impurity_drop > optimal_impurity_drop) {
        optimal_feature_num = i;
        optimal_observation_num = j;
        optimal_impurity_drop = impurity_drop;
      }
    }
  }

  // cout << "Greatest impurity drop is " << optimal_impurity_drop
  //      << " at feature " << optimal_feature_num << " and observation "
  //      << optimal_observation_num << endl;  // debugging purposes

  respective_node->SetImpurity(this->GetEntropyImpurity());
  respective_node->SetSplitDim(optimal_feature_num);
  respective_node->SetSplitValue(
      this->GetDataSet()[optimal_observation_num].GetFeature(
          optimal_feature_num));
  respective_node->SetMajorityLabel(this->GetMajorityLabel());

  // display the node's information, debugging purposes

  // cout << "Node " << dataset_id << " has impurity "
  //      << respective_node->GetImpurity() << ", split dimension "
  //      << respective_node->GetSplitDim() << ", split value "
  //      << respective_node->GetSplitValue() << ", and majority label "
  //      << respective_node->GetMajorityLabel() << endl;

  // create sub datasets on heap and assign them to the respective node's
  // children

  DataSet* left_data_set = new DataSet();
  DataSet* right_data_set = new DataSet();

  // find value to compare
  float value = this->GetDataSet()[optimal_observation_num].GetFeature(
      optimal_feature_num);

  // update the sub datasets
  for (int i = 0; i < this->GetSize(); i++) {
    if (this->GetDataSet()[i].GetFeature(optimal_feature_num) < value) {
      left_data_set->AddData(this->GetDataSet()[i].GetFeature1(),
                             this->GetDataSet()[i].GetFeature2(),
                             this->GetDataSet()[i].GetLabel());
    } else {
      right_data_set->AddData(this->GetDataSet()[i].GetFeature1(),
                              this->GetDataSet()[i].GetFeature2(),
                              this->GetDataSet()[i].GetLabel());
    }
  }

  // print each sub dataset, debugging purposes

  // cout << "Node " << dataset_id << " Left Dataset" << endl;
  // for (int i = 0; i < left_data_set->GetSize(); i++) {
  //   cout << i << "\t" << left_data_set->GetDataSet()[i].GetFeature1() << "\t"
  //        << left_data_set->GetDataSet()[i].GetFeature2() << "\t"
  //        << left_data_set->GetDataSet()[i].GetLabel() << endl;
  // }

  // cout << "Node " << dataset_id << " Right Dataset" << endl;
  // for (int i = 0; i < right_data_set->GetSize(); i++) {
  //   cout << i << "\t" << right_data_set->GetDataSet()[i].GetFeature1() <<
  //   "\t"
  //        << right_data_set->GetDataSet()[i].GetFeature2() << "\t"
  //        << right_data_set->GetDataSet()[i].GetLabel() << endl;
  // }

  Node* left_node = new Node(left_data_set);
  Node* right_node = new Node(right_data_set);

  respective_node->SetLeft(left_node);
  respective_node->SetRight(right_node);

  // cout << "Node " << dataset_id << " Now training left subdataset"
  //      << endl;  // debugging purposes
  // Recursively train left side
  left_data_set->TrainDataSet(left_node);

  // cout << "Node " << dataset_id << " Now training right subdataset"
  //      << endl;  // debugging purposes
  // Recursively train right side
  right_data_set->TrainDataSet(right_node);

  // cout << "--END OF TRAINDATASET FOR NODE-- " << dataset_id
  //      << endl;  // debugging purposes

  return true;
}

DataSet::~DataSet() {
  // cout << "I'm in Data's destructor. Value is " << this->getValue() << "." <<
  // endl; //debugging
}
