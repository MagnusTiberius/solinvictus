// setup_repo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "JsonConfig.h"
#include "SetupRepo.h"






int _tmain(int argc, _TCHAR* argv[])
{

	SetupRepo setuprepo;

	setuprepo.Run(argc, argv);

	return 0;
}

