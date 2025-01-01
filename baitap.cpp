#include<iostream>
#include<string>
using namespace std;

#define max 20

string canh[][3] = {
	{"0", "1", "D7"},  //HN-TN: D7
	{"0", "2", "D6"},  //HN-ST: D6
	{"0", "3", "D5"},  //HN-HB: D5
	{"0", "4", "D4"},  //HN-PL: D4
	{"0", "5", "D8"},  //HN-BN: D8
	{"5", "6", "D9"},  //BN-BG: D9
	{"6", "7", "D10"}, //BG-UB: D10
	{"7", "8", "D12"}, //UB-HP: D12
	{"8", "9", "D13"}, //HP-HD: D13
	{"9", "4", "D2"},  //HD-PL: D2
	{"9", "5", "D11"}, //HD-BN: D11
	{"4", "10", "D3"}  //PL-HY: D3

};

//Phan 1: Ma tran ke

void taoMatranke(string Matrix[max][max], string canh[][3], int socanh, int sodinh) {
	for (int i = 0; i < sodinh; ++i){
		for (int j = 0; j < socanh; ++j) {
			Matrix[i][j] = "0";
		}
	}
	for (int i = 0; i < socanh; ++i) {
		string u = canh[i][0];//dinh bat dau
		string v = canh[i][1];//dinh ket thuc
		string trongso = canh[i][2];//trongso cua canh

		int u_index = u[0] - '0';//lay chi so tu dinh bat dau
		int v_index = v[0] - '0';//lay chi so tu dinh ket thuc


		//do thi vo huong nen gan trong so 2 chieu
		Matrix[u_index][v_index] = trongso;
		Matrix[v_index][u_index] = trongso;
	}
}

// in ma tran ke
void displayMatrix(string matrix[max][max], int socanh) {
	cout << "\nDo thi duoi dang ma tran ke la: " << endl;
	for (int i = 0; i < socanh; ++i) {
		for (int j = 0; j < socanh; ++j) {
			cout  << matrix[i][j] << "\t";
		}
		cout << endl;
	}
}

//Phan 2: Danh sach ke
struct Node {
	string distance[max];
	Node* links[max];
	int degree;
	string name;

	Node() {
		degree = 0;
		for (int i = 0; i < max; ++i) {
			distance[i] = "D0";
			links[i] = NULL;
		}
	}
};

//nhap danh sach tu nguoi dung
void inputAdjList(Node nodes[max], int& sodinh) {
	cout << "Nhap so dinh: ";
	cin >> sodinh;
	cin.ignore();
	for (int i = 0; i < sodinh; ++i) {
		cout << "Vui long nhap ten dinh thu " << i + 1 << " : ";
		getline(cin, nodes[i].name);
		
		nodes[i].degree = 0;

	}
	
	for (int i = 0; i < sodinh; ++i) {
		cout << "So luong lien ket cua dinh " << nodes[i].name << ": ";
		cin >> nodes[i].degree;
		for (int j = 0; j < nodes[i].degree; ++j) {
			string linkedNode, trongso;
			cout << "Dinh lien ket " << j + 1 << " co trong so : ";
			getline(cin, linkedNode);
			getline(cin, trongso);

			//tim dia chi node lien ket
			Node* linkptr = NULL;
			for (int k = 0; k < sodinh; ++k) {
				if (nodes[k].name == linkedNode) {
					linkptr = &nodes[k];
					break;
				}
			}
			if (linkptr) {
				nodes[i].links[j] = linkptr;
				nodes[i].distance[j] = trongso;
			}
		}
	}
}

//ham in danh sach ke
void displayAdjList(Node nodes[max], int sodinh) {
	for (int i = 0; i < sodinh; ++i) {
		cout << nodes[i].name;
		for (int j = 0; j < nodes[i].degree; ++j) {
			cout << " -> " << nodes[i].links[j]->name << " : " << nodes[i].distance[j];
		}
		cout << endl;
	}
}

//Phan 3. Duyet do thi theo chieu sau

struct Stack {
	int top;
	int items[max];

	//khoi tao stack
	Stack() {
		top = -1;
	}

	//them phan tu vao ngan xep
	void push(int value) {
		if (top == max - 1) {
			return;
		}
		else {
			top++;
			items[top] = value;
		}
	}

	// lay phan tu ra khoi ngan xep
	int pop() {
		if (top == -1) {
			return -1;
		}
		else {
			int value = items[top];
			top--;
			return value;
		}
	}

	// kiem tra ngan xep rong
	bool isEmpty() {
		return (top == -1);
	}
};


void DFS(Node nodes[max], bool visited[max], int sodinh, int index) {
	visited[index] = true;
	cout << nodes[index].name << " ";

	for (int i = 0; i < nodes[index].degree; ++i) {
		int nextIndex = -1;
		for (int j = 0; j < sodinh; ++j) {
			if (nodes[j].name == nodes[index].links[i]->name) {
				nextIndex = j;
				break;
			}
		}
		if (!visited[nextIndex]) {
			DFS(nodes, visited, sodinh, nextIndex);
		}
	}
}

//Phan 4. Duyet do thi theo chieu rong


struct Queue {
	int front, rear;
	int items[max];

	Queue() {
		front = -1;
		rear = -1;
	}

	// them phan tu vao hang doi
	void enqueue(int value) {
		if (rear == max - 1) {
			return;
		}
		else {
			if (front == -1) front = 0;
			rear++;
			items[rear] = value;
		}
	}

	// lay phan tu tu hang doi
	int dequeue() {
		if (front == -1 || front > rear) {
			return -1;
		}
		else {
			int value = items[front];
			front++;
			return value;
		}
	}

	// kiem tra rong
	bool isEmpty() {
		return (front == -1 || front > rear);
	}
};

void BFS(Node nodes[max], bool visited[max], int sodinh, int startIndex) {
	Queue q;
	visited[startIndex] = true;
	q.enqueue(startIndex);

	while (!q.isEmpty()) {
		int current = q.dequeue();
		cout << nodes[current].name << " ";

		for (int i = 0; i < nodes[current].degree; ++i) {
			int nextIndex = -1;
			for (int j = 0; j < sodinh; ++j) {
				if (nodes[j].name == nodes[current].links[i]->name) {
					nextIndex = j;
					break;
				}
			}
			if (!visited[nextIndex]) {
				visited[nextIndex] = true;
				q.enqueue(nextIndex);
			}
		}
	}
}


//chuong trinh chinh
int main() {
	Node nodes[max];
	string Matrix[max][max];
	int sodinh = 11; // So dinh
	int socanh = sizeof(canh) / sizeof(canh[0]);

	// Tao va in ma tran ke
	taoMatranke(Matrix, canh, socanh, sodinh);
	displayMatrix(Matrix, sodinh);

	// Tao va in danh sach ke
	cout << "\nNhap danh sach ke:\n";
	inputAdjList(nodes, sodinh);
	cout << "\nDanh sach ke:\n";
	displayAdjList(nodes, sodinh);

	return 0;
}

