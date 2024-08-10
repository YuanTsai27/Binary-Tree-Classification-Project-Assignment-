# Binary Classification Tree Project Assignment (Completed October 2023)


This project is focused on developing a binary classification tree, a fundamental component in machine learning. This project heavily utilises abstract data types, data structures, recursive operations, the usual OOP principles, and AI concepts such as entropy impurity and optimal splits. Through this, I was able to design a robust and efficient solution to construct the binary classification tree.

A binary classification tree is a crucial algorithm in machine learning used for categorizing data based on specific features. The classifier is trained on labeled data and then applied to categorize unseen data. 

This project was particularly testing-intensive. I wrote extensive console output code to track the state of variables and the progress of the codebase algorithm during development. I have left some of these debugging code in the repository, commented out, to reflect the testing process.



**Code Style**
Throughout this project, I have adhered to the Google C++ Style Guide, ensuring that the code is clean, consistent, and follows industry-standard practices.

**Feel free to check this project out!** _To run this project, cmake is required._

# How to use (terminal)

* **Build:** Create a `build` directory for the output (if it doesn't already exist), generate the build files in it, then run it:
  ```bash
  mkdir build
  cd build
  cmake ..          # generates the build files
  cmake --build .   # execute the build and creates the executable(s)
  ```

* **Run:** Run the program interactively:
  ```bash
  cd build
  ./binary_classifier
  ```

* **Test:** Run the test cases:
  ```bash
  cd build
  ctest     # minimal output
  ctest -V  # verbose output
  ctest --output-on-failure  # verbose for failing test cases, but minimal for tests that pass
  ctest -V -R T1 # run a single specific test case in verbose mode
  ```
