#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <bits/stdc++.h>

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

class triangle{
	private: 
		ll a, b, c;

	public:
		triangle(ll a, ll b, ll c){
			this->a = a;
			this->b = b;
			this->c = c;
		}
		
		bool isValid(){
			return (a > 0 && b > 0 && c > 0) && (a + b > c && a + c > b && b + c > a);
		}
};

class Phanso {
	private:
		ll tu, mau;
	public:
		Phanso(){
			this->tu = 0;
			this->mau = 1;
		}
		
		Phanso(ll tu, ll mau) {
			this->tu = tu;
			this->mau = mau;
//			this->chuanhoa();
		}
	
		void rutgon() {
			long long x = __gcd(tu, mau);
			tu /= x;
			mau /= x;
		}
		
		void chuanhoa(){
			if((this->tu > 0 && this->mau > 0) || (this->tu < 0 && this->mau > 0))
				return;
			if((this->tu > 0 && this->mau < 0) || (this->tu < 0 && this->mau < 0)){
				this->tu *= -1;
				this->mau *= -1;
			}
		}
	
		friend Phanso operator + (Phanso a, Phanso b) {
			Phanso tong(1, 1);
			long long mauchung = a.mau * b.mau / __gcd(a.mau, b.mau);
			tong.tu = mauchung / a.mau * a.tu + mauchung / b.mau * b.tu;
			tong.mau = mauchung;
			tong.rutgon();
//			tong.chuanhoa();
			return tong;
		}
	
		friend Phanso operator - (Phanso a, Phanso b) {
			Phanso hieu(1, 1);
			long long mauchung = a.mau * b.mau / __gcd(a.mau, b.mau);
			hieu.tu = mauchung / a.mau * a.tu - mauchung / b.mau * b.tu;
			hieu.mau = mauchung;
			hieu.rutgon();
//			hieu.chuanhoa();
			return hieu;
		}
	
		friend Phanso operator * (Phanso a, Phanso b) {
			Phanso tich(1, 1);
			tich.tu = a.tu * b.tu;
			tich.mau = a.mau * b.mau;
			tich.rutgon();
//			tich.chuanhoa();
			return tich;
		}
	
		friend Phanso operator / (Phanso a, Phanso b) {
			Phanso thuong(1, 1);
			thuong.tu = a.tu * b.mau;
			thuong.mau = a.mau * b.tu;
			thuong.rutgon();
//			thuong.chuanhoa();
			return thuong;
		}
		
		string to_str(){
			return to_string(this->tu) + "/" + to_string(this->mau)+ "\n";
		}
		
		friend ostream& operator << (ostream&, Phanso);
		friend istream& operator >> (istream&, Phanso&);
};
class Student{
	private:
		string id, name, date;
		double point;
	public:
		Student(){
			this->id = this->name = this->date = "";
			this->point = 0;
		}
		
		Student(string id, string name, string date, double point){
			this->id = id;
			this->name = name;
			this->date = date;
			this->point = point;
		}
};

class User{
	private:
		string id, password;
	public:
		User(string id, string password){
			this->id = id;
			this->password = password;
		}
		
		string getId(){
			return this->id;
		}
		
		string getPassword(){
			return this->password;
		}
		
		bool isCorrect(string pass){
			return this->password == pass;
		}
};
vector<ll> CharArrayToListNum(char a[]){
	char * q = new char[strlen(a)];
	strcpy(q, a);
	char x[2] = " ";
	char *p = strtok(q, x);
	vector<ll> v;
	while(p != NULL){
//		printf("%s\n", p);
		long long num = (ll) (atoi(p));
		p = strtok(NULL, x);
		v.push_back(num);
	}
	return v;
}

vector<string> CharArrayToListString(char a[]){
	char * q = new char[strlen(a)];
	strcpy(q, a);
	char x[2] = " ";
	char *p = strtok(q, x);
	vector<string> v;
	while(p != NULL){
		printf("%s\n", p);
		string tmp = "";
		for (int i = 0; i < strlen(p); ++i) tmp += char(p[i]);
		v.push_back(tmp);
		p = strtok(NULL, x);
	}
	return v;
}

int main() {
	ifstream ifs("C:\\Users\\admin\\Documents\\C++\\Socket_CPP\\TCP-Socket\\server\\input.txt", ios::in);
	if(!ifs.is_open()){
		cout << "Could not open the File - " << "..\\input.txt" << endl;
		return EXIT_FAILURE;
	}
	string named, passed, line;
	vector<string> lines;
	vector<User> listUser;
	while(getline(ifs, line)){
		lines.push_back(line);
	}
	ifs.close();
	for (int i = 0; i < lines.size(); i += 2){
		listUser.push_back(User(lines[i], lines[i + 1]));
	}
	cout<<"Gui loi chao";
    int iResult=0;
    
/*****************************************************/
/*    Khoi tao Winsock 2.2
/*****************************************************/
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
    	cout << "\nWINSOCK: Khoi tao that bai\n";
    	WSACleanup();
    	return 0;
	}	else	{
		cout << "\nWINSOCK: Khoi tao thanh cong\n";
	}
/*****************************************************/
/*    Creating a Socket for the Server: ListenSocket */
/*****************************************************/
	SOCKET ListenSocket = INVALID_SOCKET;
	// Create a SOCKET for the server to listen for client connections
	ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ListenSocket == INVALID_SOCKET) {
	    printf("Error at socket(): %ld\n", WSAGetLastError());
	    WSACleanup();
	    return 1;
	}
/*****************************************************/
/*    Binding a Socket*/
/*****************************************************/
	//Xac dinh dinh danh ung dung 
    u_short port = 81;
    const char *IP = "127.0.0.1";
    SOCKADDR_IN svrAddr;
	int svrAddrLen = sizeof(svrAddr);
	svrAddr.sin_family = AF_INET;
	svrAddr.sin_port = htons(port);
	svrAddr.sin_addr.s_addr = inet_addr(IP);
    // Setup the TCP listening socket
    iResult = bind( ListenSocket, (SOCKADDR*) &svrAddr, svrAddrLen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }
    cout<<"ListenSocket: "<<ListenSocket<<endl;
    
/*****************************************************/
/*    Listening on a Socket*/
/*****************************************************/
	
	if ( listen(ListenSocket, 5 ) == SOCKET_ERROR ) {
	    printf( "Listen failed with error: %ld\n", WSAGetLastError() );
	    closesocket(ListenSocket);
	    WSACleanup();
	    return 1;
	}
    cout<<"Listening ... "<<endl;
	do{
		/************************************************/
		/*    Accepting a Connection*/
		/************************************************/

		// Accept a client socket
		SOCKADDR_IN cliAddr;
		int cliAddrLen = sizeof(cliAddr);
		SOCKET sa = accept(ListenSocket, (SOCKADDR*) &cliAddr, &cliAddrLen);
		cout<<"Nhan du lieu tu IP:"<< inet_ntoa(cliAddr.sin_addr) << " port: "<< ntohs(cliAddr.sin_port)<<endl;

		if (sa == INVALID_SOCKET) {
				printf("accept failed: %d\n", WSAGetLastError());
				closesocket(sa);
				WSACleanup();
				return 1;
		}
		/************************************************/
		/*    Receiving and Sending Data on the Server*/
		/************************************************/
		
		
		char recvbuf[DEFAULT_BUFLEN];
		int iSendResult;
		int recvbuflen = DEFAULT_BUFLEN;
	    iResult = recv(sa, recvbuf, recvbuflen, 0);
    	

	    if (iResult > 0) {
	        recvbuf[iResult] = '\0';
			// Fraction
//			vector<long long> list = CharArrayToListNum(recvbuf);
//			for(auto x: list){
//				cout << x << endl;
//			}
//			cout << "Du lieu nhap vao: " << endl;
//			Phanso a(list[0], list[1]);
//			Phanso b(list[2], list[3]);
//			cout << "Phan so thu nhat: " << a.to_str() << endl;
//			cout << "Phan so thu hai: " << b.to_str() << endl;
//			Phanso tong = a + b;
//			Phanso hieu = a - b;
//			Phanso tich = a * b;
//			Phanso thuong = a / b;
//			string sendingdata = "Tong hai phan so la: " + tong.to_str() + ""
//								+ "Hieu hai phan so la: " + hieu.to_str() + ""
//								+ "Tich hai phan so la: " + tich.to_str() + ""
//								+ "Thuong hai phan so la: " + thuong.to_str() + "";
//			cout << sendingdata << endl;

			vector<string> list = CharArrayToListString(recvbuf);
			string name = list[0], pass = list[1];
			bool ok = false;
			for (User us: listUser){
				if(us.getId() == name){
					ok = true;
					if(us.isCorrect(pass)){
						cout << "Logged in Successfully" << endl;
					}
					else{
						cout << "Password is not Correct!!" << endl;
					}
					break;
				}
			}
			if (!ok){
				cout << "Invalid Id" << endl;
			}
	        cout << "Bytes received: "<< iResult << endl;
			string sendingdata = name + " " + pass;
	        iSendResult = send(sa, sendingdata.c_str(), sendingdata.length(), 0);
	        if (iSendResult == SOCKET_ERROR) {
	            printf("send failed: %d\n", WSAGetLastError());
	            closesocket(sa);
	            WSACleanup();
	            return 1;
	        }
	        cout<<"Bytes sent: "<< sendingdata.length()<<endl;
	    }		

		iResult = shutdown(sa, SD_SEND);
		if (iResult == SOCKET_ERROR) {
			printf("shutdown failed: %d\n", WSAGetLastError());
			closesocket(sa);
			WSACleanup();
			return 1;
		}
		// cleanup
		closesocket(sa);
	}while(1);
		
	closesocket(ListenSocket);
	WSACleanup();
	getchar();
	return 0;
}//main
