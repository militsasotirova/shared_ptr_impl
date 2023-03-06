#include <iostream>
#include "shared_ptr_impl.hpp"

class TestClass {};

void testBoolOp() {
  { // shared_ptr_impl
    shared_ptr_impl<TestClass> p1;
    assert(!p1);
    shared_ptr_impl<TestClass> p2 = make_shared<TestClass>();
    assert(p2);
  }

  { // std::shared_ptr
    std::shared_ptr<TestClass> p1;
    assert(!p1);
    std::shared_ptr<TestClass> p2 = std::make_shared<TestClass>();
    assert(p2);
  }
  std::cout << "testBoolOp success\n";
}

void testUnique() {
  { // shared_ptr_impl
    TestClass* x;
    shared_ptr_impl<TestClass> p1(x);
    assert(p1.unique());
    assert(p1.use_count() == 1);
    shared_ptr_impl<TestClass> p2 = p1;
    assert(!p1.unique() && !p2.unique());
    assert(p1.use_count() == p2.use_count() && p1.use_count() == 2);
  }
  
  { // std::shared_ptr
    TestClass* x;
    std::shared_ptr<TestClass> p1(x);
    assert(p1.unique());
    assert(p1.use_count() == 1);
    std::shared_ptr<TestClass> p2 = p1;
    assert(!p1.unique() && !p2.unique());
    assert(p1.use_count() == p2.use_count() && p1.use_count() == 2);
  }
  std::cout << "testUnique success\n";
}

void testGet() {
  TestClass* x;
  shared_ptr_impl<TestClass> p1(x);
  std::shared_ptr<TestClass> p2(x);
  assert(p1.get() == p2.get());
  
  std::cout << "testGet success\n";
}

void testCopyConstructorAndDestructor() {
  { // shared_ptr_impl
    TestClass* x;
    {
      shared_ptr_impl<TestClass> p1(x);
      assert(p1.use_count() == 1);
      {
          shared_ptr_impl<TestClass> p2(p1);
          assert(p1.use_count() == 2);
      }
      assert(p1.use_count() == 1);
    }
    assert(!x); // The last shared pointer to x is gone, so is x.
  }

  { // std::shared_ptr
    TestClass* x;
    {
      std::shared_ptr<TestClass> p1(x);
      assert(p1.use_count() == 1);
      {
          std::shared_ptr<TestClass> p2(p1);
          assert(p1.use_count() == 2);
      }
      assert(p1.use_count() == 1);
    }
    assert(!x); // The last shared pointer to x is gone, so is x.
  }
  std::cout << "testCopyConstructorAndDestructor success\n";
}

void testMakeShared() {
  { // shared_ptr_impl
    shared_ptr_impl<TestClass> p1 = make_shared<TestClass>();
    shared_ptr_impl<TestClass> p2(p1);
    shared_ptr_impl<TestClass> p3 = p2;
    assert(p1.use_count() == p2.use_count() && p2.use_count() == p3.use_count() && p3.use_count() == 3);
  }

  { // std::shared_ptr
    std::shared_ptr<TestClass> p1 = std::make_shared<TestClass>();
    std::shared_ptr<TestClass> p2(p1);
    std::shared_ptr<TestClass> p3 = p2;
    assert(p1.use_count() == p2.use_count() && p2.use_count() == p3.use_count() && p3.use_count() == 3);
  }
  std::cout << "testMakeShared success\n";
}
