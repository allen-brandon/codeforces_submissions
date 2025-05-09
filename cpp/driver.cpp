#include <chrono>
#include <future>
#include <filesystem>
#include <iostream>
#include <cstdlib>
using namespace std;
namespace fs = filesystem;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: driver <solution_basename>\n";
        return 1;
    }

    string name = argv[1];
    string src = name + ".cpp";
    string exe = name;
    string input = "_input.txt";
    int timeout = 5;

    if (system(("g++-14 -std=c++17 -O2 " + src + " -o " + exe).c_str()) != 0) {
        cerr << "✖ Compile failed\n";
        return 2;
    }

    auto start = chrono::steady_clock::now();
    auto fut = async(launch::async, [&]() {
        return system(("gtimeout " + to_string(timeout) + "s ./" + exe + " < " + input).c_str());
    });

    if (fut.wait_for(chrono::seconds(timeout+1)) == future_status::timeout) {
        cerr << "✖ Timed out after " << timeout << "s\n";
        fs::remove(exe);
        return 3;
    }

    double elapsed = chrono::duration<double, milli>(chrono::steady_clock::now() - start).count();
    cout << "\n" << "Finished in " << fixed << setprecision(2) << elapsed << " ms\n";
    fs::remove(exe);
    return fut.get();
}