#include <nan.h>
#include <vector>
#include "fontface.h"

using namespace v8;

Persistent<Function> FontFace::constructor;

FontFace::FontFace(const FT_Byte* file_base, FT_Long file_size) {
  FT_New_Memory_Face(library, file_base, file_size, 0, &face);
}

FontFace::~FontFace() {
}

FT_Library FontFace::library;

void FontFace::Init() {
  if (FT_Init_FreeType(&library)) exit(EXIT_FAILURE);

  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
  tpl->SetClassName(String::NewSymbol("FontFace"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
  NanAssignPersistent(Function, constructor, tpl->GetFunction());
}

NAN_METHOD(FontFace::New) {
  NanScope();

  FontFace* obj = new FontFace(
    (FT_Byte*)node::Buffer::Data(args[0]->ToObject()),
    (FT_Long)node::Buffer::Length(args[0]->ToObject())
  );

  obj->SetObjectProperties(args.This());
  obj->Wrap(args.This());

  NanReturnValue(args.This());
}

Handle<Value> FontFace::NewInstance(_NAN_METHOD_ARGS_TYPE args) {
  NanScope();



  const unsigned argc = 1;
  Handle<Value> argv[argc] = { args[0] };
  Local<Object> instance = NanPersistentToLocal(constructor)->NewInstance(argc, argv);

  return scope.Close(instance);
}

// http://www.freetype.org/freetype2/docs/reference/ft2-base_interface.html#FT_FaceRec
void FontFace::SetObjectProperties(Handle<Object> obj) {
  obj->Set(String::NewSymbol("num_faces"), Integer::New(this->face->num_faces));
  obj->Set(String::NewSymbol("face_index"), Integer::New(this->face->face_index));

  obj->Set(String::NewSymbol("face_flags"), Integer::New(this->face->face_flags));
  obj->Set(String::NewSymbol("style_flags"), Integer::New(this->face->style_flags));

  obj->Set(String::NewSymbol("num_glyphs"), Integer::New(this->face->num_glyphs));

  obj->Set(String::NewSymbol("family_name"), String::New(this->face->family_name));
  obj->Set(String::NewSymbol("style_name"), String::New(this->face->style_name));

  obj->Set(String::NewSymbol("num_fixed_sizes"), Integer::New(this->face->num_fixed_sizes));
  // obj->Set(String::NewSymbol("available_sizes"), Integer::New(this->face->available_sizes));

  obj->Set(String::NewSymbol("num_charmaps"), Integer::New(this->face->num_charmaps));
  // obj->Set(String::NewSymbol("charmaps"), Integer::New(this->face->charmaps));

  // obj->Set(String::NewSymbol("generic"), Integer::New(this->face->generic));

  obj->Set(String::NewSymbol("units_per_EM"), Integer::New(this->face->units_per_EM));
  // obj->Set(String::NewSymbol("bbox"), Integer::New(this->face->bbox));

  obj->Set(String::NewSymbol("ascender"), Integer::New(this->face->ascender));
  obj->Set(String::NewSymbol("descender"), Integer::New(this->face->descender));
  obj->Set(String::NewSymbol("height"), Integer::New(this->face->height));

  obj->Set(String::NewSymbol("max_advance_width"), Integer::New(this->face->max_advance_width));
  obj->Set(String::NewSymbol("max_advance_height"), Integer::New(this->face->max_advance_height));

  obj->Set(String::NewSymbol("underline_position"), Integer::New(this->face->underline_position));
  obj->Set(String::NewSymbol("underline_thickness"), Integer::New(this->face->underline_thickness));

  std::vector<FT_UInt> acv = this->AvailableCharacters();
  Local<Array> aca = Array::New(acv.size());
  

  FT_ULong chrCode;
  for (size_t i = 0; i < acv.size(); i++) {
    chrCode = acv.at(i);
    aca->Set(i, Integer::New(chrCode));
  }
  obj->Set(String::NewSymbol("available_characters"), aca);
  
  FT_Error err = FT_Set_Char_Size(this->face, 100, 100, 1000, 1000);
  if (FT_HAS_KERNING(this->face) && !err) {
    std::vector< Local<Object> > pairs = this->Kernings( acv );
    Local<Array> kernArray = Array::New(pairs.size());

    Local<Object> pair;
    for (size_t i = 0; i < pairs.size(); i++) {
      pair = pairs.at(i);
      kernArray->Set(i, pair);
    }
    obj->Set(String::NewSymbol("kerning"), kernArray);
  }
}

std::vector< Local<Object> > FontFace::Kernings( std::vector<FT_UInt> acv ) {
  std::vector< Local<Object> > kernPairs;

  FT_ULong chrIndex;
  FT_ULong chrCode;
  FT_ULong otherIndex;
  FT_ULong otherCode;
  for (size_t i = 0; i < acv.size(); i++) {
    chrCode = acv.at(i);
    chrIndex = FT_Get_Char_Index(this->face, chrCode);

    //for testing..
    // if (chrCode < 32 || chrCode > 127)
    //   continue;

    for (size_t j = 0; j < acv.size(); j++) {
      otherCode = acv.at(j);

      // if (chrCode < 32 || chrCode > 127)
      //   continue;
      
      otherIndex = FT_Get_Char_Index(this->face, otherCode);
      
      FT_Vector kerning;
      FT_Error error = FT_Get_Kerning(this->face, chrIndex, otherIndex, FT_KERNING_UNSCALED, &kerning);

      if (error || kerning.x == 0) 
        continue;

      Local<Object> obj = Object::New();
      obj->Set(NanSymbol("left"), Integer::New(chrCode));
      obj->Set(NanSymbol("right"), Integer::New(otherCode));
      obj->Set(NanSymbol("value"), Integer::New(kerning.x));
      kernPairs.push_back( obj );
    }
  }

  return kernPairs;
}

std::vector<FT_UInt> FontFace::AvailableCharacters() {
  FT_ULong charcode;
  FT_UInt gindex;
  std::vector<FT_UInt> charVect;

  charcode = FT_Get_First_Char(this->face, &gindex);
  while (gindex != 0) {
    charVect.push_back(charcode);
    charcode = FT_Get_Next_Char(this->face, charcode, &gindex);
  }

  return charVect;
}
