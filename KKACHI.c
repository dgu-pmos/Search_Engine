#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "KKACHI.h"
 
void main() {
	char filename[50]; // filename�� �����ϴ� �迭 
	char filetemp[10]; // filename�� �̸��� ��������� �����ִ� ��
	char userWord[100];
	int j = 0; //�Է¹��� �ܾ� �ҹ��ڷ� ��ȯ
	int i;//���� �Է� ����
	int k = 0;
	makeDic(); //a-z����ü ����
	for (i = 1; i <= 9; i++) // 1~4�� ���� �о �迭�� ��� 
	{
		strcpy(filename, "C:\\Users\\user\\Desktop\\document");
		_itoa(i, filetemp, 10);
		strcat(filetemp, ".txt");
		strcat(filename, filetemp);
		ReadTxtWord(filename, i);
	}
	printf("===============index result===============\n");
	printf("Total Number of Documents : %d\n", i-1);
	printf("Total Number of ExistTotalWords : %d\n", totalWords); //�����ϴ� �� �ܾ��, ��ǥ���� �־���
	printf("Total Number of Indexed Words : %d\n", totalIndexedWords);
	printf("Total number of comparison : %d\n", totalCount);
	printf("--------------------------------------\n");
	printf("�˻��� �ܾ �Է��ϼ��� : ");
	scanf_s("%s", userWord, sizeof(userWord));
	printf("===============execute result===============\n");
	//�������� �Է¹��� �ܾ� ��� �ҹ��ڷ� ��ȯ
	while (userWord[j] != '\0') {
		if (!(userWord[j] >= 97 && userWord[j] <= 122)) {
			userWord[j] += 32;
		}
		j++;
	}

	//ù ��° �ܾ� ����
	char firstWord = userWord[0];

	//ù ��° �ܾ 'a'���, a�� �����ϴ� �ܾ �������� ������ ���� �ݺ�
	while (dicInitWord[firstWord - 97].words[k].word[0] != '\0') {

		//����ڰ� �Է��� �ܾ��, ������ �����ϴ� �ܾ ���ٸ�
		if (!strcmp(userWord, dicInitWord[firstWord - 97].words[k].word)) {
			frequencySort(firstWord - 97, k); // �󵵼� ���� ������ ����
			printResults(firstWord - 97, k, userWord); // ��� ���
			return;
		}
		//����ڰ� �Է��� �ܾ�� ���� �ʴٸ�, ���� Ž��
		else
			k++;
	}
	printf("�Է��� �ܾ �������� �ʽ��ϴ�!!\n");
}
