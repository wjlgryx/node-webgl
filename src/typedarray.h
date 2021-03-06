#ifndef TYPEDARRAYS_H_
#define TYPEDARRAYS_H_

#include <v8.h>

#include <node.h>
#include <node_buffer.h>

using namespace v8;
using namespace node;

class Float32Array : public ObjectWrap {
public:

    static void
    Initialize (Handle<Object> target) {
	HandleScope scope;

	Local<FunctionTemplate> t = FunctionTemplate::New(New);
	t->InstanceTemplate()->SetInternalFieldCount(1);
	t->SetClassName(String::NewSymbol("Float32Array"));

	NODE_SET_PROTOTYPE_METHOD(t, "set", Set);

	target->Set(String::NewSymbol("Float32Array"), t->GetFunction());
    }

    void *
    GetData () {
	return (void *)buf->data();
    }

    size_t
    Length () {
	return buf->length();
    }

    void
    Set (float *sequence, uint32_t length) {
	float *data = (float *)buf->data();
	for(int i = 0; i < length; i++) {
	    data[i] = sequence[i];
	}
    }

protected:

    static Handle<Value>
    New (const Arguments& args) {
	HandleScope scope;

	Buffer *buf = ObjectWrap::Unwrap<Buffer>(args[0]->ToObject());

	Float32Array *fa = new Float32Array(buf);
	fa->Wrap(args.This());

	return args.This();
    }

    static Handle<Value>
    Set (const Arguments& args) {
	HandleScope scope;

        Float32Array *fa = Unwrap<Float32Array>(args.This());

	Local<Array> a = Local<Array>::Cast(args[0]);

	size_t length = a->Length();
	float *sequence = new float[length];
	for(int i = 0; i < length; i++) {
	    Local<Value> val = a->Get(i);
	    sequence[i] = val->NumberValue();
	}
	fa->Set(sequence, length);
	delete[] sequence;

	return Undefined();
    }

    Float32Array (Buffer *b) : ObjectWrap() {
	    buf = b;
    }

private:

    Buffer *buf;

};

#endif  // TYPEDARRAYS_H_
