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
	// 2. ���� �Ǵ� ��ġ�� ���� ��û �� �׼���. �б�, ����, �� �� �Ǵ� ��� 0���� ��� �� �� �ֽ��ϴ�
	// 3. ���� �Ǵ� ��ġ�� ��û �� ���� ���. �б�, ����, �� ��, ����, ��� �Ǵ� ����
	// 4. ������ ���� ������ ��� �� ������ ���� �����ڿ� ��ȯ �� �ڵ��� �ڽ� ���μ������� ��� �� �� �ִ��� ���θ�
	//		�����ϴ� �ο� ���� ���� �ϴ� SECURITY_ATTRIBUTES ����ü�� ���� ������ �Դϴ�.
	// 5. �����ϰų� �������� �ʴ� �����̳� ��ġ�� ���ϴ� �۾�.
	// 6. ���� �Ǵ� ��ġ �Ӽ� �� �÷���
	// 7. GENERIC_READ �׼��� ���� ���ִ� ���ø� ���Ͽ� ���� ��ȿ�� �ڵ�.
	//���ø�Ʈ ������ �ۼ����� ���Ͽ� ���� ���� �Ӽ� �� Ȯ�� �Ӽ��� �����մϴ�.

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
		printf("[���� ũ��: %ld KB", TotalBytes / 1024);
		g_pmbData = new char[TotalBytes];
		if (!g_pmbData)
		{
			CloseHandle(FileHandle);
			return 0;
		}

		// �񵿱� �Է�
		OVERLAPPED readOV;
		ZeroMemory(&readOV, sizeof(OVERLAPPED));

		DWORD dwByteRead;
		//========================================================================
		// ReadFile
		//========================================================================
		// 1. ���� �ڵ�
		// 2. �о�� �����͸� ���� ����
		// 3. ���� ������ ũ��
		// 4. �о� �� ������ ũ��
		// 5. OVERLAPPED ����
		//========================================================================

		DWORD ret = ReadFile(FileHandle, g_pmbData, TotalBytes, &dwByteRead, &readOV);
		if (ret == FALSE)
		{
			if (GetLastError() == ERROR_IO_PENDING)
			{
				printf("\n �б� �۾� ��!");
			}
		}
		if (ret == TRUE)
		{
			printf("\n �Է� �Ϸ�!");
			CloseHandle(FileHandle);
			delete[] g_pmbData;
			return 0;
		}
		// �񵿱� ������� �۾��ϼ�
		while (1)
		{
			DWORD dwRet = WaitForSingleObject(FileHandle, INFINITE);
			if (dwRet == WAIT_OBJECT_0)
			{
				DWORD Tans = 0;
				BOOL Result = GetOverlappedResult(FileHandle, &readOV, &Tans, FALSE);
				if (Tans >= TotalBytes)
				{
					printf("\n--->%ld �б� �Ϸ�!!!!", readOV.InternalHigh);
					break;
				}
			}
			else if (dwRet == WAIT_TIMEOUT)
			{
				/*1. bWait == TRUE && OVERLAPPED.internal == STATUS_PENDING
					bWait�� TRUE�� ��쿡 �̸� COMMTIMEOUTS�� ������ Ÿ�Ӿƿ� ��
					��ŭ ��ٸ���.��ٸ��� ���� �Ϸ�Ǹ� TRUE ��ȯ TIMEOUT�Ǹ� FALSE ��ȯ
					GetLastError() �Լ��� ERROR_IO_INCOMPLETE ��ȯ
				2. bWait == FALSE : && OVERLAPPED.internal == STATUS_PENDING
					bWait�� FALSE�� ��쿡 �Ϸ�Ǳ� ��ٸ��� �ʰ� �ٷ� ������ ����Ʈ�� �ְ� ��ȯ�ȴ�.
					���� �����۾��� ������ �ʾҴٸ� FALSE�� ��ȯ�ϰ� GetLastError() �Լ���
					ERROR_IO_INCOMPLETE ��ȯ*/

				static int icnt = 0;
				DWORD Tans = 0;
				BOOL Result = GetOverlappedResult(FileHandle, &readOV, &Tans, FALSE);
				if (Result == FALSE)
				{
					if (GetLastError() == ERROR_IO_INCOMPLETE)
					{
						printf("�д� ��[:%d]", icnt++);
					}
				}
				if (Result == TRUE)
				{
					printf("\n------->%d �б� �Ϸ�.", readOV.InternalHigh);
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

	// �񵿱� �߷�
	HANDLE hWriteFile = CreateFile(	strFileName,
									GENERIC_READ | GENERIC_WRITE,
									0, NULL,
									CREATE_ALWAYS,
									FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
									NULL);

	printf("\n �񵿱� ��� ����------------------>!");
	if (hWriteFile != NULL)
	{
		DWORD dwWritten;
		BOOL ret = WriteFile(hWriteFile, g_pmbData, dwFileSize, &dwWritten, &ov);
		if (ret == FALSE)
		{
			if (GetLastError() == ERROR_IO_PENDING)
			{
				printf("�۾� ��");
			}
		}
		if (ret == TRUE)
		{
			printf("\n��� �Ϸ�!");
		}
	}
	// �񵿱� ������� �۾� �ϼ�
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
				printf("\n--->%d ���� ��¿Ϸ�!!!!", ov.InternalHigh);
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
					printf("�����[:%d]", icnt++);
				}
			}

			if (Result == TRUE)
			{
				printf("\n--->%d ���� ��¿Ϸ�!!!!", ov.InternalHigh);
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
	printf("\n ���α׷� ����");

	getchar();
	return 0;
}