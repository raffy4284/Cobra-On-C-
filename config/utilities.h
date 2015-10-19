#ifndef UTILITIES_H
#define UTILITIES_H
#include <string.h>

string* ParseRequest(string request){
	int spaces_seen = 0;
	string request[2];
	int index = -1;
	for (int i = 0; request[i] != '\0' || spaces_seen < 2; i++){
		index++;
		if (spaces_seen == 0)
			request[1][index] = request[i];
		else if (spaces_seen == 1)
			request[0][index] = request[i];
		else if (spaces_seen == 0 && request[i] == ' '){
			request[1][index] = '\0';
			spaces_seen ++;
			index = -1;
		}
		else if (spaces_seen == 1 && request[i] == ' '){
			request[0][index] = '\0';
			spaces_seen ++;
			index = -1;
		}
	}
	return request;

}
#endif