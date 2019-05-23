object FormFormaPagamento: TFormFormaPagamento
  Left = 298
  Top = 169
  HorzScrollBar.Visible = False
  BorderIcons = []
  BorderStyle = bsDialog
  Caption = 'TEF Discado Forma De Pagamento'
  ClientHeight = 183
  ClientWidth = 276
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
  object LabelFormaPagamento1: TLabel
    Left = 16
    Top = 16
    Width = 242
    Height = 19
    Caption = 'Escolha a Forma de Pagamento'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabelFormaPagamento2: TLabel
    Left = 29
    Top = 36
    Width = 214
    Height = 19
    Caption = 'para o Restante da Compra:'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabelFormaPagamento3: TLabel
    Left = 77
    Top = 100
    Width = 127
    Height = 19
    Caption = 'Digite o Valor R$'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentFont = False
    Visible = False
  end
  object LabelFormaPagamento4: TLabel
    Left = 28
    Top = 120
    Width = 223
    Height = 19
    Caption = 'para o Cart'#227'o Cr'#233'dito/D'#233'bito:'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentFont = False
    Visible = False
  end
  object ComboBoxFormaPagamento: TComboBox
    Left = 32
    Top = 64
    Width = 209
    Height = 27
    Style = csDropDownList
    DropDownCount = 5
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ItemHeight = 19
    ParentFont = False
    TabOrder = 0
    OnKeyDown = ComboBoxFormaPagamentoKeyDown
    Items.Strings = (
      'Dinheiro'
      'Cheque'
      'Cartao Debito'
      'Cartao Credito'
      'Cheque Eletronico')
  end
  object EditValorFormaPagamento: TEdit
    Left = 77
    Top = 144
    Width = 121
    Height = 27
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 1
    Visible = False
    OnKeyPress = EditValorFormaPagamentoKeyPress
  end
end
