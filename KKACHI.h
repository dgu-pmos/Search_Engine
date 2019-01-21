#define MAX_SIZE 1000

//단어의 정보를 가지는구조체
typedef struct wordLocation {
	int docuNumber;
	int index;
}wLocation;

//한 단어를 저장하는 구조체
typedef struct wordInformation {
	char word[100];//해당 문자로 시작되는 단어 저장
	int numbers;//총 등장횟수
	int numbersOFDocu[9];//문서별 등장횟수
	wLocation info[MAX_SIZE];
}wInfo;


//a-z구조체
typedef struct dictionary {
	char init;//첫 단어
	wInfo words[MAX_SIZE];//해당 문자로 시작되는 단어들의 정보
}dic;

typedef struct Char
{
	char name[30];//텍스트에서의 한 단어 원본
}Name;

char str[30]; // 문서들의 단어를 담을 배열 
Name docu[9][300]; // 문서의 단어들을 그대로 담는 배열(텍스트 내용 저장)

int totalIndexedWords = 0; //인덱스된 단어
int totaldocuments = 0; //총 문서의 개수
int totalCount = 0; //총 스트링 비교 연산 횟수
int totalWords = 0; //문서내에 존재하는 총 단어의 개수
dic dicInitWord[26]; //a-z구조체 배열
int frequency[10]; //문서마다 단어의 빈도수를 저장할 배열

void makeDic();//a-z구조체 initword초기화 함수
void ReadTxtWord(char Filename[], int docuNumber);//텍스트에서 단어 읽어오는 함수(읽고, 정보까지 넣는다)
void insertInfo(char *word, int docuNumber, int index); //단어 정보 입력함수
void frequencySort(int initWord, int wordLocation);//빈도수를 frequency 배열에 저장하는 함수
void printResults(int initWord, int wordLocation, char * userword);//결과를 출력하는 함수


void makeDic() {
	int i;
	for (i = 0; i < 26; i++) {
		dicInitWord[i].init = (char)('a'+i);
	}
}

void insertInfo(char *pureWord, int docuNumber, int index) {
	int i = 0;
	char  firstWord = pureWord[0]; //a-z구조체 선택하기위한 첫 단어

								   //단어가 존재하지 않을때 까지 반복
	while (dicInitWord[firstWord - 97].words[i].word[0] != '\0') {

		totalCount+=2;//if문 비교, while문 비교

		//단어가 중복될 경우(이미 존재) 인덱스만 추가
		if (!(strcmp(dicInitWord[firstWord - 97].words[i].word, pureWord))) {
			dicInitWord[firstWord - 97].words[i].info[dicInitWord[firstWord - 97].words[i].numbers].docuNumber = docuNumber;//문서정보추가
			dicInitWord[firstWord - 97].words[i].info[dicInitWord[firstWord - 97].words[i].numbers].index = index; //인덱스정보 추가
			(dicInitWord[firstWord - 97].words[i].numbers)++;//중복된 단어의 개수 증가
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
	totalCount++; // while문 빠져나올 때 한 번 더 비교

	//해당 단어가 아직 존재하지 않았을 경우 새로 추가
	strcpy(dicInitWord[firstWord - 97].words[i].word, pureWord);
	dicInitWord[firstWord - 97].words[i].info[0].docuNumber = docuNumber;
	dicInitWord[firstWord - 97].words[i].info[0].index = index;
	dicInitWord[firstWord - 97].words[i].numbers = 1;
	dicInitWord[firstWord - 97].words[i].numbersOFDocu[docuNumber - 1] = 1;
	totalIndexedWords++; // 총 색인된 단어
	totalWords++;
	
	printf("word :%s /", dicInitWord[firstWord - 97].words[i].word);
	printf("docuNumber :%d /", dicInitWord[firstWord - 97].words[i].info[0].docuNumber);
	printf("index :%d \n", dicInitWord[firstWord - 97].words[i].info[0].index);
	

}


void ReadTxtWord(char Filename[], int docuNumber) // 파일이름을 매개변수로 받아 해당 문서 단어들을 읽어 배열에 넣는 함수 
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

			totalCount+=2;//문자 2개 비교 , 한 문자 기준이면 +2
			if (str[k] >= 97 && str[k] <= 122) {//글자가 소문자면 다음 글자 탐색
				k++;
			}
			 else if (str[k] >= 65 && str[k] <= 90) {
				 totalCount +=2;
				str[k] = str[k] + 32; // 글자가 대문자면 소문자로 변경, 한 문자 기준이면 +2
				k++;
			}
			
			 //(!((str[k] >= 65 && str[k] <= 90) || (str[k] >= 97 && str[k] <= 122))) // 글자가 특수문자면 쉬프트해서 삭제
			else 
			{
				totalCount+=2;//대문자 판별 else if 문을 거치고 오므로(바로 위에)
				len = strlen(str);
				for (j = k; j<len - 1; j++)
				{
					str[j] = str[j + 1];
				}
				str[len - 1] = '\0';
			}
			
		}
		insertInfo(str, docuNumber, i); // 단어정제가 끝났으므로, 정보 삽입
		i++;
	}
	fclose(fp);
}

void frequencySort(int initWord, int wordLocation) {
	int i = 0;
	int j;
	int tmp;//큰 중복값 저장
	int max;//큰 중복값의 문자번호
	int arr[9];//단어의 빈도수를 임시저장할 배열
	int a;
	
	//나중 결과출력 함수 구현시, while문 종료플래그로 쓰기위해 하나 만듦
	//단어 횟수는 -가 될 수 없기 때문.
	frequency[9] = -1;

	//단어의 빈도수들을 복사
	for (a = 0; a < 9; a++) {
		arr[a] = dicInitWord[initWord].words[wordLocation].numbersOFDocu[a];
	}

	//중첩 while문, 맨 처음부터 시작하여 큰 값이 보이면, 그 값이 tmp가 되고
	//처음 부터 끝까지 그 값을 발견하여 최대값을 발견하고, frequency[i]에 저장
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

		//만약, 단어가 나온 횟수가 없다면 출력 할 필요가 없기 때문에,
		//문서 번호를 넣지 않고, 0 값을 넣어준다.
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
	int i = 0; // 인덱스 조절 (좌,우 4개 출력할 때)
	int j = 0; // 어떤 단어'apple'이라는 단어에 대한 정보 탐색할 때 쓰임(보유중인 index,docunumber쌍 탐색)
	int index; //문서에 위치한 인덱스

	//문서를 1~9번까지 모두 탐방
	while (frequency[max] != -1 ) {

		//빈도수가 0인 문서는 탐색하지않음
		totalCount++;
		if (frequency[max] == 0) {
			max++;
			continue;
		}

		printf("<Document%d.txt> %s : %d\n", frequency[max], userword, dicInitWord[initWord].words[wordLocation].numbersOFDocu[frequency[max]-1]);
		
		//우리가 찾는 단어에 대한 정보가 없을 때 까지 반복
		totalCount++;
		while (dicInitWord[initWord].words[wordLocation].info[j].docuNumber != 0) {
			//문서 번호와 구조체에 저장된 문서 번호와 같다면
			totalCount++;
			 if (frequency[max] == dicInitWord[initWord].words[wordLocation].info[j].docuNumber) {
				index = dicInitWord[initWord].words[wordLocation].info[j].index;
				printf("-> ");
				for (; i < 4 && index >= 1; i++) { //앞 4부분
					totalCount++;
					index--;
				}
				for (; i > 0; i--) { // 출력
					printf("%s ", docu[frequency[max] - 1][index].name);
					totalCount++;
					index++;
				}
				// 해당단어 포함 5단어 출력
				for (;  i < 5 && ((docu[frequency[max] - 1][index].name[0]) != '\0'); i++) {
					printf("%s ", docu[frequency[max] - 1][index].name);
					totalCount++;
					index++;
				}
				i = 0; // 다음 탐색위에 i=0으로 초기화
				printf("\n");
			}
			j++; // 다음 정보 탐색
		}
		j = 0; // 다음 탐색위에 j=0으로 초기화
		max++; // 다음 문서 탐색
	}
	printf("==========================================\n");
	printf("Total number of comparison : %d\n",totalCount);
}
