#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <bits/stdc++.h>

#define DEFAULT_BUFLEN 512
#define SERVER "127.0.0.1"  // or "localhost" - ip address of UDP server
//#define SERVER "10.21.128.155"
#define BUFLEN 1024  // max length of answer
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

int To_NUM(string a){
	int res = 0;
	for (int i = 0; i < a.size(); ++i){
		res = res * 10 + a[i] - '0';
	}
	return res;
}

class Student{
	private:
		string id;
		string name;
		int age;
	public:
		Student(){
			this->id = "";
			this->name = "";
			this->age = 0;
		}
		
		Student(string id, string name, int age){
			this->id = id;
			this->name = name;
			this->age = age;
		}
		
		string getName(){
			return name;
		}
		
		int getAge(){
			return age;
		}
		
		string getId(){
			return id;
		}
		
		void setName(string named){
			name = named;
		}
		
		void setAge(int aged){
			age = aged;
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
    system("UDP - Student!!!");
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
        printf("Client sended: \n%s\n", message);
        
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
		
		
		// Readfile
		ifstream ifs;
		ifs.open("data.txt");
		vector<string> list;
		if(ifs.is_open()){
			string line = "";
			while(getline(ifs, line)){
				list.push_back(line);
			}
		}
		ifs.close();
		vector<Student> stu;
		for(int i = 0; i < list.size(); ++i){
			stringstream ss(list[i]);
			string token;
			vector<string> infor;
			while(ss >> token){
				infor.push_back(token);
			}
			string name = "";
			for(int j = 1; j < infor.size() - 1; ++j){
				name += infor[j] + " ";
			}
			name.pop_back();
			string id = infor[0];
			int age = To_NUM(infor[infor.size() - 1]);
			stu.push_back(Student(id, name, age));
		}
		map<string, int> mp;
		mp.clear();
		for(Student st: stu) mp[st.getId()] ++;
		vector<string> line = CharArrayToListString(message);
		// option id name age
		string option = line[0];
		string id = line[1];
		if(mp[id] == 0){
			string result = "Not Exist this Id of Student!!!";
			cout << result << endl;
			char *tmp = new char[result.size()];
	        for (int i = 0; i < result.size(); ++i){
	        	tmp[i] = char(result[i]);
			}
			strcpy(message, tmp);
			message[result.size()] = '\0';
			printf("Server: \n%s\n", message); 
	        if (sendto(server_socket, message, strlen(message), 0, (sockaddr*)&client, sizeof(sockaddr_in)) == SOCKET_ERROR)
	        {
	            printf("sendto() failed with error code: %d", WSAGetLastError());
	            return 3;
	        }
			continue;
		}
		if(option == "1"){
			string name = "";
			for(int i = 2; i < line.size(); ++i) name += line[i] + " ";
			name.pop_back();
			for(Student &st: stu){
				if(st.getId() == id){
					st.setName(name);
					break;
				}
			}
		}
		else if(option == "2"){
			string age = line[2];
			for(Student &st: stu){
				if(st.getId() == id){
					st.setAge(To_NUM(age));
					break;
				}
			}
		}
		else if(option == "3"){
			string name = "";
			for(int i = 2; i < line.size() - 1; ++i) name += line[i] + " ";
			name.pop_back();
			string age = line[line.size() - 1];
			for(Student &st: stu){
				if(st.getId() == id){
					st.setName(name);
					st.setAge(To_NUM(age));
					break;
				}
			}
		}
//		for(Student &st: stu){
//			cout << st.getId() + " " + st.getName() + " " + to_string(st.getAge()) + "\n";
//		}
		
		ofstream of;
		of.open("data.txt");
		string result = "";
		for(Student st: stu){
			result += st.getId() + " " + st.getName() + " " + to_string(st.getAge()) + "\n";
		}
		of << result; // string
		result = "Updated Successfully. New List Student: \n" + result;
		char *tmp = new char[result.size()];
        for (int i = 0; i < result.size(); ++i){
        	tmp[i] = char(result[i]);
		}
		strcpy(message, tmp);
		message[result.size()] = '\0';
		printf("Server: \n%s\n", message); 
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
