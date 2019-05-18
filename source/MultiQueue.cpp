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
	int pid; // 아이디
	int arrive; // 최초로 준비 큐 입장 시간
	int service; // 남은 실행시간
	int endtime; // 종료시간
	int returntime; // 반환시간

	// 프로세스가 처리해야할 일은? q할당 시간 마다 계산이겠지,
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

// 현재시간 값과, q값을 통해서 남은 service, endtime, returntime을 갱신한다.
// 그리고 종료 시점도 파악,
bool Process::calcProcess(int current, int q) {
	service -= q;
	endtime = current;
	returntime = current - arrive;
	
	if (service <= 0)
		return true;
	else
		return false;
}

// 종료된 프로세스를 출력하는 함수
void Process::printEndProcess() {
	cout << pid << "||" << arrive << "||" << service << "||" << endtime << "||" << returntime << endl;
}


// 준비 큐, RR 방식
class ReadyQueue {
	int q; // 실행시간

	Process currentProcess; // 현재 실행중인 프로세스
	queue<Process> readyProcess; // 프로세스 저장공간,

public:

	class ReadyQueue() {
		q = 1;
	}

	class ReadyQueue(int q) {
		this->q = q;
	}

	void insertProcess(Process pro); // 프로세스를 추가
	Process dispatch(int current); // 

	int getQ();
	bool isEmpty();

};


// 프로세스 삽입 함수
void ReadyQueue::insertProcess(Process pro) {
	readyProcess.push(pro);
}

// 디스패치... 수행, 연산 함수, 정말 계산만 수행한다.
// RR을 구현해볼까?
Process ReadyQueue::dispatch(int current) {

	if (readyProcess.empty()) {
		return;
	}

	Process curProcess = readyProcess.front();
	readyProcess.pop();

	// 멀티 큐 구현시, 이건 멀티큐 속성으로 두고 멀티큐에서 처리해야겠다.
	current++;

	// 프로세스가 종료되었다.
	if (curProcess.calcProcess(current, q)) 
		curProcess.printEndProcess();
	else {
		// 프로세스 반환, 다음 우선순위 큐에 넣을 예정,
		return curProcess;
	}
}


int ReadyQueue::getQ() {
	return q;
}

// 해당 준비큐가 비었는 지 확인하는 함수,
// 큐가 비었다면 true
bool ReadyQueue::isEmpty() {
	return readyProcess.empty();
}







// 준비 큐들을 가지고 연산하는 다단계 큐!
// 다단계 큐는 벡터로 선언해서, 각 큐에 접근하는 게 좋겠다.
class MultiQueue {
	vector<ReadyQueue> multiQueue;
	int priority; // 0부터 고유한 값으로 올라간다. 낮을수록 우선순위가 높다.
	int current; // 실행시간


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

// 몇단계 준비 큐를 저장할지 결정,
void MultiQueue::init(int size) {
	for (int i = 0; i < size; i++) {
		insertReadyQueue(1);
	}

	if(!multiQueue.empty())
		getData();
}

// 첫번째 큐에 메모장의 정보들을 넣는다.
void MultiQueue::getData() {

	// input.txt 입출력 구현 부
	FILE* input;

	int min_arrive = 0;
	int index = 0;

	int pid = 0;
	int arrive = 0;
	int service = 0;

	input = fopen("int.txt", "r");

	if (input == NULL) {
		cout << "input.txt를 읽을 수 없습니다. " << endl;
		exit(1);
	}

	// 메모장 다 읽어보자.
	// 이것도 멀티 큐에서 구현해서 내려가는 식으로 갈까? 그게 맞겠다.. 
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

	// 다단계 큐를 구현해보자. 마지막 아닌 우선순위 큐에서 끝났을 때, 해당 작업프로세스가 종료안되면, 다음 다단계 큐에 넣는다. 끝
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