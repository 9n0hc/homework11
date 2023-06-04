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

/* �ʿ信 ���� �Լ� �߰� ���� */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function���� ���� */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a���� �� hash table�� �����. */
int hashing(int *a, int **ht);

/* hash table���� key�� ã�� hash table�� index return */
int search(int *ht, int key);


int main()
{
	char command; // ����ڷκ��� �Է� ���� ��ɾ� ����
	int *array = NULL; // �������� �Ҵ�� �迭�� ���� ������, �ʱⰪ NULL
	int *hashtable = NULL; // �������� �Ҵ�� �ؽ� ���̺� ���� ������, �ʱⰪ NULL
	int key = -1; // �ؽ� ���̺� ������ Ű ����, �ʱⰪ -1
	int index = -1; // �迭 �Ǵ� �ؽ� ���̺����� �ε��� ����, �ʱⰪ -1

    printf("[----- [������] [2022041043] -----]\n");

	srand(time(NULL)); // ���� �ð��� �õ�� ����Ͽ� ���� ������ �ʱ�ȭ

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

// �迭 �ʱ�ȭ
int initialize(int** a)
{
	int *temp = NULL; // �ӽ� �迭 ������, �ʱⰪ NULL

	/* array�� NULL�� ��� �޸� �Ҵ� */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE); // MAX_ARRAY_SIZE ũ���� int�� �迭�� ���� �Ҵ�
		*a = temp;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
	} else
		temp = *a; // ������ ���� temp�� a�� ����Ű�� �޸��ּ� �Ҵ�

	/* �������� �迭�� ������ ���� */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE; // 0���� MAX_ARRAY_SIZE-1������ ������ ���� �迭 ��ҿ� ����

	return 0;
}

// �������� �Ҵ�� �迭 �޸� ����
int freeArray(int *a)
{
	if(a != NULL)
		free(a); // a�� NULL�� �ƴ� ��� �������� �Ҵ�� �迭 �޸� ����
	return 0;
}

// �迭 ���
void printArray(int *a)
{
	if (a == NULL) {
		printf("nothing to print.\n"); // �迭�� NULL�� ��� "nothing to print." ���
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i); // �ε��� ���̺� ���
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]); // �迭 ��� ���
	printf("\n");
}

// ���� ���� �˰����� ����� �迭 ����
int selectionSort(int *a)
{
	int min; // �ּڰ� ����
	int minindex; // �ּڰ��� �ε��� ����
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // ���� ���� �迭 ���

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i; // ���� �ε����� �ּڰ� �ε����� �ʱ�ȭ
		min = a[i]; // ���� �ε����� ���� �ּڰ����� �ʱ�ȭ
		for(j = i+1; j < MAX_ARRAY_SIZE; j++) // ���� �ε���(i) �������� �迭 ������ �ݺ��ϸ� �ּڰ��� ã��
		{
			if (min > a[j]) // ���� �ּڰ����� ���� ���� ã�� ���
			{
				min = a[j]; // �ּڰ� ����
				minindex = j; // �ּڰ��� �ε��� ����
			}
		}
		// ���� �ε���(i)�� ���� �ּڰ��� ��ġ�� ��ȯ
		a[minindex] = a[i];
		a[i] = min;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); // ���� ���� �迭 ���
	return 0;
}

// ���� ���� �˰����� ����� �迭 ����(��������)
int insertionSort(int *a)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // ���� ���� �迭 ���

	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		t = a[i]; // ���� ��Ҹ� �ӽ� ���� t�� ����
		j = i;
		// ���� ��Ҹ� ���ĵ� �κ��� ������ ��ġ�� ����
		while (a[j-1] > t && j > 0)
		{
			a[j] = a[j-1]; // ���� ��Һ��� ū ������ ���������� �̵�
			j--;
		}
		a[j] = t; // ���� ��Ҹ� ���ĵ� ��ġ�� ����
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); // ���� ���� �迭 ���

	return 0;
}

// ���� ���� �˰����� ����� �迭 ����(��������)
int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // ���� ���� �迭 ���

	for(i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)
		{
			if (a[j-1] > a[j]) // ������ �� ��Ҹ� ���Ͽ� ������ �ٲ�(��ȯ)
			{
				t = a[j-1]; // a[j-1]�� ���� t�� �ӽ� ����
				a[j-1] = a[j]; // a[j]�� ���� a[j-1]�� �����Ͽ� �� ����� ��ġ�� �ٲ�
				a[j] = t; // �ӽ÷� ������ �� t�� ���� a[j]�� �����Ͽ� ��� ��ȯ
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); // ���� ���� �迭 ���

	return 0;
}

// �� ���� �˰����� ����� �迭 ����(��������)
int shellSort(int *a)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // ���� ���� �迭 ���

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)
	{
		for (i = 0; i < h; i++)
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)
			{
				v = a[j]; // ���� ��Ҹ� �ӽ� ���� v�� ����
				k = j; // ���� ����� �ε��� j�� ���� k�� �Ҵ�
				while (k > h-1 && a[k-h] > v) // ���� �κ� �迭���� ���� ��Һ��� ū ���� ���������� �̵�
				{
					a[k] = a[k-h]; // ���� ����� ���� ���� �κ� �迭���� ���� ��Һ��� ū ������ ����
					k -= h; // k�� ���� �κ� �迭�� ��ҷ� �̵�
				}
				a[k] = v; // ���� ��Ҹ� ���ĵ� ��ġ�� ����
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a); // ���� ���� �迭 ���

	return 0;
}

// �� ���� �˰����� ����� �迭 ����(��������)
int quickSort(int *a, int n)
{
	int v, t;
	int i, j;

	if (n > 1)
	{
		v = a[n-1]; // �ǹ��� �迭�� ������ ��ҷ� ����
		i = -1;
		j = n - 1; // ������ ����� �ε����� �ʱ�ȭ

		while(1)
		{
			while(a[++i] < v); // �ǹ����� ū ���� ã�� ������ i�� ����
			while(a[--j] > v); // �ǹ����� ���� ���� ã�� ������ j�� ����

			if (i >= j) break; // i�� j�� �����ϸ� �ݺ��� ����
			t = a[i]; // �ε��� i�� ���� t�� ����(�ӽ������� �� ����)
			a[i] = a[j]; // i�� j�� �� ��ȯ
			a[j] = t;
		}
		t = a[i];
		a[i] = a[n-1]; // �ε��� n-1�� ����� ���� �ε��� i�� ��ҿ� ����
		a[n-1] = t; // �ӽú��� t�� ����� ���� �迭 a�� ������ ��ҷ� �ű�

		quickSort(a, i); // �ǹ��� �������� ���� �κ� �迭 ��������� ����
		quickSort(a+i+1, n-i-1); // �ǹ��� �������� ���� �κ� �迭 ��������� ����
	}


	return 0;
}

// �־��� Ű�� �ؽ� ���̺��� �ε����� ��ȯ
int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;
}

// �迭 ��Ҹ� �ؽ� ���̺� �ؽ�
int hashing(int *a, int **ht)
{
	int *hashtable = NULL; // �ؽ� ���̺��� ����Ű�� ������ ����

	/* hash table�� NULL�� ��� �޸� �Ҵ� */
	if(*ht == NULL) { // hashtable�� �ּҸ� �����ϴ� ���� ������ ����
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
	} else {
		hashtable = *ht;	/* hash table�� NULL�� �ƴѰ��, table ��Ȱ��, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1; // hashtable�� ��� ��Ҹ� -1�� �ʱ�ȭ

	int key = -1; // �迭 a�� �� ��Ҹ� �����ϴ� ����, �ʱⰪ -1
	int hashcode = -1; // key ���� �ؽ� ���̺��� �ε����� ��ȯ�ϴ� �� ���Ǵ� ����
	int index = -1; // �浹�� �߻����� �� ���� Ž�� ������� ���� ����ִ� ��ġ�� ã�ư��� �� ���Ǵ� ����
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i]; // �迭 a�� i��° ��� ����
		hashcode = hashCode(key); // key ���� �ؽ� �ڵ�� ��ȯ

		if (hashtable[hashcode] == -1)
		{
			hashtable[hashcode] = key; // �ش� �ε����� ����ִ� ��� Ű�� ����
		} else 	{

			index = hashcode; // hashcode�� ���� �ε����� ����Ͽ� ��Ҹ� ������ ��ġ ����

			// �浹�� �߻��� ��� ���� Ž�� ������� ���� ����ִ� ��ġ�� ã�Ƽ� Ű�� ����
			while(hashtable[index] != -1)
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;
			}
			hashtable[index] = key; // index�� ���� ó�� ���� ��Ҹ� ����(�ؽ� ���̺� �� ������ �� �ְ�)
		}
	}

	return 0;
}

// �־��� Ű�� ����Ͽ� �ؽ� ���̺��� �� �˻�
int search(int *ht, int key)
{
	int index = hashCode(key); // �־��� Ű�� ���� �ؽ� �ڵ带 ����Ͽ� �ε����� ���

	if(ht[index] == key) // �ؽ� ���̺��� �ش� �ε����� ����� ���� �־��� Ű�� ��ġ�ϴ� ���
		return index;

	while(ht[++index] != key) // ��ġ�ϴ� ���� ���� ������ ���� �ε����� �̵�
	{
		index = index % MAX_HASH_TABLE_SIZE; // �迭�� ��ȯ�ϵ��� �ε����� �ٽ� �ʱ�ȭ
	}
	return index; // ��ġ�ϴ� ���� �ִ� �ε��� ��ȯ
}