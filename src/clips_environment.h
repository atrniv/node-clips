#ifndef CLIPS_ENVIRONMENT_H
#define CLIPS_ENVIRONMENT_H

#include <node.h>
#include <v8.h>
#include <uv.h>


#define CLIPS_LOAD 0
#define CLIPS_SAVE 1
#define CLIPS_BLOAD 2
#define CLIPS_BSAVE 3
#define CLIPS_BUILD 4
#define CLIPS_RESET 5
#define CLIPS_CLEAR 6
#define CLIPS_RUN 7
#define CLIPS_EVAL 8

#define RVAL_INT 0

struct func_args1 {
  v8::Persistent<v8::Value> arg0;
};

struct func_args2 {
  v8::Persistent<v8::Value> arg0;
  v8::Persistent<v8::Value> arg1;
};

struct func_baton {
  uv_work_s req;
  int argc;
  int rargc;
  int func;
  void* rval;
  void* clips;
  void* args;
  v8::Persistent<v8::Function>cb;
};

class CLIPSEnvironment: public node::ObjectWrap{
 public:
  static void Init(v8::Handle<v8::Object> exports);

 private:
  CLIPSEnvironment();
  ~CLIPSEnvironment();

  static v8::Handle<v8::Value> New(const v8::Arguments& args);
  static v8::Handle<v8::Value> Load(const v8::Arguments& args);
  static v8::Handle<v8::Value> Save(const v8::Arguments& args);
  static v8::Handle<v8::Value> BLoad(const v8::Arguments& args);
  static v8::Handle<v8::Value> BSave(const v8::Arguments& args);
  static v8::Handle<v8::Value> Build(const v8::Arguments& args);
  static v8::Handle<v8::Value> Reset(const v8::Arguments& args);
  static v8::Handle<v8::Value> Run(const v8::Arguments& args);
  static v8::Handle<v8::Value> Clear(const v8::Arguments& args);
  static v8::Handle<v8::Value> Eval(const v8::Arguments& args);

  void* clips;

};
#endif
