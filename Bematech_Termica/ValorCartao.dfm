object FormValorCartao: TFormValorCartao
  Left = 227
  Top = 220
  Width = 444
  Height = 110
  HorzScrollBar.Visible = False
  VertScrollBar.Visible = False
  Caption = 'Vendas'
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = 'Arial'
  Font.Style = [fsBold]
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 19
  object LabelValorCartao: TLabel
    Left = 24
    Top = 16
    Width = 387
    Height = 19
    Caption = 'Digite o Valor (R$) para o Cart'#227'o de Cr'#233'dito/D'#233'bito:'
  end
  object EditValorCartao: TEdit
    Left = 166
    Top = 40
    Width = 107
    Height = 27
    AutoSize = False
    BiDiMode = bdRightToLeft
    ParentBiDiMode = False
    TabOrder = 0
    OnKeyPress = EditValorCartaoKeyPress
  end
end
