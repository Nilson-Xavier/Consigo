object FormDescontoProduto: TFormDescontoProduto
  Left = 252
  Top = 168
  HorzScrollBar.Visible = False
  VertScrollBar.Visible = False
  AutoScroll = False
  BorderIcons = []
  BorderWidth = 1
  Caption = 'Vendas'
  ClientHeight = 103
  ClientWidth = 346
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
  object PanelDescontoProduto: TPanel
    Left = -3
    Top = -1
    Width = 498
    Height = 200
    TabOrder = 0
    object LabelDescontoPreco: TLabel
      Left = 11
      Top = 8
      Width = 330
      Height = 19
      Caption = 'Digite o Valor do Desconto/Acr�scimo (R$):'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ParentFont = False
      Layout = tlCenter
    end
    object EditDescontoProduto: TEdit
      Left = 11
      Top = 38
      Width = 322
      Height = 27
      AutoSize = False
      BiDiMode = bdLeftToRight
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      MaxLength = 7
      ParentBiDiMode = False
      ParentFont = False
      TabOrder = 0
      OnKeyDown = EditDescontoProdutoKeyDown
      OnKeyPress = EditDescontoProdutoKeyPress
    end
    object RadioButtonDesconto: TRadioButton
      Left = 13
      Top = 69
      Width = 113
      Height = 17
      Caption = '&Desconto'
      Checked = True
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
      TabStop = True
      OnKeyDown = RadioButtonDescontoKeyDown
    end
    object RadioButtonAcrescimo: TRadioButton
      Left = 129
      Top = 69
      Width = 113
      Height = 17
      Caption = '&Acrescimo'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 2
      OnKeyDown = RadioButtonAcrescimoKeyDown
    end
  end
end
