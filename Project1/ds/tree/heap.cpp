#include <iostream>

using bit32 = int;
class Minheap {
private:
	bit32* data;
	int capacity;
	int size;

public:
	Minheap(int cap = 16) : capacity(cap), size(0) {
		data = new bit32[capacity];
	}			//构造函数
	~Minheap() { delete[] data; }
	// 最小堆入堆：先放到数组末尾，然后上浮
	void push(int val) {
		data[size] = val;
		heapifyUp(size);
		size++;
	}
	// 取走最小值：把末尾元素搬到根，size--，再下沉
	bit32 pop() {
		if (size == 0) return -1;
		bit32 small = data[0];
		data[0] = data[size - 1];
		size--;
		heapifyDown(0);
		return small;
	}
	// 返回堆顶（最小值），不删除
	bit32 top() {
		if (size == 0) return -1;
		return data[0];
	}

	// 判空：size == 0
	bool empty() {
		return size == 0;
	}
	// 返回当前元素个数
	int getsize() {
		return size;
	}
private:
	// 上浮：比父节点小就交换，直到满足「父 <= 子」
	void heapifyUp(int i) {			//下标i
		while (i > 0 && data[i] < data[(i-1)/2]) {		//最小最大判别
			std::swap(data[i], data[(i-1)/2]);
			i = (i - 1) / 2;
		}
	}		//上浮数，子节点小/大于父节点交换
	// 下沉（成员版）：与较小的孩子交换，直到满足堆性质
	void heapifyDown(int i) {
		while (2*i+1<size) {
			int left=2*i+1;
			int right = 2 * i + 2;
			int smaller = left;			//选择较小/大的孩子
			if (right<size && data[right] < data[left]) {	//最小最大判别
				smaller = right;
			}
			if (data[i] <= data[smaller]) break;
			std::swap(data[i], data[smaller]);
			i = smaller;
		}
	}		//下沉数，父节点大/小于子节点交换
};

// TopK：维护大小为 k 的最小堆，堆顶是 K 个里最小的，方便淘汰
void findTopk(int arr[],int n,int k) {	//数组，数组长度，k
	Minheap heap(k);
	for (int i = 0; i < n; i++) {
		if (heap.getsize() < k) {
			heap.push(arr[i]);
		}
		else if (arr[i] > heap.top()) {
			heap.pop();
			heap.push(arr[i]);
		}
	}
	for (int i = 0; i < k;i++) {
		std::cout << heap.pop() << " ";
	}
}				//查找前k个最小最大值
// 借助 MinHeap 排序：全部入堆再依次 pop（最小堆得到升序）
void heapSort(int arr[],int n) {
	Minheap heap(n);
	for (int i = 0; i < n; i++) {
		heap.push(arr[i]);
	}
	for (int i = 0; i < n; i++) {
		arr[i] = heap.pop();
	}
}
// 下沉（自由函数版）：传入数组和堆大小，供原地排序复用
void heapifyDown(int arr[],int i,int heapSize) {
	while (2 * i + 1 < heapSize) {
		int left = 2 * i + 1;
		int right = 2 * i + 2;
		int larger = left;			//选择较小/大的孩子
		if (right < heapSize && arr[right] > arr[left]) {	//最小最大判别
			larger = right;
		}
		if (arr[i] >= arr[larger]) break;
		std::swap(arr[i], arr[larger]);
		i = larger;
	}
}
// 原地建最大堆：从最后一个非叶子节点 n/2-1 往前依次下沉
void buildMaxHeap(int arr[],int n) { 
	for (int i = (n - 2) / 2; i >=0; i--) {
		heapifyDown(arr,i,n);
	}
}
// 原地堆排序：先建堆，再反复「堆顶换到末尾 + 对堆顶下沉」
void heapSortInPlace(int arr[],int n) {
	buildMaxHeap(arr,n);
	for (int end = n - 1; end > 0;end--) {
		std::swap(arr[0],arr[end]);
		heapifyDown(arr,0,end);
	}
}
int main() {
	/*Minheap h;
	h.push(30);
	h.push(80);
	h.push(20);
	h.push(100);
	h.push(50);

	while (!h.empty()) {
		std::cout << h.pop() << " ";
	}*/
	int arr[] = { 30, 80, 20, 100, 50, 70, 90 };
	heapSortInPlace(arr, 7);
	for (int i = 0; i < 7;i++) {
		std::cout << arr[i] << " ";
	}
	return 0;
}




