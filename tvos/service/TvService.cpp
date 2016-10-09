#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include <utils/Log.h>
#include <binder/Parcel.h>
#include <binder/IPCThreadState.h>
#include <utils/threads.h>
#include <cutils/properties.h>
#include "TvService.h"

#define LOG_TAG "tvos: TvService"

namespace android {
	TvService::TvService() {
		myParam = 0;
	}

	int TvService::setSomething(int a) {
		ALOGD(" TvService::setSomething a = %d myParam %d", a, myParam);
		myParam += a;
		return 0;//OK
	}
	int TvService::getSomething() {
		ALOGD(" TvService::getSomething myParam = %d", myParam);
		mCallback->notifyCallback(myParam);
		return myParam;
	}
	int TvService::setCallback(const sp<ICallback>& callback) {
		ALOGD(" TvService::setCallback");
		mCallback = callback;
		return 0;
	}

}
