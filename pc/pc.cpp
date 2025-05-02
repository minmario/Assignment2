#include <iostream>
#include <chrono>
#include <thread>
#include <Windows.h>
#include <TlHelp32.h>
using namespace std;
void GetLocalTime(SYSTEMTIME& systemTime) {
    GetLocalTime(&systemTime); // 현재 시스템 시간을 얻는 Windows API 함수 호출
}

int main() {
    SYSTEMTIME t;
    while (true) { // 무한 루프 시작
        int n = 0;
        HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        // 현재 실행 중인 프로세스 스냅샷 생성
        GetLocalTime(t); // 현재 시간 얻기
        // snap가 유효하다면
        if (snap != INVALID_HANDLE_VALUE) {
            PROCESSENTRY32 proentry;
            proentry.dwSize = sizeof(PROCESSENTRY32);
            // 구조체를 선언시키고 사이즈 구함
            if (Process32First(snap, &proentry)) {
                n++; // 첫 번째 프로세스 카운트

                while (Process32Next(snap, &proentry)) {
                    n++; // 다음 프로세스 카운트
                }
            }

            
        }

        CloseHandle(snap); // 프로세스 스냅샷 닫기
        // 현재 날짜와 시간, 프로세스 개수를 출력
        cout << t.wYear << "." << t.wMonth << "." << t.wDay << " " <<
            t.wHour << ":" << t.wMinute << ":" << t.wSecond << " : " << n << endl;
        this_thread::sleep_for(std::chrono::seconds(1)); // 1초 동안 대기
    } // 무한 루프 종료하지 않음

    return 0;
}