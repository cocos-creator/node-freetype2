#include "FreeType2.h"
#include "FontFace.h"
#include "ftglyph.h"
#include "ftoutln.h"
#include "ftsnames.h"
#include "ttnameid.h"

void FreeType2::Init(v8::Handle<v8::Object> exports) {
  NanScope();

  FT_Init_FreeType(&library);

  FontFace::Init(exports);
  Glyph::Init(exports);

  char version[32];
  sprintf(version, "%i.%i.%i", FREETYPE_MAJOR, FREETYPE_MINOR, FREETYPE_PATCH);
  exports->Set(NanNew<v8::String>("version"), NanNew<v8::String>(version));

  NODE_SET_METHOD(exports, "New_Memory_Face", New_Memory_Face);
  NODE_SET_METHOD(exports, "Select_Size", Select_Size);
  NODE_SET_METHOD(exports, "Request_Size", Request_Size);
  NODE_SET_METHOD(exports, "Set_Char_Size", Set_Char_Size);
  NODE_SET_METHOD(exports, "Set_Pixel_Sizes", Set_Pixel_Sizes);
  NODE_SET_METHOD(exports, "Load_Glyph", Load_Glyph);
  NODE_SET_METHOD(exports, "Load_Char", Load_Char);
  // NODE_SET_METHOD(exports, "Set_Transform", Set_Transform);
  NODE_SET_METHOD(exports, "Render_Glyph", Render_Glyph);
  NODE_SET_METHOD(exports, "Get_Kerning", Get_Kerning);
  // NODE_SET_METHOD(exports, "Get_Track_Kerning", Get_Track_Kerning);
  // NODE_SET_METHOD(exports, "Get_Glyph_Name", Get_Glyph_Name);
  // NODE_SET_METHOD(exports, "Get_Postscript_Name", Get_Postscript_Name);
  NODE_SET_METHOD(exports, "Select_Charmap", Select_Charmap);
  NODE_SET_METHOD(exports, "Set_Charmap", Set_Charmap);
  NODE_SET_METHOD(exports, "Get_Charmap_Index", Get_Charmap_Index);
  NODE_SET_METHOD(exports, "Get_Char_Index", Get_Char_Index);
  NODE_SET_METHOD(exports, "Get_First_Char", Get_First_Char);
  NODE_SET_METHOD(exports, "Get_Next_Char", Get_Next_Char);
  NODE_SET_METHOD(exports, "Outline_Decompose", Outline_Decompose);
  NODE_SET_METHOD(exports, "Get_Sfnt_Name_Count", Get_Sfnt_Name_Count);
  NODE_SET_METHOD(exports, "Get_Sfnt_Name", Get_Sfnt_Name);
  NODE_SET_METHOD(exports, "Get_Sfnt_Full_Name", Get_Sfnt_Full_Name);
  
  // NODE_SET_METHOD(exports, "Get_Name_Index", Get_Name_Index);
  // NODE_SET_METHOD(exports, "Get_SubGlyph_Info", Get_SubGlyph_Info);

  // http://www.freetype.org/freetype2/docs/reference/ft2-base_interface.html#FT_Encoding
  exports->Set(NanNew<v8::String>("ENCODING_NONE"), NanNew<v8::Integer>(FT_ENCODING_NONE));
  exports->Set(NanNew<v8::String>("ENCODING_MS_SYMBOL"), NanNew<v8::Integer>(FT_ENCODING_MS_SYMBOL));
  exports->Set(NanNew<v8::String>("ENCODING_UNICODE"), NanNew<v8::Integer>(FT_ENCODING_UNICODE));
  exports->Set(NanNew<v8::String>("ENCODING_SJIS"), NanNew<v8::Integer>(FT_ENCODING_SJIS));
  exports->Set(NanNew<v8::String>("ENCODING_GB2312"), NanNew<v8::Integer>(FT_ENCODING_GB2312));
  exports->Set(NanNew<v8::String>("ENCODING_BIG5"), NanNew<v8::Integer>(FT_ENCODING_BIG5));
  exports->Set(NanNew<v8::String>("ENCODING_WANSUNG"), NanNew<v8::Integer>(FT_ENCODING_WANSUNG));
  exports->Set(NanNew<v8::String>("ENCODING_JOHAB"), NanNew<v8::Integer>(FT_ENCODING_JOHAB));
  exports->Set(NanNew<v8::String>("ENCODING_ADOBE_STANDARD"), NanNew<v8::Integer>(FT_ENCODING_ADOBE_STANDARD));
  exports->Set(NanNew<v8::String>("ENCODING_ADOBE_EXPERT"), NanNew<v8::Integer>(FT_ENCODING_ADOBE_EXPERT));
  exports->Set(NanNew<v8::String>("ENCODING_ADOBE_CUSTOM"), NanNew<v8::Integer>(FT_ENCODING_ADOBE_CUSTOM));
  exports->Set(NanNew<v8::String>("ENCODING_ADOBE_LATIN_1"), NanNew<v8::Integer>(FT_ENCODING_ADOBE_LATIN_1));
  exports->Set(NanNew<v8::String>("ENCODING_OLD_LATIN_2"), NanNew<v8::Integer>(FT_ENCODING_OLD_LATIN_2));
  exports->Set(NanNew<v8::String>("ENCODING_APPLE_ROMAN"), NanNew<v8::Integer>(FT_ENCODING_APPLE_ROMAN));

  // http://www.freetype.org/freetype2/docs/reference/ft2-base_interface.html#FT_LOAD_XXX
  exports->Set(NanNew<v8::String>("LOAD_DEFAULT"), NanNew<v8::Integer>(FT_LOAD_DEFAULT));
  exports->Set(NanNew<v8::String>("LOAD_NO_SCALE"), NanNew<v8::Integer>(FT_LOAD_NO_SCALE));
  exports->Set(NanNew<v8::String>("LOAD_NO_HINTING"), NanNew<v8::Integer>(FT_LOAD_NO_HINTING));
  exports->Set(NanNew<v8::String>("LOAD_RENDER"), NanNew<v8::Integer>(FT_LOAD_RENDER));
  exports->Set(NanNew<v8::String>("LOAD_NO_BITMAP"), NanNew<v8::Integer>(FT_LOAD_NO_BITMAP));
  exports->Set(NanNew<v8::String>("LOAD_VERTICAL_LAYOUT"), NanNew<v8::Integer>(FT_LOAD_VERTICAL_LAYOUT));
  exports->Set(NanNew<v8::String>("LOAD_FORCE_AUTOHINT"), NanNew<v8::Integer>(FT_LOAD_FORCE_AUTOHINT));
  exports->Set(NanNew<v8::String>("LOAD_CROP_BITMAP"), NanNew<v8::Integer>(FT_LOAD_CROP_BITMAP));
  exports->Set(NanNew<v8::String>("LOAD_PEDANTIC"), NanNew<v8::Integer>(FT_LOAD_PEDANTIC));
  exports->Set(NanNew<v8::String>("LOAD_IGNORE_GLOBAL_ADVANCE_WIDTH"), NanNew<v8::Integer>(FT_LOAD_IGNORE_GLOBAL_ADVANCE_WIDTH));
  exports->Set(NanNew<v8::String>("LOAD_NO_RECURSE"), NanNew<v8::Integer>(FT_LOAD_NO_RECURSE));
  exports->Set(NanNew<v8::String>("LOAD_IGNORE_TRANSFORM"), NanNew<v8::Integer>(FT_LOAD_IGNORE_TRANSFORM));
  exports->Set(NanNew<v8::String>("LOAD_MONOCHROME"), NanNew<v8::Integer>(FT_LOAD_MONOCHROME));
  exports->Set(NanNew<v8::String>("LOAD_LINEAR_DESIGN"), NanNew<v8::Integer>(FT_LOAD_LINEAR_DESIGN));
  exports->Set(NanNew<v8::String>("LOAD_NO_AUTOHINT"), NanNew<v8::Integer>(FT_LOAD_NO_AUTOHINT));
  exports->Set(NanNew<v8::String>("LOAD_COLOR"), NanNew<v8::Integer>(FT_LOAD_COLOR));

  // http://www.freetype.org/freetype2/docs/reference/ft2-base_interface.html#FT_Kerning_Mode
  exports->Set(NanNew<v8::String>("KERNING_DEFAULT"), NanNew<v8::Integer>(FT_KERNING_DEFAULT));
  exports->Set(NanNew<v8::String>("KERNING_UNFITTED"), NanNew<v8::Integer>(FT_KERNING_UNFITTED));
  exports->Set(NanNew<v8::String>("KERNING_UNSCALED"), NanNew<v8::Integer>(FT_KERNING_UNSCALED));

  // http://www.freetype.org/freetype2/docs/reference/ft2-base_interface.html#FT_FACE_FLAG_XXX
  exports->Set(NanNew<v8::String>("FACE_FLAG_SCALABLE"), NanNew<v8::Integer>(FT_FACE_FLAG_SCALABLE));
  exports->Set(NanNew<v8::String>("FACE_FLAG_FIXED_SIZES"), NanNew<v8::Integer>(FT_FACE_FLAG_FIXED_SIZES));
  exports->Set(NanNew<v8::String>("FACE_FLAG_FIXED_WIDTH"), NanNew<v8::Integer>(FT_FACE_FLAG_FIXED_WIDTH));
  exports->Set(NanNew<v8::String>("FACE_FLAG_SFNT"), NanNew<v8::Integer>(FT_FACE_FLAG_SFNT));
  exports->Set(NanNew<v8::String>("FACE_FLAG_HORIZONTAL"), NanNew<v8::Integer>(FT_FACE_FLAG_HORIZONTAL));
  exports->Set(NanNew<v8::String>("FACE_FLAG_VERTICAL"), NanNew<v8::Integer>(FT_FACE_FLAG_VERTICAL));
  exports->Set(NanNew<v8::String>("FACE_FLAG_KERNING"), NanNew<v8::Integer>(FT_FACE_FLAG_KERNING));
  exports->Set(NanNew<v8::String>("FACE_FLAG_FAST_GLYPHS"), NanNew<v8::Integer>(FT_FACE_FLAG_FAST_GLYPHS));
  exports->Set(NanNew<v8::String>("FACE_FLAG_MULTIPLE_MASTERS"), NanNew<v8::Integer>(FT_FACE_FLAG_MULTIPLE_MASTERS));
  exports->Set(NanNew<v8::String>("FACE_FLAG_GLYPH_NAMES"), NanNew<v8::Integer>(FT_FACE_FLAG_GLYPH_NAMES));
  exports->Set(NanNew<v8::String>("FACE_FLAG_EXTERNAL_STREAM"), NanNew<v8::Integer>(FT_FACE_FLAG_EXTERNAL_STREAM));
  exports->Set(NanNew<v8::String>("FACE_FLAG_HINTER"), NanNew<v8::Integer>(FT_FACE_FLAG_HINTER));
  exports->Set(NanNew<v8::String>("FACE_FLAG_CID_KEYED"), NanNew<v8::Integer>(FT_FACE_FLAG_CID_KEYED));
  exports->Set(NanNew<v8::String>("FACE_FLAG_TRICKY"), NanNew<v8::Integer>(FT_FACE_FLAG_TRICKY));
  exports->Set(NanNew<v8::String>("FACE_FLAG_COLOR"), NanNew<v8::Integer>(FT_FACE_FLAG_COLOR));

  // http://www.freetype.org/freetype2/docs/reference/ft2-base_interface.html#FT_STYLE_FLAG_XXX
  exports->Set(NanNew<v8::String>("STYLE_FLAG_ITALIC"), NanNew<v8::Integer>(FT_STYLE_FLAG_ITALIC));
  exports->Set(NanNew<v8::String>("STYLE_FLAG_BOLD"), NanNew<v8::Integer>(FT_STYLE_FLAG_BOLD));

  // http://www.freetype.org/freetype2/docs/reference/ft2-basic_types.html#FT_Glyph_Format
  exports->Set(NanNew<v8::String>("GLYPH_FORMAT_NONE"), NanNew<v8::Integer>(FT_GLYPH_FORMAT_NONE));
  exports->Set(NanNew<v8::String>("GLYPH_FORMAT_COMPOSITE"), NanNew<v8::Integer>(FT_GLYPH_FORMAT_COMPOSITE));
  exports->Set(NanNew<v8::String>("GLYPH_FORMAT_BITMAP"), NanNew<v8::Integer>(FT_GLYPH_FORMAT_BITMAP));
  exports->Set(NanNew<v8::String>("GLYPH_FORMAT_OUTLINE"), NanNew<v8::Integer>(FT_GLYPH_FORMAT_OUTLINE));
  exports->Set(NanNew<v8::String>("GLYPH_FORMAT_PLOTTER"), NanNew<v8::Integer>(FT_GLYPH_FORMAT_PLOTTER));

  // http://www.freetype.org/freetype2/docs/reference/ft2-base_interface.html#FT_Render_Mode
  exports->Set(NanNew<v8::String>("RENDER_MODE_NORMAL"), NanNew<v8::Integer>(FT_RENDER_MODE_NORMAL));
  exports->Set(NanNew<v8::String>("RENDER_MODE_LIGHT"), NanNew<v8::Integer>(FT_RENDER_MODE_LIGHT));
  exports->Set(NanNew<v8::String>("RENDER_MODE_MONO"), NanNew<v8::Integer>(FT_RENDER_MODE_MONO));
  exports->Set(NanNew<v8::String>("RENDER_MODE_LCD"), NanNew<v8::Integer>(FT_RENDER_MODE_LCD));
  exports->Set(NanNew<v8::String>("RENDER_MODE_LCD_V"), NanNew<v8::Integer>(FT_RENDER_MODE_LCD_V));
  exports->Set(NanNew<v8::String>("RENDER_MODE_MAX"), NanNew<v8::Integer>(FT_RENDER_MODE_MAX));

  // http://www.freetype.org/freetype2/docs/reference/ft2-base_interface.html#FT_FSTYPE_XXX
  exports->Set(NanNew<v8::String>("FSTYPE_INSTALLABLE_EMBEDDING"), NanNew<v8::Integer>(FT_FSTYPE_INSTALLABLE_EMBEDDING));
  exports->Set(NanNew<v8::String>("FSTYPE_RESTRICTED_LICENSE_EMBEDDING"), NanNew<v8::Integer>(FT_FSTYPE_RESTRICTED_LICENSE_EMBEDDING));
  exports->Set(NanNew<v8::String>("FSTYPE_PREVIEW_AND_PRINT_EMBEDDING"), NanNew<v8::Integer>(FT_FSTYPE_PREVIEW_AND_PRINT_EMBEDDING));
  exports->Set(NanNew<v8::String>("FSTYPE_EDITABLE_EMBEDDING"), NanNew<v8::Integer>(FT_FSTYPE_EDITABLE_EMBEDDING));
  exports->Set(NanNew<v8::String>("FSTYPE_NO_SUBSETTING"), NanNew<v8::Integer>(FT_FSTYPE_NO_SUBSETTING));
  exports->Set(NanNew<v8::String>("FSTYPE_BITMAP_EMBEDDING_ONLY"), NanNew<v8::Integer>(FT_FSTYPE_BITMAP_EMBEDDING_ONLY));

  // http://www.freetype.org/freetype2/docs/reference/ft2-basic_types.html#FT_Pixel_Mode
  exports->Set(NanNew<v8::String>("PIXEL_MODE_NONE"), NanNew<v8::Integer>(FT_PIXEL_MODE_NONE));
  exports->Set(NanNew<v8::String>("PIXEL_MODE_MONO"), NanNew<v8::Integer>(FT_PIXEL_MODE_MONO));
  exports->Set(NanNew<v8::String>("PIXEL_MODE_GRAY"), NanNew<v8::Integer>(FT_PIXEL_MODE_GRAY));
  exports->Set(NanNew<v8::String>("PIXEL_MODE_GRAY2"), NanNew<v8::Integer>(FT_PIXEL_MODE_GRAY2));
  exports->Set(NanNew<v8::String>("PIXEL_MODE_GRAY4"), NanNew<v8::Integer>(FT_PIXEL_MODE_GRAY4));
  exports->Set(NanNew<v8::String>("PIXEL_MODE_LCD"), NanNew<v8::Integer>(FT_PIXEL_MODE_LCD));
  exports->Set(NanNew<v8::String>("PIXEL_MODE_LCD_V"), NanNew<v8::Integer>(FT_PIXEL_MODE_LCD_V));
  exports->Set(NanNew<v8::String>("PIXEL_MODE_BGRA"), NanNew<v8::Integer>(FT_PIXEL_MODE_BGRA));

  // http://www.freetype.org/freetype2/docs/reference/ft2-base_interface.html#FT_Size_Request_Type
  exports->Set(NanNew<v8::String>("SIZE_REQUEST_TYPE_NOMINAL"), NanNew<v8::Integer>(FT_SIZE_REQUEST_TYPE_NOMINAL));
  exports->Set(NanNew<v8::String>("SIZE_REQUEST_TYPE_REAL_DIM"), NanNew<v8::Integer>(FT_SIZE_REQUEST_TYPE_REAL_DIM));
  exports->Set(NanNew<v8::String>("SIZE_REQUEST_TYPE_BBOX"), NanNew<v8::Integer>(FT_SIZE_REQUEST_TYPE_BBOX));
  exports->Set(NanNew<v8::String>("SIZE_REQUEST_TYPE_CELL"), NanNew<v8::Integer>(FT_SIZE_REQUEST_TYPE_CELL));
  exports->Set(NanNew<v8::String>("SIZE_REQUEST_TYPE_SCALES"), NanNew<v8::Integer>(FT_SIZE_REQUEST_TYPE_SCALES));
}

FreeType2::~FreeType2() {
  FT_Done_FreeType(library);
}

NAN_METHOD(FreeType2::New_Memory_Face) {
  NanScope();
  FT_Face ftFace;
  FT_New_Memory_Face(library,
                     (FT_Byte*)node::Buffer::Data(args[0]->ToObject()),
                     (FT_Long)node::Buffer::Length(args[0]->ToObject()),
                     args[1]->Int32Value(),
                     &ftFace);
  v8::Handle<v8::Object> faceObj = NanNew(FontFace::constructor)->NewInstance();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(faceObj);
  fontFace->ftFace = ftFace;
  NanReturnValue(faceObj);
}

NAN_METHOD(FreeType2::Select_Size) {
  NanScope();
  if (args[0]->IsUndefined()) {
    NanReturnUndefined();
  }
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(v8::Handle<v8::Object>::Cast(args[0]));
  FT_Select_Size(fontFace->ftFace, args[1]->Int32Value());
  NanReturnUndefined();
}

NAN_METHOD(FreeType2::Request_Size) {
  NanScope();
  if (args[0]->IsUndefined()) {
    NanReturnUndefined();
  }
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(v8::Handle<v8::Object>::Cast(args[0]));
  FT_Size_RequestRec req = {
    static_cast<FT_Size_Request_Type>(args[1]->Int32Value()),
    args[2]->Int32Value(),
    args[3]->Int32Value(),
    args[4]->Int32Value(),
    args[5]->Int32Value()
  };
  FT_Request_Size(fontFace->ftFace, &req);
  NanReturnUndefined();
}

NAN_METHOD(FreeType2::Set_Char_Size) {
  NanScope();
  if (args[0]->IsUndefined()) {
    NanReturnUndefined();
  }
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(v8::Handle<v8::Object>::Cast(args[0]));
  FT_Set_Char_Size(fontFace->ftFace,
                   args[1]->Int32Value(),
                   args[2]->Int32Value(),
                   args[3]->Int32Value(),
                   args[4]->Int32Value());
  NanReturnUndefined();
}

NAN_METHOD(FreeType2::Set_Pixel_Sizes) {
  NanScope();
  if (args[0]->IsUndefined()) {
    NanReturnUndefined();
  }
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(v8::Handle<v8::Object>::Cast(args[0]));
  FT_Set_Pixel_Sizes(fontFace->ftFace, args[1]->Uint32Value(), args[2]->Uint32Value());
  NanReturnUndefined();
}

NAN_METHOD(FreeType2::Load_Glyph) {
  NanScope();
  if (args[0]->IsUndefined()) {
    NanReturnUndefined();
  }
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(v8::Handle<v8::Object>::Cast(args[0]));
  FT_Load_Glyph(fontFace->ftFace, args[1]->Int32Value(), args[2]->Int32Value());
  NanReturnUndefined();
}

NAN_METHOD(FreeType2::Load_Char) {
  NanScope();
  if (args[0]->IsUndefined()) {
    NanReturnUndefined();
  }
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(v8::Handle<v8::Object>::Cast(args[0]));
  FT_Error err = FT_Load_Char(fontFace->ftFace, args[1]->Int32Value(), args[2]->Int32Value());
  NanReturnValue(NanNew<v8::Integer>(err));
}

NAN_METHOD(FreeType2::Get_Kerning) {
  NanScope();
  if (args[0]->IsUndefined() || args[4]->IsUndefined()) {
    NanReturnUndefined();
  }
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(v8::Handle<v8::Object>::Cast(args[0]));
  FT_Vector kerning;
  FT_Error err = FT_Get_Kerning(fontFace->ftFace,
                   args[1]->Int32Value(),  //left_glyph 
                   args[2]->Int32Value(),  //right_glyph
                   args[3]->Int32Value(),  //kern_mode
                   &kerning);              //kerning
  if (!err) {
    v8::Handle<v8::Object>::Cast(args[4])->Set(NanNew<v8::String>("x"), NanNew<v8::Integer>(kerning.x));
    v8::Handle<v8::Object>::Cast(args[4])->Set(NanNew<v8::String>("y"), NanNew<v8::Integer>(kerning.y));
  }
  NanReturnValue(NanNew<v8::Integer>(err));
}

NAN_METHOD(FreeType2::Render_Glyph) {
  NanScope();
  if (args[0]->IsUndefined()) {
    NanReturnUndefined();
  }
  Glyph* glyph = node::ObjectWrap::Unwrap<Glyph>(v8::Handle<v8::Object>::Cast(args[0]));
  FT_Render_Glyph(glyph->ftGlyph, static_cast<FT_Render_Mode>(args[1]->Int32Value()));
  NanReturnUndefined();
}

NAN_METHOD(FreeType2::Select_Charmap) {
  NanScope();
  if (args[0]->IsUndefined()) {
    NanReturnUndefined();
  }
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(v8::Handle<v8::Object>::Cast(args[0]));
  FT_Select_Charmap(fontFace->ftFace, static_cast<FT_Encoding>(args[1]->Int32Value()));
  NanReturnUndefined();
}

NAN_METHOD(FreeType2::Set_Charmap) {
  NanScope();
  if (args[0]->IsUndefined()) {
    NanReturnUndefined();
  }
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(v8::Handle<v8::Object>::Cast(args[0]));
  FT_Set_Charmap(fontFace->ftFace, fontFace->ftFace->charmaps[args[1]->Int32Value()]);
  NanReturnUndefined();
}

NAN_METHOD(FreeType2::Get_Charmap_Index) {
  NanScope();
  if (args[0]->IsUndefined()) {
    NanReturnUndefined();
  }
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(v8::Handle<v8::Object>::Cast(args[0]));
  NanReturnValue(NanNew<v8::Integer>(FT_Get_Charmap_Index(fontFace->ftFace->charmap)));
}

NAN_METHOD(FreeType2::Get_Char_Index) {
  NanScope();
  if (args[0]->IsUndefined()) {
	NanReturnUndefined();
  }
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(v8::Handle<v8::Object>::Cast(args[0]));
  NanReturnValue(NanNew<v8::Integer>(FT_Get_Char_Index(fontFace->ftFace, args[1]->Int32Value())));
}

NAN_METHOD(FreeType2::Get_First_Char) {
  NanScope();
  if (args[0]->IsUndefined()) {
    NanReturnUndefined();
  }
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(v8::Handle<v8::Object>::Cast(args[0]));
  FT_UInt gindex;
  FT_ULong charcode = FT_Get_First_Char(fontFace->ftFace, &gindex);
  v8::Handle<v8::Object>::Cast(args[1])->Set(NanNew<v8::String>("gindex"), NanNew<v8::Integer>(gindex));
  NanReturnValue(NanNew<v8::Integer>(charcode));
}

NAN_METHOD(FreeType2::Get_Next_Char) {
  NanScope();
  if (args[0]->IsUndefined()) {
    NanReturnUndefined();
  }
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(v8::Handle<v8::Object>::Cast(args[0]));
  FT_UInt gindex;
  FT_ULong charcode = FT_Get_Next_Char(fontFace->ftFace, args[1]->Int32Value(), &gindex);
  v8::Handle<v8::Object>::Cast(args[2])->Set(NanNew<v8::String>("gindex"), NanNew<v8::Integer>(gindex));
  NanReturnValue(NanNew<v8::Integer>(charcode));
}

typedef struct OutlineContext {
  v8::Handle<v8::Object> functions;
} OutlineContext;

NAN_METHOD(FreeType2::Outline_Decompose) {
  NanScope();
  if (args[0]->IsUndefined()) {
    NanReturnUndefined();
  }
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(v8::Handle<v8::Object>::Cast(args[0]));
  
  FT_Outline_Funcs outline_funcs;
  outline_funcs.shift = 0;
  outline_funcs.delta = 0;
  outline_funcs.move_to = move_to;
  outline_funcs.line_to = line_to;
  outline_funcs.conic_to = quad_to;
  outline_funcs.cubic_to = cubic_to;

  OutlineContext context;
  context.functions = v8::Handle<v8::Object>::Cast(args[1]);

  FT_Glyph glyph;
  FT_Error getErr = FT_Get_Glyph( fontFace->ftFace->glyph, &glyph );
  if (getErr) {
    NanReturnValue(NanNew<v8::Integer>(getErr));  
  } else if (fontFace->ftFace->glyph->format != FT_GLYPH_FORMAT_OUTLINE) {
    NanReturnValue(NanNew<v8::Integer>(1)); //error, font doesn't have outline format
  } else {
    FT_OutlineGlyph outline_glyph = (FT_OutlineGlyph)glyph;
    FT_Error outErr = FT_Outline_Decompose(&outline_glyph->outline, &outline_funcs, &context );
    FT_Done_Glyph( glyph );
    NanReturnValue(NanNew<v8::Integer>(outErr));
  }
}

NAN_METHOD(FreeType2::Get_Sfnt_Name_Count) {
  NanScope();
  if (args.Length() < 1 || args[0]->IsUndefined()) {
    NanReturnUndefined();
  }
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(v8::Handle<v8::Object>::Cast(args[0]));
  NanReturnValue(NanNew<v8::Integer>(FT_Get_Sfnt_Name_Count(fontFace->ftFace)));
}

NAN_METHOD(FreeType2::Get_Sfnt_Name) {
  NanScope();
  if (args.Length() < 2 || args[0]->IsUndefined()) {
    NanReturnUndefined();
  }
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(v8::Handle<v8::Object>::Cast(args[0]));
  int index = args[1]->Int32Value();
  FT_SfntName data;
  if (FT_Get_Sfnt_Name(fontFace->ftFace, index, &data) == FT_Err_Ok) {
    v8::Local<v8::String> name = v8::String::NewFromOneByte(v8::Isolate::GetCurrent(), 
                                                            data.string, 
															v8::String::NewStringType::kNormalString,
                                                            data.string_len);

	v8::Handle<v8::Object> retval = NanNew<v8::Object>();
    retval->Set(NanNew<v8::String>("platform_id"), NanNew<v8::Integer>(data.platform_id));
    retval->Set(NanNew<v8::String>("encoding_id"), NanNew<v8::Integer>(data.encoding_id));
    retval->Set(NanNew<v8::String>("language_id"), NanNew<v8::Integer>(data.language_id));
    retval->Set(NanNew<v8::String>("name_id"), NanNew<v8::Integer>(data.name_id));
    retval->Set(NanNew<v8::String>("string"), name);
    NanReturnValue(retval);
  }
  NanReturnNull();
}

NAN_METHOD(FreeType2::Get_Sfnt_Full_Name) {
  NanScope();
  if (args.Length() < 3 || args[0]->IsUndefined()) {
    NanReturnUndefined();
  }
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(v8::Handle<v8::Object>::Cast(args[0]));
  int platformId = args[1]->Int32Value();
  int languageId = args[2]->Int32Value();
  FT_SfntName data;
  int nameCount = FT_Get_Sfnt_Name_Count(fontFace->ftFace);
  for (int i = 0; i < nameCount; ++i) {
    if (FT_Get_Sfnt_Name(fontFace->ftFace, i, &data) == FT_Err_Ok && data.name_id == TT_NAME_ID_FULL_NAME
                                                                  && data.language_id == languageId) {
      bool isUcs2be = data.string_len % 2 == 0
                    && ( (data.platform_id == TT_PLATFORM_APPLE_UNICODE && data.encoding_id <= TT_APPLE_ID_UNICODE_2_0)
                      || (data.platform_id == TT_PLATFORM_MICROSOFT && data.encoding_id == TT_MS_ID_UNICODE_CS)
                      || (data.platform_id == TT_PLATFORM_ISO && data.encoding_id == TT_ISO_ID_10646)
                       );
      if (isUcs2be) {
        // convert to little endian
        for (int i = 0; i < data.string_len; i += 2) {
          FT_Byte c = data.string[i];
          data.string[i] = data.string[i + 1];
          data.string[i + 1] = c;
        }
        v8::Local<v8::String> name = v8::String::NewFromOneByte(v8::Isolate::GetCurrent(), 
                                                                data.string, 
                                                                v8::String::NewStringType::kNormalString, 
                                                                data.string_len);
		v8::Handle<v8::Object> retval = NanNew<v8::Object>();
        retval->Set(NanNew<v8::String>("encoding"), NanNew<v8::String>("ucs2"));
        retval->Set(NanNew<v8::String>("name"), name);
        NanReturnValue(retval);
      }

      bool isAscii = (data.platform_id == TT_PLATFORM_MACINTOSH && data.encoding_id == TT_MAC_ID_ROMAN)
                  || (data.platform_id == TT_PLATFORM_ISO && (data.encoding_id == TT_ISO_ID_7BIT_ASCII || data.encoding_id == TT_ISO_ID_8859_1));
      if (isAscii) {
        v8::Local<v8::String> name = v8::String::NewFromOneByte(v8::Isolate::GetCurrent(), 
                                                                data.string, 
                                                                v8::String::NewStringType::kNormalString, 
                                                                data.string_len);
		v8::Handle<v8::Object> retval = NanNew<v8::Object>();
        retval->Set(NanNew<v8::String>("encoding"), NanNew<v8::String>("ascii"));
        retval->Set(NanNew<v8::String>("name"), name);
        NanReturnValue(retval);
      }
    }
  }
  // unsupported encoding
  NanReturnNull();
}




int FreeType2::move_to(const FT_Vector* to, void *p) {
  OutlineContext *context = (OutlineContext*)p;

  v8::Handle<v8::Object> funcs = v8::Handle<v8::Object>::Cast(context->functions);
  if (funcs->IsObject() && funcs->Has(NanNew<v8::String>("move_to"))) {
    v8::Handle<v8::Value> fn = funcs->Get(NanNew<v8::String>("move_to"));
    if (!fn->IsFunction()) {
      NanThrowError(("move_to for Outline_Decompose must be a function"));
      return 1;
    }
    v8::Handle<v8::Value> args[2];
    args[0] = NanNew<v8::Integer>(to->x);
    args[1] = NanNew<v8::Integer>(to->y);

	v8::Handle<v8::Function>::Cast(fn)->Call(NanGetCurrentContext()->Global(), 2, args);
    return 0;
  } else {
    NanThrowError(("must define a move_to() function for Outline_Decompose"));
    return 1;
  }
}

int FreeType2::line_to(const FT_Vector* to, void *p) {
  OutlineContext *context = (OutlineContext*)p;
  
  v8::Handle<v8::Object> funcs = v8::Handle<v8::Object>::Cast(context->functions);
  if (funcs->IsObject() && funcs->Has(NanNew<v8::String>("line_to"))) {
    v8::Handle<v8::Value> fn = funcs->Get(NanNew<v8::String>("line_to"));
    if (!fn->IsFunction()) {
      NanThrowError(("line_to for Outline_Decompose must be a function"));
      return 1;
    }
    v8::Handle<v8::Value> args[2];
    args[0] = NanNew<v8::Integer>(to->x);
    args[1] = NanNew<v8::Integer>(to->y);

    v8::Handle<v8::Function>::Cast(fn)->Call( NanGetCurrentContext()->Global(), 2, args );
    return 0;
  } else {
    NanThrowError(("must define a line_to() function for Outline_Decompose"));
    return 1;
  }
}

int FreeType2::quad_to(const FT_Vector*  cp, const FT_Vector*  to, void *p) {
  OutlineContext *context = (OutlineContext*)p;
  
  v8::Handle<v8::Object> funcs = v8::Handle<v8::Object>::Cast(context->functions);
  if (funcs->IsObject() && funcs->Has(NanNew<v8::String>("quad_to"))) {
    v8::Handle<v8::Value> fn = funcs->Get(NanNew<v8::String>("quad_to"));
    if (!fn->IsFunction()) {
      NanThrowError(("quad_to for Outline_Decompose must be a function"));
      return 1;
    }
    v8::Handle<v8::Value> args[4];
    args[0] = NanNew<v8::Integer>(cp->x);
    args[1] = NanNew<v8::Integer>(cp->y);
    args[2] = NanNew<v8::Integer>(to->x);
    args[3] = NanNew<v8::Integer>(to->y);

    v8::Handle<v8::Function>::Cast(fn)->Call( NanGetCurrentContext()->Global(), 4, args );
    return 0;
  } else {
    NanThrowError(("must define a quad_to() function for Outline_Decompose"));
    return 1;
  }
}

int FreeType2::cubic_to(const FT_Vector*  cp1,
         const FT_Vector*  cp2,
         const FT_Vector*  to,
         void *p) {
  OutlineContext *context = (OutlineContext*)p;
  v8::Handle<v8::Object> funcs = v8::Handle<v8::Object>::Cast(context->functions);
  if (funcs->IsObject() && funcs->Has(NanNew<v8::String>("cubic_to"))) {
    v8::Handle<v8::Value> fn = funcs->Get(NanNew<v8::String>("cubic_to"));
    if (!fn->IsFunction()) {
      NanThrowError(("cubic_to for Outline_Decompose must be a function"));
      return 1;
    }
    v8::Handle<v8::Value> args[6];
    args[0] = NanNew<v8::Integer>(cp1->x);
    args[1] = NanNew<v8::Integer>(cp1->y);
    args[2] = NanNew<v8::Integer>(cp2->x);
    args[3] = NanNew<v8::Integer>(cp2->y);
    args[4] = NanNew<v8::Integer>(to->x);
    args[5] = NanNew<v8::Integer>(to->y);

    v8::Handle<v8::Function>::Cast(fn)->Call( NanGetCurrentContext()->Global(), 6, args );
    return 0;
  } else {
    NanThrowError(("must define a cubic_to() function for Outline_Decompose"));
    return 1;
  }
}

FT_Library FreeType2::library;
