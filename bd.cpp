#include <Windows.h>
#include <WinHttp.h>
#include <string>
#include <algorithm>

#pragma comment(lib, "winhttp.lib")

int main() {
    HINTERNET s = WinHttpOpen(L"Fetch", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, 0, 0, 0);
    HINTERNET c = WinHttpConnect(s, L"raw.githubusercontent.com", INTERNET_DEFAULT_HTTPS_PORT, 0);
    HINTERNET r = WinHttpOpenRequest(c, 0, L"Тут вставьте ссылку на файл(без raw.githubusercontent.com так как он уже есть)", 0, 0, 0, WINHTTP_FLAG_SECURE);
    WinHttpSendRequest(r, 0, 0, 0, 0, 0, 0);
    WinHttpReceiveResponse(r, 0);
    std::string o;
    DWORD b;
    char t[1024];
    while (WinHttpReadData(r, t, sizeof(t), &b) && b) o.append(t, b);
    printf("%s", o.c_str());
    WinHttpCloseHandle(r);
    WinHttpCloseHandle(c);
    WinHttpCloseHandle(s);
}
