#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "KKACHI.h"
 
void main() {
	char filename[50]; // filename을 저장하는 배열 
	char filetemp[10]; // filename의 이름을 만들기위해 도와주는 배
	char userWord[100];
	int j = 0; //입력받은 단어 소문자로 변환
	int i;//파일 입력 개수
	int k = 0;
	makeDic(); //a-z구조체 생성
	for (i = 1; i <= 9; i++) // 1~4번 문서 읽어서 배열에 담는 
	{
		strcpy(filename, "C:\\Users\\user\\Desktop\\document");
		_itoa(i, filetemp, 10);
		strcat(filetemp, ".txt");
		strcat(filename, filetemp);
		ReadTxtWord(filename, i);
	}
	printf("===============index result===============\n");
	printf("Total Number of Documents : %d\n", i-1);
	printf("Total Number of ExistTotalWords : %d\n", totalWords); //존재하는 총 단어수, 발표위해 넣었음
	printf("Total Number of Indexed Words : %d\n", totalIndexedWords);
	printf("Total number of comparison : %d\n", totalCount);
	printf("--------------------------------------\n");
	printf("검색할 단어를 입력하세요 : ");
	scanf_s("%s", userWord, sizeof(userWord));
	printf("===============execute result===============\n");
	//유저한테 입력받은 단어 모두 소문자로 전환
	while (userWord[j] != '\0') {
		if (!(userWord[j] >= 97 && userWord[j] <= 122)) {
			userWord[j] += 32;
		}
		j++;
	}

	//첫 번째 단어 추출
	char firstWord = userWord[0];

	//첫 번째 단어가 'a'라면, a로 시작하는 단어가 존재하지 않을때 까지 반복
	while (dicInitWord[firstWord - 97].words[k].word[0] != '\0') {

		//사용자가 입력한 단어와, 사전에 존재하는 단어가 같다면
		if (!strcmp(userWord, dicInitWord[firstWord - 97].words[k].word)) {
			frequencySort(firstWord - 97, k); // 빈도수 높은 순으로 정렬
			printResults(firstWord - 97, k, userWord); // 결과 출력
			return;
		}
		//사용자가 입력한 단어와 같지 않다면, 다음 탐색
		else
			k++;
	}
	printf("입력한 단어가 존재하지 않습니다!!\n");
}
