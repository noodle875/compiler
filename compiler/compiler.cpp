// compiler.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "Compiler.h"

auto printTokenList(vector<Token> tokenList) -> void;

auto main(int argc, char** argv) -> int {
	string sourceCode = R""""(
	function main(){
		printLine 'Hello, World!';
		printLine 1 + 2  * 3;
	}
	)"""";
	auto tokenList = scan(sourceCode);
	auto syntaxTree = parse(tokenList);
	// printSyntaxTree(syntaxTree);
	// printTokenList(tokenList);
	// interpret(syntaxTree);
	// auto objectCode = generate(syntaxTree);
	// printObjectCode(objectCode);
	auto objectCode = generate(syntaxTree);
	execute(objectCode);
	return 0;
}

auto printTokenList(vector<Token> tokenList) -> void
{
	cout << setw(12) << left << "KIND" << "STRING" << endl;
	cout << string(23, '-') << endl;
	for (auto& token : tokenList)
		cout << token << endl;
}

auto printObjectCode(tuple<vector<Code>, map<string, size_t>>objectCode) -> void {
	auto codeList = get<0>(objectCode);
	auto functionTable = get<1>(objectCode);
	cout << setw(11) << left << "FUNCTION" << "ADDRESS" << endl;
	cout << string(18, '-') << endl;
	for (auto& [key, value] : functionTable)
		cout << setw(11) << key << value << endl;
	cout << endl;
	cout << "ADDR" << " " << setw(15) << "INSTRUCTION" << "OPERAND" << endl;
	cout << string(36, '-') << endl;
	for (size_t i = 0; i < codeList.size(); i++)
		cout << setw(4) << right << i << " " << codeList[i] << endl;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
