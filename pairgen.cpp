// CPP header

#include <bits/stdc++.h>
#include <filesystem>

#include "CPHeader.h"

using namespace std;
namespace fs = std::filesystem;

// END

// Golbal config - User config
string tenbaiCap = "BAI1";
int botestCap = 1;
map<char, pair<int, pair<int, int>>> cauhinhCap;
// END

// Generator functional
pair<int, int> taotestcauhinhCap(int maxlim, int minlim, int kichthuoc, vector<pair<int, int>> &testcase, bool themM) {
    if (maxlim < minlim) swap(maxlim, minlim);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> dist_n(1, kichthuoc);
    uniform_int_distribution<int> dist_val(minlim, maxlim);
    int cols = dist_n(rng);
    int ranN = -1010101;
    if (themM) {
        ranN = dist_n(rng);
    }

    for (int i = 0; i < cols; ++i) {
        testcase.push_back(make_pair(dist_n(rng), dist_n(rng)));
    }
    return make_pair(cols, ranN);
}

int sinhtestPAIR() {
    cout << u8"Tên bài là gì á bạn? (Mặc định là " << tenbaiCap << ") : ";
    cin >> tenbaiCap;

    cout << u8"Thầy đòi bạn bao nhiêu bộ test? (Mặc định là " << botestCap << ") : ";
    cin >> botestCap;

    int giatri;
    cout << u8"Trong bộ test bạn cần bao nhiêu giá trị? : ";
    cin >> giatri;

    cout << u8"Nhập tên của từng cặp, kích thước và giới hạn phần tử (Ví dụ 'A 10 1000 -1000') : ";
    for (int i = 0; i < giatri; ++i) {
        char name;
        int maxsize, maxlim = 0, minlim = 0;
        cin >> name >> maxsize >> maxlim >> minlim;
        cauhinhCap[name] = make_pair(maxsize, make_pair(maxlim, minlim));
    }

    bool themM;
    cout << "Bạn có muốn tạo thêm một giá trị M phụ không? (Nhập 'co' hoặc 'khong') : ";
    string ans;
    cin >> ans;
    if (ans == "khong") {
        themM = false;
    } else themM = true;

    cout << u8"Chờ chút nha, mình đang ráng..." << endl;

    fs::create_directory("BOTEST");

    for (int i = 1; i <= botestCap; ++i) {
        string tenthumuc = "BOTEST/TEST" + to_string(i);
        fs::create_directory(tenthumuc);

        string input_file_path = tenthumuc + "/" + tenbaiCap + ".INP";
        ofstream input_file(input_file_path);

        vector<pair<int, int>> kichthuocTest;
        vector<vector<pair<int, int>>> testDauVao;

        for (auto &gen : cauhinhCap) {
            vector<pair<int, int>> testcase;
            pair<int, int> kichthuoc_moi = taotestcauhinhCap(gen.second.second.first, gen.second.second.second, gen.second.first, testcase, themM);
            kichthuocTest.push_back(kichthuoc_moi);
            testDauVao.push_back(testcase);
        }

        for (auto &test : kichthuocTest) {
            if (!themM && test.second == -1010101) {
                input_file << test.first << " ";
            } else {
                input_file << test.first << " " << test.second << " ";
            }
        }

        input_file << endl;

        for (auto &test : testDauVao) {
            for (auto &pairtest : test) {
                input_file << pairtest.first << " " << pairtest.second;
                input_file << endl;
            }
        }

        string output_file_path = tenthumuc + "/" + tenbaiCap + ".OUT";
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
