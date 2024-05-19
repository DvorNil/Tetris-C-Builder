//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <algorithm>
#include <chrono>
#include <ctime>
#include <fstream>
#include <thread>
#include <vector>

#include "Unit1.h"
using namespace std;
using namespace std::this_thread;  // sleep_for, sleep_until
using namespace std::chrono;       // nan

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent *Owner) : TForm(Owner) {}
//---------------------------------------------------------------------------
Graphics::TBitmap *bl = new Graphics::TBitmap();
Graphics::TBitmap *bla = new Graphics::TBitmap();
int fig;
bool youlost = 0;
int skin = 0;
int x = 0, y = 0;
const int cs = 10;
int cur_interval = 400;
int score = 0;
const int rs = 20;
bool ifstolk = 0;
vector<vector<int>> field(cs + 3, vector<int>(rs + 1));
vector<vector<int>> exfield(4, vector<int>(4));
vector<vector<int>> figfield(4, vector<int>(4));
vector <vector <vector <int>>> figd =
{
	{{0,0,0,0},
	{1,1,1,0},
	{1,0,0,0},
	{0,0,0,0}},

	{{0,0,0,0},
	{0,1,1,1},
	{0,0,0,1},
	{0,0,0,0}},

	{{0,0,0,0},
	{0,1,1,0},
	{1,1,0,0},
	{0,0,0,0}},

	{{0,0,0,0},
	{1,1,0,0},
	{0,1,1,0},
	{0,0,0,0}},

	{{0,0,0,0},
	{0,1,0,0},
	{1,1,1,0},
	{0,0,0,0}},

	{{0,0,0,0},
	{1,1,1,1},
	{0,0,0,0},
	{0,0,0,0}},

	{{0,0,0,0},
	{0,1,1,0},
	{0,1,1,0},
	{0,0,0,0}}
};
	

void __fastcall TForm1::randomize() {
  srand(time(NULL));
  int ch = rand() % 7;
  exfield = figd[ch];
  ExtraField->Repaint();
}

void __fastcall TForm1::HideAll() {
  Field->Visible = 0;
  ExtraField->Visible = 0;
  Button6->Visible = 0;
  Label1->Visible = 0;
  Label2->Visible = 0;
  Image1->Visible = 1;
  Button7->Visible = 1;
}

void __fastcall TForm1::ShowAll() {
  Field->Visible = 1;
  ExtraField->Visible = 1;
  Button6->Visible = 1;
  Label1->Visible = 1;
  Label2->Visible = 1;
  Image1->Visible = 0;
  Button7->Visible = 0;
}

void __fastcall TForm1::FigureCreate() {
  x = 3;
  y = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (exfield[i][j] && field[i + x][j]) {
        if (!youlost) {
          HideAll();
        }
        Timer1->Enabled = 0;
        youlost = 1;
      }
      if (exfield[i][j]) field[i + x][j] = 1;
    }
  }
  figfield = exfield;
  randomize();
  Field->Repaint();
}

void __fastcall TForm1::FigureRotate() {
  vector<vector<int>> tfield = figfield;
  vector<vector<int>> t1field = figfield;
  bool possible = 1;

  for (int i = 3; i >= 0; i--)
    for (int j = 3; j >= 0; j--) tfield[i][j] = figfield[3 - j][i];
  for (int i = 3; i >= 0; i--)
    for (int j = 3; j >= 0; j--) t1field[i][j] = field[x + i][y + j];

  for (int i = 3; i >= 0; i--) {
    for (int j = 3; j >= 0; j--) {
      if (tfield[i][j] == 1) {
        if (field[x + i][y + j] >= 2) {
          possible = 0;
          break;
        }
        field[x + i][y + j] = tfield[i][j];
      } else {
        if (field[x + i][y + j] == 1) field[x + i][y + j] = 0;
      }
    }
  }

  if (!possible) {
    for (int i = 3; i >= 0; i--)
      for (int j = 3; j >= 0; j--) field[i + x][j + y] = t1field[i][j];
  }
  
  if (possible) figfield = tfield;
  Field->Repaint();
}

void __fastcall TForm1::stolk() {
  for (int i = 3; i >= 0; i--) {
    for (int j = 3; j >= 0; j--) {
      if (field[x + i][y + j] == 1) {
        field[x + i][y + j] = 2;
      }
    }
  }
}

void __fastcall TForm1::MoveLeft() {
  if (youlost) return;
  if (x - 1 < 0) return;
  bool possible = 1;
  vector<vector<int>> tfield(4, vector<int>(4));
  for (int i = 3; i >= 0; i--)
    for (int j = 3; j >= 0; j--) tfield[i][j] = field[i + x][j + y];

  for (int i = 3; i >= 0; i--)
    for (int j = 3; j >= 0; j--)
      if (field[i + x][j + y] == 1) field[i + x][j + y] = 0;

  x--;

  for (int i = 3; i >= 0; i--) {
    for (int j = 3; j >= 0; j--) {
      if (field[i + x][j + y] >= 2 && figfield[i][j]) {
        possible = 0;
        break;
      }
      if (field[i + x][j + y] < 2) field[i + x][j + y] = figfield[i][j];
    }
  }
  if (!possible) {
    x++;
    for (int i = 3; i >= 0; i--)
      for (int j = 3; j >= 0; j--) field[i + x][j + y] = tfield[i][j];
  }
  Field->Repaint();
}

void __fastcall TForm1::MoveRight() {
  if (youlost) return;
  if (x + 1 + 3 - 2 > cs) return;
  bool possible = 1;
  vector<vector<int>> tfield(4, vector<int>(4));
  for (int i = 3; i >= 0; i--)
    for (int j = 3; j >= 0; j--) tfield[i][j] = field[i + x][j + y];

  for (int i = 3; i >= 0; i--)
    for (int j = 3; j >= 0; j--)
      if (field[i + x][j + y] == 1) field[i + x][j + y] = 0;

  x++;
  for (int i = 3; i >= 0; i--) {
    for (int j = 3; j >= 0; j--) {
      if (field[i + x][j + y] >= 2 && figfield[i][j]) {
        possible = 0;
        break;
      }
      if (field[i + x][j + y] < 2) field[i + x][j + y] = figfield[i][j];
    }
  }
  if (!possible) {
    x--;
    for (int i = 3; i >= 0; i--)
      for (int j = 3; j >= 0; j--) field[i + x][j + y] = tfield[i][j];
  }
  Field->Repaint();
}

void __fastcall TForm1::normalize(int raw) {
  for (int i = 1; i < cs + 1; i++) {
    for (int j = raw; j > 0; j--) {
      field[i][j] = field[i][j - 1];
    }
  }
  Field->Repaint();
}

void __fastcall TForm1::ScoreUpdate() { Label2->Caption = IntToStr(score); }

int __fastcall TForm1::isline() {
  int sch = 0;
  bool ch = 0;
  vector<vector<int>> tfield = field;
  for (int i = 1; i < rs; i++) {
    ch = 0;
    for (int j = 1; j < cs + 1; j++) {
      if (field[j][i] != 2 && field[j][i] != 3) ch = 1;
    }
    if (ch == 0) {
      for (int ii = 1; ii < cs + 1; ii++) {
        field[ii][i] = 0;
      }
      normalize(i);
      sch++;
    }
  }
  Field->Repaint();
  switch (sch) {
    case 1: {
      score += 100;
      break;
    }
    case 2: {
      score += 300;
      break;
    }
    case 3: {
      score += 700;
      break;
    }
    case 4: {
      score += 1500;
      break;
    }
  }
  ScoreUpdate();
  return (sch);
}

void __fastcall TForm1::TimeTick() {
  bool possible = 1;
  vector<vector<int>> tfield(4, vector<int>(5));
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 5; j++) {
      tfield[i][j] = field[i + x][j + y];
    }
  }

  for (int i = 3; i >= 0; i--) {
    for (int j = 3; j >= 0; j--) {
      if (field[x + i][y + j] == 1) {
        if (field[x + i][y + j + 1] < 2) {
          tfield[i][j + 1] = 51;
          tfield[i][j] = 0;
        } else {
          possible = 0;
          break;
        }
      }
    }
  }
  ifstolk = 0;
  if (!possible) {
    stolk();
    ifstolk = 1;
  } else {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 5; j++) {
        if (tfield[i][j] == 51)
          field[i + x][j + y] = 1;
        else if (tfield[i][j] == 0)
          field[i + x][j + y] = 0;
      }
    }
    y++;
  }
  isline();
  if (ifstolk) FigureCreate();
  Field->Repaint();
}

void __fastcall TForm1::FormCreate(TObject *Sender) {
  Button6->OnKeyDown = FormKeyDown;
  Button7->OnKeyDown = FormKeyDown;
  OpenDialog1->InitialDir = ExtractFilePath(ParamStr(0));
  SaveDialog1->InitialDir = ExtractFilePath(ParamStr(0));
  bl->LoadFromFile("bl.0.bmp");
  bla->LoadFromFile("bl2.0.bmp");
  for (int i = 0; i < field.size(); i++) field[i][rs] = 2;
  for (int i = 0; i < rs; i++) field[0][i] = 3;
  for (int i = 0; i < rs; i++) field[cs + 1][i] = 3;
  randomize();
  FigureCreate();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FieldDrawCell(TObject *Sender, int ACol, int ARow,
                                      TRect &Rect, TGridDrawState State) {
  if (field[ACol][ARow] == 3)
    Field->Canvas->StretchDraw(Rect, bla);
  else if (field[ACol][ARow])
    Field->Canvas->StretchDraw(Rect, bl);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ExtraFieldDrawCell(TObject *Sender, int ACol, int ARow,
                                         TRect &Rect, TGridDrawState State) {
  if (exfield[ACol][ARow]) ExtraField->Canvas->StretchDraw(Rect, bl);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N2Click(TObject *Sender) {
  youlost = 0;
  score = 0;
  KeyPreview = 0;
  ScoreUpdate();
  ShowAll();
  Timer1->Interval = cur_interval;
  Timer1->Enabled = 0;
  x = 0, y = 0;
  for (int i = 0; i < field.size(); i++) {
    for (int j = 0; j < field[i].size(); j++) {
      field[i][j] = 0;
    }
  }

  for (int i = 0; i < cs; i++) field[i][rs] = 2;
  for (int i = 0; i < rs; i++) field[0][i] = 3;
  for (int i = 0; i < rs; i++) field[cs + 1][i] = 3;
  Field->Repaint();
  randomize();
  FigureCreate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender) { TimeTick(); }
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
                                    TShiftState Shift)

{
  if (KeyPreview) {
    switch (Key) {
      case VK_DOWN: {
        while (!ifstolk) TimeTick();
        break;
      }
      case VK_LEFT: {
        MoveLeft();
        break;
      }
      case VK_RIGHT: {
        MoveRight();
        break;
      }
      case VK_UP: {
        FigureRotate();
        break;
      }
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender) {
  Timer1->Enabled = 1;
  Button6->Visible = 0;
  KeyPreview = 1;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N4Click(TObject *Sender) {
  Timer1->Interval = 650;
  cur_interval = 650;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N5Click(TObject *Sender) {
  Timer1->Interval = 400;
  cur_interval = 400;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N6Click(TObject *Sender) {
  Timer1->Interval = 200;
  cur_interval = 200;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button7Click(TObject *Sender) {
  ShowAll();
  Button6->Visible = 0;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

void __fastcall TForm1::ChangeSkinTo(int sk) {
  skin = sk;
  String S1 = "bl.";
  String S2 = "bl2.";
  S1 += IntToStr(skin);
  S2 += IntToStr(skin);
  S1 += ".bmp";
  S2 += ".bmp";
  bl->LoadFromFile(S1);
  bla->LoadFromFile(S2);
  Field->Repaint();
  ExtraField->Repaint();
}

void __fastcall TForm1::N8Click(TObject *Sender) { ChangeSkinTo(0); }
//---------------------------------------------------------------------------

void __fastcall TForm1::N9Click(TObject *Sender) { ChangeSkinTo(1); }
//---------------------------------------------------------------------------
