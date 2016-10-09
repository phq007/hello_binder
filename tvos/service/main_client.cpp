#include <stdio.h>
#include <binder/IServiceManager.h>
#include "ITvService.h"
#include "Callback.h"

#define LOG_TAG "tvos: Client-main"

using namespace android;

sp<ITvService> mTvService;

void initTvServiceClient() {	
	if (mTvService == 0) {
		sp<IServiceManager> sm = defaultServiceManager();
		sp<IBinder> binder;
		do {
			binder = sm->getService(String16("TvService"));
			if (binder != 0)
				break;
			ALOGW("TvService not published, waiting...");
			usleep(500000); // 0.5s			
		} while (true);
		mTvService = interface_cast<ITvService>(binder);
	}
}

#if !SERVICE_BUILD
int main(int argc, char* argv[]) {
	initTvServiceClient();
	if (mTvService == NULL) {
		ALOGW("cannot find TvService");
		return 0;
	}
	int ret = 0;
	sp<Callback> c = new Callback();
	mTvService->setCallback(c);
	while (1)
	{		
		ret = mTvService->getSomething();		
		//ALOGW("getSomething %d\n",ret);	
		mTvService->setSomething(1);
		sleep(1);	
		ALOGD("getSomething %d", ret);
	}
	return 0;
}
#endif