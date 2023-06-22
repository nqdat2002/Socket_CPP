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

#define SERVER "127.0.0.1"
#define BUFLEN 512 
#define PORT 8888 
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

int main(){
    WSADATA ws;
    printf("Initialising Winsock...");
    if (WSAStartup(MAKEWORD(2, 2), &ws) != 0)
    {
        printf("Failed. Error Code: %d", WSAGetLastError());
        return 1;
    }
    printf("Initialised.\n");

    sockaddr_in server;
    int client_socket;
    if ((client_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR) // <<< UDP socket
    {
        printf("socket() failed with error code: %d", WSAGetLastError());
        return 2;
    }

    memset((char*)&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.S_un.S_addr = inet_addr(SERVER);
    while (true)
    {
        char message[BUFLEN];
        printf("\tClient: ");
        cin.getline(message, BUFLEN);

        if (sendto(client_socket, message, strlen(message), 0, (sockaddr*)&server, sizeof(sockaddr_in)) == SOCKET_ERROR)
        {
            printf("sendto() failed with error code: %d", WSAGetLastError());
            return 3;
        }
        char answer[BUFLEN] = {};
        int slen = sizeof(sockaddr_in);
        int answer_length;
        if (answer_length = recvfrom(client_socket, answer, BUFLEN, 0, (sockaddr*)&server, &slen) == SOCKET_ERROR)
        {
            printf("recvfrom() failed with error code: %d", WSAGetLastError());
            exit(0);
        }

        cout << "\tServer: " << answer << "\n";
    }
    closesocket(client_socket);
    WSACleanup();
}

