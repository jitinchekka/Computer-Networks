// Client side C/C++ program to demonstrate Socket
// programming
#include <iostream>
#include <vector>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080
using namespace std;

int main(int argc, char const *argv[])
{
	int sock = 0, valread, client_fd;
	struct sockaddr_in serv_addr;
	char *hello = "Hello from client";
	char buffer[1024] = {0};
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary
	// form
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
	{
		printf(
			"\nInvalid address/ Address not supported \n");
		return -1;
	}

	if ((client_fd = connect(sock, (struct sockaddr *)&serv_addr,
							 sizeof(serv_addr))) < 0)
	{
		printf("\nConnection Failed \n");
		return -1;
	}
	cout << "Testing connection...\n";
	printf("Connection Established\n");
	int n;
	cout << "Enter n\n";
	cin >> n;
	int data[n] = {0};
	for (int i = 0; i < n; i++)
	{
		recv(sock, data + i, sizeof(int), 0);
	}

	// GO back N
	cout << "Enter the window size N:\n";
	int N;
	cin >> N;
	cout << "Enter i such that every ith bit is missed\n";
	int fail;
	cin >> fail;
	// cout << "N = " << N << " fail = " << fail << endl;
	cout << "Sent data is:\n";
	for (int j = 0; j < N; j++)
	{
		cout << data[j] << " ";
	}

	int windowStart = 0, windowEnd = N - 1;
	int sent = N;
	int i = 0;
	bool flag = false;
	while (windowStart != windowEnd)
	{
		if ((i + 1) >= fail && (i + 1 - fail) % (fail - N) == 0)
		{
			for (int j = windowStart; j <= windowEnd; j++)
			{
				cout << data[j] << " ";
				sent++;
			}
			// if (windowStart < n - 1)
			// 	windowStart++;
			// if (windowEnd < n - 1)
			// 	windowEnd++;
			i++;
			flag = true;
		}
		else
		{
			if (flag == true)
			{
				flag = false;
			}
			else
			{
				i++;
			}

			// Acknowledgment received for data[windowStart]
			if (windowStart < n - 1)
				windowStart++;
			if (windowEnd < n - 1)
			{
				windowEnd++;
				cout << data[windowEnd] << " ";
				sent++;
			}
		}
	}
	cout << "\nTotal packets received = " << sent << endl;
	// closing the connected socket
	close(client_fd);
	return 0;
}