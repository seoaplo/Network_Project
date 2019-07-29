#pragma once
#include "SClient.h"
#include "Game/SssCore.h"
#include "SssSceenManeger.h"

class SssSampler : public SssCore
{
public:
	bool BeginInit();
	bool BeginFrame();
	bool BeginRenderer();
public:
	bool Init();
	bool Renderer();
	bool Frame();
	bool Release();
public:
	bool EndInit();
	bool EndFrame();
	bool EndRenderer();
public:
	SssSampler();
	~SssSampler();
};

