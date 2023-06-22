#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <bits/stdc++.h>

#define DEFAULT_BUFLEN 512
#define SERVER "127.0.0.1"  // or "localhost" - ip address of UDP server
#define BUFLEN 512  // max length of answer
#define PORT 8888  // the port on which to listen for incoming data
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

using namespace std;

void FileIO(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
}

class triangle{
	private:
		ll a, b, c;
	public:
		triangle(){
			this->a = 0;
			this->b = 0;
			this->c = 0;
		}
		
		triangle(ll a, ll b, ll c){
			this->a = a;
			this->b = b;
			this->c = c;
		}
		
		bool isTriangle(){
			return (a > 0 && b > 0 && c > 0) && (a + b > c) && (a + c > b) && (b + c > a);
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
//		printf("%s\n", p);
		string tmp = "";
		for (int i = 0; i < strlen(p); ++i) tmp += char(p[i]);
		v.push_back(tmp);
		p = strtok(NULL, x);
	}
	return v;
}

int main()
{
    system("title UDP Server");

    sockaddr_in server, client;
    WSADATA wsa;
    printf("Initialising Winsock...");
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Failed. Error Code: %d", WSAGetLastError());
        exit(0);
    }
    printf("Initialised.\n");
    SOCKET server_socket;
    if ((server_socket = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
    {
        printf("Could not create socket: %d", WSAGetLastError());
    }
    printf("Socket created.\n");
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    if (bind(server_socket, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code: %d", WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    puts("Bind done.");
	printf("Waiting for data...\n");	
    while (true){
        fflush(stdout);
        char message[BUFLEN] = {};
        int message_len;
        int slen = sizeof(sockaddr_in);
        if (message_len = recvfrom(server_socket, message, BUFLEN, 0, (sockaddr*)&client, &slen) == SOCKET_ERROR){
            printf("recvfrom() failed with error code: %d", WSAGetLastError());
            exit(0);
        }
        printf("Received packet from %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
        printf("\tClient: %s\n", message);
        
//        send number
//        vector<long long> v = CharArrayToListNum(message);
//        string sum = to_string(v[0] + v[1]);
//        char *tmp = new char[sum.size()];
//        for (int i = 0; i < sum.size(); ++i){
//        	tmp[i] = char(sum[i]);
//		}
//		strcpy(message, tmp);
//		message[sum.size()] = '\0';
//		printf("\tServer: %s\n", message); 
		
//		printf("\tServer: "); 
//		cin.getline(message, BUFLEN);

		vector<long long> v = CharArrayToListNum(message);
		triangle tri = triangle(v[0], v[1], v[2]);
		string result = "The tuple you has pressed: (" + (to_string(v[0]) + ", ") + (to_string(v[1]) + ", ") + (to_string(v[2]) + ") ");
		if(tri.isTriangle()) result += "Valid Triangle!";
		else result += "Invalid Triangle!";
		char *tmp = new char[result.size()];
        for (int i = 0; i < result.size(); ++i){
        	tmp[i] = char(result[i]);
		}
		strcpy(message, tmp);
		message[result.size()] = '\0';
		printf("\tServer: %s\n", message); 
        if (sendto(server_socket, message, strlen(message), 0, (sockaddr*)&client, sizeof(sockaddr_in)) == SOCKET_ERROR)
        {
            printf("sendto() failed with error code: %d", WSAGetLastError());
            return 3;
        }
    }
    closesocket(server_socket);
    WSACleanup();
	return 0;
}
