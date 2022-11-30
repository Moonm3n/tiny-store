#include <cstdlib>
#include <unistd.h>

#include <ctime>
#include <iostream>
#include <thread>

#include "b_plus_tree.h"

using namespace std;
#define ORDER 4

int main() {
  BPlusTree bpt(ORDER);  // 初始化一个 4 阶 B+ 树
  for (int i = 0; i < 10; i++) {
    bpt.insert_data(i * 5, rand());
  }
  bpt.print_tree();
  cout << "*****************************************************************************" << endl << endl;
  for (int i = 0; i < 10; i++) {
    bpt.insert_data(i * 3, rand());
  }
  bpt.print_tree();
  cout << "*****************************************************************************" << endl << endl;

  bpt.search_data(3);
  bpt.search_data(4);
  cout << "*****************************************************************************" << endl << endl;

  bpt.update_data(3, 333333);
  bpt.search_data(3);
  cout << "*****************************************************************************" << endl << endl;

  bpt.save_bpt("/home/zhanyueyang/BPlusTree/tree_instance");
  for (int i = 0; i < 5; i++) {
    bpt.remove_data(i * 5);
    bpt.remove_data(i * 3);
  }
  bpt.print_tree();
  cout << "*****************************************************************************" << endl << endl;

  bpt.destroy_bpt();

  bpt.print_tree();
  cout << "*****************************************************************************" << endl << endl;

  bpt.read_bpt("/home/zhanyueyang/BPlusTree/tree_instance");
  bpt.print_tree();
  return 0;
}