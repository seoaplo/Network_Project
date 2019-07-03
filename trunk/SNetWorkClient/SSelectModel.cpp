#include "SSelectModel.h"

bool SSelectModel::RecvMsg(SOCKET sock, char* pBuffer, int iNumDataByte)
{
	if(iNumDataByte == 0) return true;
	int iRecvByte = 0;
	do
	{
		int iByte = recv(sock, &pBuffer[iRecvByte], iNumDataByte - iRecvByte, 0);
		if (iByte == 0)
		{
			return false;
		}
		if (iByte == SOCKET_ERROR)
		{
			return false;
		}
		iRecvByte += iByte;
	} while(iNumDataByte > iRecvByte);

	return true;
}
bool SSelectModel::SendMsg(SOCKET sock, int type, char* data, int iSize)
{
	UPACKET packet;
	ZeroMemory(&packet, sizeof(UPACKET));
	packet.ph.type = type;
	packet.ph.len = PACKET_HEADER_SIZE + iSize;
	if (data != nullptr)
	{
		memcpy(packet.msg, data, iSize);
	}

	int iSendByte = 0;
	do
	{
		int iPacketByte = send(sock,
								(char*)&packet, packet.ph.len - iSendByte, 0);
		if (iPacketByte == SOCKET_ERROR)
		{
			return false;
		}
		iSendByte += iPacketByte;
	} while(packet.ph.len > iSendByte);
	return true;
}

SSelectModel::SSelectModel()
{
}


SSelectModel::~SSelectModel()
{
}
