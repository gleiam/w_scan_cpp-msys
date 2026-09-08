/*
 * msys/font_jpeg_stub.cpp: MSYS-Stubs fuer font.o (freetype/fontconfig/fribidi
 * nicht im msys-Repo) und RgbToJpeg (libjpeg fehlt).
 *
 * Der Scanner (SAT>IP-only) nutzt weder OSD/Menus noch JPEG-Debug-Ausgabe;
 * alle Stubs sind No-Ops, die nur das Linken ermoeglichen.
 */
#include "font.h"
#include "tools.h"

// --- Default-Fontnamen (identisch zu vdr/font.c) ---------------------------
const char *DefaultFontOsd = "Sans Serif:Bold";
const char *DefaultFontSml = "Sans Serif";
const char *DefaultFontFix = "Courier:Bold";

// --- Dummy-Font ------------------------------------------------------------
class cMsysDummyFont : public cFont {
private:
  int height;
public:
  cMsysDummyFont(int Height = 0) : height(Height) {}
  int Width(void) const override { return 0; }
  int Width(uint c) const override { (void)c; return 0; }
  int Width(const char *s) const override { (void)s; return 0; }
  int Height(void) const override { return height; }
  void DrawText(cBitmap *Bitmap, int x, int y, const char *s, tColor ColorFg, tColor ColorBg, int Width) const override
  { (void)Bitmap; (void)x; (void)y; (void)s; (void)ColorFg; (void)ColorBg; (void)Width; }
  void DrawText(cPixmap *Pixmap, int x, int y, const char *s, tColor ColorFg, tColor ColorBg, int Width) const override
  { (void)Pixmap; (void)x; (void)y; (void)s; (void)ColorFg; (void)ColorBg; (void)Width; }
};

static cMsysDummyFont msysDummyFont;

cFont *cFont::fonts[eDvbFontSize] = { NULL };

void cFont::SetFont(eDvbFont Font, const char *Name, int CharHeight)
{
  (void)Name; (void)CharHeight;
  if (Font >= 0 && Font < eDvbFontSize && !fonts[Font])
     fonts[Font] = &msysDummyFont;
}

const cFont *cFont::GetFont(eDvbFont Font)
{
  if (Font >= 0 && Font < eDvbFontSize) {
     if (!fonts[Font])
        fonts[Font] = &msysDummyFont;
     return fonts[Font];
     }
  return &msysDummyFont;
}

cFont *cFont::CreateFont(const char *Name, int CharHeight, int CharWidth)
{
  (void)Name; (void)CharWidth;
  return new cMsysDummyFont(CharHeight);
}

bool cFont::GetAvailableFontNames(cStringList *FontNames, bool Monospaced)
{
  (void)FontNames; (void)Monospaced;
  return false;
}

cString cFont::GetFontFileName(const char *FontName)
{
  (void)FontName;
  return cString("");
}

// --- cTextWrapper minimal (nur Zeilen-Split, kein Wrapping) ----------------
cTextWrapper::cTextWrapper(void)
{
  text = eol = NULL;
  lines = 0;
  lastLine = -1;
}

cTextWrapper::cTextWrapper(const char *Text, const cFont *Font, int Width)
{
  (void)Font; (void)Width;
  text = NULL;
  Set(Text, Font, Width);
}

cTextWrapper::~cTextWrapper()
{
  free(text);
}

void cTextWrapper::Set(const char *Text, const cFont *Font, int Width)
{
  (void)Font; (void)Width;
  free(text);
  text = Text ? strdup(Text) : NULL;
  eol = NULL;
  lines = 0;
  lastLine = -1;
  if (!text)
     return;
  lines = 1;
  for (const char *p = text; *p; p++) {
      if (*p == '\n')
         lines++;
      }
}

const char *cTextWrapper::Text(void)
{
  if (eol) {
     *eol = '\n';
     eol = NULL;
     }
  return text;
}

const char *cTextWrapper::GetLine(int Line)
{
  char *s = NULL;
  if (Line < lines) {
     if (eol) {
        *eol = '\n';
        if (Line == lastLine + 1)
           s = eol + 1;
        eol = NULL;
        }
     if (!s) {
        s = text;
        for (int i = 0; i < Line; i++) {
            s = strchr(s, '\n');
            if (s)
               s++;
            else
               break;
            }
        }
     if (s) {
        char *e = strchr(s, '\n');
        if (e) {
           eol = e;
           lastLine = Line;
           *eol = '\0';
           }
        }
     }
  return s;
}

// --- RgbToJpeg-Stub (libjpeg fehlt; nur Debug-Ausgabe in dvbsubtitle.c) ----
uchar *RgbToJpeg(uchar *Mem, int Width, int Height, int &Size, int Quality)
{
  (void)Mem; (void)Width; (void)Height; (void)Quality;
  Size = 0;
  return NULL;
}
