#ifndef DATA_H
#define DATA_H

class Data {
 private:
  // int index number; // probs not necessary
  float feature1_;
  float feature2_;
  int label_;

 public:
  Data(float feature1, float feature2, int label);
  float GetFeature1() const;
  float GetFeature2() const;
  float GetFeature(int feature_num) const;
  int GetLabel() const;

  ~Data();
};

#endif /* DATA_H */
