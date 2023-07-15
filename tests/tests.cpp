#include <gtest/gtest.h>

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

//TODO: create tests for routes
//TODO: move mocks to a separate file (header?)
