// CPP header

#include <bits/stdc++.h>
#include <filesystem>

#include "CPHeader.h"

using namespace std;
namespace fs = std::filesystem;

// END

// Golbal config - User config
string tenbaiMang2D = "BAI1";
int botestMang2D = 1;
map<char, pair<int, pair<int, int>>> cauhinhMang2D;
// END

// Generator functional
pair<int, int> taotestCauHinhMang2D(int maxlim, int minlim, int kichthuoc, vector<vector<int>> &testcase, bool bangnhau) {
    if (maxlim < minlim) swap(maxlim, minlim);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> dist_n(1, kichthuoc);
    uniform_int_distribution<int> dist_val(minlim, maxlim);
    int rows = dist_n(rng);
    int cols = rows;
    if (!bangnhau) {
        cols = dist_n(rng);
    }

    testcase.resize(rows, vector<int>(cols));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            testcase[i][j] = dist_val(rng);
        }
    }
    return make_pair(rows, cols);
}

int sinhtestARRAY2D() {
    cout << u8"Tên bài là gì á bạn? (Mặc định là " << tenbaiMang2D << ") : ";
    cin >> tenbaiMang2D;

    cout << u8"Thầy đòi bạn bao nhiêu bộ test? (Mặc định là " << botestMang2D << ") : ";
    cin >> botestMang2D;

    int giatri;
    cout << u8"Trong bộ test bạn cần bao nhiêu giá trị? : ";
    cin >> giatri;

    cout << u8"Nhập tên của từng mảng, kích thước và giới hạn phần tử (Vi du 'A 10 1000 -1000') : ";
    for (int i = 0; i < giatri; ++i) {
        char name;
        int maxsize, maxlim = 0, minlim = 0;
        cin >> name >> maxsize >> maxlim >> minlim;
        cauhinhMang2D[name] = make_pair(maxsize, make_pair(maxlim, minlim));
    }

    bool bangNhau;
    cout << "Bạn có muốn mảng 2 chiều có cột và hàng bằng nhau không? (Nhập 'co' hoặc 'khong') : ";
    string ans;
    cin >> ans;
    if (ans == "khong") {
        bangNhau = false;
    } else bangNhau = true;

    cout << u8"Chờ chút nha, mình đang ráng..." << endl;

    fs::create_directory("BOTEST");

    for (int i = 1; i <= botestMang2D; ++i) {
        string tenthumuc = "BOTEST/TEST" + to_string(i);
        fs::create_directory(tenthumuc);

        string input_file_path = tenthumuc + "/" + tenbaiMang2D + ".INP";
        ofstream input_file(input_file_path);

        vector<pair<int, int>> kichthuocTest;
        vector<vector<vector<int>>> testDauVao;

        for (auto &gen : cauhinhMang2D) {
            vector<vector<int>> testcase;
            pair<int, int> kichthuoc_moi = taotestCauHinhMang2D(gen.second.second.first, gen.second.second.second, gen.second.first, testcase, bangNhau);
            kichthuocTest.push_back(kichthuoc_moi);
            testDauVao.push_back(testcase);
        }

        for (auto &test : kichthuocTest) {
            input_file << test.first << " " << test.second << " ";
        }

        input_file << endl;

        for (auto &test : testDauVao) {
            for (auto &row : test) {
                for (auto &val : row) {
                    input_file << val << " ";
                }
                input_file << endl;
            }
        }

        string output_file_path = tenthumuc + "/" + tenbaiMang2D + ".OUT";
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
