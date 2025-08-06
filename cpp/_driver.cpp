#include "_driver_pch.hpp"

// PCH BUILD CODE //
// g++-14 -std=c++23 -O2 -x c++-header _pch.hpp -o _pch.hpp.gch
// Run this every time _pch.hpp changes
// g++-14 -std=c++23 -O2 -x c++-header _driver_pch.hpp -o _driver_pch.hpp.gch
// Run this every time _driver_pch.hpp changes

extern char** environ;

static const int TIMEOUT_THRESHOLD = 5000; //in ms


int run_child_process(string sol, char* const argv[]) {
	string sol_path = "./"+sol;
	pid_t pid;
	//a way to modify the child process
	posix_spawn_file_actions_t fa;
	posix_spawn_file_actions_init(&fa);

	//make the child process look at _input.txt
	posix_spawn_file_actions_addopen(&fa, 0, "_input.txt", O_RDONLY, 0);

	//start the process
	int err = posix_spawnp(&pid, sol_path.c_str(), &fa, nullptr, argv, environ);
	posix_spawn_file_actions_destroy(&fa);
	if (err != 0) {
		cerr << "Process spawn failed. Error number: " << err << "\n";
		return -1;
	}
	
	//solution timer
	thread([pid]() {
		this_thread::sleep_for(chrono::milliseconds(TIMEOUT_THRESHOLD));
		kill(pid, SIGKILL);
	}).detach();
	
	int status;
	if (waitpid(pid, &status, 0) < 0) return -1;
	return WIFEXITED(status) ? WEXITSTATUS(status) : -1;
	return 0;
}

int main(int argc, char* const argv[]) {
	string sol = argv[1];
	char* const sol_argv[] = {argv[1], nullptr};
	
	//compile
	string cmd = string("g++-14 -std=c++23 -DLOCAL -O2 ") + sol + ".cpp -o " + sol;
	if (system(cmd.c_str()) != 0) {
		cerr << "Compile failed\n";
		return -1;
	}
	//run
	auto start = chrono::steady_clock::now();
	int err = run_child_process(sol, sol_argv);
	auto end = chrono::steady_clock::now();
	double time = chrono::duration<double, milli>(end - start).count();
	cout << "\nFinished in " << fixed << setprecision(2) << time << "ms\n";
	filesystem::remove(sol);
}