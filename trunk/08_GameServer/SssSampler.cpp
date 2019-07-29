#include "SssSampler.h"


#pragma region Begin
bool SssSampler::BeginInit()
{
	return true;
}
bool SssSampler::BeginFrame()
{
	return true;
}
bool SssSampler::BeginRenderer()
{
	return true;
}
#pragma endregion

#pragma region Middle
bool SssSampler::Init()
{
	SingleSceenManeger.Init(MyhMemoryDC, MyOutPutDC);
	return true;
}
bool SssSampler::Frame()
{
	if (!SingleSceenManeger.Frame())
	{
		return false;
	}
	return true;
}
bool SssSampler::Renderer()
{
	SingleSceenManeger.Render();

	return true;
}
bool SssSampler::Release()
{
	SingleSceenManeger.Release();
	return true;
}
#pragma endregion

#pragma region End
bool SssSampler::EndInit()
{
	return true;
}
bool SssSampler::EndFrame()
{
	return true;
}
bool SssSampler::EndRenderer()
{
	return true;
}
#pragma endregion
SssSampler::SssSampler()
{
}


SssSampler::~SssSampler()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

}