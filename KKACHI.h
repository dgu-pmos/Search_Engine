#define MAX_SIZE 1000

//�ܾ��� ������ �����±���ü
typedef struct wordLocation {
	int docuNumber;
	int index;
}wLocation;

//�� �ܾ �����ϴ� ����ü
typedef struct wordInformation {
	char word[100];//�ش� ���ڷ� ���۵Ǵ� �ܾ� ����
	int numbers;//�� ����Ƚ��
	int numbersOFDocu[9];//������ ����Ƚ��
	wLocation info[MAX_SIZE];
}wInfo;


//a-z����ü
typedef struct dictionary {
	char init;//ù �ܾ�
	wInfo words[MAX_SIZE];//�ش� ���ڷ� ���۵Ǵ� �ܾ���� ����
}dic;

typedef struct Char
{
	char name[30];//�ؽ�Ʈ������ �� �ܾ� ����
}Name;

char str[30]; // �������� �ܾ ���� �迭 
Name docu[9][300]; // ������ �ܾ���� �״�� ��� �迭(�ؽ�Ʈ ���� ����)

int totalIndexedWords = 0; //�ε����� �ܾ�
int totaldocuments = 0; //�� ������ ����
int totalCount = 0; //�� ��Ʈ�� �� ���� Ƚ��
int totalWords = 0; //�������� �����ϴ� �� �ܾ��� ����
dic dicInitWord[26]; //a-z����ü �迭
int frequency[10]; //�������� �ܾ��� �󵵼��� ������ �迭

void makeDic();//a-z����ü initword�ʱ�ȭ �Լ�
void ReadTxtWord(char Filename[], int docuNumber);//�ؽ�Ʈ���� �ܾ� �о���� �Լ�(�а�, �������� �ִ´�)
void insertInfo(char *word, int docuNumber, int index); //�ܾ� ���� �Է��Լ�
void frequencySort(int initWord, int wordLocation);//�󵵼��� frequency �迭�� �����ϴ� �Լ�
void printResults(int initWord, int wordLocation, char * userword);//����� ����ϴ� �Լ�


void makeDic() {
	int i;
	for (i = 0; i < 26; i++) {
		dicInitWord[i].init = (char)('a'+i);
	}
}

void insertInfo(char *pureWord, int docuNumber, int index) {
	int i = 0;
	char  firstWord = pureWord[0]; //a-z����ü �����ϱ����� ù �ܾ�

								   //�ܾ �������� ������ ���� �ݺ�
	while (dicInitWord[firstWord - 97].words[i].word[0] != '\0') {

		totalCount+=2;//if�� ��, while�� ��

		//�ܾ �ߺ��� ���(�̹� ����) �ε����� �߰�
		if (!(strcmp(dicInitWord[firstWord - 97].words[i].word, pureWord))) {
			dicInitWord[firstWord - 97].words[i].info[dicInitWord[firstWord - 97].words[i].numbers].docuNumber = docuNumber;//���������߰�
			dicInitWord[firstWord - 97].words[i].info[dicInitWord[firstWord - 97].words[i].numbers].index = index; //�ε������� �߰�
			(dicInitWord[firstWord - 97].words[i].numbers)++;//�ߺ��� �ܾ��� ���� ����
			(dicInitWord[firstWord - 97].words[i].numbersOFDocu[docuNumber - 1])++;
			
			printf("word :%s /", dicInitWord[firstWord - 97].words[i].word);
			printf("docuNumber :%d /", dicInitWord[firstWord - 97].words[i].info[dicInitWord[firstWord - 97].words[i].numbers - 1].docuNumber);
			printf("index :%d /", dicInitWord[firstWord - 97].words[i].info[dicInitWord[firstWord - 97].words[i].numbers - 1].index);
			printf("numbers :%d / ", dicInitWord[firstWord - 97].words[i].numbers);
			printf("numbersOfDocu :%d \n", dicInitWord[firstWord - 97].words[i].numbersOFDocu[docuNumber - 1]);
			totalWords++;
			
			return;
		}
		i++;
	}
	totalCount++; // while�� �������� �� �� �� �� ��

	//�ش� �ܾ ���� �������� �ʾ��� ��� ���� �߰�
	strcpy(dicInitWord[firstWord - 97].words[i].word, pureWord);
	dicInitWord[firstWord - 97].words[i].info[0].docuNumber = docuNumber;
	dicInitWord[firstWord - 97].words[i].info[0].index = index;
	dicInitWord[firstWord - 97].words[i].numbers = 1;
	dicInitWord[firstWord - 97].words[i].numbersOFDocu[docuNumber - 1] = 1;
	totalIndexedWords++; // �� ���ε� �ܾ�
	totalWords++;
	
	printf("word :%s /", dicInitWord[firstWord - 97].words[i].word);
	printf("docuNumber :%d /", dicInitWord[firstWord - 97].words[i].info[0].docuNumber);
	printf("index :%d \n", dicInitWord[firstWord - 97].words[i].info[0].index);
	

}


void ReadTxtWord(char Filename[], int docuNumber) // �����̸��� �Ű������� �޾� �ش� ���� �ܾ���� �о� �迭�� �ִ� �Լ� 
{
	int i=0;
	int j;
	int len;
	int length=0;

	FILE *fp = fopen(Filename, "r");

	if (fp == NULL)
	{
		printf("error!\n");
		fclose(fp);
		exit(1);
	}

	while (fscanf(fp, "%s", str) != EOF)
	{
		strcpy((docu[docuNumber-1][i]).name, str);
		int k = 0;
		
		while (k<strlen(str)) {

			totalCount+=2;//���� 2�� �� , �� ���� �����̸� +2
			if (str[k] >= 97 && str[k] <= 122) {//���ڰ� �ҹ��ڸ� ���� ���� Ž��
				k++;
			}
			 else if (str[k] >= 65 && str[k] <= 90) {
				 totalCount +=2;
				str[k] = str[k] + 32; // ���ڰ� �빮�ڸ� �ҹ��ڷ� ����, �� ���� �����̸� +2
				k++;
			}
			
			 //(!((str[k] >= 65 && str[k] <= 90) || (str[k] >= 97 && str[k] <= 122))) // ���ڰ� Ư�����ڸ� ����Ʈ�ؼ� ����
			else 
			{
				totalCount+=2;//�빮�� �Ǻ� else if ���� ��ġ�� ���Ƿ�(�ٷ� ����)
				len = strlen(str);
				for (j = k; j<len - 1; j++)
				{
					str[j] = str[j + 1];
				}
				str[len - 1] = '\0';
			}
			
		}
		insertInfo(str, docuNumber, i); // �ܾ������� �������Ƿ�, ���� ����
		i++;
	}
	fclose(fp);
}

void frequencySort(int initWord, int wordLocation) {
	int i = 0;
	int j;
	int tmp;//ū �ߺ��� ����
	int max;//ū �ߺ����� ���ڹ�ȣ
	int arr[9];//�ܾ��� �󵵼��� �ӽ������� �迭
	int a;
	
	//���� ������ �Լ� ������, while�� �����÷��׷� �������� �ϳ� ����
	//�ܾ� Ƚ���� -�� �� �� ���� ����.
	frequency[9] = -1;

	//�ܾ��� �󵵼����� ����
	for (a = 0; a < 9; a++) {
		arr[a] = dicInitWord[initWord].words[wordLocation].numbersOFDocu[a];
	}

	//��ø while��, �� ó������ �����Ͽ� ū ���� ���̸�, �� ���� tmp�� �ǰ�
	//ó�� ���� ������ �� ���� �߰��Ͽ� �ִ밪�� �߰��ϰ�, frequency[i]�� ����
	while (i < 9) {
		j = 0;
		tmp = 0;
		totalCount++;
		while (j < 9) {
			if (tmp <= arr[j]) {
				tmp = arr[j];
				max = j + 1;
				totalCount++;
				j++;
				continue;
			}
			j++;
		}
		arr[max-1] = -1;
		frequency[i] = max;

		//����, �ܾ ���� Ƚ���� ���ٸ� ��� �� �ʿ䰡 ���� ������,
		//���� ��ȣ�� ���� �ʰ�, 0 ���� �־��ش�.
		totalCount++;
		if (dicInitWord[initWord].words[wordLocation].numbersOFDocu[max-1] == 0) {
			frequency[i] = 0;
		}
		i++;
	}
}

void printResults(int initWord, int wordLocation, char * userword) {
	int totalCount = 0;
	int max = 0;
	int i = 0; // �ε��� ���� (��,�� 4�� ����� ��)
	int j = 0; // � �ܾ�'apple'�̶�� �ܾ ���� ���� Ž���� �� ����(�������� index,docunumber�� Ž��)
	int index; //������ ��ġ�� �ε���

	//������ 1~9������ ��� Ž��
	while (frequency[max] != -1 ) {

		//�󵵼��� 0�� ������ Ž����������
		totalCount++;
		if (frequency[max] == 0) {
			max++;
			continue;
		}

		printf("<Document%d.txt> %s : %d\n", frequency[max], userword, dicInitWord[initWord].words[wordLocation].numbersOFDocu[frequency[max]-1]);
		
		//�츮�� ã�� �ܾ ���� ������ ���� �� ���� �ݺ�
		totalCount++;
		while (dicInitWord[initWord].words[wordLocation].info[j].docuNumber != 0) {
			//���� ��ȣ�� ����ü�� ����� ���� ��ȣ�� ���ٸ�
			totalCount++;
			 if (frequency[max] == dicInitWord[initWord].words[wordLocation].info[j].docuNumber) {
				index = dicInitWord[initWord].words[wordLocation].info[j].index;
				printf("-> ");
				for (; i < 4 && index >= 1; i++) { //�� 4�κ�
					totalCount++;
					index--;
				}
				for (; i > 0; i--) { // ���
					printf("%s ", docu[frequency[max] - 1][index].name);
					totalCount++;
					index++;
				}
				// �ش�ܾ� ���� 5�ܾ� ���
				for (;  i < 5 && ((docu[frequency[max] - 1][index].name[0]) != '\0'); i++) {
					printf("%s ", docu[frequency[max] - 1][index].name);
					totalCount++;
					index++;
				}
				i = 0; // ���� Ž������ i=0���� �ʱ�ȭ
				printf("\n");
			}
			j++; // ���� ���� Ž��
		}
		j = 0; // ���� Ž������ j=0���� �ʱ�ȭ
		max++; // ���� ���� Ž��
	}
	printf("==========================================\n");
	printf("Total number of comparison : %d\n",totalCount);
}
