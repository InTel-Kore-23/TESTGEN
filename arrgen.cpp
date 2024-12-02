// CPP header

#include <bits/stdc++.h>
#include <filesystem>

#include "CPHeader.h"

using namespace std;
namespace fs = std::filesystem;

// END

// Golbal config - User config
string tenbaiMang = "BAI1";
int botestMang = 1;
map<char, pair<int, pair<int, int>>> cauhinhMang;
// END

// Generator functional
int taotestCauHinhMang(int maxlim, int minlim, int kichthuoc, vector<int> &testcase) {
    if (maxlim < minlim) swap(maxlim, minlim);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> dist_n(1, kichthuoc);
    uniform_int_distribution<int> dist_val(minlim, maxlim);
    int kichthuoc_moi = dist_n(rng);
    for (int i = 0; i < kichthuoc_moi; ++i) {
        testcase.push_back(dist_val(rng));
    }
    return kichthuoc_moi;
}

int sinhtestARRAY() {
    cout << u8"Tên bài là gì á bạn? (Mặc định là " << tenbaiMang << ") : ";
    cin >> tenbaiMang;

    cout << u8"Thầy đòi bạn bao nhiêu bộ test? (Mặc định là " << botestMang << ") : ";
    cin >> botestMang;

    int giatri;
    cout << u8"Trong bộ test bạn cần bao nhiêu giá trị? : ";
    cin >> giatri;

    cout << u8"Nhập tên của từng mảng, kích thước và giới hạn phần tử (Ví dụ 'A 10 1000 -1000') : ";
    for (int i = 0; i < giatri; ++i) {
        char name;
        int maxsize, maxlim = 0, minlim = 0;
        cin >> name >> maxsize >> maxlim >> minlim;
        cauhinhMang[name] = make_pair(maxsize, make_pair(maxlim, minlim));
    }

    cout << u8"Chờ chút nha, mình đang ráng..." << endl;

    fs::create_directory("BOTEST");

    for (int i = 1; i <= botestMang; ++i) {
        string tenthumuc = "BOTEST/TEST" + to_string(i);
        fs::create_directory(tenthumuc);

        string input_file_path = tenthumuc + "/" + tenbaiMang + ".INP";
        ofstream input_file(input_file_path);

        vector<int> kichthuocTest;
        vector<vector<int>> testDauVao;

        for (auto &gen : cauhinhMang) {
            vector<int> testcase;
            int kichthuoc_moi = taotestCauHinhMang(gen.second.second.first, gen.second.second.second, gen.second.first, testcase);
            kichthuocTest.push_back(kichthuoc_moi);
            testDauVao.push_back(testcase);
        }

        for (auto &test : kichthuocTest) {
            input_file << test << " ";
        }

        input_file << endl;

        for (auto &test : testDauVao) {
            for (auto &val : test) {
                input_file << val << " ";
            }
            input_file << endl;
        }

        string output_file_path = tenthumuc + "/" + tenbaiMang + ".OUT";
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
