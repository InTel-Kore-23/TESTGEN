// CPP header

#include <bits/stdc++.h>

#include "CPHeader.h"

using namespace std;

// END

// Golbal config
string solve_code = "solve.cpp";
map<int, string> generator;
// END

// Generator setup
void setup() {
    #ifdef _WIN32
        system("chcp 65001");
    #endif
  generator.insert(make_pair(0, u8"Dạng số"));
  generator.insert(make_pair(1, u8"Dạng xâu"));
  generator.insert(make_pair(2, u8"Dạng mảng"));
  generator.insert(make_pair(3, u8"Dạng mảng hai chiều"));
  generator.insert(make_pair(4, u8"Dạng cặp 2 số (có thêm M)"));
}
// END

// User option
signed main() {
  setup();

  cout << u8"Tên bài giải (ví dụ solve.cpp): ";
  cin >> solve_code;

  if (!fopen(solve_code.c_str(), "r")) {
    cout << u8"File bài giải không tồn tại! Kiểm tra lại đi bạn ơi =))" << endl;
    return 0;
  }

  cout << u8"Bạn muốn sinh test dạng nào?" << endl;
  cout << u8"Chọn một cái nè:" << endl;
  for (auto gen : generator) {
    cout << "(" << gen.first << ") : " << gen.second << endl;
  }

  string option;
  cout << u8"Chọn một số (0, 1, 2, 3): ";
  cin >> option;

  cout << u8"Chờ mình tí nha..." << endl;

  if (option == "0") {
    string command = "g++ " + solve_code;
    system(command.c_str());
    sinhtestINT();
  } else if (option == "1") {
    string command = "g++ " + solve_code;
    system(command.c_str());
    sinhtestSTR();
  } else if (option == "2") {
    string command = "g++ " + solve_code;
    system(command.c_str());
    sinhtestARRAY();
  } else if (option == "3") {
    string command = "g++ " + solve_code;
    system(command.c_str());
    sinhtestARRAY2D();
  } else if (option == "4") {
    string command = "g++ " + solve_code;
    system(command.c_str());
    sinhtestPAIR();
  } else {
    cout << u8"Chọn lại nha, mình không biết chọn cái nào hết á..." << endl;
  }

  return 0;
}

// EOF
