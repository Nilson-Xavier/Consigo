object FormPassword: TFormPassword
  Left = 240
  Top = 251
  Width = 283
  Height = 106
  HorzScrollBar.Visible = False
  VertScrollBar.Visible = False
  BorderIcons = []
  Caption = 'Administração - Senha de Acesso'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object LabelSenhaDeAcesso: TLabel
    Left = 36
    Top = 16
    Width = 200
    Height = 19
    Caption = 'Digite a Senha de Acesso:'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object EditSenhaDeAcesso: TEdit
    Left = 76
    Top = 40
    Width = 121
    Height = 27
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentFont = False
    PasswordChar = '*'
    TabOrder = 0
    OnKeyDown = EditSenhaDeAcessoKeyDown
  end
end
