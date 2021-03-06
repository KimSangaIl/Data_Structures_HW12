/*
 * hw12-sorting-hashing.c
 *
 *  Homework 12: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	printf("[----- [Kim Sangil] [2019038041] -----]\n");
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)
{
	int *temp = NULL;

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a;

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a)
{
	if(a != NULL)
		free(a);	//배열에 할당된 메모리를 해제
	return 0;
}

void printArray(int *a)
{
	if (a == NULL) {
		printf("nothing to print.\n");
		return;		//배열이 공백일 경우 오류 메시지 출력 후 함수 종료
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)	//배열의 모든 원소를 순서대로 출력
		printf("%5d ", a[i]);
	printf("\n");
}


int selectionSort(int *a)
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);	//배열 출력 함수 호출

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i;
		min = a[i];	//i+1번째 자리를 기준으로 정함
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)	//기준으로 정한 자리부터 나머지 원소들을 하나씩 비교
		{
			if (min > a[j])
			{
				min = a[j];
				minindex = j;	//i+1번째 원소를 기준으로 나머지 원소들중 가장 작은 원소를 탐색
			}
		}
		a[minindex] = a[i];
		a[i] = min;			//탐색한 가장 작은 원소와 자리를 바꿈
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);	//정렬 전후를 비교하기 위해 배열을 한 번더 출력
	return 0;
}

int insertionSort(int *a)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 1; i < MAX_ARRAY_SIZE; i++)	//두 번째 자리부터 마지막 자리까지 순서대로 기준으로 잡음
	{
		t = a[i];
		j = i;
		while (a[j-1] > t && j > 0)
		{
			a[j] = a[j-1];
			j--;		//앞쪽으로 한칸씩 이동하면서 기준으로 잡은 원소를 삽입할 위치를 탐색
		}
		a[j] = t;		//탐색한 위치에 원소를 삽입
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)
		{
			if (a[j-1] > a[j])	//인접한 두 원소의 크기를 비교해서 앞쪽 원소의 크기가 더 큰 경우
			{
				t = a[j-1];
				a[j-1] = a[j];
				a[j] = t;	//두 원소의 자리를 바꿈
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int shellSort(int *a)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)	//간격은 최대원소 개수의 절반으로 설정하고 반복할때마다 그 값을 반으로 줄임
	{
		for (i = 0; i < h; i++)
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)	//같은 간격으로 떨어져있는 원소들끼리 삽입 정렬
			{
				v = a[j];
				k = j;
				while (k > h-1 && a[k-h] > v)
				{
					a[k] = a[k-h];
					k -= h;		//같은 간격을 가진 원소들을 부분집합으로 묶었을때 그 안에서 앞쪽으로 이동하면서 기준이 되는 원소를 삽입할 위치 탐색
				}
				a[k] = v;		//탐색한 위치에 기준으로 잡은 원소를 삽입
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int quickSort(int *a, int n)
{
	int v, t;
	int i, j;

	if (n > 1)
	{
		v = a[n-1];	//정렬을 수행하는 리스트의 마지막 원소를 기준으로 설정
		i = -1;		//리스트의 왼쪽 끝
		j = n - 1;	//오른쪽 끝

		while(1)
		{
			while(a[++i] < v);	//왼쪽 끝에서 오른쪽으로 비교하면서 기준 원소보다 큰 원소를 탐색하면 반복 종료
			while(a[--j] > v);	//오른쪽 끝에서 왼쪽으로 비교하면서 기준 원소보다 작은 원소를 탐색하면 반복 종료

			if (i >= j) break;	//큰 값과 작은 값을 탐색하는 i와 j의 위치가 엇갈리면 반복 종료
			t = a[i];
			a[i] = a[j];
			a[j] = t;		//큰 값과 작은 값의 위치를 바꿈
		}
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t;			//i와 j가 엇갈린 위치에 기준으로 설정한 원소를 삽입

		quickSort(a, i);
		quickSort(a+i+1, n-i-1);	//원소를 삽입한 위치를 기준으로 왼쪽 리스트와 오른쪽 리스트에 각각 퀵정렬을 수행
	}


	return 0;
}

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;	//hash table 값들을 -1로 리셋

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];			//배열의 i+1번째 원소로 키값 초기화
		hashcode = hashCode(key);	//hashCode 함수를 호출하여 코드값 초기화
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1)
		{
			hashtable[hashcode] = key;	//hash table 값이 -1인 경우 키값으로 초기화
		} else 	{				//-1이 아닌 경우

			index = hashcode;

			while(hashtable[index] != -1)
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;	//-1이 될때까지 탐색
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key;		//탐색한 값을 키값으로 초기화
		}
	}

	return 0;
}

int search(int *ht, int key)
{
	int index = hashCode(key);	//hashCode 함수를 호출하여 인덱스값 초기화

	if(ht[index] == key)
		return index;		//hash table에서 키값을 찾으면 그 인덱스 값을 리턴

	while(ht[++index] != key)	//키값을 찾을때까지 반복
	{
		index = index % MAX_HASH_TABLE_SIZE;	//인덱스 값을 hash table 크기로 나눈 나머지로 초기화
	}
	return index;			//인덱스 값 리턴
}



