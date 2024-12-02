// CPP header

#include <bits/stdc++.h>
#include <filesystem>

#include "CPHeader.h"

using namespace std;
namespace fs = std::filesystem;

// END

// Golbal config - User config
string tenbaiSo = "BAI1";
int botestSo = 1;
map<char, pair<int, int>> cauhinhSo;
// END

// Generator functional
void taotestCauHinhSo(int maxlim, int minlim, string &testcase) {
    if (maxlim < minlim) swap(maxlim, minlim);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> dist_val(minlim, maxlim);
    testcase += to_string(dist_val(rng)) + " ";
}

int sinhtestINT() {
    cout << u8"Tên bài là gì á bạn? (Mặc định là " << tenbaiSo << ") : ";
    cin >> tenbaiSo;

    cout << u8"Thầy đòi bạn bao nhiêu bộ test? (Mặc định là " << botestSo << ") : ";
    cin >> botestSo;

    int giatri;
    cout << u8"Trong bộ test bạn cần bao nhiêu giá trị? : ";
    cin >> giatri;

    cout << u8"Nhập tên từng biến và giới hạn của nó nha (Ví dụ 'N 10 1') : ";
    for (int i = 0; i < giatri; ++i) {
        char name;
        int maxlim = 0, minlim = 0;
        cin >> name >> maxlim >> minlim;
        cauhinhSo[name] = make_pair(maxlim, minlim);
    }

    cout << u8"Chờ chút nha, mình đang ráng..." << endl;

    fs::create_directory("BOTEST");

    for (int i = 1; i <= botestSo; ++i) {
        string testcase = "";

        string tenthumuc = "BOTEST/TEST" + to_string(i);
        fs::create_directory(tenthumuc);

        string input_file_path = tenthumuc + "/" + tenbaiSo + ".INP";
        ofstream input_file(input_file_path);

        for (auto &gen : cauhinhSo) {
            taotestCauHinhSo(gen.second.first, gen.second.second, testcase);
        }

        input_file << testcase << endl;

        string output_file_path = tenthumuc + "/" + tenbaiSo + ".OUT";
        string command = "./a.out < " + input_file_path + " > " + output_file_path;
        #ifdef _WIN32
            command = "a.exe < " + input_file_path + " > " + output_file_path;
        #endif
        system(command.c_str());
    }

    cout << u8"Xong rồi nha, nộp thầy lẹ bạn ơi!" << endl;

    return 0;
}

// EOF
