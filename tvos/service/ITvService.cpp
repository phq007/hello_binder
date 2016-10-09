#include "ITvService.h"
#include <binder/Parcel.h>
#include <binder/IInterface.h>
#include <utils/Log.h>
#include "ICallback.h"

#define LOG_TAG "tvos: ITvService"

namespace android {

	enum {
		SET_SOMETHING = IBinder::FIRST_CALL_TRANSACTION,
		GET_SOMETHING,
		SET_CALLBACK
	};

	//------------------------------------proxy side--------------------------------

	class BpTvService : public BpInterface<ITvService> {
	public:
		BpTvService(const sp<IBinder>& impl)
			: BpInterface<ITvService>(impl) {
		}
		virtual int setSomething(int a) {
			ALOGD(" BpTvService::setSomething a = %d ", a);
			Parcel data, reply;
			data.writeInt32(a);
			remote()->transact(SET_SOMETHING, data, &reply);
			return reply.readInt32();
		}
		virtual int getSomething() {
			ALOGD(" BpTvService::getSomething ");
			Parcel data, reply;						
			data.writeInterfaceToken(ITvService::getInterfaceDescriptor());						
			remote()->transact(GET_SOMETHING, data, &reply);
			return reply.readInt32();
		}
		virtual int setCallback(const sp<ICallback>& callback) {
			ALOGD("BpTvService::setCallback");
			Parcel data, reply;
			data.writeStrongBinder(callback->asBinder());// TODO: important
			remote()->transact(SET_CALLBACK, data, &reply);
			return reply.readInt32();
		}

	};
	//---------------------- interface--------------------
	IMPLEMENT_META_INTERFACE(TvService, "tvos.binder.ITvService");


	//------------------------------------server side--------------------------------
	status_t BnTvService::onTransact(
		uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags){
		switch (code) {
			case SET_SOMETHING: {
				ALOGD("BnTvService::onTransact  SET_SOMETHING ");
				reply->writeInt32(setSomething((int)data.readInt32()));
				return NO_ERROR;
			} break;
			case GET_SOMETHING: {
				ALOGD("BnTvService::onTransact  GET_SOMETHING ");
				reply->writeInt32(getSomething());
				return NO_ERROR;
			} break;
			case SET_CALLBACK: {
				ALOGD("BnTvService::onTransact  SET_CALLBACK ");
				sp<ICallback> callback = interface_cast<ICallback>(data.readStrongBinder());// TODO: important!
				reply->writeInt32(setCallback(callback));
				return NO_ERROR;
			}
		}
		return BBinder::onTransact(code, data, reply, flags);
	}
}
