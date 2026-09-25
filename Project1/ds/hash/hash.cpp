#include <iostream>
#include <string>


class hash {
private:
	struct hashnode {
		std::string key;
		int value;
		hashnode* next;
	};
	hashnode** buckets; //数组
	int capacity;	//容量(桶数组有多少个格子)
	int size;	//大小(现在存了多少条数据)
public:
	hash(int cap = 8) :capacity(cap), size(0) {
		buckets = new hashnode*[capacity];
		for (int i = 0; i < capacity; i++) {
			buckets[i] = nullptr;
		}
	}			//初始化
	~hash() {
		for (int i = 0; i < capacity;i++) {
			hashnode* cur = buckets[i];
			while (cur) {
				hashnode* next = cur->next;
				delete cur;
				cur = next;
			}
		}
		delete[] buckets;
	}
	hash(const hash&) = delete;
	hash& operator=(const hash&) = delete;
	int getSize() const { return size; }
	int getCapacity() const { return capacity; }
	int hashFunc(const std::string& key) {
		int asciisum = 0;
		for (char t:key) {
			asciisum += t; //累加key中每个字符的ascii值
		}				//hash = hash * 31 + t;   
				//31 是质数，打散效果更好,"ab"与"ba"能算出不同
		return asciisum % capacity;		//返回根据容量的hash值
	}
	void insert(const std::string& key,int value) {
		hashnode* node = findnode(key);
		if (node) {
			node->value = value;
			return;
		}
		int pos = hashFunc(key);
		// 空桶(node为nullptr)和非空桶(如果没找到)走同一个逻辑
		hashnode* newnode = new hashnode{key,value,buckets[pos]};
		buckets[pos] = newnode;
		size++;
		if ((float)size / capacity > 0.7) {
			rehash();
		}
	}
	void rehash() {
		int oldcap = capacity;//保留旧容量
		hashnode** oldbuckets = buckets;//保留旧桶数组
		capacity *= 2;	//更新扩大capacity
		buckets = new hashnode * [capacity];
		for (int i = 0; i < capacity; i++) buckets[i] = nullptr;
		//初始化新数组，防止野指针
		for (int i = 0; i < oldcap; i++) {
			hashnode* cur = oldbuckets[i];	//遍历指针
			while (cur) {
				hashnode* next = cur->next;		//记录原先cur->next
				int newpos = hashFunc(cur->key);	//找到新位置
				cur->next = buckets[newpos];	//头插法
				buckets[newpos] = cur;		//头插法
				cur = next;			//cur=cur->next
			}
		}
		delete[] oldbuckets;	//释放旧数组
	}
	int find(const std::string&key) {
		hashnode* node = findnode(key);
		return node ? node->value : -1;
	}
	hashnode* findnode(const std::string&key) {
		int pos = hashFunc(key);
		hashnode* cur = buckets[pos];
		while (cur) {
			if (cur->key == key) {
				return cur;
			}
			cur = cur->next;
		}
		return nullptr;
	}
	void remove(const std::string& key) {
		int pos = hashFunc(key);
		hashnode* cur = buckets[pos];
		hashnode* prev = nullptr;
		while (cur) {
			if (cur->key == key) {
				if (prev) {
					prev->next = cur->next;
				}
				else {
					buckets[pos] = cur->next; //第一个节点
				}
				delete cur;
				size--;
				return;
			}
			prev = cur;			//记录上一个节点
			cur = cur->next;	
		}
	}
};

int main() {
	hash h;
	for (int i = 0; i < 10; i++) {
		std::string key = "key" + std::to_string(i);
		h.insert(key, i);
		std::cout << "size: " << h.getSize() << " cap: " << h.getCapacity() << std::endl;
	}
	std::cout << h.find("key7") << std::endl;
	std::cout << h.find("key10") << std::endl;

	h.insert("key7", 77);
	std::cout << h.find("key7") << std::endl;

	h.remove("key0");
	h.remove("key5");
	std::cout << h.find("key0") << std::endl;
	std::cout << h.find("key5") << std::endl;


	return 0;
}