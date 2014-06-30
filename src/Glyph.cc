#include "Glyph.h"

void Glyph::Init(v8::Handle<v8::Object> exports) {
  NanScope();

  v8::Local<v8::FunctionTemplate> constructorTemplate = NanNew<v8::FunctionTemplate>(New);
  constructorTemplate->SetClassName(NanNew<v8::String>("Glyph"));

  v8::Local<v8::ObjectTemplate> constructorObjectTemplate = constructorTemplate->InstanceTemplate();
  constructorObjectTemplate->SetAccessor(NanNew<v8::String>("metrics"), acc_metrics);
  constructorObjectTemplate->SetAccessor(NanNew<v8::String>("format"), acc_format);
  constructorObjectTemplate->SetAccessor(NanNew<v8::String>("lsb_delta"), acc_lsb_delta);
  constructorObjectTemplate->SetAccessor(NanNew<v8::String>("rsb_delta"), acc_rsb_delta);
  constructorObjectTemplate->SetAccessor(NanNew<v8::String>("bitmap"), acc_bitmap);
  constructorObjectTemplate->SetAccessor(NanNew<v8::String>("bitmap_left"), acc_bitmap_left);
  constructorObjectTemplate->SetAccessor(NanNew<v8::String>("bitmap_top"), acc_bitmap_top);
  constructorObjectTemplate->SetInternalFieldCount(1);

  NanAssignPersistent(constructor, constructorTemplate->GetFunction());
}

v8::Persistent<v8::Function> Glyph::constructor;

NAN_METHOD(Glyph::New) {
  NanScope();
  Glyph* glyph = new Glyph();
  glyph->Wrap(args.This());
  NanReturnValue(args.This());
}

Glyph::Glyph() {}

Glyph::~Glyph() {}

NAN_GETTER(Glyph::acc_metrics) {
  NanScope();
  Glyph* glyph = node::ObjectWrap::Unwrap<Glyph>(args.This());
  v8::Handle<v8::Object> metrics = NanNew<v8::Object>();
  metrics->Set(NanNew<v8::String>("width"), NanNew<v8::Integer>(glyph->ftGlyph->metrics.width));
  metrics->Set(NanNew<v8::String>("height"), NanNew<v8::Integer>(glyph->ftGlyph->metrics.height));
  metrics->Set(NanNew<v8::String>("horiBearingX"), NanNew<v8::Integer>(glyph->ftGlyph->metrics.horiBearingX));
  metrics->Set(NanNew<v8::String>("horiBearingY"), NanNew<v8::Integer>(glyph->ftGlyph->metrics.horiBearingY));
  metrics->Set(NanNew<v8::String>("horiAdvance"), NanNew<v8::Integer>(glyph->ftGlyph->metrics.horiAdvance));
  metrics->Set(NanNew<v8::String>("vertBearingX"), NanNew<v8::Integer>(glyph->ftGlyph->metrics.vertBearingX));
  metrics->Set(NanNew<v8::String>("vertBearingY"), NanNew<v8::Integer>(glyph->ftGlyph->metrics.vertBearingY));
  metrics->Set(NanNew<v8::String>("vertAdvance"), NanNew<v8::Integer>(glyph->ftGlyph->metrics.vertAdvance));
  NanReturnValue(metrics);
}

NAN_GETTER(Glyph::acc_format) {
  NanScope();
  Glyph* glyph = node::ObjectWrap::Unwrap<Glyph>(args.This());
  NanReturnValue(NanNew<v8::Integer>(glyph->ftGlyph->format));
}

NAN_GETTER(Glyph::acc_lsb_delta) {
  NanScope();
  Glyph* glyph = node::ObjectWrap::Unwrap<Glyph>(args.This());
  NanReturnValue(NanNew<v8::Integer>(glyph->ftGlyph->lsb_delta));
}

NAN_GETTER(Glyph::acc_rsb_delta) {
  NanScope();
  Glyph* glyph = node::ObjectWrap::Unwrap<Glyph>(args.This());
  NanReturnValue(NanNew<v8::Integer>(glyph->ftGlyph->rsb_delta));
}

NAN_GETTER(Glyph::acc_bitmap) {
  NanScope();
  Glyph* glyph = node::ObjectWrap::Unwrap<Glyph>(args.This());
  v8::Local<v8::Object> bitmap = NanNew<v8::Object>();
  bitmap->Set(NanNew<v8::String>("rows"), NanNew<v8::Integer>(glyph->ftGlyph->bitmap.rows));
  bitmap->Set(NanNew<v8::String>("width"), NanNew<v8::Integer>(glyph->ftGlyph->bitmap.width));
  bitmap->Set(NanNew<v8::String>("pitch"), NanNew<v8::Integer>(glyph->ftGlyph->bitmap.pitch));
  bitmap->Set(NanNew<v8::String>("buffer"), NanNewBufferHandle((char*)glyph->ftGlyph->bitmap.buffer, glyph->ftGlyph->bitmap.width * glyph->ftGlyph->bitmap.rows));
  bitmap->Set(NanNew<v8::String>("num_grays"), NanNew<v8::Integer>(glyph->ftGlyph->bitmap.num_grays));
  bitmap->Set(NanNew<v8::String>("pixel_mode"), NanNew<v8::Integer>(glyph->ftGlyph->bitmap.pixel_mode));
  NanReturnValue(bitmap);
}

NAN_GETTER(Glyph::acc_bitmap_left) {
  NanScope();
  Glyph* glyph = node::ObjectWrap::Unwrap<Glyph>(args.This());
  NanReturnValue(NanNew<v8::Integer>(glyph->ftGlyph->bitmap_left));
}

NAN_GETTER(Glyph::acc_bitmap_top) {
  NanScope();
  Glyph* glyph = node::ObjectWrap::Unwrap<Glyph>(args.This());
  NanReturnValue(NanNew<v8::Integer>(glyph->ftGlyph->bitmap_top));
}