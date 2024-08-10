#include "bct.h"

#include <math.h>

#include <iostream>

using namespace std;

int BinaryClassificationTree::node_iteration_ = 1;  // for debugging

BinaryClassificationTree::BinaryClassificationTree() { root_ = nullptr; }

BinaryClassificationTree::BinaryClassificationTree(Node* root) { root_ = root; }

void BinaryClassificationTree::SetRoot(Node* root) { root_ = root; }

Node* BinaryClassificationTree::GetRoot() const { return root_; }

bool BinaryClassificationTree::IsEmpty() const {
  if (root_ == nullptr) {
    return true;
  } else {
    return false;
  }
}

int BinaryClassificationTree::GetLeafNodes(Node* node) const {
  // cout << "Entered GetLeafNodes function" << endl;
  if (node == nullptr) {
    return 0;
  }

  // if current node is a leaf node
  if ((node->GetLeft() == nullptr) && (node->GetRight() == nullptr)) {
    return 1;
  }

  return GetLeafNodes(node->GetLeft()) + GetLeafNodes(node->GetRight());
  // cout << "Exiting GetLeafNodes function" << endl;
}

void BinaryClassificationTree::PrintTree(Node* root, int starting_indent) {
  int node = node_iteration_;
  node_iteration_++;
  // cout << "Entered PrintTree function for node " << node << endl;

  if (root != nullptr) {
    for (int i = 0; i < starting_indent; i++) {
      cout << " ";
    }

    if ((root->GetLeft() == nullptr) && (root->GetRight() == nullptr)) {
      cout << "label: " << root->GetMajorityLabel() << endl;
    } else {
      cout << std::fixed << std::setprecision(0) << root->GetSplitDim() - 1
           << ", ";
      cout << std::fixed << std::setprecision(3)
           << roundf(root->GetSplitValue() * 1000) / 1000 << ", ";
      cout << std::fixed << std::setprecision(3)
           << roundf(root->GetImpurity() * 1000) / 1000;
      cout << endl;  // convert dimensions 1 and 2 to 0 and 1 respectively
    }

    // cout << "Now printing node " << node << "'s left child" << endl;
    if (root->GetLeft() != nullptr) {
      PrintTree(root->GetLeft(), starting_indent + 3);
    }

    // cout << "Now printing node " << node << "'s right child" << endl;
    if (root->GetRight() != nullptr) {
      PrintTree(root->GetRight(), starting_indent + 3);
    }
  }

  // if (root == nullptr) {
  //   cout << "Node " << node << "is a null pointer" << endl;
  // }

  // cout << "Exiting PrintTree function for node " << node << endl;

  return;
}

// void BinaryClassificationTree::PrintTree(Node* root) {
//   if (root != nullptr) {
//     cout << root->GetSplitDim() - 1 << ", " << root->GetSplitValue() << ", "
//          << root->GetImpurity() << endl;
//     if (root->GetRight()) {
//       cout << "\t";
//       PrintTree(root->GetRight());
//     }
//     if (root->GetLeft()) {
//       cout << "\t";
//       PrintTree(root->GetLeft());
//     }
//   }

//   return;
// }

int BinaryClassificationTree::ClassifyPoint(Node* root, float feature1,
                                            float feature2) {
  if (root->GetLeft() == nullptr && root->GetRight() == nullptr) {
    // is leaf node is reached
    return root->GetMajorityLabel();
  } else {
    if (root->GetSplitDim() == 1) {
      if (feature1 < root->GetSplitValue()) {
        return ClassifyPoint(root->GetLeft(), feature1, feature2);
      } else {
        return ClassifyPoint(root->GetRight(), feature1, feature2);
      }
    } else {
      if (feature2 < root->GetSplitValue()) {
        return ClassifyPoint(root->GetLeft(), feature1, feature2);
      } else {
        return ClassifyPoint(root->GetRight(), feature1, feature2);
      }
    }
  }
}

BinaryClassificationTree::~BinaryClassificationTree() {
  // cout << "I'm in Data's destructor. Value is " << this->getValue() << "." <<
  // endl; //debugging
}
