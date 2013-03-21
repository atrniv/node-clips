#include <stdlib.h>
#include "clips_environment.h"
#include "../CLIPS/clips.h"

using namespace v8;


CLIPSEnvironment::CLIPSEnvironment () {};
CLIPSEnvironment::~CLIPSEnvironment () {};

void CLIPSEnvironment::Init(Handle<Object> exports) {

  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
  tpl->SetClassName(String::NewSymbol("Environment"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
  // Prototype
  tpl->PrototypeTemplate()->Set(String::NewSymbol("load"), FunctionTemplate::New(Load)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("save"), FunctionTemplate::New(Save)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("bload"), FunctionTemplate::New(BLoad)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("bsave"), FunctionTemplate::New(BSave)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("build"), FunctionTemplate::New(Build)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("reset"), FunctionTemplate::New(Reset)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("run"), FunctionTemplate::New(Run)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("clear"), FunctionTemplate::New(Clear)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("eval"), FunctionTemplate::New(Eval)->GetFunction());

  Persistent<Function> constructor = Persistent<Function>::New(tpl->GetFunction());
  exports->Set(String::NewSymbol("Environment"), constructor);
}

Handle<Value> CLIPSEnvironment::New(const Arguments& args) {
  HandleScope scope;
  CLIPSEnvironment* env = new CLIPSEnvironment();
  env->clips = CreateEnvironment();
  env->Wrap(args.This());
  return args.This();
}

void CLIPSLoad(uv_work_t* req) {
  func_baton* baton = (func_baton*) req->data;
  func_args1* args = (func_args1*) baton->args;

  Persistent<String> _filename = Persistent<String>::Cast(args->arg0);

  // Create filename string
  char* filename = (char*) malloc(sizeof(char*) * _filename->Utf8Length());
  _filename->WriteUtf8(filename);

  // Load file using CLIPS and store result
  int* rval = (int*) malloc(sizeof(int));
  *rval = EnvLoad(baton->clips, filename);

  baton->rval = rval;
  return;
}

void CLIPSSave(uv_work_t* req) {
  func_baton* baton = (func_baton*) req->data;
  func_args1* args = (func_args1*) baton->args;

  Persistent<String> _filename = Persistent<String>::Cast(args->arg0);

  // Create filename string
  char* filename = (char*) malloc(sizeof(char*) * _filename->Utf8Length());
  _filename->WriteUtf8(filename);

  // Save file using CLIPS and store result
  int* rval = (int*) malloc(sizeof(int));
  *rval = EnvSave(baton->clips, filename);

  baton->rval = rval;
  return;
}

void CLIPSBLoad(uv_work_t* req) {
  func_baton* baton = (func_baton*) req->data;
  func_args1* args = (func_args1*) baton->args;

  Persistent<String> _filename = Persistent<String>::Cast(args->arg0);

  // Create filename string
  char* filename = (char*) malloc(sizeof(char*) * _filename->Utf8Length());
  _filename->WriteUtf8(filename);

  // Load file using CLIPS and store result
  int* rval = (int*) malloc(sizeof(int));
  *rval = EnvBload(baton->clips, filename);

  baton->rval = rval;
  return;
}

void CLIPSBSave(uv_work_t* req) {
  func_baton* baton = (func_baton*) req->data;
  func_args1* args = (func_args1*) baton->args;

  Persistent<String> _filename = Persistent<String>::Cast(args->arg0);

  // Create filename string
  char* filename = (char*) malloc(sizeof(char*) * _filename->Utf8Length());
  _filename->WriteUtf8(filename);

  // Save file using CLIPS and store result
  int* rval = (int*) malloc(sizeof(int));
  *rval = EnvBsave(baton->clips, filename);

  baton->rval = rval;
  return;
}

void CLIPSBuild(uv_work_t* req) {
  func_baton* baton = (func_baton*) req->data;
  func_args1* args = (func_args1*) baton->args;

  Persistent<String> _construct = Persistent<String>::Cast(args->arg0);

  // Create filename string
  char* construct = (char*) malloc(sizeof(char*) * _construct->Utf8Length());
  _construct->WriteUtf8(construct);

  // Save file using CLIPS and store result
  int* rval = (int*) malloc(sizeof(int));
  *rval = EnvBuild(baton->clips, construct);

  baton->rval = rval;
  return;
}

void CLIPSReset(uv_work_t* req) {
  func_baton* baton = (func_baton*) req->data;
  EnvReset(baton->clips);
  return;
}

void CLIPSClear(uv_work_t* req) {
  func_baton* baton = (func_baton*) req->data;
  EnvClear(baton->clips);
  return;
}

void CLIPSRun(uv_work_t* req) {
  func_baton* baton = (func_baton*) req->data;
  func_args1* args = (func_args1*) baton->args;

  Persistent<Integer> run_limit = Persistent<Integer>::Cast(args->arg0);

  // Save file using CLIPS and store result
  long long int* rval = (long long int*) malloc(sizeof(long long int*));
  *rval = EnvRun(baton->clips, run_limit->NumberValue());

  baton->rval = rval;
  return;
}

void CLIPSEval(uv_work_t* req) {

  return;
}

void CLIPSWork(uv_work_t* req) {
  func_baton* baton = (func_baton*) req->data;

  switch(baton->func) {
    case CLIPS_LOAD:
      CLIPSLoad(req);
      break;
    case CLIPS_SAVE:
      CLIPSSave(req);
      break;
    case CLIPS_BLOAD:
      CLIPSBLoad(req);
      break;
    case CLIPS_BSAVE:
      CLIPSBSave(req);
      break;
    case CLIPS_BUILD:
      CLIPSBuild(req);
      break;
    case CLIPS_RESET:
      CLIPSReset(req);
      break;
    case CLIPS_CLEAR:
      CLIPSClear(req);
      break;
    case CLIPS_RUN:
      CLIPSRun(req);
      break;
    case CLIPS_EVAL:
      CLIPSEval(req);
      break;
  }
}

void CLIPSCleanup(uv_work_t* req, int status) {
  HandleScope scope;

  func_baton* baton = (func_baton*) req->data;

  const int argc = baton->rargc;
  Local<Value> argv[argc];
  argv[0] = Local<Value>::New(Null());

  // Handle Return value
  if (baton->func == CLIPS_LOAD) {
    int* rval = (int *)baton->rval;
    if (*rval == 0) {
      argv[0] = Exception::Error(String::New("File not found."));
    } else if (*rval == -1) {
      argv[0] = Exception::Error(String::New("An error occurred while loading the file."));
    }
  } else if (baton->func == CLIPS_SAVE) {
    int* rval = (int *)baton->rval;
    if (*rval == 0) {
      argv[0] = Exception::Error(String::New("An error occurred while saving the file."));
    }
  } else if (baton->func == CLIPS_BLOAD) {
    int* rval = (int *)baton->rval;
    if (*rval == 0) {
      argv[0] = Exception::Error(String::New("File not found."));
    } else if (*rval == -1) {
      argv[0] = Exception::Error(String::New("An error occurred while loading the binary file."));
    }
  } else if (baton->func == CLIPS_BSAVE) {
    int* rval = (int *)baton->rval;
    if (*rval == 0) {
      argv[0] = Exception::Error(String::New("An error occurred while saving the binary file."));
    }
  } else if (baton->func == CLIPS_BUILD) {
    int* rval = (int *)baton->rval;
    if (*rval == 0) {
      argv[0] = Exception::Error(String::New("An error occurred while parsing the construct."));
    }
  } else if (baton->func == CLIPS_RUN) {
    // return number of rules fired.
    long long int* rval = (long long int*)baton->rval;
    argv[1] = Integer::New(*rval);
  } else if (baton->func == CLIPS_EVAL) {

  }

  // Return result in callback
  baton->cb->Call(Context::GetCurrent()->Global(), argc, argv);

  // Cleanup
  if (baton->argc == 1) {
    func_args1* args = (func_args1*)baton->args;
    args->arg0.Dispose();
  } else if (baton->argc == 2) {
    func_args2* args = (func_args2*)baton->args;
    args->arg0.Dispose();
    args->arg1.Dispose();
  }

  baton->cb.Dispose();
  if(baton->rval != NULL) free(baton->rval);
  if(baton->args != NULL) free(baton->args);
  free(baton);
  scope.Close(Undefined());

  return;
}

func_baton* CreateBaton(int func, void* clips, const Arguments& args) {
  func_baton* baton = NULL;
  baton = (func_baton*) malloc(sizeof(func_baton));
  baton->req.data = (void*) baton;
  baton->clips = clips;
  baton->rval = NULL;
  baton->args = NULL;
  baton->func = func;

  switch(func){
    case CLIPS_RESET:
    case CLIPS_CLEAR:
      baton->argc = 0;
      baton->cb = Persistent<Function>::Cast(Persistent<Value>::New(args[0]));
      break;
    case CLIPS_LOAD:
    case CLIPS_SAVE:
    case CLIPS_BLOAD:
    case CLIPS_BSAVE:
    case CLIPS_BUILD:
    case CLIPS_RUN:
    case CLIPS_EVAL:
      baton->argc = 1;
      func_args1* _args = (func_args1*) malloc(sizeof(func_args1));
      _args->arg0 = Persistent<Value>::New(args[0]);
      baton->args = _args;
      baton->cb = Persistent<Function>::Cast(Persistent<Value>::New(args[1]));
      break;
  }

  // Set return value count
  switch(func) {
    case CLIPS_LOAD:
    case CLIPS_SAVE:
    case CLIPS_BLOAD:
    case CLIPS_BSAVE:
    case CLIPS_BUILD:
    case CLIPS_RESET:
    case CLIPS_CLEAR:
      baton->rargc = 1;
      break;
    case CLIPS_RUN:
    case CLIPS_EVAL:
      baton->rargc = 2;
      break;
  }
  return baton;
}


Handle<Value> CLIPSEnvironment::Load(const Arguments& args) {
  HandleScope scope;
  CLIPSEnvironment* env = ObjectWrap::Unwrap<CLIPSEnvironment>(args.This());

  if (args.Length() == 2 && args[0]->IsString() && args[1]->IsFunction()) {
    // Perform async execution
    func_baton* baton = CreateBaton(CLIPS_LOAD, env->clips, args);
    uv_queue_work(uv_default_loop(), &baton->req, CLIPSWork, CLIPSCleanup);
  } else {
    ThrowException(Exception::Error(String::New("Invalid arguments.")));
  }
  return scope.Close(Undefined());
}


Handle<Value> CLIPSEnvironment::Save(const Arguments& args) {
  HandleScope scope;
  CLIPSEnvironment* env = ObjectWrap::Unwrap<CLIPSEnvironment>(args.This());

  if (args.Length() == 2 && args[0]->IsString() && args[1]->IsFunction()) {
    // Perform async execution
    func_baton* baton = CreateBaton(CLIPS_SAVE, env->clips, args);
    uv_queue_work(uv_default_loop(), &baton->req, CLIPSWork, CLIPSCleanup);
  } else {
    ThrowException(Exception::Error(String::New("Invalid arguments.")));
  }
  return scope.Close(Undefined());
}

Handle<Value> CLIPSEnvironment::BLoad(const Arguments& args) {
  HandleScope scope;
  CLIPSEnvironment* env = ObjectWrap::Unwrap<CLIPSEnvironment>(args.This());

  if (args.Length() == 2 && args[0]->IsString() && args[1]->IsFunction()) {
    // Perform async execution
    func_baton* baton = CreateBaton(CLIPS_BLOAD, env->clips, args);
    uv_queue_work(uv_default_loop(), &baton->req, CLIPSWork, CLIPSCleanup);
  } else {
    ThrowException(Exception::Error(String::New("Invalid arguments.")));
  }
  return scope.Close(Undefined());
}

Handle<Value> CLIPSEnvironment::BSave(const Arguments& args) {
  HandleScope scope;
  CLIPSEnvironment* env = ObjectWrap::Unwrap<CLIPSEnvironment>(args.This());

  if (args.Length() == 2 && args[0]->IsString() && args[1]->IsFunction()) {
    // Perform async execution
    func_baton* baton = CreateBaton(CLIPS_BSAVE, env->clips, args);
    uv_queue_work(uv_default_loop(), &baton->req, CLIPSWork, CLIPSCleanup);
  } else {
    ThrowException(Exception::Error(String::New("Invalid arguments.")));
  }
  return scope.Close(Undefined());
}

Handle<Value> CLIPSEnvironment::Build(const Arguments& args) {
  HandleScope scope;
  CLIPSEnvironment* env = ObjectWrap::Unwrap<CLIPSEnvironment>(args.This());

  if (args.Length() == 2 && args[0]->IsString() && args[1]->IsFunction()) {
    // Perform async execution
    func_baton* baton = CreateBaton(CLIPS_BUILD, env->clips, args);
    uv_queue_work(uv_default_loop(), &baton->req, CLIPSWork, CLIPSCleanup);
  } else {
    ThrowException(Exception::Error(String::New("Invalid arguments.")));
  }
  return scope.Close(Undefined());
}

Handle<Value> CLIPSEnvironment::Reset(const Arguments& args) {
  HandleScope scope;
  CLIPSEnvironment* env = ObjectWrap::Unwrap<CLIPSEnvironment>(args.This());

  if (args.Length() == 1 && args[0]->IsFunction()) {
    // Perform async execution
    func_baton* baton = CreateBaton(CLIPS_RESET, env->clips, args);
    uv_queue_work(uv_default_loop(), &baton->req, CLIPSWork, CLIPSCleanup);
  } else {
    ThrowException(Exception::Error(String::New("Invalid arguments.")));
  }
  return scope.Close(Undefined());
}

Handle<Value> CLIPSEnvironment::Run(const Arguments& args) {
  HandleScope scope;
  CLIPSEnvironment* env = ObjectWrap::Unwrap<CLIPSEnvironment>(args.This());

  if (args.Length() == 2 && args[0]->IsNumber() && args[1]->IsFunction()) {
    // Perform async execution
    func_baton* baton = CreateBaton(CLIPS_RUN, env->clips, args);
    uv_queue_work(uv_default_loop(), &baton->req, CLIPSWork, CLIPSCleanup);
  } else {
    ThrowException(Exception::Error(String::New("Invalid arguments.")));
  }
  return scope.Close(Undefined());
}

Handle<Value> CLIPSEnvironment::Clear(const Arguments& args) {
  HandleScope scope;
  CLIPSEnvironment* env = ObjectWrap::Unwrap<CLIPSEnvironment>(args.This());

  if (args.Length() == 1 && args[0]->IsFunction()) {
    // Perform async execution
    func_baton* baton = CreateBaton(CLIPS_CLEAR, env->clips, args);
    uv_queue_work(uv_default_loop(), &baton->req, CLIPSWork, CLIPSCleanup);
  } else {
    ThrowException(Exception::Error(String::New("Invalid arguments.")));
  }
  return scope.Close(Undefined());
}

Handle<Value> CLIPSEnvironment::Eval(const Arguments& args) {
  HandleScope scope;
  CLIPSEnvironment* env = ObjectWrap::Unwrap<CLIPSEnvironment>(args.This());

  if (args.Length() == 2 && args[0]->IsString() && args[1]->IsFunction()) {
    // Perform async execution
    func_baton* baton = CreateBaton(CLIPS_EVAL, env->clips, args);
    uv_queue_work(uv_default_loop(), &baton->req, CLIPSWork, CLIPSCleanup);
  } else {
    ThrowException(Exception::Error(String::New("Invalid arguments.")));
  }
  return scope.Close(Undefined());
}
