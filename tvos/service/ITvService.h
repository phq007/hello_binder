#ifndef __I_TV_SERVICE_H_  
#define __I_TV_SERVICE_H_

#include <binder/IInterface.h>
#include "ICallback.h"

namespace android {
	class ITvService : public IInterface {
	public:
		DECLARE_META_INTERFACE(TvService);
		virtual int setSomething(int a) = 0;
		virtual int getSomething() = 0;
		virtual int setCallback(const sp<ICallback>& callback) = 0;
	};

	class BnTvService : public BnInterface<ITvService> {
	public:
		virtual status_t    onTransact(uint32_t code,
			const Parcel& data,
			Parcel* reply,
			uint32_t flags = 0);
	};

}
#endif
