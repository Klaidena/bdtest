#include <Windows.h>
#include <WinHttp.h>
#include <string>
#include <iostream>

#pragma comment(lib, "winhttp.lib")

int main() {
    std::cout << "enter a query to the database: ";
    std::string query;
    std::getline(std::cin, query);
    
    HINTERNET s = WinHttpOpen(L"Fetch", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, 0, 0, 0);
    HINTERNET c = WinHttpConnect(s, L"raw.githubusercontent.com", INTERNET_DEFAULT_HTTPS_PORT, 0);
    HINTERNET r = WinHttpOpenRequest(c, 0, L"/Klaidena/bdtest/refs/heads/main/bd2.txt", 0, 0, 0, WINHTTP_FLAG_SECURE);
    WinHttpSendRequest(r, 0, 0, 0, 0, 0, 0);
    WinHttpReceiveResponse(r, 0);
    
    std::string o;
    DWORD b;
    char t[1024];
    while (WinHttpReadData(r, t, sizeof(t), &b) && b) o.append(t, b);
    
    WinHttpCloseHandle(r);
    WinHttpCloseHandle(c);
    WinHttpCloseHandle(s);
    
    std::string line;
    size_t pos = 0;
    while (pos < o.size()) {
        size_t end = o.find('\n', pos);
        if (end == std::string::npos) end = o.size();
        line = o.substr(pos, end - pos);
        pos = end + 1;
        
        if (line.find(query + ":") == 0) {
            std::cout << line << std::endl;
            return 0;
        }
    }
    
    std::cout << "Query not found" << std::endl;
    return 0;
}
