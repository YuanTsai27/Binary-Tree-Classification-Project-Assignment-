#include "data.h"

#include <math.h>

#include <iostream>

using namespace std;

Data::Data(float feature1, float feature2, int label) {
  this->feature1_ = feature1;
  this->feature2_ = feature2;
  this->label_ = label;
}

float Data::GetFeature1() const { return this->feature1_; }

float Data::GetFeature2() const { return this->feature2_; }

float Data::GetFeature(int feature_num) const {
  if (feature_num == 1) {
    return this->feature1_;
  } else {
    return this->feature2_;
  }
}

int Data::GetLabel() const { return this->label_; }

Data::~Data() {
  // cout << "I'm in Data's destructor. Value is " << this->getValue() << "." <<
  // endl; //debugging
}
