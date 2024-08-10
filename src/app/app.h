#ifndef APP_H
#define APP_H

#include <math.h>

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "bct.h"
#include "data.h"
#include "dataset.h"
#include "node.h"

using namespace std;

class App {
 private:
  DataSet* training_data_set_;
  BinaryClassificationTree* binary_classification_tree_;
  bool is_trained_;

 public:
  App(void);
  ~App(void);
  void AddData(std::string, std::string, std::string);
  void ClearData(void);
  void ShowData(void);
  void TrainClassifier(void);
  void Classify(std::string, std::string);
  void ShowClassifier(void);
};

#endif  // APP_H
