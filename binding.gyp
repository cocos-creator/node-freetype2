{
  'targets': [
    {
      'target_name': 'freetype2',
      'dependencies': [
        'gyp/libfreetype.gyp:libfreetype'
      ],
      'sources': [
        'src/init.cc',
        'src/FreeType2.cc',
        'src/FontFace.cc',
        'src/Glyph.cc',
      ],
      'include_dirs' : [
        "<!(node -e \"require('nan')\")"
      ],
      'conditions': [
          [ 'OS=="mac"', {
              'xcode_settings': {
                  'OTHER_CPLUSPLUSFLAGS' : ['-std=c++11', '-Wno-c++11-narrowing'],
              },
          }],
      ],
    }
  ]
}

