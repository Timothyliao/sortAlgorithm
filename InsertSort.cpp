#include <stdio.h>
#include <malloc.h>

void Swop(int array[], int i, int j) {
	int temp = array[i];
	array[i] = array[j];
	array[j] = temp;
}

//希尔排序
void ShellSort(int array[], int length, int add) {
	int num = add;
	for (num; num > 0; num -= 2) {
		for (int i = 0; i < num; ++i) {
			for (int j = num + i; j < length; j += num) {
				int temp = array[j];
				int m = j;
				while (m >= num && array[m - num] > temp) {
					array[m] = array[m - num];
					m -= num;
				}
				array[m] = temp;
			}
		}
	}
}

//插入排序
void InsertionSort(int array[], int length) {
	for (int i = 1; i < length; i++)
	{
		int j = i;
		int temp = array[i];
		while (j > 0 && array[j - 1] > temp) {
			array[j] = array[j - 1];
			--j;
		}
		array[j] = temp;
	}
}

//折半插入排序
void BinaryInsertionSort(int array[], int length) {
	for (int i = 1; i < length; i++)
	{
		int low = 0, high = i - 1;
		int temp = array[i];
		while (high >= low) {
			int m = (high + low) / 2;
			if (temp < array[m])
				high = m - 1;
			else
				low = m + 1;
		}
		for (int j = i; j > high + 1; --j)
			array[j] = array[j - 1];
		array[high + 1] = temp;
	}
}

//冒泡排序
void BubbleSort(int array[], int length) {
	for (int i = length - 1; i >= 1; --i) {
		int flag = 0;
		for (int j = 1; j <= i; j++)
			if (array[j] < array[j - 1]) {
				Swop(array, j, j - 1);
				flag = 1;
			}
		if (flag == 0)
			break; //一趟冒泡排序没有发生交换说明整个序列是有序的
	}
}

//快速排序
void QuickSort(int array[], int low, int high) {
	int temp;
	int i = low, j = high;
	if (low < high) {
		temp = array[low];
		//一趟快速排序
		while (i < j) {
			while (i < j && array[j] >= temp) --j; //从右边开始扫描，找出第一个小于temp的值
			if (i < j) {
				array[i] = array[j];
				++i; //i向后移动一位
			}
			while (i < j && array[i] < temp) ++i; //从右边开始扫描，找出第一个大于temp的值，放到右边
			if (i < j) {
				array[j] = array[i];
				--j; //j向前移动一位
			}
		}

		array[i] = temp;
		QuickSort(array, low, i - 1);
		QuickSort(array, i + 1, high);
	}
}

//简单选择排序
void SimpleSelectSort(int array[], int length) {
	for (int i = 0; i < length; ++i) {
		int min = i; //默认第一个为无序序列的最小值
		for (int j = min + 1; j < length; ++j) {
			if (array[j] < array[min])
				min = j;
		}
		Swop(array, i, min);
	}
}

//堆排序
//对一个完全二叉树的某个节点进行调整，使之成为一个堆(递归)
void HeapifyByRecursion(int array[], int length, int i) {
	if (i >= length)
		return;

	int child1 = 2 * i + 1;
	int child2 = 2 * i + 2;
	int max = i;
	if (child1 < length && array[child1] > array[max])
		max = child1;
	if (child2 < length && array[child2] > array[max])
		max = child2;
	if (max != i) {
		Swop(array, i, max);
		HeapifyByRecursion(array, length, max);
	}
}

//建立一个堆(递归)
void BuildHeapByRecursion(int array[], int length) {
	int lastnode = length - 1;
	int parent = (lastnode - 1) / 2;
	for (int i = parent; i >= 0; --i) {
		HeapifyByRecursion(array, length, i);
	}
}

//运用递归的堆排序
void HeapSortByRecursion(int array[], int length) {
	for (int i = length - 1; i >= 0; --i)
	{
		BuildHeapByRecursion(array, i + 1);
		Swop(array, 0, i);
	}
}

void BuildHeap(int array[], int length, int i) {
	int temp = array[i];
	int j = i;
	while (j < length) {
		int c1 = 2 * i + 1;//左孩子
		int c2 = 2 * i + 2;//右孩子
		if (c1 < length && array[c1] > array[j])
			j = c1;
		if (c2 < length && array[c2] > array[j])
			j = c2;
		if (j != i) {
			Swop(array, j, i);
			i = j;
		}
		else
			break;
	}
	array[i] = temp;
}

void HeapSort(int array[], int length) {
	int parent = (length - 2) / 2;
	for (int i = parent; i >= 0; --i)
		BuildHeap(array, length, i);//逆序的heapify
	for (int j = length - 1; j > 0; --j) {
		Swop(array, j, 0);
		BuildHeap(array, j, 0);
	}
}

//归并排序
void Merge(int array[], int low, int high, int mid) {
	int tempArray[11] = { 0 };
	int f = low, r = mid + 1;
	int flag = 0;
	while (f <= mid && r <= high) {
		if (array[f] < array[r])
			tempArray[flag++] = array[f++];
		else if (array[f] >= array[r])
			tempArray[flag++] = array[r++];
	}

	//将剩下的元素填入数组
	while (f <= mid)
		tempArray[flag++] = array[f++];
	while (r <= high)
		tempArray[flag++] = array[r++];

	for (int j = low, m = 0; j <= high; j++, m++)
		array[j] = tempArray[m];

}
//low:开始下标  high:结束下标
void MergeSort(int array[], int low, int high) {
	if (low < high) {
		int mid = (low + high) / 2;
		MergeSort(array, low, mid);
		MergeSort(array, mid + 1, high);
		Merge(array, low, high, mid);
	}
}

//基数排序
void RadixSort(int array[], int length) {
	int bucket[11][11] = { 0 };//初始化桶子
	int poiner[11] = { 0 };//指针数组

	//循环每个位数上的值，先分类在收集
	for (int i = 0; i < 3; i++)
	{
		int num = 0, flag = 0;
		if (i == 0) num = 1;
		else if (i == 1) num = 10;
		else num = 100;
		//分类
		for (int m = 0; m < length; m++)
		{
			int s = (array[m] / num) % 10;
			bucket[poiner[s]++][s] = array[m];//poiner[s] 代表第s列的当前指针的位置
		}

		//收集  遍历所有的bucket
		for (int col = 0; col < 11; col++)
		{
			//说明这个bucket存放了元素，则从第0行开始收集
			if (poiner[col] != 0) {
				for (int row = 0; row < poiner[col]; row++) {
					array[flag++] = bucket[row][col];
					bucket[row][col] = 0;
				}
				poiner[col] = 0;//将指针置于初始位置
			}
		}
	}
}


int main(void) {
	int RadixArray[] = { 112, 503, 461, 284, 351, 620, 205, 316, 348, 289, 363 };
	int array[] = { 9,8,6,3,7,1,8,6,5,10,2 };
	//ShellSort(array, 11, 5);
	//InsertionSort(array, 11);
	//BinaryInsertionSort(array, 11);
	//BubbleSort(array, 11);
	//QuickSort(array, 0, 10);
	//SimpleSelectSort(array, 11);
	//HeapSortByRecursion(array, 11);
	//HeapSort(array, 11);
	//MergeSort(array, 0, 10);
	RadixSort(RadixArray, 11);


	for (int i = 0; i < 11; ++i)
		printf("%d ", RadixArray[i]);

	return 1;
}