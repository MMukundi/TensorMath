#include "TensorWrapper.h"

Napi::FunctionReference TensorWrapper::constructor;

Napi::Object TensorWrapper::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function func = DefineClass(env, "TensorWrapper", {
    InstanceMethod("add", &TensorWrapper::Add),
    InstanceMethod("getValue", &TensorWrapper::GetValue),
  });

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("TensorWrapper", func);
  return exports;
}

TensorWrapper::TensorWrapper(const Napi::CallbackInfo& info) : Napi::ObjectWrap<TensorWrapper>(info)  {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  int length = info.Length();
  
  if (length != 1) {
    Napi::TypeError::New(env, "Only one argument expected").ThrowAsJavaScriptException();
  }

  if(!info[0].IsNumber()){
    Napi::Object object_parent = info[0].As<Napi::Object>();
    TensorWrapper* example_parent = Napi::ObjectWrap<TensorWrapper>::Unwrap(object_parent);
    ActualClass* parent_actual_class_instance = example_parent->GetInternalInstance();
    this->actualClass_ = new ActualClass(parent_actual_class_instance->getValue());
    return;
  }

  Napi::Number value = info[0].As<Napi::Number>();
  this->actualClass_ = new ActualClass(value.DoubleValue());
}

Napi::Value TensorWrapper::GetValue(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  double num = this->actualClass_->getValue();
  return Napi::Number::New(env, num);
}


Napi::Value TensorWrapper::Add(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  if (info.Length() != 1 || !info[0].IsNumber()) {
    Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
  }

  Napi::Number toAdd = info[0].As<Napi::Number>();
  double answer = this->actualClass_->add(toAdd.DoubleValue());

  return Napi::Number::New(info.Env(), answer);
}

ActualClass* TensorWrapper::GetInternalInstance() {
  return this->actualClass_;
}