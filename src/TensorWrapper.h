#include "Tensor.h"
#include "../node_modules/node-addon-api/napi.h"

class TensorWrapper : public Napi::ObjectWrap<TensorWrapper> {
 public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  TensorWrapper(const Napi::CallbackInfo& info);
  Tensor* GetInternalInstance();

 private:
  static Napi::FunctionReference constructor;
  Napi::Value GetValue(const Napi::CallbackInfo& info);
  Napi::Value Add(const Napi::CallbackInfo& info);
  Tensor *tensor;
};
Napi::Function func = DefineClass(env, "Tensor", 
{
  InstanceMethod("add", &ClassExample::Add),
  InstanceMethod("getValue", &ClassExample::GetValue),
});
constructor = Napi::Persistent(func);