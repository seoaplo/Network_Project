#include <windows.h>
#include <stdio.h>
#include <tchar.h>

#define _CRT_SECURE_NO_WARNINGS
#define HasOverlappedIoCompleted (pOverlapped) ((pOverlapped)->Internal != STATUS_PENDING)

CHAR*	g_pmbData;
CHAR*	g_pmbDataCopy;

DWORD Load(const TCHAR* strFileName)
{
	TCHAR Drive[MAX_PATH];
	TCHAR Dir[MAX_PATH];
	TCHAR FName[MAX_PATH];
	TCHAR Ext[MAX_PATH];
	_tsplitpath(strFileName, Drive, Dir, FName, Ext);

	DWORD TotalBytes;
	LARGE_INTEGER FileSize;
	
	//===================================================================
	// CreateFile
	//===================================================================
	// 1. FileName
	// 2. 파일 또는 장치에 대한 요청 된 액세스. 읽기, 쓰기, 둘 다 또는 모두 0으로 요약 할 수 있습니다
	// 3. 파일 또는 장치의 요청 된 공유 모드. 읽기, 쓰기, 둘 다, 삭제, 모두 또는 없음
	// 4. 별도의 관련 데이터 멤버 인 선택적 보안 설명자와 반환 된 핸들을 자식 프로세스에서 상속 할 수 있는지 여부를
	//		결정하는 부울 값을 포함 하는 SECURITY_ATTRIBUTES 구조체에 대한 포인터 입니다.
	// 5. 존재하거나 존재하지 않는 파일이나 장치를 취하는 작업.
	// 6. 파일 또는 장치 속성 및 플래그
	// 7. GENERIC_READ 액세스 권한 이있는 템플릿 파일에 대한 유효한 핸들.
	//템플리트 파일은 작성중인 파일에 대한 파일 속성 및 확장 속성을 제공합니다.

	HANDLE FileHandle = CreateFile(	strFileName,
									GENERIC_READ, FILE_SHARE_READ,
									NULL, OPEN_EXISTING,
									FILE_ATTRIBUTE_NORMAL,
									NULL);

	if (FileHandle != INVALID_HANDLE_VALUE)
	{
		GetFileSizeEx(FileHandle, &FileSize);
		TotalBytes = FileSize.LowPart;

		g_pmbData = new char[TotalBytes];
		if (!g_pmbData)
		{
			CloseHandle(FileHandle);
			return 0;
		}

		DWORD BytesRead;
		if (!ReadFile(FileHandle, g_pmbData, TotalBytes, &BytesRead, NULL))
		{
			CloseHandle(FileHandle);
			delete[] g_pmbData;
			return 0;
		}
		SetFilePointer( FileHandle, 0, 0, FILE_BEGIN );
	}
	else
	{
		return 0;
	}
	CloseHandle(FileHandle);
	return TotalBytes;
}

DWORD AsyncLoad(const TCHAR* strFileName)
{
	TCHAR Drive[MAX_PATH];
	TCHAR Dir[MAX_PATH];
	TCHAR FName[MAX_PATH];
	TCHAR Ext[MAX_PATH];
	_tsplitpath(strFileName, Drive, Dir, FName, Ext);

	DWORD TotalBytes;
	LARGE_INTEGER FileSize;
	HANDLE FileHandle = CreateFile(	strFileName,
									GENERIC_READ, FILE_SHARE_READ,
									NULL, OPEN_EXISTING,
									FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
									NULL);

	if (FileHandle != INVALID_HANDLE_VALUE)
	{
		GetFileSizeEx(FileHandle, &FileSize);
		TotalBytes = FileSize.LowPart;
		printf("[파일 크기: %ld KB", TotalBytes / 1024);
		g_pmbData = new char[TotalBytes];
		if (!g_pmbData)
		{
			CloseHandle(FileHandle);
			return 0;
		}

		// 비동기 입력
		OVERLAPPED readOV;
		ZeroMemory(&readOV, sizeof(OVERLAPPED));

		DWORD dwByteRead;
		//========================================================================
		// ReadFile
		//========================================================================
		// 1. 파일 핸들
		// 2. 읽어온 데이터를 넣을 버퍼
		// 3. 읽을 데이터 크기
		// 4. 읽어 온 데이터 크기
		// 5. OVERLAPPED 변수
		//========================================================================

		DWORD ret = ReadFile(FileHandle, g_pmbData, TotalBytes, &dwByteRead, &readOV);
		if (ret == FALSE)
		{
			if (GetLastError() == ERROR_IO_PENDING)
			{
				printf("\n 읽기 작업 중!");
			}
		}
		if (ret == TRUE)
		{
			printf("\n 입력 완료!");
			CloseHandle(FileHandle);
			delete[] g_pmbData;
			return 0;
		}
		// 비동기 입출력의 작업완성
		while (1)
		{
			DWORD dwRet = WaitForSingleObject(FileHandle, INFINITE);
			if (dwRet == WAIT_OBJECT_0)
			{
				DWORD Tans = 0;
				BOOL Result = GetOverlappedResult(FileHandle, &readOV, &Tans, FALSE);
				if (Tans >= TotalBytes)
				{
					printf("\n--->%ld 읽기 완료!!!!", readOV.InternalHigh);
					break;
				}
			}
			else if (dwRet == WAIT_TIMEOUT)
			{
				/*1. bWait == TRUE && OVERLAPPED.internal == STATUS_PENDING
					bWait가 TRUE인 경우에 미리 COMMTIMEOUTS에 설정한 타임아웃 값
					만큼 기다린다.기다리는 도중 완료되면 TRUE 반환 TIMEOUT되면 FALSE 반환
					GetLastError() 함수는 ERROR_IO_INCOMPLETE 반환
				2. bWait == FALSE : && OVERLAPPED.internal == STATUS_PENDING
					bWait가 FALSE인 경우에 완료되길 기다리지 않고 바로 쓰기한 바이트를 넣고 반환된다.
					아직 쓰기작업이 끝나지 않았다면 FALSE를 반환하고 GetLastError() 함수는
					ERROR_IO_INCOMPLETE 반환*/

				static int icnt = 0;
				DWORD Tans = 0;
				BOOL Result = GetOverlappedResult(FileHandle, &readOV, &Tans, FALSE);
				if (Result == FALSE)
				{
					if (GetLastError() == ERROR_IO_INCOMPLETE)
					{
						printf("읽는 중[:%d]", icnt++);
					}
				}
				if (Result == TRUE)
				{
					printf("\n------->%d 읽기 완료.", readOV.InternalHigh);
				}
			}
			else
			{
				printf("\n--->%d Error!!!!", dwRet);
				break;
			}
			Sleep(1);
		}

	}
	else
	{
		return 0;
	}
	SetFilePointer(FileHandle, 0, 0, FILE_BEGIN);
	CloseHandle(FileHandle);
	return TotalBytes;
}

DWORD AsyncSave(const TCHAR* strFileName, DWORD dwFileSize)
{
	OVERLAPPED ov;
	ZeroMemory(&ov, sizeof(OVERLAPPED));
	ov.hEvent = 0; //::CreateEvent(NULL, FALSE, FALSE, NULL);

	// 비동기 추력
	HANDLE hWriteFile = CreateFile(	strFileName,
									GENERIC_READ | GENERIC_WRITE,
									0, NULL,
									CREATE_ALWAYS,
									FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
									NULL);

	printf("\n 비동기 출력 시작------------------>!");
	if (hWriteFile != NULL)
	{
		DWORD dwWritten;
		BOOL ret = WriteFile(hWriteFile, g_pmbData, dwFileSize, &dwWritten, &ov);
		if (ret == FALSE)
		{
			if (GetLastError() == ERROR_IO_PENDING)
			{
				printf("작업 중");
			}
		}
		if (ret == TRUE)
		{
			printf("\n출력 완료!");
		}
	}
	// 비동기 입출력의 작업 완성
	while (1)
	{
		DWORD dwRet = WaitForSingleObject(hWriteFile, INFINITE);
		if (dwRet == WAIT_OBJECT_0)
		{
			DWORD Tans = 0;
			BOOL Result = GetOverlappedResult(hWriteFile, &ov, &Tans, FALSE);
			if (Tans >= dwFileSize)
			{
				delete[] g_pmbData;
				CloseHandle(hWriteFile);
				printf("\n--->%d 복사 출력완료!!!!", ov.InternalHigh);
				break;
			}
		}
		else if (dwRet == WAIT_TIMEOUT)
		{
			static int icnt = 0;
			DWORD Tans = 0;
			BOOL Result = GetOverlappedResult(hWriteFile, &ov, &Tans, FALSE);
			if (Result == FALSE)
			{
				if (GetLastError() == ERROR_IO_INCOMPLETE)
				{
					printf("출력중[:%d]", icnt++);
				}
			}

			if (Result == TRUE)
			{
				printf("\n--->%d 복사 출력완료!!!!", ov.InternalHigh);
			}
		}
		else
		{
			delete[] g_pmbData;
			CloseHandle(hWriteFile);
			printf("\n--->%d Error!!!!", dwRet);
			break;
		}
		Sleep(1);
	}
	CloseHandle(ov.hEvent);
	printf("\n 프로그램 종료");

	getchar();
	return 0;
}