#include "DragAndDrop.h"
#include <SFML/System.hpp>
#include <iostream>
LONG_PTR sfmlCallBack = 0x0;

static std::string currentPath;

LRESULT CALLBACK dragAndDropCallBack(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	if (message == WM_DROPFILES) {
        currentPath.clear();
		HDROP hDrop = reinterpret_cast<HDROP>(wParam);
		const UINT filesCount = DragQueryFile(hDrop, 0xFFFFFFFF, nullptr, 0);
		for (UINT i{ 0 }; i < filesCount; i++) {
            const UINT bufSize = DragQueryFile(hDrop, i, NULL, 0);
            std::wstring path;
            path.resize(bufSize + 1);
            if (DragQueryFile(hDrop, i, &path[0], bufSize + 1)) {            
                sf::Utf8::fromWide(path.begin(), path.end(), std::back_inserter(currentPath));         
            }
        }
        DragFinish(hDrop);
        std::cout << currentPath.data() << std::endl;
	}
    return CallWindowProcW(reinterpret_cast<WNDPROC>(sfmlCallBack), hwnd, message, wParam, lParam);
}

void setHandle(HWND hwnd) {
    DragAcceptFiles(hwnd, true);
    sfmlCallBack = SetWindowLongPtrW(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(dragAndDropCallBack));
}

std::string_view getPath() {  
    return currentPath;
}
