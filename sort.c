#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

void heapify(int arr[], int n, int root) {
	//this function is used for heapifying the array into a max heap
    //multiply by 2 as each subtree has two children
	int rightchild = 2 * root + 2;
	int leftchild = 2 * root + 1;
	int highestvalue = root;
	//set the highest value as the root of the tree
    if ((rightchild < n) && (arr[rightchild] > arr[highestvalue]))
        highestvalue = rightchild;
		//checks if the rightchild child is larger than the root element
		//and if it is, then set the root to that element
    if ((leftchild < n) && (arr[leftchild] > arr[highestvalue]))
    	highestvalue = leftchild;
		//same thing, but this time, we're checking the leftchild element
    if (highestvalue != root) {
		//checks if the root is the highest value
		int temp = arr[root];
		arr[root] = arr[highestvalue];
		arr[highestvalue] = temp;
		//keep on swapping and heapifying the elements 
		//until the root is the highest value
        heapify(arr, n, highestvalue);
    }
}
 
void heapSort(int arr[], int n) {
    for (int i = (n / 2) - 1; i >= 0; i--)
        heapify(arr, n, i);
		//making the max heap for sorting
    for (int i = n - 1; i > 0; i--) {
		int temp = arr[0];
		arr[0] = arr[i];
		arr[i] = temp;
		//swap the elements
        heapify(arr, i, 0);
		//heapify again after swapping
    }
}

//taken from the last lab assignment
void mergeSort(int pData[], int l, int r) {

    if (l < r) {
        int m = l + (r - l) / 2;
        // sort left and right halves
        mergeSort(pData, l, m);
        mergeSort(pData, m + 1, r);
        // merge sorted halves
        int n1 = m - l + 1;
        int n2 = r - m;
        int *L = (int *)malloc(n1 * sizeof(int));
        int *R = (int *)malloc(n2 * sizeof(int));
        extraMemoryAllocated += n1 * sizeof(int) + n2 * sizeof(int);
		//count the extra memory allocated
        for (int i = 0; i < n1; i++)
            L[i] = pData[l + i];
        for (int j = 0; j < n2; j++)
            R[j] = pData[m + 1 + j];
        int i = 0;
        int j = 0;
        int k = l;
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                pData[k] = L[i];
                i++;
            }
            else {
                pData[k] = R[j];
                j++;
            }
            k++;
        }
        while (i < n1) {
            pData[k] = L[i];
            i++;
            k++;
        }
        while (j < n2) {
            pData[k] = R[j];
            j++;
            k++;
        }
        free(L);
        free(R);
    }
}


// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	int i, n, *data;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i=0;i<dataSz;++i)
		{
			fscanf(inFile, "%d ",&n);
			data = *ppData + i;
			*data = n;
		}

		fclose(inFile);
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = { "input1.txt", "input2.txt", "input3.txt", "input4.txt" };
	
	for (i=0;i<4;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		printf("Heap Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		heapSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}