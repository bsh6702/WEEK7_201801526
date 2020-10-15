#include <iostream>
#include <stdexcept>
class Test {
public:
	Test(char id) : id_(id) {}
	~Test() {
		std::cout << "Destructor execution: "
			<< id_ << std::endl;
	}
private:
	char id_;
};
int funcB() {
	Test r('B');
	throw std::runtime_error("Exception from funcB!\n");
	std::cout << "Executed in B" << std::endl;
	return 0;
}
int funcA() {
	Test r('A');
	funcB();
	std::cout << "Executed in A" << std::endl;
	return 0;
}
int main() {
	try {
		funcA();
	}
	catch (std::exception& e) {
		std::cout << "Exception : " << e.what();
	}
}
/* 
스택 언와이딩은 예외처리와 관련된 개념이다.
exception 발생 시 exception 핸들러가 있는 위치를 찾아 가는 것을
 스택 언와인딩이라고 한다.

(실습 1-1) 분석결과 : 
Executed in B
Destructor execution: B
Executed in A
Destructor execution: A

예외가 발생하지 않은 경우로
throw부분이 주석처리가 되어있을 때는 exception이 되지 않아
cout 부분이 호출되지 않는다.
*/
/* (실습 1-2) 분석결과 :
Destructor execution: B
Destructor execution: A
Exception : Exception from funcB!

예외가 발생한 경우이다. 
cout부분들이 호출 되지 않고 funcA가 종료가 되었다.
*/