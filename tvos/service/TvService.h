#ifndef __TV_SERVICE_H_  
#define __TV_SERVICE_H_

#include "ITvService.h"
#include "BinderService.h"
#include "ICallback.h"

namespace android {
	class TvService : public BinderService<TvService>, public BnTvService {
//	class TvService : public BnTvService {
	public:
		TvService();
		static const char* getServiceName() { return "TvService"; }//will be the service name
		virtual int setSomething(int a);
		virtual int getSomething();
		virtual int setCallback(const sp<ICallback>& callback);
	protected:
		int myParam;
		sp<ICallback> mCallback;
	};
}




#endif