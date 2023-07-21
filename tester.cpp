#include <bits/stdc++.h>

using namespace std;
using sz_t = unsigned long long;

const int test = 100;

mt19937_64 rd(chrono::steady_clock::now().time_since_epoch().count());

template<typename T>
long long randint(T start, T end){
	assert(start <= end);
	return uniform_int_distribution<T>(start, end)(rd);
}

template<typename T>
T choice(vector<T> G){
	sz_t index = randint(0ULL, G.size() - 1);
	return G[index];
}

char choice(string G){
	sz_t index = randint((std::size_t) 0, G.size() - 1);
	return G[index];
}

template<typename T>
vector<T> choices(vector<T> G, sz_t k){
	vector<T> result(k);
	for(sz_t i = 0; i < k ; i++){
		result[i] = choice(G);
	}
	return result;
}

string choices(string G, sz_t k){
	string result;
	for(sz_t i = 0; i < k ; i++){
		result += choice(G);
	}
	return result;
}

template<typename T>
vector<T> genPrimeNum(T limit){
	vector<bool> sieve(limit + 1, true);
	sieve[0] = sieve[1] = false;
	for(T i = 2; i <= limit; i++){
		if(sieve[i]){
			for(T j = 2*i; j <= limit; j += i){
				sieve[j] = false;
			}
		}
	}

	vector<T> result;

	for(T i = 0; i <= limit; i++){
		if(sieve[i]) result.push_back(i);
	}

	return result;
}

template<typename T, typename H>
vector<pair<pair<T, T>, H>> genTree(T limit_nodes, H start, H end){
	vector<T> parents{1};
	vector<T> children;
	for(T i = 2; i <= limit_nodes; i++){
		children.push_back(i);
	}

	vector<pair<pair<T, T>, H>> result;

	while(!children.empty()){
		sz_t pos1 = randint(0, parents.size() - 1);
		sz_t pos2 = randint(0, children.size() - 1);
		H w = randint(start, end);
		result.push_back(make_pair(make_pair(parents[pos1], children[pos2]), w));
		parents.push_back(children[pos2]);
		children[pos2] = children.back();
		children.pop_back();
	}

	return result;
}

template<typename T, typename H>
vector<pair<pair<T, T>, H>> genGraph(T limit_nodes, T limit_edges, H start, H end){
	set<pair<pair<T, T>, H>> edges;
	while(edges.size() < limit_edges){
		T u = randint(1, limit_nodes);
		T v = randint(1, limit_nodes);
		H w = randint(start, end);
		if(u == v) continue;
		if(u > v) swap(u, v);
		edges.insert(make_pair(make_pair(u, v), w));
	}

	vector<pair<pair<T, T>, H>> result;
	for(auto it : edges){
		result.push_back(it);
	}

	shuffle(result.begin(), result.end(), rd);

	return result;
}

void makeTest(){
	ofstream inputfile;
	inputfile.open("input.inp", ios::out);
	// Make test here

	inputfile.close();
}

void makeTest(int test){
	ofstream inputfile;
	string name = "./tests/" + to_string(test) + ".inp";
	inputfile.open(name, ios::out);
	// Make test here

	inputfile.close();
}

bool compare(){
	ifstream outputfile;
	outputfile.open("output.out", ios::in);
	
	ifstream answerfile;
	answerfile.open("answer.out", ios::in);

	while(!outputfile.eof() && !answerfile.eof()){
		string x, y;
		outputfile >> x;
		answerfile >> y;

		if(x != y){
			cout << "Wrong answer at " << x << endl;
			cout << "Expected answer is " << y << endl;
			return false;
		}
	}

	outputfile.close();
	answerfile.close();

	return true;
}

void run(){
	for(int t = 1; t <= test; t++){
		makeTest();
		int status = system("*.exe");
		if(status != 0){
			cout << "Error! Exit code: " << status << endl;
			return;
		}
		system("checker.exe");
		if(!compare()){
			return;
		}else{
			cout << "Correct answer at test " << t << endl;
		}
	}

	cout << "Correct!" << endl;
}

int main(){
	// run();
	// makeTest();

	// string command;
	
	// #ifdef _WIN32
	// command = "del .\\tests";
	// #else
	// command = "rm -rf ./tests";
	// #endif

	// system(command.c_str());

	// int start = 1;
	// int end = 100;

	// for(int i = start; i <= end; i++){
	// 	makeTest(i);
	// }

	return 0;
}