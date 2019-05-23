object FormOrdemDeServico: TFormOrdemDeServico
  Left = 112
  Top = 153
  Width = 808
  Height = 580
  HorzScrollBar.Visible = False
  VertScrollBar.Visible = False
  Caption = 'Ordem De Serviço'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenuCadastroOrdemServico
  OldCreateOrder = False
  Position = poDefaultPosOnly
  WindowState = wsMaximized
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBoxConsertoCadastro: TGroupBox
    Left = -1
    Top = 0
    Width = 798
    Height = 553
    Caption = 'Cadastro de Ordem De Serviço'
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlack
    Font.Height = -32
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
    object LabelConsertoDefeito: TLabel
      Left = 9
      Top = 106
      Width = 65
      Height = 22
      Caption = '&Defeito'
      FocusControl = MemoDefeito
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -19
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object LabelConsertoCadastroCliente: TLabel
      Left = 299
      Top = 48
      Width = 153
      Height = 22
      Caption = '&Nome Do Cliente'
      FocusControl = ComboBoxCliente
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -19
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object LabelConsertoVendedor: TLabel
      Left = 9
      Top = 48
      Width = 91
      Height = 22
      Hint = 'RG do Vendedor'
      Caption = '&Vendedor'
      FocusControl = ComboBoxVendedor
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -19
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label13: TLabel
      Left = 9
      Top = 248
      Width = 177
      Height = 24
      AutoSize = False
      Caption = '&Produto'
      FocusControl = ComboBoxCodigoProduto
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -19
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object LabelNumeroSerie: TLabel
      Left = 244
      Top = 248
      Width = 126
      Height = 22
      Caption = 'N&umero Série'
      FocusControl = EditNumeroSerie
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -19
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object LabelPreco: TLabel
      Left = 399
      Top = 248
      Width = 84
      Height = 22
      Caption = 'P&reço R$'
      FocusControl = EditPreco
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -19
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object LabelTotal: TLabel
      Left = 614
      Top = 496
      Width = 76
      Height = 22
      Caption = 'Total R$'
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -19
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object MemoDefeito: TMemo
      Left = 9
      Top = 128
      Width = 778
      Height = 117
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -19
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 2
      OnKeyPress = MemoDefeitoKeyPress
    end
    object ComboBoxCliente: TComboBox
      Left = 299
      Top = 70
      Width = 405
      Height = 30
      DropDownCount = 5
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -19
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ItemHeight = 22
      ParentFont = False
      TabOrder = 1
      OnKeyDown = ComboBoxClienteKeyDown
    end
    object ComboBoxVendedor: TComboBox
      Left = 9
      Top = 70
      Width = 225
      Height = 30
      Style = csDropDownList
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -19
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ItemHeight = 22
      ParentFont = False
      Sorted = True
      TabOrder = 0
      OnKeyDown = ComboBoxVendedorKeyDown
    end
    object ComboBoxCodigoProduto: TComboBox
      Left = 9
      Top = 270
      Width = 227
      Height = 30
      DropDownCount = 10
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -19
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ItemHeight = 22
      ParentFont = False
      TabOrder = 3
      OnKeyDown = ComboBoxCodigoProdutoKeyDown
    end
    object EditNumeroSerie: TEdit
      Left = 244
      Top = 270
      Width = 140
      Height = 30
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -19
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 4
      OnKeyPress = EditNumeroSerieKeyPress
    end
    object EditPreco: TEdit
      Left = 398
      Top = 270
      Width = 90
      Height = 30
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -19
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 5
      OnKeyPress = EditPrecoKeyPress
    end
    object BitBtnConfirmarProduto: TBitBtn
      Left = 502
      Top = 252
      Width = 217
      Height = 49
      Caption = '&Confirmar Produto'
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -19
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 6
      OnClick = BitBtnConfirmarProdutoClick
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        04000000000000010000130B0000130B00001000000000000000000000000000
        800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
        33333333FF33333333FF333993333333300033377F3333333777333993333333
        300033F77FFF3333377739999993333333333777777F3333333F399999933333
        33003777777333333377333993333333330033377F3333333377333993333333
        3333333773333333333F333333333333330033333333F33333773333333C3333
        330033333337FF3333773333333CC333333333FFFFF77FFF3FF33CCCCCCCCCC3
        993337777777777F77F33CCCCCCCCCC3993337777777777377333333333CC333
        333333333337733333FF3333333C333330003333333733333777333333333333
        3000333333333333377733333333333333333333333333333333}
      NumGlyphs = 2
    end
    object StringGridConserto: TStringGrid
      Left = 9
      Top = 307
      Width = 780
      Height = 178
      FixedCols = 0
      RowCount = 2
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -19
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goDrawFocusSelected]
      ParentFont = False
      TabOrder = 7
      OnKeyDown = StringGridConsertoKeyDown
      ColWidths = (
        64
        64
        64
        64
        64)
    end
    object BitBtnImprimirOrcamento: TBitBtn
      Left = 22
      Top = 496
      Width = 267
      Height = 30
      Caption = '&Imprimir Orçamento'
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -19
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 8
      OnClick = BitBtnImprimirOrcamentoClick
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        04000000000000010000120B0000120B00001000000000000000000000000000
        800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00300000000000
        0003377777777777777308888888888888807F33333333333337088888888888
        88807FFFFFFFFFFFFFF7000000000000000077777777777777770F8F8F8F8F8F
        8F807F333333333333F708F8F8F8F8F8F9F07F333333333337370F8F8F8F8F8F
        8F807FFFFFFFFFFFFFF7000000000000000077777777777777773330FFFFFFFF
        03333337F3FFFF3F7F333330F0000F0F03333337F77773737F333330FFFFFFFF
        03333337F3FF3FFF7F333330F00F000003333337F773777773333330FFFF0FF0
        33333337F3F37F3733333330F08F0F0333333337F7337F7333333330FFFF0033
        33333337FFFF7733333333300000033333333337777773333333}
      NumGlyphs = 2
    end
    object BitBtnVoltar: TBitBtn
      Left = 310
      Top = 496
      Width = 267
      Height = 30
      Caption = 'Voltar'
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -19
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 9
      OnClick = BitBtnVoltarClick
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        04000000000000010000130B0000130B00001000000000000000000000000000
        800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
        3333333333FFFFF3333333333999993333333333F77777FFF333333999999999
        3333333777333777FF3333993333339993333377FF3333377FF3399993333339
        993337777FF3333377F3393999333333993337F777FF333337FF993399933333
        399377F3777FF333377F993339993333399377F33777FF33377F993333999333
        399377F333777FF3377F993333399933399377F3333777FF377F993333339993
        399377FF3333777FF7733993333339993933373FF3333777F7F3399933333399
        99333773FF3333777733339993333339933333773FFFFFF77333333999999999
        3333333777333777333333333999993333333333377777333333}
      NumGlyphs = 2
    end
  end
  object EditTotal: TEdit
    Left = 693
    Top = 490
    Width = 95
    Height = 30
    TabStop = False
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlack
    Font.Height = -19
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentFont = False
    ReadOnly = True
    TabOrder = 1
    OnKeyPress = EditPrecoKeyPress
  end
  object MainMenuCadastroOrdemServico: TMainMenu
    Left = 631
    Top = 24
    object MenuItemAtalhos: TMenuItem
      Caption = '&Atalhos'
      object MenuItemImprimirRelatorio: TMenuItem
        Caption = '&Imprimir Orçamento'
        ShortCut = 16457
        OnClick = BitBtnImprimirOrcamentoClick
      end
      object MenuItemConfirmarProduto: TMenuItem
        Caption = '&Confirmar Produto'
        OnClick = BitBtnConfirmarProdutoClick
      end
    end
    object MenuItemSair: TMenuItem
      Caption = '&Sair'
      ShortCut = 27
      OnClick = BitBtnVoltarClick
    end
  end
end
