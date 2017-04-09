#pragma once

#include <Windows.h>

#include <ShellScalingApi.h>
#pragma comment(lib, "shcore.lib")

#include <CommCtrl.h>
#pragma comment(lib,"comctl32.lib")

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#define CLS_NAME	L"MainApp"		//类名
#define WIN_TITLE	L"MyApp"		//窗口标题

#define ACCEL_NUM	1				//快捷键数目
#define CMD_CLOSE	101				//关闭命令