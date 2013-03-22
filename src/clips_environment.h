#ifndef CLIPS_ENVIRONMENT_H
#define CLIPS_ENVIRONMENT_H

#include <node.h>
#include <v8.h>
#include <uv.h>
#include <stdlib.h>
#include "../CLIPS/clips.h"


#define CLIPS_INITIALIZE 0
#define CLIPS_DISPOSE 1
#define CLIPS_LOAD 2
#define CLIPS_SAVE 3
#define CLIPS_BLOAD 4
#define CLIPS_BSAVE 5
#define CLIPS_BUILD 6
#define CLIPS_RESET 7
#define CLIPS_CLEAR 8
#define CLIPS_RUN 9
#define CLIPS_EVAL 10
#define CLIPS_ASSERT_STRING 11
#define CLIPS_FACTS 12

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
  void** clips;
  void* args;
  v8::Persistent<v8::Function>cb;
};

void CLIPSInitialize(uv_work_t* req);
void CLIPSDispose(uv_work_t* req);
void CLIPSLoad(uv_work_t* req);
void CLIPSSave(uv_work_t* req);
void CLIPSBLoad(uv_work_t* req);
void CLIPSBSave(uv_work_t* req);
void CLIPSBuild(uv_work_t* req);
void CLIPSReset(uv_work_t* req);
void CLIPSClear(uv_work_t* req);
void CLIPSRun(uv_work_t* req);
void CLIPSEval(uv_work_t* req);
void CLIPSWork(uv_work_t* req);
void CLIPSCleanup(uv_work_t* req, int status);

v8::Handle<v8::Value> FactToJSON(void* fact_ptr);
v8::Handle<v8::Value> MultiFieldToJSON(void* multifield_ptr, long begin, long end);
v8::Handle<v8::Value> DataObjectToJSON(DATA_OBJECT& obj);

class CLIPSEnvironment: public node::ObjectWrap {
 public:
  static void Init(v8::Handle<v8::Object> exports);

 private:
  CLIPSEnvironment();
  ~CLIPSEnvironment();

  static v8::Handle<v8::Value> New(const v8::Arguments& args);
  static v8::Handle<v8::Value> Initialize(const v8::Arguments& args);
  static v8::Handle<v8::Value> Dispose(const v8::Arguments& args);
  static v8::Handle<v8::Value> Load(const v8::Arguments& args);
  static v8::Handle<v8::Value> Save(const v8::Arguments& args);
  static v8::Handle<v8::Value> BLoad(const v8::Arguments& args);
  static v8::Handle<v8::Value> BSave(const v8::Arguments& args);
  static v8::Handle<v8::Value> Build(const v8::Arguments& args);
  static v8::Handle<v8::Value> Reset(const v8::Arguments& args);
  static v8::Handle<v8::Value> Run(const v8::Arguments& args);
  static v8::Handle<v8::Value> Clear(const v8::Arguments& args);
  static v8::Handle<v8::Value> Eval(const v8::Arguments& args);
  static v8::Handle<v8::Value> ListFacts(const v8::Arguments& args);
  static v8::Handle<v8::Value> JSAssert(const v8::Arguments& args);

  void* clips;

};

#endif
