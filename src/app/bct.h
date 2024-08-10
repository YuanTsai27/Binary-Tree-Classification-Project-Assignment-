#ifndef BCT_H
#define BCT_H

#include <math.h>

#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

#include "node.h"

using namespace std;

class BinaryClassificationTree {
 private:
  Node* root_;

  static int node_iteration_;  // for debugging

 public:
  BinaryClassificationTree();
  BinaryClassificationTree(Node* root);
  void SetRoot(Node* root);
  Node* GetRoot() const;
  bool IsEmpty() const;
  int GetLeafNodes(Node* root) const;
  void PrintTree(Node* root, int starting_indent);
  int ClassifyPoint(Node* root, float feature1, float feature2);

  ~BinaryClassificationTree();
};

#endif /* BCT_H */
