#include <iostream>
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <stdlib.h>

using namespace std;

CRITICAL_SECTION cs1, cs2, cs3, cs4, cs5, cs6, cs7;
DWORD t1, t2, t3, t4;

DWORD WINAPI Squaring1(void* tmp) {
    int data;
    DWORD n;


   // Создание/открытие объекта и возвращение дескриптора для получения доступа к нему
    HANDLE pipe = CreateFileA("\\\\.\\pipe\\my_pipe1", GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
                              OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    HANDLE pipe1 = CreateNamedPipeA("\\\\.\\pipe\\my_pipe12", PIPE_ACCESS_OUTBOUND, PIPE_TYPE_BYTE, 1, sizeof(int), 2, 0, NULL);

    while (1) {
        if (cs3.LockCount == -1) {
            EnterCriticalSection(&cs3);
            EnterCriticalSection(&cs1);
            ReadFile(pipe, &data, sizeof(int), &n, NULL);
            cout << "Cathet1:" << data << std::endl;
            int x = 0;
            int temp;
            temp = data * data;
            WriteFile(pipe1, &temp, sizeof(int), &n, NULL);
            LeaveCriticalSection(&cs1);
            LeaveCriticalSection(&cs7);

            //Завершение выполнения потока
            TerminateThread(&t1, 0);
        }
    }
}

DWORD WINAPI Squaring2(void* tmp) {
    DWORD n;
    int data;

    HANDLE pipe = CreateFileA("\\\\.\\pipe\\my_pipe2", GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
                              OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    HANDLE pipe2 = CreateNamedPipeA("\\\\.\\pipe\\my_pipe22", PIPE_ACCESS_OUTBOUND, PIPE_TYPE_BYTE, 1, 2 * sizeof(int), 2, 0, NULL);

    while (1) {
        if (cs7.LockCount == -1)
        {
            EnterCriticalSection(&cs7);
            EnterCriticalSection(&cs1);
            ReadFile(pipe, &data, sizeof(int), &n, NULL);
            cout << "Cathet2:"<< data<< std::endl;
            int x = 0;
            int temp;
            temp = data * data;
            WriteFile(pipe2, &temp, sizeof(int), &n, NULL);
            LeaveCriticalSection(&cs1);
            LeaveCriticalSection(&cs4);

            //Завершение выполнения потока
            TerminateThread(&t2, 0);
        }
    }
}
DWORD WINAPI Adding(void* tmp) {
    DWORD n;
    int a, b;

    HANDLE pipe1 = CreateFileA("\\\\.\\pipe\\my_pipe12", GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
                               OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    HANDLE pipe2 = CreateFileA("\\\\.\\pipe\\my_pipe22", GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
                               OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    HANDLE pipe3 = CreateNamedPipeA("\\\\.\\pipe\\my_pipe3", PIPE_ACCESS_OUTBOUND, PIPE_TYPE_BYTE, 1, sizeof(int), 2, 0, NULL);

    while (1) {
        if (cs4.LockCount == -1) {
            EnterCriticalSection(&cs4);
            EnterCriticalSection(&cs1);
            ReadFile(pipe1, &a, sizeof(int), &n, NULL);
            ReadFile(pipe2, &b, sizeof(int), &n, NULL);
            int res = a+b;
            cout << "Addition of squares of cathets: " << a << " + " << b << " = "<< res << endl;

            WriteFile(pipe3, &res, sizeof(int), &n, NULL);
            LeaveCriticalSection(&cs1);
            LeaveCriticalSection(&cs5);

            //Завершение выполнения потока
            TerminateThread(&t3, 0);
        }
    }
}

DWORD WINAPI Root(void* tmp) {
    DWORD n;
    int c;

    HANDLE pipe = CreateFileA("\\\\.\\pipe\\my_pipe3", GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
                              OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    HANDLE pipe1 = CreateNamedPipeA("\\\\.\\pipe\\my_pipe4", PIPE_ACCESS_OUTBOUND, PIPE_TYPE_BYTE, 1, sizeof(double), 2, 0, NULL);

    while (1) {
        if (cs5.LockCount == -1) {
            EnterCriticalSection(&cs5);
            EnterCriticalSection(&cs1);
            ReadFile(pipe, &c, sizeof(int), &n, NULL);
            cout << "Get square of "<< c <<endl;

            double res = sqrt(c);
            WriteFile(pipe1, &res, sizeof(double), &n, NULL);
            LeaveCriticalSection(&cs1);
            LeaveCriticalSection(&cs6);

            //Завершение выполнения потока
            TerminateThread(&t4, 0);
        }
    }
}

int main() {
    DWORD n;
    int a = 0,b = 0;

    // Создаются именнованные каналы
    HANDLE pipe1 = CreateNamedPipeA("\\\\.\\pipe\\my_pipe1", PIPE_ACCESS_OUTBOUND, PIPE_TYPE_BYTE, 1, 2*sizeof(int), 2, 0, NULL);
    HANDLE pipe2 = CreateNamedPipeA("\\\\.\\pipe\\my_pipe2", PIPE_ACCESS_DUPLEX, PIPE_TYPE_BYTE, 1, 2*sizeof(int), 2, 0, NULL);

    // Инициализация критической секции
    InitializeCriticalSection(&cs1);
    InitializeCriticalSection(&cs2);
    InitializeCriticalSection(&cs3);
    InitializeCriticalSection(&cs4);
    InitializeCriticalSection(&cs5);
    InitializeCriticalSection(&cs6);
    InitializeCriticalSection(&cs7);

    // Позволение потокам войти в критическую секцию, заблокировав другим потокам доступ
    EnterCriticalSection(&cs3);
    EnterCriticalSection(&cs4);
    EnterCriticalSection(&cs5);
    EnterCriticalSection(&cs6);
    EnterCriticalSection(&cs7);

    // Создание потоков внутри вызывающих
    CreateThread(NULL, 0, Squaring1, NULL, 0, &t1);
    CreateThread(NULL, 0, Squaring2, NULL, 0, &t2);
    CreateThread(NULL, 0, Adding, NULL, 0, &t3);
    CreateThread(NULL, 0, Root, NULL, 0, &t4);

    //Ввод катетов
    while (a<=0||b<=0) {
        cout << " a = ";
        cin >> a;
        cout << "b = ";
        cin >> b;
        if (a<=0||b<=0)
        {
            cout<< "Wrong values of cathets, they must be more than 0!\n Try again:\n";
        }
    }

    // Используя дескриптор доступа, передаем данные из буфера памяти;
    WriteFile(pipe1, &a, sizeof(int), &n, NULL);
    WriteFile(pipe2, &b, sizeof(int), &n, NULL);
    HANDLE pipe = CreateFileA("\\\\.\\pipe\\my_pipe4", GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    while (1) {
        if (cs2.LockCount == -1) {
            EnterCriticalSection(&cs2);
            EnterCriticalSection(&cs1);
            cout << "Start counting" << endl;

            // Освобождение блокировки «критической секции»
            LeaveCriticalSection(&cs1);
            LeaveCriticalSection(&cs3);
        }

        if (cs6.LockCount == -1)
        {
            double res;
            ReadFile(pipe, &res, sizeof(double), &n, NULL);
            cout << "c = " << res << endl;
            return 0;
        }
    }
}
