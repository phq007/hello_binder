#ifndef __CALLBACK_H_  
#define __CALLBACK_H_

#include "ITvService.h"
#include "ICallback.h"
#include "BinderService.h"


namespace android {
	class Callback : public BnCallback {
	public:
		virtual int notifyCallback(int a);
	};
}


#endif