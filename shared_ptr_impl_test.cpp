#include "shared_ptr_impl_test.hpp"

int main() {
  testBoolOp();
  testUnique();
  testGet();
  testCopyConstructorAndDestructor();
  testMakeShared();
  std::cout << "----------\nall tests succeeded\n"; 
  return 0;
}
