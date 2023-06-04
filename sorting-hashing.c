/*
 * sorting-hashing.c
 *
 *  Sorting & Hashing
 *  School of Computer Science at Chungbuk National University
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
	char command; // 사용자로부터 입력 받을 명령어 변수
	int *array = NULL; // 동적으로 할당된 배열에 대한 포인터, 초기값 NULL
	int *hashtable = NULL; // 동적으로 할당된 해시 테이블에 대한 포인터, 초기값 NULL
	int key = -1; // 해시 테이블에 저장할 키 변수, 초기값 -1
	int index = -1; // 배열 또는 해시 테이블에서의 인덱스 변수, 초기값 -1

    printf("[----- [이은총] [2022041043] -----]\n");

	srand(time(NULL)); // 현재 시간을 시드로 사용하여 난수 생성기 초기화

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

// 배열 초기화
int initialize(int** a)
{
	int *temp = NULL; // 임시 배열 포인터, 초기값 NULL

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE); // MAX_ARRAY_SIZE 크기의 int형 배열을 동적 할당
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a; // 포인터 변수 temp에 a가 가리키는 메모리주소 할당

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE; // 0부터 MAX_ARRAY_SIZE-1까지의 랜덤한 값을 배열 요소에 저장

	return 0;
}

// 동적으로 할당된 배열 메모리 해제
int freeArray(int *a)
{
	if(a != NULL)
		free(a); // a가 NULL이 아닌 경우 동적으로 할당된 배열 메모리 해제
	return 0;
}

// 배열 출력
void printArray(int *a)
{
	if (a == NULL) {
		printf("nothing to print.\n"); // 배열이 NULL인 경우 "nothing to print." 출력
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i); // 인덱스 레이블 출력
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]); // 배열 요소 출력
	printf("\n");
}

// 선택 정렬 알고리즘을 사용한 배열 정렬
int selectionSort(int *a)
{
	int min; // 최솟값 변수
	int minindex; // 최솟값의 인덱스 변수
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 정렬 이전 배열 출력

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i; // 현재 인덱스를 최솟값 인덱스로 초기화
		min = a[i]; // 현재 인덱스의 값을 최솟값으로 초기화
		for(j = i+1; j < MAX_ARRAY_SIZE; j++) // 현재 인덱스(i) 다음부터 배열 끝까지 반복하며 최솟값을 찾음
		{
			if (min > a[j]) // 현재 최솟값보다 작은 값을 찾을 경우
			{
				min = a[j]; // 최솟값 갱신
				minindex = j; // 최솟값의 인덱스 갱신
			}
		}
		// 현재 인덱스(i)의 값과 최솟값의 위치를 교환
		a[minindex] = a[i];
		a[i] = min;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); // 정렬 이후 배열 출력
	return 0;
}

// 삽입 정렬 알고리즘을 사용한 배열 정렬(오름차순)
int insertionSort(int *a)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 정렬 이전 배열 출력

	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		t = a[i]; // 현재 요소를 임시 변수 t에 저장
		j = i;
		// 현재 요소를 정렬된 부분의 적절한 위치에 삽입
		while (a[j-1] > t && j > 0)
		{
			a[j] = a[j-1]; // 현재 요소보다 큰 값들을 오른쪽으로 이동
			j--;
		}
		a[j] = t; // 현재 요소를 정렬된 위치에 삽입
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); // 정렬 이후 배열 출력

	return 0;
}

// 버블 정렬 알고리즘을 사용한 배열 정렬(오름차순)
int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 정렬 이전 배열 출력

	for(i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)
		{
			if (a[j-1] > a[j]) // 인접한 두 요소를 비교하여 순서를 바꿈(교환)
			{
				t = a[j-1]; // a[j-1]의 값을 t에 임시 저장
				a[j-1] = a[j]; // a[j]의 값을 a[j-1]에 대입하여 두 요소의 위치를 바꿈
				a[j] = t; // 임시로 저장해 둔 t의 값을 a[j]에 대입하여 요소 교환
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); // 정렬 이후 배열 출력

	return 0;
}

// 셸 정렬 알고리즘을 사용한 배열 정렬(오름차순)
int shellSort(int *a)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 정렬 이전 배열 출력

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)
	{
		for (i = 0; i < h; i++)
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)
			{
				v = a[j]; // 현재 요소를 임시 변수 v에 저장
				k = j; // 현재 요소의 인덱스 j의 값을 k에 할당
				while (k > h-1 && a[k-h] > v) // 이전 부분 배열에서 현재 요소보다 큰 값을 오른쪽으로 이동
				{
					a[k] = a[k-h]; // 현재 요소의 값을 이전 부분 배열에서 현재 요소보다 큰 값으로 덮음
					k -= h; // k를 이전 부분 배열의 요소로 이동
				}
				a[k] = v; // 현재 요소를 정렬된 위치에 삽입
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a); // 정렬 이후 배열 출력

	return 0;
}

// 퀵 정렬 알고리즘을 사용한 배열 정렬(오름차순)
int quickSort(int *a, int n)
{
	int v, t;
	int i, j;

	if (n > 1)
	{
		v = a[n-1]; // 피벗을 배열의 마지막 요소로 설정
		i = -1;
		j = n - 1; // 마지막 요소의 인덱스로 초기화

		while(1)
		{
			while(a[++i] < v); // 피벗보다 큰 값을 찾을 때까지 i를 증가
			while(a[--j] > v); // 피벗보다 작은 값을 찾을 때까지 j를 감소

			if (i >= j) break; // i와 j가 교차하면 반복문 종료
			t = a[i]; // 인덱스 i의 값을 t에 복사(임시적으로 값 보관)
			a[i] = a[j]; // i와 j의 값 교환
			a[j] = t;
		}
		t = a[i];
		a[i] = a[n-1]; // 인덱스 n-1의 요소의 값을 인덱스 i의 요소에 복사
		a[n-1] = t; // 임시변수 t에 저장된 값을 배열 a의 마지막 요소로 옮김

		quickSort(a, i); // 피벗을 기준으로 좌측 부분 배열 재귀적으로 정렬
		quickSort(a+i+1, n-i-1); // 피벗을 기준으로 우측 부분 배열 재귀적으로 정렬
	}


	return 0;
}

// 주어진 키를 해시 테이블의 인덱스로 변환
int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;
}

// 배열 요소를 해시 테이블에 해싱
int hashing(int *a, int **ht)
{
	int *hashtable = NULL; // 해시 테이블을 가리키는 포인터 변수

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) { // hashtable의 주소를 저장하는 이중 포인터 변수
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1; // hashtable의 모든 요소를 -1로 초기화

	int key = -1; // 배열 a의 각 요소를 저장하는 변수, 초기값 -1
	int hashcode = -1; // key 값을 해시 테이블의 인덱스로 변환하는 데 사용되는 변수
	int index = -1; // 충돌이 발생했을 때 선형 탐사 방식으로 다음 비어있는 위치를 찾아가는 데 사용되는 변수
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i]; // 배열 a의 i번째 요소 저장
		hashcode = hashCode(key); // key 값을 해시 코드로 변환

		if (hashtable[hashcode] == -1)
		{
			hashtable[hashcode] = key; // 해당 인덱스가 비어있는 경우 키를 저장
		} else 	{

			index = hashcode; // hashcode의 값을 인덱스로 사용하여 요소를 삽입할 위치 결정

			// 충돌이 발생한 경우 선형 탐사 방식으로 다음 비어있는 위치를 찾아서 키를 저장
			while(hashtable[index] != -1)
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;
			}
			hashtable[index] = key; // index에 현재 처리 중인 요소를 삽입(해시 테이블에 값 저장할 수 있게)
		}
	}

	return 0;
}

// 주어진 키를 사용하여 해시 테이블에서 값 검색
int search(int *ht, int key)
{
	int index = hashCode(key); // 주어진 키에 대한 해시 코드를 계산하여 인덱스로 사용

	if(ht[index] == key) // 해시 테이블의 해당 인덱스에 저장된 값이 주어진 키와 일치하는 경우
		return index;

	while(ht[++index] != key) // 일치하는 값이 나올 때까지 다음 인덱스로 이동
	{
		index = index % MAX_HASH_TABLE_SIZE; // 배열을 순환하도록 인덱스를 다시 초기화
	}
	return index; // 일치하는 값이 있는 인덱스 반환
}