#include "FontFace.h"

void FontFace::Init(v8::Handle<v8::Object> exports) {
  NanScope();

  v8::Local<v8::FunctionTemplate> constructorTemplate = NanNew<v8::FunctionTemplate>(New);
  constructorTemplate->SetClassName(NanSymbol("FontFace"));

  v8::Local<v8::ObjectTemplate> constructorObjectTemplate = constructorTemplate->InstanceTemplate();
  constructorObjectTemplate->SetAccessor(NanSymbol("num_faces"), acc_num_faces);
  constructorObjectTemplate->SetAccessor(NanSymbol("face_index"), acc_face_index);
  constructorObjectTemplate->SetAccessor(NanSymbol("face_flags"), acc_face_flags);
  constructorObjectTemplate->SetAccessor(NanSymbol("style_flags"), acc_style_flags);
  constructorObjectTemplate->SetAccessor(NanSymbol("num_glyphs"), acc_num_glyphs);
  constructorObjectTemplate->SetAccessor(NanSymbol("family_name"), acc_family_name);
  constructorObjectTemplate->SetAccessor(NanSymbol("style_name"), acc_style_name);
  constructorObjectTemplate->SetAccessor(NanSymbol("num_fixed_sizes"), acc_num_fixed_sizes);
  constructorObjectTemplate->SetAccessor(NanSymbol("available_sizes"), acc_available_sizes);
  constructorObjectTemplate->SetAccessor(NanSymbol("num_charmaps"), acc_num_charmaps);
  constructorObjectTemplate->SetAccessor(NanSymbol("charmaps"), acc_charmaps);
  constructorObjectTemplate->SetAccessor(NanSymbol("bbox"), acc_bbox);
  constructorObjectTemplate->SetAccessor(NanSymbol("units_per_EM"), acc_units_per_EM);
  constructorObjectTemplate->SetAccessor(NanSymbol("ascender"), acc_ascender);
  constructorObjectTemplate->SetAccessor(NanSymbol("descender"), acc_descender);
  constructorObjectTemplate->SetAccessor(NanSymbol("height"), acc_height);
  constructorObjectTemplate->SetAccessor(NanSymbol("max_advance_width"), acc_max_advance_width);
  constructorObjectTemplate->SetAccessor(NanSymbol("max_advance_height"), acc_max_advance_height);
  constructorObjectTemplate->SetAccessor(NanSymbol("underline_position"), acc_underline_position);
  constructorObjectTemplate->SetAccessor(NanSymbol("underline_thickness"), acc_underline_thickness);
  constructorObjectTemplate->SetAccessor(NanSymbol("glyph"), acc_glyph);
  constructorObjectTemplate->SetAccessor(NanSymbol("size"), acc_size);
  // constructorObjectTemplate->SetAccessor(NanSymbol("charmap"), acc_charmap);
  constructorObjectTemplate->SetInternalFieldCount(1);

  NanAssignPersistent(constructor, constructorTemplate->GetFunction());
}

v8::Persistent<v8::Function> FontFace::constructor;

NAN_METHOD(FontFace::New) {
  NanScope();
  FontFace* fontFace = new FontFace();
  fontFace->Wrap(args.This());
  NanReturnValue(args.This());
}

FontFace::FontFace() {}

FontFace::~FontFace() {
  FT_Done_Face(this->ftFace);
}

NAN_GETTER(FontFace::acc_num_faces) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(args.This());
  NanReturnValue(NanNew<v8::Number>(fontFace->ftFace->num_faces));
}

NAN_GETTER(FontFace::acc_face_index) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(args.This());
  NanReturnValue(NanNew<v8::Number>(fontFace->ftFace->face_index));
}

NAN_GETTER(FontFace::acc_face_flags) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(args.This());
  NanReturnValue(NanNew<v8::Number>(fontFace->ftFace->face_flags));
}

NAN_GETTER(FontFace::acc_style_flags) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(args.This());
  NanReturnValue(NanNew<v8::Number>(fontFace->ftFace->style_flags));
}

NAN_GETTER(FontFace::acc_num_glyphs) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(args.This());
  NanReturnValue(NanNew<v8::Number>(fontFace->ftFace->num_glyphs));
}

NAN_GETTER(FontFace::acc_family_name) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(args.This());
  NanReturnValue(NanNew<v8::String>(fontFace->ftFace->family_name));
}

NAN_GETTER(FontFace::acc_style_name) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(args.This());
  NanReturnValue(NanNew<v8::String>(fontFace->ftFace->style_name));
}

NAN_GETTER(FontFace::acc_num_fixed_sizes) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(args.This());
  NanReturnValue(NanNew<v8::Number>(fontFace->ftFace->num_fixed_sizes));
}

NAN_GETTER(FontFace::acc_available_sizes) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(args.This());
  v8::Handle<v8::Array> available_sizes = NanNew<v8::Array>(fontFace->ftFace->num_fixed_sizes);
  for (int i = 0; i < fontFace->ftFace->num_fixed_sizes; i++) {
    v8::Handle<v8::Object> size = NanNew<v8::Object>();
    size->Set(NanSymbol("height"), NanNew(fontFace->ftFace->available_sizes[i].height));
    size->Set(NanSymbol("width"), NanNew(fontFace->ftFace->available_sizes[i].width));
	size->Set(NanSymbol("size"), NanNew<v8::Number>(fontFace->ftFace->available_sizes[i].size));
	size->Set(NanSymbol("x_ppem"), NanNew<v8::Number>(fontFace->ftFace->available_sizes[i].x_ppem));
	size->Set(NanSymbol("y_ppem"), NanNew<v8::Number>(fontFace->ftFace->available_sizes[i].y_ppem));
    available_sizes->Set(i, size);
  }
  NanReturnValue(available_sizes);
}

NAN_GETTER(FontFace::acc_num_charmaps) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(args.This());
  NanReturnValue(NanNew<v8::Number>(fontFace->ftFace->num_charmaps));
}

NAN_GETTER(FontFace::acc_charmaps) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(args.This());
  v8::Handle<v8::Array> charmaps = NanNew<v8::Array>(fontFace->ftFace->num_charmaps);
  for (int i = 0; i < fontFace->ftFace->num_charmaps; i++) {
    v8::Handle<v8::Object> charmap = NanNew<v8::Object>();
    charmap->Set(NanSymbol("encoding"), NanNew<v8::Number>(fontFace->ftFace->charmaps[i]->encoding));
    charmap->Set(NanSymbol("platform_id"), NanNew<v8::Number>(fontFace->ftFace->charmaps[i]->platform_id));
    charmap->Set(NanSymbol("encoding_id"), NanNew<v8::Number>(fontFace->ftFace->charmaps[i]->encoding_id));
    charmaps->Set(i, charmap);
  }
  NanReturnValue(charmaps);
}

NAN_GETTER(FontFace::acc_bbox) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(args.This());
  v8::Handle<v8::Object> bbox = NanNew<v8::Object>();
  bbox->Set(NanSymbol("xMin"), NanNew<v8::Number>(fontFace->ftFace->bbox.xMin));
  bbox->Set(NanSymbol("xMax"), NanNew<v8::Number>(fontFace->ftFace->bbox.xMax));
  bbox->Set(NanSymbol("yMin"), NanNew<v8::Number>(fontFace->ftFace->bbox.yMin));
  bbox->Set(NanSymbol("yMax"), NanNew<v8::Number>(fontFace->ftFace->bbox.yMax));
  NanReturnValue(bbox);
}

NAN_GETTER(FontFace::acc_units_per_EM) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(args.This());
  NanReturnValue(NanNew<v8::Number>(fontFace->ftFace->units_per_EM));
}

NAN_GETTER(FontFace::acc_ascender) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(args.This());
  NanReturnValue(NanNew<v8::Number>(fontFace->ftFace->ascender));
}

NAN_GETTER(FontFace::acc_descender) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(args.This());
  NanReturnValue(NanNew<v8::Number>(fontFace->ftFace->descender));
}

NAN_GETTER(FontFace::acc_height) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(args.This());
  NanReturnValue(NanNew<v8::Number>(fontFace->ftFace->height));
}

NAN_GETTER(FontFace::acc_max_advance_width) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(args.This());
  NanReturnValue(NanNew<v8::Number>(fontFace->ftFace->max_advance_width));
}

NAN_GETTER(FontFace::acc_max_advance_height) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(args.This());
  NanReturnValue(NanNew<v8::Number>(fontFace->ftFace->max_advance_height));
}

NAN_GETTER(FontFace::acc_underline_position) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(args.This());
  NanReturnValue(NanNew<v8::Number>(fontFace->ftFace->underline_position));
}

NAN_GETTER(FontFace::acc_underline_thickness) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(args.This());
  NanReturnValue(NanNew<v8::Number>(fontFace->ftFace->underline_thickness));
}

NAN_GETTER(FontFace::acc_glyph) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(args.This());
  v8::Handle<v8::Object> glyphObj = NanNew(Glyph::constructor)->NewInstance();
  Glyph* glyph = node::ObjectWrap::Unwrap<Glyph>(glyphObj);
  glyph->ftGlyph = fontFace->ftFace->glyph;
  NanReturnValue(glyphObj);
}

NAN_GETTER(FontFace::acc_size) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(args.This());
  FT_Size_Metrics metrics = fontFace->ftFace->size->metrics;
  v8::Handle<v8::Object> retval = NanNew<v8::Object>();
  
  retval->Set(NanSymbol("x_ppem"), NanNew<v8::Number>(metrics.x_ppem));
  retval->Set(NanSymbol("y_ppem"), NanNew<v8::Number>(metrics.y_ppem));
  retval->Set(NanSymbol("x_scale"), NanNew<v8::Number>(metrics.x_scale / (float)(1 << 16)));
  retval->Set(NanSymbol("y_scale"), NanNew<v8::Number>(metrics.y_scale / (float)(1 << 16)));
  retval->Set(NanSymbol("ascender"), NanNew<v8::Number>(metrics.ascender / (float)(1 << 6)));
  retval->Set(NanSymbol("descender"), NanNew<v8::Number>(metrics.descender / (float)(1 << 6)));
  retval->Set(NanSymbol("height"), NanNew<v8::Number>(metrics.height / (float)(1 << 6)));
  retval->Set(NanSymbol("max_advance"), NanNew<v8::Number>(metrics.max_advance / (float)(1 << 6)));
  
  NanReturnValue(retval);
}
