// CPP header

#include <bits/stdc++.h>
#include <filesystem>

#include "CPHeader.h"

using namespace std;
namespace fs = std::filesystem;

// END

// Golbal config - User config
string tenbaiChuoi = "BAI1";
char kiTuBatDau = 'a', kiTuKetThuc = 'z';
int botestChuoi = 1;
map<char, pair<int, int>> cauhinhChuoi;
// END

// Generator functional
void taotestCauHinhChuoi(int maxlen, int minlen, string &testcase) {
    if (maxlen < minlen) swap(maxlen, minlen);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> len_dist(minlen, maxlen);
    int length = len_dist(rng);
    if ((kiTuBatDau <= 'z' && kiTuKetThuc >= 'a') || (kiTuBatDau <= 'Z' && kiTuKetThuc >= 'A')) {
        uniform_int_distribution<char> char_dist(kiTuBatDau, kiTuKetThuc);
        for (int i = 0; i < length; ++i) {
            testcase += char_dist(rng);
        }
    } else {
        const string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        uniform_int_distribution<size_t> num_dist(0, charset.size() - 1);
        for (int i = 0; i < length; ++i) {
            testcase += charset[num_dist(rng)];
        }
    }

    testcase += "\n";
}

int sinhtestSTR() {
    cout << u8"Tên bài là gì á bạn? (Mặc định là " << tenbaiChuoi << ") : ";
    cin >> tenbaiChuoi;

    cout << u8"Thầy đòi bạn bao nhiêu bộ test? (Mặc định là " << botestChuoi << ") : ";
    cin >> botestChuoi;

    cout << u8"Cho ki tu bat dau va ki tu ket thuc? (Vi du 'a' den 'Z') : ";
    cin >> kiTuBatDau >> kiTuKetThuc;

    int giatri;
    cout << u8"Trong bộ test bạn cần bao nhiêu giá trị? : ";
    cin >> giatri;

    cout << u8"Nhập từng tên xâu và giới hạn của nó (Vi du 'S MAX MIN') : ";
    for (int i = 0; i < giatri; ++i) {
        char name;
        int maxlen = 0, minlen = 0;
        cin >> name >> maxlen >> minlen;
        cauhinhChuoi[name] = make_pair(maxlen, minlen);
    }

    bool inSoluong;
    cout << "Bạn có muốn in ra số lượng xâu ở đầu file input không? (Nhập 'co' hoặc 'khong') : ";
    string ans;
    cin >> ans;
    if (ans == "khong") {
        inSoluong = false;
    } else inSoluong = true;

    cout << u8"Chờ chút nha, mình đang ráng..." << endl;

    fs::create_directory("BOTEST");

    for (int i = 1; i <= botestChuoi; ++i) {
        string testcase = "";

        string tenthumuc = "BOTEST/TEST" + to_string(i);
        fs::create_directory(tenthumuc);

        string input_file_path = tenthumuc + "/" + tenbaiChuoi + ".INP";
        ofstream input_file(input_file_path);

        int cnt = 0;

        for (auto &gen : cauhinhChuoi) {
            taotestCauHinhChuoi(gen.second.first, gen.second.second, testcase);
            if (inSoluong == true) {
                cnt++;
            }
        }

        if (inSoluong == true) {
            input_file << cnt << endl;
        }
        input_file << testcase << endl;

        string output_file_path = tenthumuc + "/" + tenbaiChuoi + ".OUT";
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
