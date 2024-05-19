//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.Imaging.jpeg.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *MainMenu1;
	TSaveDialog *SaveDialog1;
	TOpenDialog *OpenDialog1;
	TImage *Image1;
	TDrawGrid *Field;
	TDrawGrid *ExtraField;
	TMenuItem *N1;
	TMenuItem *N2;
	TButton *Button6;
	TTimer *Timer1;
	TMenuItem *N3;
	TMenuItem *N4;
	TMenuItem *N5;
	TMenuItem *N6;
	TButton *Button7;
	TLabel *Label1;
	TLabel *Label2;
	TMenuItem *N7;
	TMenuItem *N8;
	TMenuItem *N9;
	void __fastcall randomize();
	void __fastcall HideAll();
	void __fastcall ScoreUpdate();
	void __fastcall ShowAll();
	void __fastcall ChangeSkinTo(int sk);
	void __fastcall FigureCreate();
	void __fastcall TimeTick();
	void __fastcall stolk();
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FigureRotate();
	void __fastcall MoveLeft();
	void __fastcall MoveRight();
	int __fastcall isline();
	void __fastcall normalize(int raw);
	void __fastcall FieldDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State);
	void __fastcall ExtraFieldDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall N5Click(TObject *Sender);
	void __fastcall N6Click(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall N8Click(TObject *Sender);
	void __fastcall N9Click(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
