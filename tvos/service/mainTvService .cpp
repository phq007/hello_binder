#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include "TvService.h"
#include <utils/Log.h>

#define LOG_TAG "tvos: TvService-main"

#define EASY_START_BINDER_SERVICE 0

using namespace android;

#if SERVICE_BUILD
int main(int argc, char** argv)
{
#if EASY_START_BINDER_SERVICE
	TvService::publishAndJoinThreadPool();//使用了父类BinderService的函数
#else
	sp<ProcessState> proc(ProcessState::self());
	sp<IServiceManager> sm(defaultServiceManager());
	sm->addService(String16(TvService::getServiceName()), new TvService());
	ProcessState::self()->startThreadPool();
	IPCThreadState::self()->joinThreadPool();
	while (1);
#endif

	return 0;
}
#endif