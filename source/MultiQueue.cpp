#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <fstream>
#include <stdlib.h>


using namespace std;


class Process {
	int pid; // ���̵�
	int arrive; // ���ʷ� �غ� ť ���� �ð�
	int service; // ���� ����ð�
	int endtime; // ����ð�
	int returntime; // ��ȯ�ð�

	// ���μ����� ó���ؾ��� ����? q�Ҵ� �ð� ���� ����̰���,
public:
	Process() {
		int pid = 0;
		int arrive = 0;
		int service = 0;
		int endtime = 0;
		int returntime = 0;
	}
	Process(int pid, int arrive, int service) {
		this->pid = pid;
		this->arrive = arrive;
		this->service = service;

		this->endtime = 0;
		this->returntime = 0;
	}
	bool calcProcess(int current, int q);
	void printEndProcess();

	
};

// ����ð� ����, q���� ���ؼ� ���� service, endtime, returntime�� �����Ѵ�.
// �׸��� ���� ������ �ľ�,
bool Process::calcProcess(int current, int q) {
	service -= q;
	endtime = current;
	returntime = current - arrive;
	
	if (service <= 0)
		return true;
	else
		return false;
}

// ����� ���μ����� ����ϴ� �Լ�
void Process::printEndProcess() {
	cout << pid << "||" << arrive << "||" << service << "||" << endtime << "||" << returntime << endl;
}


// �غ� ť, RR ���
class ReadyQueue {
	int q; // ����ð�

	Process currentProcess; // ���� �������� ���μ���
	queue<Process> readyProcess; // ���μ��� �������,

public:

	class ReadyQueue() {
		q = 1;
	}

	class ReadyQueue(int q) {
		this->q = q;
	}

	void insertProcess(Process pro); // ���μ����� �߰�
	Process dispatch(int current); // 

	int getQ();
	bool isEmpty();

};


// ���μ��� ���� �Լ�
void ReadyQueue::insertProcess(Process pro) {
	readyProcess.push(pro);
}

// ����ġ... ����, ���� �Լ�, ���� ��길 �����Ѵ�.
// RR�� �����غ���?
Process ReadyQueue::dispatch(int current) {

	if (readyProcess.empty()) {
		return;
	}

	Process curProcess = readyProcess.front();
	readyProcess.pop();

	// ��Ƽ ť ������, �̰� ��Ƽť �Ӽ����� �ΰ� ��Ƽť���� ó���ؾ߰ڴ�.
	current++;

	// ���μ����� ����Ǿ���.
	if (curProcess.calcProcess(current, q)) 
		curProcess.printEndProcess();
	else {
		// ���μ��� ��ȯ, ���� �켱���� ť�� ���� ����,
		return curProcess;
	}
}


int ReadyQueue::getQ() {
	return q;
}

// �ش� �غ�ť�� ����� �� Ȯ���ϴ� �Լ�,
// ť�� ����ٸ� true
bool ReadyQueue::isEmpty() {
	return readyProcess.empty();
}







// �غ� ť���� ������ �����ϴ� �ٴܰ� ť!
// �ٴܰ� ť�� ���ͷ� �����ؼ�, �� ť�� �����ϴ� �� ���ڴ�.
class MultiQueue {
	vector<ReadyQueue> multiQueue;
	int priority; // 0���� ������ ������ �ö󰣴�. �������� �켱������ ����.
	int current; // ����ð�


public:
	MultiQueue() {
		priority = 0;
		current = 0;
	}

	void init(int size);
	void getData();
	void insertReadyQueue(int q);
	void dispatch();

};

// ��ܰ� �غ� ť�� �������� ����,
void MultiQueue::init(int size) {
	for (int i = 0; i < size; i++) {
		insertReadyQueue(1);
	}

	if(!multiQueue.empty())
		getData();
}

// ù��° ť�� �޸����� �������� �ִ´�.
void MultiQueue::getData() {

	// input.txt ����� ���� ��
	FILE* input;

	int min_arrive = 0;
	int index = 0;

	int pid = 0;
	int arrive = 0;
	int service = 0;

	input = fopen("int.txt", "r");

	if (input == NULL) {
		cout << "input.txt�� ���� �� �����ϴ�. " << endl;
		exit(1);
	}

	// �޸��� �� �о��.
	// �̰͵� ��Ƽ ť���� �����ؼ� �������� ������ ����? �װ� �°ڴ�.. 
	while (!feof(input)) {
		fscanf(input, "%d,%d,%d \n", &pid, &arrive, &service);
		if (pid == 0)
			break;

		cout << pid << " " << arrive << " " << service << endl;

	
		multiQueue[0].insertProcess(Process(pid, arrive, service));
	}
}

void MultiQueue::insertReadyQueue(int q) {
	multiQueue.push_back(ReadyQueue(q));
	priority++;
}

void MultiQueue::dispatch() {
	
	init(5);

	// �ٴܰ� ť�� �����غ���. ������ �ƴ� �켱���� ť���� ������ ��, �ش� �۾����μ����� ����ȵǸ�, ���� �ٴܰ� ť�� �ִ´�. ��
	while (1) {

		for (int i = 0; i < multiQueue.size(); i++) {
			if (multiQueue[i].dispatch(current)) {

			}

		}
	}

}


int main(int argc, char *argv[]) {
	ReadyQueue ready;
	Process pro;

	ready.insertProcess(pro);

}