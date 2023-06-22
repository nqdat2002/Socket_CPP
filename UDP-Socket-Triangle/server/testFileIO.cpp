#include <bits/stdc++.h>
using namespace std;

int main(){
	ofstream ofs("C:\\Users\\admin\\Desktop\\TPC-Socket\\server\\input.txt");
	if (!ofs){
		cout << "Error: File not Open";
		return 0;
	}
	ofs << "Hello";
	ofs.close();
}
