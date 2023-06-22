#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>

#define DEFAULT_BUFLEN 512
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
const ll mod = 1e9 + 7;
const int oo = 1e6 + 7;

#define pb push_back
#define ep emplace_back
#define sz(a) (int) a.size()
#define ms(s, n) memset(s, n, sizeof(s))
#define present(t, x) (t.find(x) != t.end())
#define all(a) (a.begin(), a.end())
#define For(i, l, r) for (int i = l; i <= r; i++)
#define Fod(i, r, l) for (int i = r; i >= l; i--)
#define fillchar(a, x) memset(a, x, sizeof (a))
#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

void FileIO(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
}

using namespace std;

long long To_NUM(string a){
	long long res = 0;
	for (int i = 0; i < a.size(); ++i){
		res = res * 10 + a[i] - 48;
	}
	return res;
}

string to_STR(long long a){
	string res = "";
	while(a > 0){
		int i = a % 10;
		res = char(i + 48) + res;
		a /= 10;
	}
	return res;
}

int main(int argc, char **argv) 
{
    WSADATA wsaData;

    char recvbuf[DEFAULT_BUFLEN];
    int iResult;
    int recvbuflen = DEFAULT_BUFLEN;
    char connectedClient[256];
    
	/*****************************************************/
	/*    Khoi tao Winsock 2.2
	/*****************************************************/
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }
	cout<<"WSAStartup OK"<<endl;
	/*****************************************************/
	/*    Creating a Socket for the Server: ListenSocket */
	/*****************************************************/
    SOCKET sc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sc == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
	cout<<"ConnectSocket = socket OK"<<endl;
	/*****************************************************/
	/*    */
	/*****************************************************/
	//Xac dinh dinh danh ung dung dich (destination)
	int port=81;
	const char *IP="127.0.0.1";//"10.170.72.81"
	SOCKADDR_IN svrAddr;
	int svrAddrLen = sizeof(svrAddr);
	svrAddr.sin_family = AF_INET;
	svrAddr.sin_port = htons(port);
	svrAddr.sin_addr.s_addr = inet_addr(IP);

	if (connect(sc, (SOCKADDR*) &svrAddr, svrAddrLen) == SOCKET_ERROR) {
		printf ("\nCLIENT: Ket noi that bai\n");
		system("pause");
		WSACleanup();
		return 0;
	}else{
		printf("\nCLIENT: Ket noi thanh cong\n");
		printf("-----------------------------------------------------------------------\n");
	}
	//Gui nhan du lieu


	string myName;
	//Nhap ten
	// cout << "\nNhap ten cua ban: ";
	// getline(cin,myName);
	// send(sc, myName.c_str(), myName.size(), 0);

	// string a, b;
	// cout << "Chuong trinh nhap 2 so: \n";
	// cout << "Nhap so thu nhat: " << endl;
	// getline(cin, a);

	// cout << "Nhap so thu hai: " << endl;
	// getline(cin, b);
	// long long c = To_NUM(a) + To_NUM(b);
	// string d = to_STR(c);
	// send(sc, d.c_str(), d.size(), 0);
	
	
	// cout << "Chuong trinh thuc hien phep toan tren phan so" << endl;
	// // Phan so 1
	// cout << "Nhap phan so thu nhat:\n" << endl;
	// string data = "";
	// cout << "	Tu so: ";
	// string c; cin >> c;
	// data += c + " ";
	// cout << "	Mau so: ";
	// cin >> c;
	// data += c + " ";

	// // Phan so 2
	// cout << "Nhap phan so thu hai:\n" << endl;
	// cout << "	Tu so: "; cin >> c;
	// data += c + " ";
	// cout << "	Mau so: "; cin >> c;
	// data += c;


	// LOGIN STEP
	cout << "Login Step" << endl;
	string name, pass;
	getline(cin, name);
	getline(cin, pass);
	string data = name + " " + pass;
	send(sc, data.c_str(), data.size(), 0);

	recv(sc,connectedClient,256,0);
	cout << "\nNhan tu server: \n"<<connectedClient;

    // cleanup
    closesocket(sc);
    WSACleanup();
	getchar();
    return 0;
}

