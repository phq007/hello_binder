#include <binder/Parcel.h>
#include <binder/IPCThreadState.h>
#include <utils/String16.h>
#include <utils/threads.h>
#include <utils/Atomic.h>

//#include <cutils/bitops.h>
#include <cutils/properties.h>
#include <cutils/compiler.h>
#include "Callback.h"
#include <utils/Log.h>


#define LOG_TAG "tvos: client-Callback"

namespace android {
	int Callback::notifyCallback(int a) {
		ALOGD("Callback::notifyCallback, Actually, come from TvService.., the callback value:  %d", a);
		return 1;
	}

}
