#include <iostream>
#include <chrono>
#include <thread>
#include <Windows.h>
#include <TlHelp32.h>
using namespace std;
void GetLocalTime(SYSTEMTIME& systemTime) {
    GetLocalTime(&systemTime); // ���� �ý��� �ð��� ��� Windows API �Լ� ȣ��
}

int main() {
    SYSTEMTIME t;
    while (true) { // ���� ���� ����
        int n = 0;
        HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        // ���� ���� ���� ���μ��� ������ ����
        GetLocalTime(t); // ���� �ð� ���
        // snap�� ��ȿ�ϴٸ�
        if (snap != INVALID_HANDLE_VALUE) {
            PROCESSENTRY32 proentry;
            proentry.dwSize = sizeof(PROCESSENTRY32);
            // ����ü�� �����Ű�� ������ ����
            if (Process32First(snap, &proentry)) {
                n++; // ù ��° ���μ��� ī��Ʈ

                while (Process32Next(snap, &proentry)) {
                    n++; // ���� ���μ��� ī��Ʈ
                }
            }

            
        }

        CloseHandle(snap); // ���μ��� ������ �ݱ�
        // ���� ��¥�� �ð�, ���μ��� ������ ���
        cout << t.wYear << "." << t.wMonth << "." << t.wDay << " " <<
            t.wHour << ":" << t.wMinute << ":" << t.wSecond << " : " << n << endl;
        this_thread::sleep_for(std::chrono::seconds(1)); // 1�� ���� ���
    } // ���� ���� �������� ����

    return 0;
}