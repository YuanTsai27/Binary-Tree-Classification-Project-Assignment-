#include <algorithm>
#include <cctype>
#include <cstring>
#include <fstream>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "app/launcher.h"
#include "app/utils.h"

using namespace std;

enum TestResult { TEST_RESULT_PASS, TEST_RESULT_FAIL };

#define RUN_COMMAND(command_with_args)                         \
  cout << app.GetCommandPrefix() << command_with_args << endl; \
  app.ProcessCommand(command_with_args);

#define __FILENAME__ \
  (std::strrchr(__FILE__, '/') ? std::strrchr(__FILE__, '/') + 1 : __FILE__)

#define EXPECT_CONTAINS(expected)                                              \
  if (still_capturing_cout) {                                                  \
    still_capturing_cout = false;                                              \
    output = buffer.str();                                                     \
    std::cout.rdbuf(old);                                                      \
    std::cout << output << std::endl;                                          \
  }                                                                            \
  if (output.find(expected) == std::string::npos) {                            \
    cerr << "FAILED Test " << test_number << " in " << __FILENAME__            \
         << " on line " << __LINE__ << endl                                    \
         << "\tExpected '" << expected                                         \
         << "' in the output, but it was not found." << endl                   \
         << endl                                                               \
         << "----------------------------------------------------------------" \
            "------------"                                                     \
         << endl                                                               \
         << endl;                                                              \
    return TEST_RESULT_FAIL;                                                   \
  }

#define EXPECT_DOES_NOT_CONTAINS(expected, ignore_case)             \
  output = buffer.str();                                            \
  if (Utils::Contains(output, expected, ignore_case)) {             \
    cerr << "FAILED Test " << test_number << " in " << __FILENAME__ \
         << " on line " << __LINE__ << endl                         \
         << "\tExpected '" << expected                              \
         << "' to NOT be in the output, but it was." << endl        \
         << endl;                                                   \
    return TEST_RESULT_FAIL;                                        \
  }

int main(int argc, char *argv[]) {
  Launcher app;
  string output = "";
  bool still_capturing_cout = true;
  std::stringstream buffer;
  std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());

  int test_number = std::stoi(argv[1]);
  switch (test_number) {
    case 1:  // T1
      RUN_COMMAND("clear-data");
      RUN_COMMAND("show-data");
      RUN_COMMAND("exit");
      EXPECT_CONTAINS("No observations in training data set.");
      break;

    case 2:  // T2
      RUN_COMMAND("clear-data");
      RUN_COMMAND("add-data 0.9074 0.5488 -1");
      RUN_COMMAND("add-data 0.9529 0.6392 -1");
      RUN_COMMAND("show-data");
      RUN_COMMAND("exit");
      EXPECT_CONTAINS(
          "0\t0.907\t0.549\t-1\n"
          "1\t0.953\t0.639\t-1");
      break;

    case 3:  // T3
      RUN_COMMAND("clear-data");
      RUN_COMMAND("add-data 0.9074 0.5488 2");
      RUN_COMMAND("add-data 0.9529 0.6392 -1");
      RUN_COMMAND("show-data");
      RUN_COMMAND("exit");
      EXPECT_CONTAINS("Label must be either -1 or 1.");
      EXPECT_CONTAINS("0\t0.953\t0.639\t-1");
      break;

    case 4:  // T4
      for (int i = 0; i < 500; i++) {
        RUN_COMMAND("add-data 0.9529 0.6392 -1");
        RUN_COMMAND("add-data 0.0788 0.5709 1")
      }
      RUN_COMMAND("show-data");
      RUN_COMMAND("clear-data");
      RUN_COMMAND("add-data 0.9074 0.5488 -1");
      RUN_COMMAND("add-data 0.9529 0.6392 -1");
      RUN_COMMAND("show-data");
      RUN_COMMAND("exit");
      EXPECT_CONTAINS("998\t0.953\t0.639\t-1");
      EXPECT_CONTAINS("999\t0.079\t0.571\t1");
      EXPECT_CONTAINS(
          "0\t0.907\t0.549\t-1\n"
          "1\t0.953\t0.639\t-1");
      EXPECT_DOES_NOT_CONTAINS("Label must be either -1 or 1.", true);
      break;

    case 5:  // T5
      RUN_COMMAND("add-data 0.4246 0.1961 -1")
      RUN_COMMAND("add-data 0.4670 0.3277 -1")
      RUN_COMMAND("add-data 0.3394 0.0856 -1")
      RUN_COMMAND("add-data 0.0788 0.5709 1")
      RUN_COMMAND("add-data 0.4853 0.7109 1")
      RUN_COMMAND("add-data 0.4786 0.9579 1")
      RUN_COMMAND("show-data")
      RUN_COMMAND("clear-data")
      RUN_COMMAND("show-data")
      RUN_COMMAND("exit");
      EXPECT_CONTAINS(
          "0\t0.425\t0.196\t-1\n"
          "1\t0.467\t0.328\t-1\n"
          "2\t0.339\t0.086\t-1\n"
          "3\t0.079\t0.571\t1\n"
          "4\t0.485\t0.711\t1\n"
          "5\t0.479\t0.958\t1");
      EXPECT_CONTAINS("No observations in training data set");
      break;

    case 6:  // T6
      RUN_COMMAND("clear-data");
      RUN_COMMAND("show-classifier");
      RUN_COMMAND("exit");
      EXPECT_CONTAINS(
          "Cannot perform that operation without first training a classifier");
      break;

    case 7:  // T7
      RUN_COMMAND("clear-data");
      RUN_COMMAND("train-classifier");
      RUN_COMMAND("exit");
      EXPECT_CONTAINS(
          "Cannot perform that operation without at least one observation from "
          "each category in training data set.");
      break;

    case 8:  // T8
      RUN_COMMAND("clear-data");
      RUN_COMMAND("add-data 0.9074 0.5488 -1");
      RUN_COMMAND("train-classifier");
      RUN_COMMAND("exit");
      EXPECT_CONTAINS(
          "Cannot perform that operation without at least one observation from "
          "each category in training data set.");
      break;

    case 9:  // T9
      RUN_COMMAND("clear-data");
      RUN_COMMAND("add-data 0.9074 0.5488 -1");
      RUN_COMMAND("add-data 0.9529 0.6392 -1");
      RUN_COMMAND("add-data 0.5635 0.7734 -1");
      RUN_COMMAND("add-data 0.9567 0.9788 -1");
      RUN_COMMAND("add-data 0.8162 0.9824 -1");
      RUN_COMMAND("add-data 0.3279 0.3789 -1");
      RUN_COMMAND("add-data 0.0179 0.3716 -1");
      RUN_COMMAND("add-data 0.4246 0.1961 -1");
      RUN_COMMAND("add-data 0.4670 0.3277 -1");
      RUN_COMMAND("add-data 0.3394 0.0856 -1");
      RUN_COMMAND("add-data 0.0788 0.5709 1");
      RUN_COMMAND("add-data 0.4853 0.7109 1");
      RUN_COMMAND("add-data 0.4786 0.9579 1");
      RUN_COMMAND("add-data 0.2427 0.8961 1");
      RUN_COMMAND("add-data 0.4001 0.9797 1");
      RUN_COMMAND("add-data 0.8530 0.4117 1");
      RUN_COMMAND("add-data 0.5159 0.3474 1");
      RUN_COMMAND("add-data 0.6385 0.1585 1");
      RUN_COMMAND("add-data 0.5231 0.4751 1");
      RUN_COMMAND("add-data 0.5486 0.0172 1");
      RUN_COMMAND("train-classifier");
      RUN_COMMAND("show-classifier");
      RUN_COMMAND("classify 0.99 0.99");
      RUN_COMMAND("exit");
      EXPECT_CONTAINS(
          "0, 0.907, 1.000\n"
          "   0, 0.479, 0.977\n"
          "      1, 0.571, 0.954\n"
          "         label: -1\n"
          "         label: 1\n"
          "      1, 0.773, 0.764\n"
          "         label: 1\n"
          "         0, 0.564, 0.918\n"
          "            label: 1\n"
          "            label: -1\n"
          "   label: -1\n"
          "Binary classification tree is comprised of 6 leaf node(s).");
      EXPECT_CONTAINS("Observation classified as: -1");
      break;

    case 10:  // T10
      RUN_COMMAND("clear-data");
      RUN_COMMAND("add-data 0.6377 0.9577 -1");
      RUN_COMMAND("add-data 0.6761 0.2891 1");
      RUN_COMMAND("add-data 0.6951 0.0680 -1");
      RUN_COMMAND("add-data 0.2240 0.6678 1");
      RUN_COMMAND("add-data 0.3445 0.7805 1");
      RUN_COMMAND("add-data 0.0067 0.6022 -1");
      RUN_COMMAND("add-data 0.9160 0.0012 -1");
      RUN_COMMAND("add-data 0.4243 0.4609 1");
      RUN_COMMAND("add-data 0.3225 0.7847 -1");
      RUN_COMMAND("add-data 0.0358 0.1759 1");
      RUN_COMMAND("add-data 0.4735 0.1527 -1");
      RUN_COMMAND("add-data 0.6074 0.1917 1");
      RUN_COMMAND("train-classifier");
      RUN_COMMAND("show-classifier");
      RUN_COMMAND("classify 0.99 0.55");
      RUN_COMMAND("clear-data");
      RUN_COMMAND("train-classifier");
      RUN_COMMAND("add-data 0.8959 0.4597	-1");
      RUN_COMMAND("add-data 0.1959 0.8497	1");
      RUN_COMMAND("add-data 0.6622 0.1071	1");
      RUN_COMMAND("add-data 0.4549 0.6506	1");
      RUN_COMMAND("add-data 0.1107 0.6038	-1");
      RUN_COMMAND("add-data 0.0912 0.9057	1");
      RUN_COMMAND("add-data 0.6442 0.2359	1");
      RUN_COMMAND("add-data 0.0790 0.6458	-1");
      RUN_COMMAND("add-data 0.6189 0.9703	1");
      RUN_COMMAND("add-data 0.3318 0.4579	-1");
      RUN_COMMAND("add-data 0.5231 0.9892	1");
      RUN_COMMAND("add-data 0.3969 0.5907	1");
      RUN_COMMAND("add-data 0.5077 0.1455	-1");
      RUN_COMMAND("add-data 0.5011 0.1419	-1");
      RUN_COMMAND("add-data 0.5931 0.8094	-1");
      RUN_COMMAND("add-data 0.6741 0.7572	-1");
      RUN_COMMAND("add-data 0.6196 0.7699	-1");
      RUN_COMMAND("add-data 0.4390 0.4888	-1");
      RUN_COMMAND("add-data 0.8329 0.5015	-1");
      RUN_COMMAND("add-data 0.3644 0.8208	-1");
      RUN_COMMAND("add-data 0.6494 0.7366	1");
      RUN_COMMAND("add-data 0.1053 0.9586	-1");
      RUN_COMMAND("add-data 0.5601 0.0988	-1");
      RUN_COMMAND("add-data 0.1536 0.3085	-1");
      RUN_COMMAND("add-data 0.3435 0.6631	1");
      RUN_COMMAND("add-data 0.7967 0.5766	-1");
      RUN_COMMAND("add-data 0.2485 0.9087	1");
      RUN_COMMAND("add-data 0.9898 0.3237	1");
      RUN_COMMAND("add-data 0.6139 0.6521	1");
      RUN_COMMAND("add-data 0.7978 0.6104	-1");
      RUN_COMMAND("add-data 0.1746 0.0599	-1");
      RUN_COMMAND("add-data 0.3834 0.0131	1");
      RUN_COMMAND("add-data 0.3182 0.9556	-1");
      RUN_COMMAND("add-data 0.3972 0.2778	-1");
      RUN_COMMAND("add-data 0.7805 0.4457	-1");
      RUN_COMMAND("add-data 0.0480 0.5308	1");
      RUN_COMMAND("add-data 0.6146 0.9324	1");
      RUN_COMMAND("add-data 0.7549 0.3262	1");
      RUN_COMMAND("add-data 0.6456 0.5112	1");
      RUN_COMMAND("add-data 0.2313 0.9826	-1");
      RUN_COMMAND("add-data 0.4127 0.9853	-1");
      RUN_COMMAND("add-data 0.6119 0.0112	1");
      RUN_COMMAND("add-data 0.7416 0.2173	-1");
      RUN_COMMAND("add-data 0.2626 0.0786	-1");
      RUN_COMMAND("add-data 0.4850 0.5153	1");
      RUN_COMMAND("add-data 0.4132 0.4022	1");
      RUN_COMMAND("add-data 0.3351 0.1338	1");
      RUN_COMMAND("add-data 0.9228 0.4875	1");
      RUN_COMMAND("add-data 0.0046 0.1885	1");
      RUN_COMMAND("add-data 0.6108 0.7925	1");
      RUN_COMMAND("show-data");
      RUN_COMMAND("train-classifier");
      RUN_COMMAND("show-classifier");
      RUN_COMMAND("classify 0.435 0.815");
      RUN_COMMAND("exit");
      EXPECT_CONTAINS(
          "1, 0.176, 1.000\n"
          "   label: -1\n"
          "   1, 0.785, 0.918\n"
          "      0, 0.036, 0.592\n"
          "         label: -1\n"
          "         label: 1\n"
          "      label: -1\n"
          "Binary classification tree is comprised of 4 leaf node(s).");
      EXPECT_CONTAINS("Observation classified as: 1");
      EXPECT_CONTAINS(
          "Cannot perform that operation without at least one observation from "
          "each category in training data set.");
      EXPECT_CONTAINS(
          "0\t0.896\t0.460\t-1\n"
          "1\t0.196\t0.850\t1\n"
          "2\t0.662\t0.107\t1\n"
          "3\t0.455\t0.651\t1\n"
          "4\t0.111\t0.604\t-1\n"
          "5\t0.091\t0.906\t1\n"
          "6\t0.644\t0.236\t1\n"
          "7\t0.079\t0.646\t-1\n"
          "8\t0.619\t0.970\t1\n"
          "9\t0.332\t0.458\t-1\n"
          "10\t0.523\t0.989\t1\n"
          "11\t0.397\t0.591\t1\n"
          "12\t0.508\t0.146\t-1\n"
          "13\t0.501\t0.142\t-1\n"
          "14\t0.593\t0.809\t-1\n"
          "15\t0.674\t0.757\t-1\n"
          "16\t0.620\t0.770\t-1\n"
          "17\t0.439\t0.489\t-1\n"
          "18\t0.833\t0.502\t-1\n"
          "19\t0.364\t0.821\t-1\n"
          "20\t0.649\t0.737\t1\n"
          "21\t0.105\t0.959\t-1\n"
          "22\t0.560\t0.099\t-1\n"
          "23\t0.154\t0.309\t-1\n"
          "24\t0.344\t0.663\t1\n"
          "25\t0.797\t0.577\t-1\n"
          "26\t0.249\t0.909\t1\n"
          "27\t0.990\t0.324\t1\n"
          "28\t0.614\t0.652\t1\n"
          "29\t0.798\t0.610\t-1\n"
          "30\t0.175\t0.060\t-1\n"
          "31\t0.383\t0.013\t1\n"
          "32\t0.318\t0.956\t-1\n"
          "33\t0.397\t0.278\t-1\n"
          "34\t0.781\t0.446\t-1\n"
          "35\t0.048\t0.531\t1\n"
          "36\t0.615\t0.932\t1\n"
          "37\t0.755\t0.326\t1\n"
          "38\t0.646\t0.511\t1\n"
          "39\t0.231\t0.983\t-1\n"
          "40\t0.413\t0.985\t-1\n"
          "41\t0.612\t0.011\t1\n"
          "42\t0.742\t0.217\t-1\n"
          "43\t0.263\t0.079\t-1\n"
          "44\t0.485\t0.515\t1\n"
          "45\t0.413\t0.402\t1\n"
          "46\t0.335\t0.134\t1\n"
          "47\t0.923\t0.488\t1\n"
          "48\t0.005\t0.189\t1\n"
          "49\t0.611\t0.793\t1");
      EXPECT_CONTAINS(
          "0, 0.079, 1.000\n"
          "   label: 1\n"
          "   0, 0.335, 0.999\n"
          "      1, 0.850, 0.811\n"
          "         label: -1\n"
          "         1, 0.956, 1.000\n"
          "            label: 1\n"
          "            label: -1\n"
          "      0, 0.674, 0.991\n"
          "         0, 0.611, 0.931\n"
          "            0, 0.364, 1.000\n"
          "               label: 1\n"
          "               0, 0.560, 0.985\n"
          "                  1, 0.402, 1.000\n"
          "                     0, 0.397, 0.811\n"
          "                        label: 1\n"
          "                        label: -1\n"
          "                     0, 0.455, 0.954\n"
          "                        1, 0.821, 0.971\n"
          "                           0, 0.439, 0.918\n"
          "                              label: 1\n"
          "                              label: -1\n"
          "                           label: -1\n"
          "                        label: 1\n"
          "                  label: -1\n"
          "            1, 0.770, 0.469\n"
          "               label: 1\n"
          "               0, 0.620, 0.811\n"
          "                  label: 1\n"
          "                  label: -1\n"
          "         0, 0.923, 0.881\n"
          "            1, 0.446, 0.544\n"
          "               0, 0.755, 1.000\n"
          "                  label: -1\n"
          "                  label: 1\n"
          "               label: -1\n"
          "            label: 1\n"
          "Binary classification tree is comprised of 19 leaf node(s).");
      EXPECT_DOES_NOT_CONTAINS("Observation classified as: -1", false);
      break;

    default:
      cerr << "Test case not found: #" << test_number << endl;
      return TEST_RESULT_FAIL;
  }

  cerr << "PASSED Test " << test_number << "." << endl
       << endl
       << "--------------------------------------------------------------------"
          "--------"
       << endl
       << endl;

  return TEST_RESULT_PASS;
}